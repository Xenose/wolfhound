@ECHO OFF

SET PRP=%cd%
@ECHO Using path: %PRP%

REM code
DOSKEY wh-build=%PRP%\tools\shell\build.bat %PRP%

REM build systems
DOSKEY wh-clang=%PRP%\tools\shell\clang.bat %PRP%
DOSKEY wh-ninja=%PRP%\tools\shell\ninja.bat %PRP%
