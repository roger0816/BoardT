#!/bin/bash

killall ActiveBoard

sudo rm -rf ~/BoardT/bin/data/model0

#sudo cp -r ~/BoardT/bin/data ~/BoardT/bin/dataBK

sudo cp -r $1 ~/BoardT/bin/data/

echo $1

cd /home/pi/BoardT/bin

DISPLAY=:0.0 ./ActiveBoard


