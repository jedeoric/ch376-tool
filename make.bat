SET ORICUTRON="..\..\..\oricutron\"

SET ORIGIN_PATH=%CD%

cl65 -ttelestrat ch376.c ..\oric-common\lib\ca65\ch376.s

copy ch376 release

IF "%1"=="NORUN" GOTO End

copy ch376 %ORICUTRON%\usbdrive\bin\ch376

cd %ORICUTRON%
OricutronV4 -mt -d teledisks\stratsed.dsk
rem Oricutron_ch376V3 -mt -d teledisks\stratsed.dsk
cd %ORIGIN_PATH%
:End

