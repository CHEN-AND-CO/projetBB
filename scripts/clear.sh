#!/bin/bash

gpio=/sys/class/gpio

declare -A ports=(  [3]=out         # Blue
                    [48]=in         # BP
                    [50]=out        # Red
                    [60]=out        # Green
                    [51]=out        # QAM
)

for k in "${!ports[@]}"
do
    v=${ports[$k]}
    
    echo $k > $gpio/unexport
done 

echo cape-bone-iio > /sys/devices/bone_capemgr.*/slots