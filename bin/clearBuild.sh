#!/bin/bash

cd /home/pi/work/src/ActiveBoard/
qmake ActiveBoard.pro
make clean
make

cd /home/pi/work/bin

DISPLAY=:0.0 ./ActiveBoard
