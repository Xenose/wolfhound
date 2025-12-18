# The Wolfhound Game Engine [ C23 ]
*This code is IN the Rapid DEVelopment branch or 'INRDEV' for short, meaning that the code will change a lot and that after first release the commit history will be squashed.*

| Platform     | Tested | Supported | Description                             |
| ------------ | ------ | --------- | --------------------------------------- |
| Arch Linux   | YES    | YES       | Primary development platform.           |
| Fedora Linux | YES    | YES       | Secondary development platform.         |
| Debian Linux | NO     | Not yet   | Planned.                                |
| Windows      | NO     | Not yet   | Unstable might break at any second      |
| MacOS        | NO     | No        | No Plans.                               |

## Core Concepts
### Action Entity System
The Action Entity System is based on DoD model while still some similarity to
ECS, instead of logic being tided to a entity AES makes data subscribe to action
so the logic calls the data.

In a ECS system :: Entity -> \[ Data, Logic \]
In AES system :: action(logic) -> Entity -> Data

## Building instructions
See full [Manual Build Guide](docs/markdown/build.md) for details.

### Linux [ POSIX SHELL, BASH, ZSH ]
```sh
. ./tools/cmake/activate.sh
```

### Windows [ CMD ]
```cmd
call tools\cmake\activate.bat
```

### Windows [ Powershell Experimental ]
```ps1
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
. .\tools\shell\activate.ps1
```

### Build
```sh
wh-ninja	# set build system.
wh-clang	# set compiler.
wh-build	# compiles code.
```

### Commands

| Command     | Platform                        | Description                                                               |
| ----------- | ------------------------------- | ------------------------------------------------------------------------- |
| wh-check    | Linux                           | Checks for missing software and libraries.                                |
| wh-build    | Linux, Windows(PowerShell, CMD) | Compiles the code.                                                        |
| wh-clang    | Linux, Windows(CMD)             | Sets the compiler to Clang.                                               |
| wh-coverage | Linux                           | Generates a coverage report and opens it.                                 |
| wh-gcc      | Linux                           | Sets the compiler to gcc                                                  |
| wh-msvc     | Windows(CMD)                    | Sets the compiler to MSVC                                                 |
| wh-mingw    | Linux                           | Sets the compiler to gcc-mingw.                                           |
| wh-ninja    | Linux, Windows(CMD)             | Sets the build system to Ninja.                                           |
| wh-make     | Linux, Windows(CMD)             | Sets the build system to Make, NMake for windows and UNIX for the others. |

## Languages
| Name        | Version | Use                                              |
| ----------- | ------- | ------------------------------------------------ |
| C           | 23      | Engine core.                                     |
| Fortran     | 95      | Optional maths functions.                        |
| C++         | 23      | C++ wrapper for the C code and gtesting.         |
| Lua         | N/A     | Configuration, Command Line, data.               |
| Shell       | N/A     | Tools.                                           |
| Python      | 3       | Tools.                                           |
| DOS Batch   | N/A     | Build tools.                                     |
| Dockerfiles | N/A     | Temporary testing enviroments.                   |

## Compilers
| Name  | Version | Notes                                         |
| ----- | ------- | --------------------------------------------- |
| clang | 21      |                                               |
| gcc   | 15      |                                               |
| msvc  | 2020    | Compiles for now, but could break any second. |

## Libraries

| Name    | Current Supported | Required       | Notes                                                                     |
| ------- | ----------------- | -------------- | ------------------------------------------------------------------------- |
| vulkan  | NO                | NO             | At least one graphics library is required, vulkan needs sdl3 also.        |
| sdl3    | NO                | NO             | At least one graphics library is required,                                |
| glfw    | NO                | NO             | At least one graphics library is required,                                |
| lua     |                   | YES            | Used for data, arguments and configurations.                              |
| unwind  |                   | NO(but useful) | Used to backtrace Segfaults from the signal handler.                      |
| gtest   |                   | NO             | Used for unit testing of the engine.                                      |

## Editors / IDE
| Name                | Status    | Platform       | Description                                                        |
| ------------------- | --------- | -------------- | ------------------------------------------------------------------ |
| NeoVim              | Working   | Linux, Windows | Main editor for the project.                                       |
| Visual Studio Code  | Working   | Linux, Windows |                                                                    |
| Visual Studio       | Broken    | Windows        | Will not compile with MSVC(no C23) and headers are not showing up. |

## Stats
<!--python-stats-start-->

|  Language       | File Count | Lines of Code | Percentage |
| --------------- | ---------- | ------------- | ---------- |
| C               | 150        | 6200          | 76.27%     |
| C++             | 17         | 455           | 5.60%      |
| Bourne Shell    | 20         | 405           | 4.98%      |
| CMake           | 20         | 405           | 4.98%      |
| Lua             | 13         | 175           | 2.15%      |
| Markdown        | 3          | 160           | 1.97%      |
| Python          | 2          | 155           | 1.91%      |
| Dockerfile      | 4          | 82            | 1.01%      |
| DOS Batch       | 6          | 36            | 0.44%      |
| Fortran 95      | 1          | 32            | 0.39%      |
| Assembly        | 2          | 11            | 0.14%      |
| PowerShell      | 3          | 10            | 0.12%      |
| INI             | 1          | 3             | 0.04%      |
| Summary         | 242        | 8129          | 100.00%    |

<!--python-stats-end-->
