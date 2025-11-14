@ECHO OFF

SET PRP=%cd%
SET TP="\tools\shell\"
@ECHO Using path: %PRP%

REM code
DOSKEY wh-build=%PRP%%TP%build.bat %PRP%

REM build systems
DOSKEY wh-msvc=%PRP%%TP%\msvc.bat %PRP%
DOSKEY wh-clang=%PRP%%TP%\clang.bat %PRP%
DOSKEY wh-ninja=%PRP%%TP%\shell\ninja.bat %PRP%
