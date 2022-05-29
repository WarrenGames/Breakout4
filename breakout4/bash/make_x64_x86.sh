#!/bin/bash
#
cd ..
./runCmake.sh 64
./makeBinaries.sh 64
./runCmake.sh 86
./makeBinaries.sh 86
./runCmake.sh 96
./makeBinaries.sh 96
