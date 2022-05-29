#!/bin/bash
#List the sources and headers of 'generic' directory
#
find ../libs/genericLib -type f -name "*.h" > lists/genericLibHeaders.txt
find ../libs/genericLib -type f -name "*.cpp" > lists/genericLibSources.txt
#
sed 's#../libs/genericLib/#\t\t#g' -i lists/genericLib*.txt
