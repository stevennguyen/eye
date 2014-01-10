eye
===
Facial/feature tracking pan-tilt camera with the Raspberry Pi SBC and camera module. A few notes about the Raspberry Pi:
* Revision 2 board with 512 MB RAM.
* arm_freq=950
* core_freq=350
* sdram_freq=450
* over_voltage=0
* gpu_mem_512=128

notes
==
PWM generated via DMA using a slightly modified [library](https://github.com/metachris/RPIO/tree/master/source/c_pwm). Changes were made to avoid casting errors/warnings when compiling with g++.

PD control loop has been implemented however gain constants are untuned. Performance seems acceptable at the moment, but values will be changed according to Ziegler-Nichols method when possible.
