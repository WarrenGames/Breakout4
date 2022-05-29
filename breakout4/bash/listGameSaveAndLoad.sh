#!/bin/bash
#List the sources and headers of 'generic' directory
#
find ../libs/gameSaveAndLoad -type f -name "*.h" > lists/gameSaveAndLoadHeaders.txt
find ../libs/gameSaveAndLoad -type f -name "*.cpp" > lists/gameSaveAndLoadSources.txt
#
sed 's#../libs/gameSaveAndLoad/#\t\t#g' -i lists/gameSaveAndLoad*.txt
