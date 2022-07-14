#!/bin/bash
shopt -s extglob
echo "Downloading CEF binary..."
mkdir -p .buildtemp
wget "https://cef-builds.spotifycdn.com/cef_binary_86.0.24%2Bg85e79d4%2Bchromium-86.0.4240.198_linux64_minimal.tar.bz2" -O .buildtemp/cef.tar.bz2 &&
echo "Extracting..."
tar -xjf .buildtemp/cef.tar.bz2 --strip-components=1 -C .buildtemp/ &&
cd .buildtemp
echo "Building libcef_dll_wrapper"
# Fix build bug in CEF binary
sed -i '/-Werror/d' ./cmake/cef_variables.cmake
cmake . &&
make libcef_dll_wrapper -j`nproc` &&
cd ..
mkdir -p Release
echo "Copying libcef_dll_wrapper.a..."
cp .buildtemp/libcef_dll_wrapper/libcef_dll_wrapper.a Release
echo "Copying CEF Binaries..."
cp -a .buildtemp/Release/. Release/
echo "Copying CEF Assets..."
cp -a .buildtemp/Resources/. Release/
echo "Stripping libcef.so to reduce it's size..."
strip Release/libcef.so
echo "Compiling the app..."
g++ main.cpp MyApp.cpp -I. -L./Release -lcef -lpthread -lX11 -lcef_dll_wrapper -Wl,-rpath,. -o connect &&
echo "Copying app files..."
cp -a {install.sh,connect.desktop,open.sh,connect,LICENSE,connect.png} Release/
rm -r .buildtemp/*
rmdir .buildtemp
chmod +x Release/open.sh Release/connect Release/install.sh
echo "Done!"
