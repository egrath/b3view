SET THIS_EXE=b3view.exe
SET PROGRAMS="%USERPROFILE%\Applications"
IF NOT EXIST "%PROGRAMS%" MD "%PROGRAMS%"
IF NOT EXIST "%PROGRAMS%\b3view" MD "%PROGRAMS%\Applications\b3view"
echo.
echo.
IF NOT EXIST "%THIS_EXE%" ECHO ERROR: Nothing done since %THIS_EXE% not found--you must run this from the build directory
COPY "%THIS_EXE%" ""
pause
