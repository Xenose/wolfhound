# The Wolfhound Game Engine

| Platform     | Tested | Supported | Description                             |
| ------------ | ------ | --------- | --------------------------------------- |
| Arch Linux   | YES    | YES       | Primary development platform.           |
| Debian Linux | NO     | Not yet   | Planned.                                |
| Windows      | NO     | Not yet   | Planned.                                |
| MacOS        | NO     | No        | No Plans.                               |

## Building instructions
[how to build the project](docs/markdown/build.md)

<!--python-stats-start-->

|  Language       | File Count | Lines of Code | Procentage |
| --------------- | ---------- | ------------- | ---------- |
| C               | 61         | 2398          | 71.33%     |
| Markdown        | 55         | 347           | 10.32%     |
| JSON            | 5          | 269           | 8.00%      |
| Python          | 2          | 155           | 4.61%      |
| CMake           | 3          | 109           | 3.24%      |
| Fortran 95      | 1          | 30            | 0.89%      |
| Bourne Shell    | 3          | 19            | 0.57%      |
| Lua             | 4          | 16            | 0.48%      |
| C++             | 2          | 15            | 0.45%      |
| Text            | 2          | 4             | 0.12%      |
| Summary         | 138        | 3362          | 100.00%    |

<!--python-stats-end-->

## Libraries

| Name    | Current Supported | Required       | Notes                                                                     |
| ------- | ----------------- | -------------- | ------------------------------------------------------------------------- |
| raylib  | YES               | NO             | At least one graphics library is required.                                |
| vulkan  | NO                | NO             | At least one graphics library is required, vulkan needs sdl3 also.        |
| sdl3    | NO                | NO             | At least one graphics library is required,                                |
| lua     |                   | YES            | Used for data, arguments and configurations.                              |
| unwind  |                   | NO(but useful) | Used to backtrace Segfaults from the signal handler.                      |
