# The Wolfhound Game Engine [ C23 ]
*This code is IN the Rapid DEVelopment branch or 'INRDEV' for short, meaning that the code will change a lot and that after first release the commit history will be squashed.*

| Platform        | Kernel  | Tested | Supported     | Description                             |
| --------------- | ------- | ------ | ------------- | --------------------------------------- |
| Arch Linux      | Linux   | YES    | UNSTABLE      | Primary development platform.           |
| Fedora Linux    | Linux   | YES    | UNSTABLE      | Secondary development platform.         |
| Debian Linux    | Linux   | NO     | PLANNED       | Planned.                                |
| Windows         | NT      | YES    | UNSTABLE      | Unstable might break at any second.     |
| Android(Termux) | Android | YES    | UNSTABLE      |                                         |
| FreeBSD         | BSD     | YES    | UNSTABLE      |                                         |
| OpenIndiana     | Solaris | YES    | PLANNED       |                                         |
| Haiku           | Haiku   | NO     | PLANNED       |                                         |
| Aros            | Amiga   | NO     | PLANNED       |                                         |
| MacOS           | Darwin  | NO     | EXPERIMENTING | No Plans for full support.              |

## Compilers

| Name   | Tier | Issues                                                       | Notes                                     |
| ------ | ---- | ------------------------------------------------------------ | ----------------------------------------- |
| Clang  | 0x01 | None                                                         | Main compiler.                            |
| GCC    | 0x01 | WH_EPF(breaks)                                               | Main compiler outside Windows.            |
| ICX    | 0x02 |                                                              | Testing as a 3rd tier 0x01 compiler       |
| Zig    | 0x02 | Unknown                                                      | Testing vability.                         |
| TCC    | 0x03 | No thread local, No 128 bit integers.                        |                                           |
| MSVC   | 0x03 | No 128 bit integers.                                         | C++ compiler masking as a C compiler...   |
| MinGW  | 0x03 | A pain to setup.                                             |                                           |

**Tiers**
* Tier 0x01 :: Main compilers and used for release builds.
* Tier 0x02 :: Should work and could be used for release.
* Tier 0x03 :: Validating C correctness and shouldn't be used for release builds.

**Note by using the include/wh-common/c23-comp.h header it maybe possible to use a c11/c17 compiler also**

## Core Concepts
### Action Entity System
The Action Entity System is based on DoD model while still some similarity to
ECS, instead of logic being tided to a entity AES makes data subscribe to action
so the logic calls the data.

In a ECS system :: Entity -> \[ Data, Logic \]
In AES system :: action(logic) -> Entity -> Data

## Building instructions
See full [Manual Build Guide](docs/markdown/build.md) for details.

### Linux [ POSIX SHELL, BASH, ZSH, ASH, DASH ]
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

| Command      | Platform                                                   | Description                                                               |
| ------------ | ---------------------------------------------------------- | ------------------------------------------------------------------------- |
| wh-check     | Linux                                                      | Checks for missing software and libraries.                                |
| wh-build     | Linux, BSD, Android, OpenIndiana, Windows(PowerShell, CMD) | Compiles the code.                                                        |
| wh-build-all | Linux                                                      | Builds the CMake using all compilers that are installed/supported.        |
| wh-clang     | Linux, Windows(CMD)                                        | Sets the compiler to Clang.                                               |
| wh-coverage  | Linux                                                      | Generates a coverage report and opens it.                                 |
| wh-gcc       | Linux                                                      | Sets the compiler to gcc                                                  |
| wh-tcc       | Linux                                                      | Sets the compiler to TinyCC                                               |
| wh-msvc      | Windows(CMD)                                               | Sets the compiler to MSVC                                                 |
| wh-mingw     | Linux                                                      | Sets the compiler to gcc-mingw.                                           |
| wh-ninja     | Linux, Windows(CMD)                                        | Sets the build system to Ninja.                                           |
| wh-make      | Linux, Windows(CMD/nmake)                                  | Sets the build system to Make, NMake for windows and UNIX for the others. |

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
| C               | 189        | 7004          | 76.45%     |
| CMake           | 28         | 499           | 5.45%      |
| Bourne Shell    | 23         | 496           | 5.41%      |
| C++             | 17         | 457           | 4.99%      |
| Markdown        | 3          | 186           | 2.03%      |
| Lua             | 13         | 175           | 1.91%      |
| Python          | 3          | 157           | 1.71%      |
| Dockerfile      | 4          | 82            | 0.90%      |
| DOS Batch       | 6          | 36            | 0.39%      |
| Fortran 95      | 1          | 32            | 0.35%      |
| GLSL            | 1          | 13            | 0.14%      |
| Assembly        | 2          | 11            | 0.12%      |
| PowerShell      | 3          | 10            | 0.11%      |
| INI             | 1          | 3             | 0.03%      |
| Summary         | 294        | 9161          | 100.00%    |

<!--python-stats-end-->

## Hardware Tested on

| OS         | CPU         | RAM  | GPU           | Notes                  |
| ---------- | ----------- | ---- | ------------- | ---------------------- |
| Arch Linux | Ryzen 3900x | 64GB | RX6800xt      |                        |
| FreeBSD    | I5 6300u    | 32GB | NaN           |                        |
| Android    | T616        | 8GB  | NaN           | Compiled using Termux. |
| Windows 11 | Ryzen 2200g | 16GB | Redaon WX6100 |                        |

