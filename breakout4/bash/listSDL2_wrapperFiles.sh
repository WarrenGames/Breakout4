#!/bin/bash
#List the sources and headers of 'sdl2_wrapper' directory
#
find ../libs/sdl2_wrapper -type f -name "*.h" > lists/sdl2_wrapperHeaders.txt
find ../libs/sdl2_wrapper -type f -name "*.cpp" > lists/sdl2_wrapperSources.txt
#
sed 's#../libs/sdl2_wrapper/#\t\t#g' -i lists/sdl2_wrapper*.txt
