mkdir wrk
cd wrk
copy ..\data\cities.trackfile .
copy c:\data\backup.sqlite .
..\xxx\Release\wiglewifitotrackfile.exe backup.sqlite backup.trackfile
..\xxx\Release\svgfromtrackfile.exe backup.trackfile trackfile.svg
..\xxx\Release\svgfromlabellist.exe cities.trackfile cities.svg

cd ..

