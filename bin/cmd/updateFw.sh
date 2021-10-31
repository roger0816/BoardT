#!/bin/bash

cd /home/pi/BoardT

git checkout .

git pull

cd /home/pi/BoardT/src/ActiveBoard

cd /home/pi/BoardT/bin

killall ActiveBoard

DISPLAY=:0.0 ./ActiveBoard
