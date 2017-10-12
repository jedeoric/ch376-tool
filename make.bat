@echo off



SET BINARYFILE=ch376
SET PATH_RELEASE=build\usr\share\%BINARYFILE%\
SET ORICUTRON="..\..\..\oricutron\"
set VERSION=1.0.1
SET ORIGIN_PATH=%CD%
echo %osdk%
SET PATH=%PATH%;%CC65%

echo Cleaning build folder

del /F /S /Q build\
          
mkdir build\usr\bin
mkdir build\usr\share\doc\
mkdir build\usr\share\doc\%BINARYFILE%
mkdir build\usr\share\man
IF NOT EXIST build\usr\share\ipkg mkdir build\usr\share\ipkg      

echo #define VERSION "%VERSION%" > src\version.h
rem  123456789012345678
echo | set /p dummyName=ch376     1.0.0  CH376 diagnostic tool > src\ipkg\%BINARYFILE%.csv


copy src\man\%BINARYFILE%.hlp build\usr\share\man
copy src\ipkg\%BINARYFILE%.csv build\usr\share\ipkg 
copy README.md build\usr\share\doc\%BINARYFILE%


cl65 -obuild\usr\bin\%BINARYFILE% -ttelestrat src/ch376.c ..\telemon\src\include\libs\ca65\ch376.s



IF "%1"=="NORUN" GOTO End
copy src\ipkg\%BINARYFILE%.csv %ORICUTRON%\usbdrive\usr\share\ipkg\
copy build\usr\bin\ch376 %ORICUTRON%\usbdrive\bin\ch376
copy src\man\%BINARYFILE%.hlp %ORICUTRON%\usbdrive\usr\share\man\

cd %ORICUTRON%
OricutronV4 -mt 
rem Oricutron_ch376V3 -mt -d teledisks\stratsed.dsk
cd %ORIGIN_PATH%
:End

