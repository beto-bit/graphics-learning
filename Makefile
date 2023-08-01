MAKEFLAGS := --jobs=2

SRC_DIR :=		./src
INCLUDE_DIR :=	./src/include
BUILD_DIR :=	./build
VCPKG_DIR :=	./vcpkg_installed/x64-linux

WFLAGS := -Wall -Wextra -Wpedantic -Wdeprecated -Wundef -Wunused \
		  -Wunreachable-code -Winvalid-pch -Wctor-dtor-privacy \
		  -Wshadow -Wmissing-include-dirs -Wredudant-decls \
		  -Winit-self -Wswitch-default -Wswitch-enum -Wformat=2 \
		  -Wdouble-promotion -Wfloat-equal -Wpointer-arith \
		  -Wcast-qual -Wcast-align -Wconversion \
		  -Werror=return-local-addr -Werror=return-type

CXXFLAGS := -std=c++20 -flto ${WFLAGS} \
			-I ${INCLUDE_DIR} \
			-isystem ${VCPKG_DIR}/include

LDFLAGS := -flto \
		   -L ${VCPKG_DIR}/lib -lfmt -lglad -lglfw3

.PHONY: compile_flags.txt
compile_flags.txt: Makefile
	@echo ${CXXFLAGS} | tr ' ' '\n' > $@
