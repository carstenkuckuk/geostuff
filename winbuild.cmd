
mkdir xxx
cd xxx
REM For Visual Studio 2010 use: cmake -G "Visual Studio 10 Win64" ..
REM For Visual Studio 2012 use: cmake -G "Visual Studio 11 Win64" ..
REM For Visual Studio 2017 use:
cmake -G "Visual Studio 15 2017 Win64" ..

cmake --build . --config Release

cd ..

