mkdir wrk
cd wrk
copy ..\data\cities.trackfile .
copy ..\data\background.svg .
copy c:\data\backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe backup.sqlite backup.trackfile
..\xxx\Release\svgfromtrackfile.exe backup.trackfile backup.svg
..\xxx\Release\svgfromlabellist.exe cities.trackfile cities.svg

..\xxx\Release\addtrackfiletomap.exe backup.trackfile working.map
..\xxx\Release\svgfrommap.exe working.map working.svg

..\xxx\Release\svgfromstackofsvgs.exe map.svg background.svg backup.svg cities.svg

..\xxx\Release\svgfromstackofsvgs.exe workingmap.svg background.svg working.svg cities.svg

cd ..

