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

| Command  | Platform       | Description                                |
| -------- | -------------- | ------------------------------------------ |
| wh-check | Linux          | Checks for missing software and libraries. |
| wh-build | Linux, Windows | Compiles the code.                         |
| wh-clang | Linux, Windows | Sets the compiler to Clang.                |
| wh-gcc   | Linux          | Sets the compiler to gcc                   |
| wh-mingw | Linux          | Sets the compiler to gcc-mingw.            |
| wh-ninja | Linux, Windows | Sets the build system to Ninja.            |
| wh-make  | Linux          | Sets the build system to Make.             |

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
| vulkan  | NO                | NO             | At least one graphics library is required, vulkan needs sdl3 also.        |
| sdl3    | NO                | NO             | At least one graphics library is required,                                |
| glfw    | NO                | NO             | At least one graphics library is required,                                |
| lua     |                   | YES            | Used for data, arguments and configurations.                              |
| unwind  |                   | NO(but useful) | Used to backtrace Segfaults from the signal handler.                      |

## Editors / IDE
| Name                | Status    | Platform       | Description                                                        |
| ------------------- | --------- | -------------- | ------------------------------------------------------------------ |
| NeoVim              | Working   | Linux, Windows | Main editor for the project.                                       |
| Visual Studio Code  | Working   | Linux, Windows |                                                                    |
| Visual Studio       | Broken    | Windows        | Will not compile with MSCV(no C23) and headers are not showing up. |

## Stats
<!--python-stats-start-->

|  Language       | File Count | Lines of Code | Percentage |
| --------------- | ---------- | ------------- | ---------- |
| C               | 122        | 4891          | 82.27%     |
| CMake           | 12         | 253           | 4.26%      |
| Bourne Shell    | 15         | 230           | 3.87%      |
| Python          | 2          | 155           | 2.61%      |
| Markdown        | 3          | 135           | 2.27%      |
| C++             | 7          | 121           | 2.04%      |
| Lua             | 9          | 80            | 1.35%      |
| Fortran 95      | 1          | 32            | 0.54%      |
| Dockerfile      | 1          | 25            | 0.42%      |
| DOS Batch       | 4          | 20            | 0.34%      |
| INI             | 1          | 3             | 0.05%      |
| Summary         | 177        | 5945          | 100.00%    |

<!--python-stats-end-->
