#!/bin/bash

cd /home/pi/BoardT/src/ActiveBoard/
qmake ActiveBoard.pro
make clean
make

cd /home/pi/BoardT/bin

DISPLAY=:0.0 ./ActiveBoard
