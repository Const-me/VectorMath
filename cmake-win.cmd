rmdir /q /s msvc
mkdir msvc
cd msvc
cmake ../ -G "Visual Studio 14 2015 Win64"
pause