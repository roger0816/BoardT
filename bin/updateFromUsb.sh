#!/bin/bash

killall ActiveBoard

cp -r ~/BoardT/bin/data ~/BoardT/bin/dataBK

cp -r $1 ~/BoardT/bin/data

cd /home/pi/BoardT/bin

DISPLAY=:0.0 ./ActiveBoard


