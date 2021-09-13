#!/bin/bash

killall ActiveBoard

cp -r ~/BoardT/bin/data ~/BoardT/bin/dataBK

cp -r $1 ~/BoardT/bin/data


