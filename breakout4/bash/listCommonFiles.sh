#!/bin/bash
#List the sources and headers of 'commonFiles' directory
#
find ../libs/commonFiles -type f -name "*.h" > lists/commonHeaders.txt
find ../libs/commonFiles -type f -name "*.cpp" > lists/commonSources.txt
#
sed 's#../libs/commonFiles/#\t\t#g' -i lists/common*.txt
