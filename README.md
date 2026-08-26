# Micromouse 2026

Firmware and native simulation tools for the XuperM Micromouse, built around the STM32F411.

## Repository layout

- `app/` contains hardware test programs, the navigation application, CLI, and native simulator.
- `common/core/` contains maze solving, motion control, navigation, and peripheral abstractions.
- `common/drivers/` contains portable interfaces and STM32F4 implementations.
- `mcu_support/` contains CMSIS, STM32 HAL sources, startup code, and linker scripts.
- `cmake/` contains the cross-compilation toolchain and shared CMake helpers.

## Prerequisites

Install CMake 3.26 or newer, Ninja, and clang-format 17 or newer. Embedded builds also require the Arm GNU toolchain (`arm-none-eabi-gcc`).

## Build

Build all STM32F411 applications:

```sh
./make.sh -t stm32f411
```

Build one application:

```sh
./make.sh -t stm32f411 -a nav_app
```

Use `-r` for a release build and `-c` to remove the selected build directory before configuring. Windows users can run the equivalent `make.ps1` commands.

Build the native simulator and portable libraries:

```sh
./make.sh -t native
```

Run native tests after building:

```sh
ctest --test-dir build/native --output-on-failure
```

## Development checks

```sh
./format_check.sh
cmake --preset native -DCMAKE_BUILD_TYPE=Debug
cmake --build build/native
ctest --test-dir build/native --output-on-failure
```

Hardware calibration work and known limitations are tracked in [`todo.md`](todo.md).
