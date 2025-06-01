# Tools(Needed for both paths)
* [Git](https://git-scm.com/downloads/win)

## Editors(Nice to have)
[VS Code](https://code.visualstudio.com/)

# Windows VCPKG

## VCPKG(Automatic install)
1. In your terminal go to "C:\Program Files\".
2. Git clone "https://github.com/microsoft/vcpkg.git"
3. cd into vcpk and run .\bootstrap
4. Open up "edit environment variables for your account"..
5. Press "Environment Variables".
6. Select Path and press edit.
7. Press new and paste "C:\Program Files\vcpkg" into the path.
8. Execute the following:
```bat
vcpkg install sdl3:x64-windows
vcpkg install lua:x64-windows
vcpkg install vulkan:x64-windows
```

### Install Libraries

# Windows Manual Setup
Note: It is recommended to restart the shell once done as many of these
steps will take effect after reload.

* Also [vcpkg]() can be used instead.

## Build Tools
1. Install the tools below and make sure to add them to the system path.
* [CMake](https://cmake.org/download/)
* [Clang LLVM](https://github.com/llvm/llvm-project/releases/tag/llvmorg-20.1.0)
* [Microsoft C++ Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
* [Windows SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)

## [Ninja](https://github.com/ninja-build/ninja/releases)
1. Download the binary and drop it in "C:\Program Files\Ninja".
2. Open up "edit environment variables for your account"..
3. Press "Environment Variables".
4. Select Path and press edit.
5. Press new and paste "C:\Program Files\Ninja" into the path.

## Libraries
[Vulkan SDK](https://vulkan.lunarg.com/sdk/home)
1. In CMD run the following.
```bat
setx INCLUDE "%INCLUDE%;C:\VulkanSDK\X.X.XXX.X\Include"
setx LIB "%LIB%;C:\VulkanSDK\X.X.XXX.X\Lib"
setx PATH "%PATH%;C:\VulkanSDK\X.X.XXX.X\Bin"
```

## [SDL3](https://github.com/libsdl-org/SDL/releases)
1. Go to the path "${PATH_TO_ZIP}\SDL3-devel-XX.XX.XX-VC.zip\SDL3-XX.XX.XX\lib\x64\".
2. Copy the files into "C:\usr\lib\".
3. Then go into "${PATH_TO_ZIP}\SDL3-devel-XX.XX.XX-VC.zip\SDL3-XX.XX.XX\include" path.
4. Copy the SDL3 folder into "C:\usr\include".

## [LUA](https://luabinaries.sourceforge.net/)
1. Go to the path "${PATH_TO_TAR}\lua-5.4.2_Win64_dll17_lib.zip\".
2. Copy the .lib and .dll into "C:\usr\lib\".
3. Then go into "${PATH_TO_TAR}\lua-5.4.2_Win64_dll17_lib.zip\include\".
4. Copy all files into "C:\usr\include\".
