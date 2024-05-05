#!/bin/bash
#
cmake -G"Unix Makefiles" \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE \
	-DBUILD_SHARED_LIBS=TRUE \
	-DSQUARE_SIZE=${1} \
	-DCMAKE_CXX_COMPILER=g++-12 \
	-S./ \
	-Bbuild_x${1}