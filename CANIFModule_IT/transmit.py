#!/usr/bin/python3
import os
import time
import sys

os.system("modprobe vcan")
os.system("ip link add dev vcan0 type vcan")
os.system("ip link set up vcan0")
print('Press Enter to start transmiting...')
sys.stdin.read(1)
cmd = "cansend vcan0 "
for i in range(100):
	fullcmd = cmd + str(i).zfill(3) + "#1326"
	print(fullcmd)
	os.system(fullcmd)
	time.sleep(0.1)


