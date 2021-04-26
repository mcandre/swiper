#!/bin/sh
unset IFS
set -euf

rm -f *.profdata || :
rm -f *.profraw || :
rm -f crash-* || :
rm -rf html || :
rm -rf latex || :
rm -f debug.log || :
rm -rf bin || :
rm -rf debug || :
rm -rf Testing || :
rm -rf build || :
rm -rf Makefile || :
rm -rf *.vcxproj || :
rm -rf *.vcxproj.filters || :
rm -rf *.sln || :
rm -rf x64 || :
rm -rf *.dir || :
rm -rf CMakeFiles || :
rm Findbenchmark.cmake || :
rm cmake_install.cmake || :
rm CTestTestfile.cmake || :
rm CMakeCache.txt || :
rm conanbuildinfo.cmake || :
rm graph_info.json || :
rm conan.lock || :
rm conanbuildinfo.txt || :
rm conaninfo.txt || :
