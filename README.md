# graphics-learning
My OpenGL learning roadmap. Not using CMake, but mantaining a Makefile and a Visual Studio solution.

# Build Instructions
I use [vcpkg](https://vcpkg.io/en/) to manage dependencies, so clone this repo with `git clone --recurse-submodules` in order to use it.

Use the [scripts](./scripts) to configure vcpkg, or directly follow the [instructions](https://vcpkg.io/en/getting-started).
Then just open the solution in Visual Studio if you are on Windows or run `make` if you're on Linux (not tested in other POSIX OS).
