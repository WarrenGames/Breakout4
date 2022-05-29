#!/bin/bash
#List the sources and headers of 'editor' directory
#
find ../executables/wxEditor -type f -name "*.h" > lists/wxEditorHeaders.txt
find ../executables/wxEditor -type f -name "*.cpp" > lists/wxEditorSources.txt
#
sed 's#../executables/wxEditor/#\t\t#g' -i lists/wxEditor*.txt
