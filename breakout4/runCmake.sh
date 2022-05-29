#!/bin/bash
#
cmake -G"Unix Makefiles" \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE \
	-DBUILD_SHARED_LIBS=TRUE \
	-DCMAKE_CXX_COMPILER=g++-11 \
	-S./ \
	-B../build