SET ORICUTRON="..\..\..\oricutron\"

SET ORIGIN_PATH=%CD%

cl65 -ttelemon30 ch376.c
copy ch376 C:\Users\plifp\OneDrive\oric\oricutron\usbdrive\bin\ch376

cd %ORICUTRON%
Oricutronoffset -mt -d teledisks\stratsed.dsk
rem Oricutron_ch376V3 -mt -d teledisks\stratsed.dsk
cd %ORIGIN_PATH%

