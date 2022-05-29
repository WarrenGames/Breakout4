#!/bin/bash
#List the sources and headers of 'game' directory
#
find ../executables/game -type f -name "*.h" > lists/gameHeaders.txt
find ../executables/game -type f -name "*.cpp" > lists/gameSources.txt
#
sed 's#../executables/game/#\t\t#g' -i lists/game*.txt
