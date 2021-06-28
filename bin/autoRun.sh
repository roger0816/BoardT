#!/bin/bash

#/home/pi/.config/autostart/auto.desktop

cd /home/pi/BoardT/bin/

chmod a+x ActiveBoard

#cp ActiveBoard ActiveBoardBK

#cp ActiveBoardNew ActiveBoard

./ActiveBoard & python IR_Temperature.py 0x52

