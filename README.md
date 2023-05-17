### GUIDE USED PI-PICO

#### INSTALLATION DEPENDENCIES DEV PI-PICO
1. [Install brew](https://brew.sh/)
``` bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
2. [Download and install the latest version of the Pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk)
For example, on macOS, you can use Homebrew to install the SDK:
``` bash
    brew install cmake
    brew tap ArmMbed/homebrew-formulae
    brew install armmbed/formulae/arm-none-eabi-gcc
    brew install arm-none-eabi-newlib
    git clone https://github.com/raspberrypi/pico-sdk

    # Set an environment variable PICO_SDK_PATH to point to the SDK
    nano ~/.bash_profile
    export PICO_SDK_PATH=/path/to/pico-sdk
    source ~/.bash_profile

    # copy pico import.cmake to pico-sdk
    cp /my-project/pico_sdk_import.cmake $PICO_SDK_PATH/external/pico_sdk_import.cmake

    # create build directory
    mkdir build

    # create CMakeLists.txt
    touch CMakeLists.txt
```

3. Write config of CMakeLists.txt, for example:

``` txt

cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
set(PICO_SDK_PATH "/Volumes/Data/pi-pico/pico-sdk")
include(pico_sdk_import.cmake)
pico_sdk_init()

# Set the path to the Pico SDK

project(p_control C CXX ASM)

add_executable(hello_world
    hello_world.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello_world pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello_world)

```
4. On vscode, install extension C/C++ and CMake Tools. So, you can build and debug your project.
With CMake Tools, you can build and debug your project select CMake: GCC x.x.x arm-none-eabi

``` bash
    # build
    cmake --build build --target hello_world -- -j 4

    # debug
    cmake --build build --target hello_world -- -j 4
```