#!/bin/bash

#cd /home/pi/work/src/ActiveBoard
#qmake ActiveBoard.pro
#make clean
#make

cd /home/pi/BoardT/bin

killall ActiveBoard

DISPLAY=:0.0 ./ActiveBoard
