#!/bin/sh
unset IFS
set -euf
find . -name '*.profdata' -delete || :
find . -name '*.profraw' -delete || :
find . -name 'crash-*' -delete || :
rm -rf html || :
rm -rf latex || :
rm -f debug.log || :
rm -rf bin || :
rm -rf debug || :
rm -rf Testing || :
rm -rf build || :
rm -rf Makefile || :
find . -name '*.vcxproj*' -delete || :
find . -name '*.sln' -delete || :
rm -rf x64 || :
find . -name '*.dir' -exec rm -rf "{}" \; || :
rm -rf CMakeFiles || :
rm -f cmake_install.cmake || :
rm -f CTestTestfile.cmake || :
rm -f CMakeCache.txt || :
