#!/bin/sh
unset IFS
set -euf

rm -f crash-* || :
rm -rf html || :
rm -rf latex || :
rm -f debug.log || :
rm -rf bin || :
rm -rf debug || :
rm -rf Testing || :
rm -rf Makefile || :
rm -rf *.vcxproj || :
rm -rf *.vcxproj.filters || :
rm -rf *.sln || :
rm -rf x64 || :
rm -rf *.dir || :

/usr/bin/find . \
    -iwholename '*cmake*' \
    -not -name CMakeLists.txt \
    -not -name clean-cmake.sh \
    -print \
    -exec rm -rf '{}' \; || :