#!/usr/bin/python
import os
import time


os.system("modprobe vcan")
os.system("ip link add dev vcan0 type vcan")
os.system("ip link set up vcan0")
raw_input('Press Enter to start transmiting...')
cmd = "cansend vcan0 "
for i in range(100):
	fullcmd = cmd + str(i).zfill(3) + "#1326"
	print(fullcmd)
	os.system(fullcmd)
	time.sleep(0.5)


