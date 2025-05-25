# The Wolfhound Game Engine [ C23 ]

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
| C               | 65         | 2708          | 67.31%     |
| JSON            | 6          | 439           | 10.91%     |
| Markdown        | 56         | 438           | 10.89%     |
| Python          | 2          | 155           | 3.85%      |
| CMake           | 10         | 146           | 3.63%      |
| Bourne Shell    | 9          | 59            | 1.47%      |
| Fortran 95      | 1          | 30            | 0.75%      |
| Lua             | 4          | 16            | 0.40%      |
| C++             | 2          | 15            | 0.37%      |
| DOS Batch       | 3          | 15            | 0.37%      |
| Text            | 1          | 2             | 0.05%      |
| Summary         | 159        | 4023          | 100.00%    |

<!--python-stats-end-->
