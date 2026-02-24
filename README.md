# The Wolfhound Game Engine [ C23 ]
*This code is IN the Rapid DEVelopment branch or 'INRDEV' for short, meaning that the code will change a lot and that after first release the commit history will be squashed.*

| Platform        | Kernel  | Tested | Supported     | Description                             |
| --------------- | ------- | ------ | ------------- | --------------------------------------- |
| Arch Linux      | Linux   | YES    | UNSTABLE      | Primary development platform.           |
| Fedora Linux    | Linux   | YES    | UNSTABLE      | Secondary development platform.         |
| Alpine Linux    | Linux   | YES    | UNSTABLE      | Testing on Musl.                        |
| Debian Linux    | Linux   | NO     | PLANNED       | Planned.                                |
| Windows         | NT      | YES    | BROKEN        | Unstable might break at any second.     |
| Android(Termux) | Android | YES    | UNSTABLE      |                                         |
| FreeBSD         | BSD     | YES    | UNSTABLE      |                                         |
| OpenIndiana     | Solaris | YES    | UNSTABLE      |                                         |
| Haiku           | Haiku   | NO     | PLANNED       |                                         |
| Aros            | Amiga   | NO     | PLANNED       |                                         |
| MacOS           | Darwin  | NO     | EXPERIMENTING | No Plans for full support.              |

**Noted UNSTABLE means it can break and Linux is probably the most stable**

## Compilers

| Name   | Version | Tier | Issues                                                       | Notes                                     |
| ------ | ------- | ---- | ------------------------------------------------------------ | ----------------------------------------- |
| Clang  |         | 0x01 | None                                                         | Main compiler.                            |
| GCC    |         | 0x01 | WH_EPF(breaks)                                               | Main compiler outside Windows.            |
| ICX    |         | 0x02 |                                                              | Testing as a 3rd tier 0x01 compiler       |
| Zig    |         | 0x02 | Unknown                                                      | Testing viability.                        |
| TCC    |         | 0x03 | No thread local, No 128 bit integers.                        |                                           |
| MSVC   |         | 0x03 | No 128 bit integers.                                         | C++ compiler masking as a C compiler...   |
| MinGW  |         | 0x03 | A pain to setup.                                             |                                           |

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

### Systems planned
| Name                               | Status        | File                    | Notes                                                                        |
| ---------------------------------- | ------------- | ----------------------- | ---------------------------------------------------------------------------  |
| AES                                | Experimenting | N/A                     | DoD style entity system.                                                     |
| print system                       | Finalizing    | Print.h                 | Print functionality with possbility for C++ hooks.                           |
| Grabage collector                  | Finalizing    | Tracker.h               | Needs to move from linked list to hashmap.                                   |
| Fixed point CPU math               | Theory        | N/A                     | Using fixed point math for positions on the CPU and floats on the GPU.       |
| SDF Mesh hybrid rendering          | Theory        | N/A                     | To save model size and allow faster transfer should look into SDF rendering. |
| Lua command line and config parser | Needs cleanup | arg_parser.h / config.h | A bit rough and could need improvment.                                       |
| Generic render backend interface   | Indev         | render.h                | Allow use of sdl, glfw, vulkan, gl and etc instead of hardcoding backends.   |

## Building instructions
**Need to be in the project root dir**
```sh
# Activates the python build shell.
python3 tools/shell/python/main.py
```

### Commands ( NOT POSIX : Experimental )
**Fore more info do --help**
| Name        | Notes                                                                                   |
| ----------- | --------------------------------------------------------------------------------------- |
| build       | Create the build folder and compiles the software, uses cmake underneth.                |
| cd          | Change the current directory.                                                           |
| clang       | Set the shell state compiler to Clang.                                                  |
| clear       | Clears the shell screen.                                                                |
| dump-state  | Dumps the current state of the shell.                                                   |
| exit        | Exits the shell.                                                                        |
| gcc         | Set the shell state compiler to GGC.                                                    |
| ls          | List a directories content.                                                             |
| push_inrdev | On the inrdev branch allows automated pushing of code.                                  |
| pwd         | Get the current working path.                                                           |
| stats       | Uses Cloc to dump project status, might not work on Windows.                            |
| tcc         | Set the shell state compiler to TCC.                                                    |


[legacy_build.md](Legacy Build System)

### Manual build
```sh
cmake \
   -S . \
   -B "build/some_path" \
   -DCMAKE_C_COMPILER="your_compiler" \
   -DCMAKE_CXX_COMPILER="your_compiler"

cmake --build "build/some_path"
```

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

## Libraries

| Name    | Current Supported | Required       | Notes                                                                     |
| ------- | ----------------- | -------------- | ------------------------------------------------------------------------- |
| vulkan  | NO                | NO             |                                                                           |
| sdl3    | NO                | NO             |                                                                           |
| glfw    | NO                | NO             |                                                                           |
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
| C               | 194        | 7191          | 71.74%     |
| Python          | 30         | 763           | 7.61%      |
| CMake           | 24         | 545           | 5.44%      |
| Bourne Shell    | 24         | 493           | 4.92%      |
| C++             | 17         | 457           | 4.56%      |
| Markdown        | 4          | 230           | 2.29%      |
| Lua             | 13         | 175           | 1.75%      |
| Dockerfile      | 4          | 64            | 0.64%      |
| DOS Batch       | 6          | 36            | 0.36%      |
| Fortran 95      | 1          | 32            | 0.32%      |
| GLSL            | 1          | 13            | 0.13%      |
| Assembly        | 2          | 11            | 0.11%      |
| PowerShell      | 3          | 10            | 0.10%      |
| INI             | 1          | 3             | 0.03%      |
| Summary         | 324        | 10023         | 100.00%    |

<!--python-stats-end-->

## Hardware Tested on

| OS           | Architecture | CPU           | RAM  | GPU            | Notes                              |
| ------------ | ------------ | ------------- | ---- | -------------- | ---------------------------------- |
| Alpine Linux | X64          | Pentium D 820 | 8GB  | Radeon HD 6950 |                                    |
| Android      | AArch64      | T616          | 8GB  | N/A            | Compiled using Termux.             |
| Arch Linux   | X64          | Ryzen 3900x   | 64GB | RX6800xt       |                                    |
| Arch Linux   | X64          | Ryzen 4650u   | 16GB | N/A            | X13 Gen 1 ThinkPad.                |
| FreeBSD      | X64          | I5 6300u      | 32GB | N/A            | T470                               |
| Windows 11   | X64          | Ryzen 2200g   | 16GB | Radeon WX6100  |                                    |
| OpenIndiana  | X64          | VM            | N/A  | N/A            | Hard to test on physical machines. |

