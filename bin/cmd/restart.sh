#!/bin/bash


cd /home/pi/BoardT/bin

killall ActiveBoard

DISPLAY=:0.0 ./ActiveBoard
