# The Wolfhound Game Engine [ C23 ]
*This code is IN the Rapid DEVelopment branch or 'INRDEV' for short, meaning that the code will change a lot and that after first release the commit history will be squashed.*

| Platform     | Tested | Supported | Description                             |
| ------------ | ------ | --------- | --------------------------------------- |
| Arch Linux   | YES    | YES       | Primary development platform.           |
| Debian Linux | NO     | Not yet   | Planned.                                |
| Windows      | NO     | Not yet   | Planned.                                |
| MacOS        | NO     | No        | No Plans.                               |

## Building instructions
See full [Manual Build Guide](docs/markdown/build.md) for details.

### Linux [ POSIX SHELL, BASH, ZSH ]
```bash
. ./tools/cmake/activate.sh
```

### Windows [ CMD ]
```cmd
call tools\cmake\activate.bat
```
### Build
```sh
wh-ninja	# set build system.
wh-clang	# set compiler.
wh-build	# compiles code.
```

### Commands

| Command  | Platform       | Description                     |
| -------- | -------------- | ------------------------------- |
| wh-build | Linux, Windows | Compiles the code.              |
| wh-clang | Linux, Windows | Sets the compiler to Clang.     |
| wh-gcc   | Linux          | Sets the compiler to gcc        |
| wh-mingw | Linux          | Sets the compiler to gcc-mingw. |
| wh-ninja | Linux, Windows | Sets the build system to Ninja. |
| wh-make  | Linux          | Sets the build system to Make.  |

## Languages
| Name      | Version | Use                                |
| --------- | ------- | ---------------------------------- |
| C         | 23      | Engine core.                       |
| Fortran   | 95      | Optional maths functions.          |
| C++       | 23      | C++ wrapper for the C code         |
| Lua       |         | Configuration, Command Line, data. |
| Shell     |         | Tools.                             |
| Python    | 3       | Tools.                             |
| DOS Batch |         | Build tools.                       |

## Libraries

| Name    | Current Supported | Required       | Notes                                                                     |
| ------- | ----------------- | -------------- | ------------------------------------------------------------------------- |
| raylib  | YES               | NO             | At least one graphics library is required.                                |
| vulkan  | NO                | NO             | At least one graphics library is required, vulkan needs sdl3 also.        |
| sdl3    | NO                | NO             | At least one graphics library is required,                                |
| lua     |                   | YES            | Used for data, arguments and configurations.                              |
| unwind  |                   | NO(but useful) | Used to backtrace Segfaults from the signal handler.                      |


## Stats
<!--python-stats-start-->

|  Language       | File Count | Lines of Code | Percentage |
| --------------- | ---------- | ------------- | ---------- |
| C               | 73         | 2982          | 76.66%     |
| Markdown        | 56         | 439           | 11.29%     |
| Python          | 2          | 155           | 3.98%      |
| CMake           | 10         | 150           | 3.86%      |
| Bourne Shell    | 10         | 76            | 1.95%      |
| Fortran 95      | 1          | 30            | 0.77%      |
| Lua             | 5          | 26            | 0.67%      |
| C++             | 2          | 15            | 0.39%      |
| DOS Batch       | 3          | 15            | 0.39%      |
| Text            | 1          | 2             | 0.05%      |
| Summary         | 163        | 3890          | 100.00%    |

<!--python-stats-end-->
