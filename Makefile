MAKEFLAGS := --jobs=2

CXX := g++
LD := g++

TARGET_EXEC :=	main
SRC_DIR :=		./src
INCLUDE_DIR :=	./src/include
BUILD_DIR :=	./build
VCPKG_DIR :=	./vcpkg_installed/x64-linux


# Flags
WFLAGS := -Wall -Wextra -Wpedantic -Wdeprecated -Wundef -Wunused \
		  -Wunreachable-code -Winvalid-pch -Wctor-dtor-privacy \
		  -Wshadow -Wmissing-include-dirs -Wredundant-decls \
		  -Winit-self -Wswitch-default -Wswitch-enum -Wformat=2 \
		  -Wdouble-promotion -Wfloat-equal -Wpointer-arith \
		  -Wcast-qual -Wcast-align -Wconversion \
		  -Werror=return-local-addr -Werror=return-type

CXXFLAGS := -std=c++20 -flto -MD -MP ${WFLAGS} \
			-I ${INCLUDE_DIR} \
			-isystem ${VCPKG_DIR}/include

X11FLAGS := $(shell pkg-config x11 --cflags --libs)
LDFLAGS := -flto \
		   -L ${VCPKG_DIR}/lib -lfmt -lglad -lglfw3 \
		   ${X11FLAGS}


# Files, headers, objects and dependencies
SRCS := $(shell find ${SRC_DIR} -type f -name "*.cpp")
OBJS := $(patsubst %.cpp,${BUILD_DIR}/%.o,${SRCS})
HDRS := $(shell find ${SRC_DIR} -type f -name "*.h")

DEPS := $(patsubst %.o,%.d,${OBJS})
-include ${DEPS}


# Targets
.DEFAULT_GOAL := all
.PHONY: all
all: ${TARGET_EXEC}

${TARGET_EXEC}: ${OBJS}
	@ echo "Linking..."
	@ ${LD} $^ ${LDFLAGS} -o $@

${BUILD_DIR}/%.o: %.cpp
	@ mkdir -p $(@D)
	@ echo "Compiling $<..."
	@ ${CXX} ${CXXFLAGS} -O2 $< -c -o $@



# Run and clean
.PHONY: run
run: ${TARGET_EXEC}
	@ echo "Starting..."
	@ ./${TARGET_EXEC}

.PHONY: clean
clean:
	rm -rf ${TARGET_EXEC} ${BUILD_DIR}

compile_flags.txt: Makefile
	@echo ${CXXFLAGS} | tr ' ' '\n' > $@
