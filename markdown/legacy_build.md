
### Linux [ POSIX SHELL, BASH, ZSH, DASH ]
```sh
# Note ASH might not work
. ./graveyard/cmake/activate.sh
```

### Windows [ CMD ]
```cmd
call graveyard\cmake\activate.bat
```

### Windows [ Powershell Experimental ]
```ps1
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
. .\graveyard\shell\activate.ps1
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

