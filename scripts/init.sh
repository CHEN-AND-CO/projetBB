#!/bin/sh

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
    
    echo $k > $gpio/export
    echo $v > $gpio/gpio$k/direction
done 

echo cape-bone-iio > /sys/devices/bone_capemgr.*/slots

echo am33xx_pwm > /sys/devices/bone_capemgr.9
echo bone_pwm_P9_16 > /sys/devices/bone_capemgr.9

