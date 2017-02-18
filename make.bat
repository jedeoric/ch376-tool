@echo off

SET ORICUTRON="..\..\..\oricutron\"
SET PATH=%PATH%;%CC65%

SET ORIGIN_PATH=%CD%

cl65 -orelease\usr\bin\ch376 -ttelestrat ch376.c ..\oric-common\lib\ca65\ch376.s



IF "%1"=="NORUN" GOTO End

copy release\usr\bin\ch376 %ORICUTRON%\usbdrive\usr\bin\ch376

cd %ORICUTRON%
OricutronV4 -mt -d teledisks\stratsed.dsk
rem Oricutron_ch376V3 -mt -d teledisks\stratsed.dsk
cd %ORIGIN_PATH%
:End

