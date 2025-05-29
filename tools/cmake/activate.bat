@ECHO OFF

SET PRP=%cd%
@ECHO Using path: %PRP%

REM code
DOSKEY wh-build = %PRP%\tools\cmake\build.bat %PRP%

REM build systems
DOSKEY wh-ninja = %PRP%\tools\cmake\ninja.bat %PRP%
