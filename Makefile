MAKEFLAGS := --jobs=2

CXX := g++
LD := g++

TARGET_EXEC :=	main
SRC_DIR :=		./src
INCLUDE_DIR :=	./src/include
BUILD_DIR :=	./build
VCPKG_DIR :=	./vcpkg_installed/x64-linux

WFLAGS := -Wall -Wextra -Wpedantic -Wdeprecated -Wundef -Wunused \
		  -Wunreachable-code -Winvalid-pch -Wctor-dtor-privacy \
		  -Wshadow -Wmissing-include-dirs -Wredundant-decls \
		  -Winit-self -Wswitch-default -Wswitch-enum -Wformat=2 \
		  -Wdouble-promotion -Wfloat-equal -Wpointer-arith \
		  -Wcast-qual -Wcast-align -Wconversion \
		  -Werror=return-local-addr -Werror=return-type

CXXFLAGS := -std=c++20 -flto ${WFLAGS} \
			-I ${INCLUDE_DIR} \
			-isystem ${VCPKG_DIR}/include

X11FLAGS := $(shell pkg-config x11 --cflags --libs)
LDFLAGS := -flto \
		   -L ${VCPKG_DIR}/lib -lfmt -lglad -lglfw3 \
		   ${X11FLAGS}


# Operations
SRCS := $(shell find ${SRC_DIR} -type f -name "*.cpp")
OBJS := $(patsubst %.cpp,${BUILD_DIR}/%.o,${SRCS})
HDRS := $(shell find ${SRC_DIR} -type f -name "*.h")


all: ${TARGET_EXEC}

${TARGET_EXEC}: ${OBJS}
	${LD} $^ ${LDFLAGS} -o $@

${BUILD_DIR}/%.o: %.cpp
	@ mkdir -p $(@D)
	${CXX} ${CXXFLAGS} $^ -c -o $@


.PHONY: run
run: ${TARGET_EXEC}
	@ ./${TARGET_EXEC}

.PHONY: test
test:
	@echo ${SRCS}
	@echo ${OBJS}
	@echo ${HDRS}
	@echo ${X11FLAGS}

.PHONY: clean
clean:
	rm -rf ${TARGET_EXEC} ${BUILD_DIR}

compile_flags.txt: Makefile
	@echo ${CXXFLAGS} | tr ' ' '\n' > $@
