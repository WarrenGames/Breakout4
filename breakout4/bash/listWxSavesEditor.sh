#!/bin/bash
#List the sources and headers of 'editor' directory
#
find ../executables/wxSavesEditor -type f -name "*.h" > lists/savesEditorHeaders.txt
find ../executables/wxSavesEditor -type f -name "*.cpp" > lists/savesEditorSources.txt
#
sed 's#../executables/wxSavesEditor/#\t\t#g' -i lists/savesEditor*.txt
