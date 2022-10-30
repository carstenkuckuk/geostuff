mkdir wrk
cd wrk
copy ..\data\cities.trackfile .
copy ..\data\background.svg .

REM copy c:\data\backup.sqlite .
REM ..\xxx\Release\wiglewifitotrackfile.exe backup.sqlite backup.trackfile
REM ..\xxx\Release\svgfromtrackfile.exe backup.trackfile backup.svg
..\xxx\Release\svgfromlabellist.exe cities.trackfile cities.svg

REM ..\xxx\Release\svgfromstackofsvgs.exe map.svg background.svg backup.svg cities.svg

copy c:\data\backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe backup.sqlite     backup.trackfile
..\xxx\Release\addtrackfiletomap.exe    backup.trackfile  working.map

copy c:\data\Bis20170603_backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe Bis20170603_backup.sqlite     Bis20170603_backup.trackfile
..\xxx\Release\addtrackfiletomap.exe    Bis20170603_backup.trackfile  working.map

copy c:\data\Bis20171228_backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe Bis20171228_backup.sqlite     Bis20171228_backup.trackfile
..\xxx\Release\addtrackfiletomap.exe    Bis20171228_backup.trackfile  working.map

copy c:\data\Bis20180603_backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe Bis20180603_backup.sqlite     Bis20180603_backup.trackfile
..\xxx\Release\addtrackfiletomap.exe    Bis20180603_backup.trackfile  working.map

copy c:\data\Bis20190808_backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe Bis20190808_backup.sqlite     Bis20190808_backup.trackfile
..\xxx\Release\addtrackfiletomap.exe    Bis20190808_backup.trackfile  working.map

copy c:\data\Bis20200724_backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe Bis20200724_backupsqlite     Bis20200724_backup.trackfile
..\xxx\Release\addtrackfiletomap.exe    Bis20200724_backup.trackfile  working.map


..\xxx\Release\svgfrommap.exe working.map working.svg
..\xxx\Release\svgfromstackofsvgs.exe workingmap.svg background.svg working.svg cities.svg

cd ..

