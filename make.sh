#!/bin/bash
shopt -s extglob
echo "Downloading CEF binary..."
mkdir -p build_temp
wget "https://cef-builds.spotifycdn.com/cef_binary_86.0.24%2Bg85e79d4%2Bchromium-86.0.4240.198_linux64_minimal.tar.bz2" -O build_temp/cef.tar.bz2
echo "Extracting..."
tar -xjf build_temp/cef.tar.bz2 --strip-components=1 -C build_temp/
cd build_temp
echo "Building libcef_dll_wrapper"
cmake .
make libcef_dll_wrapper -j$(($(grep -c ^processor /proc/cpuinfo) * 2))
cd ..
mkdir -p Release
echo "Copying libcef_dll_wrapper.a..."
cp build_temp/libcef_dll_wrapper/libcef_dll_wrapper.a Release
echo "Copying CEF Binaries..."
cp -a build_temp/Release/. Release/
echo "Copying CEF Assets..."
cp -a build_temp/Resources/. Release/
echo "Stripping libcef.so to reduce it's size..."
strip Release/libcef.so
echo "Compiling the app..."
g++ main.cpp MyApp.cpp -I. -L. `pkg-config --cflags --libs gtk+-3.0` -lcef -lX11 -lcef_dll_wrapper -Wl,-rpath,. -o connect
echo "Copying app files..."
cp -a {install.sh,connect.desktop,open.sh,connect,LICENSE} Release/
rm -r build_temp/*
rmdir build_temp
echo "Done!"