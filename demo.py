from controller.SN30_8BitDo import SN30_8BitDO
import pygame
import numpy as np
import pygame.locals as pgl
from util.math_utils import *

DIRECTION_MAP = {2:'UP', 1:'UP-RIGHT', 0:'RIGHT', -1:'DOWN-RIGHT', -2:'DOWN', -3:'DOWN-LEFT', -4:'LEFT', 3:'UP-LEFT', 4:'LEFT'}

if __name__ == "__main__":
    sn30 = SN30_8BitDO()
    clock = pygame.time.Clock()

    while True:
        sn30.update()
        
        if sn30.get_button(2):
            break
        
        axis_0 = sn30.get_axis(0)
        axis_1 = sn30.get_axis(1)
        angle = get_angle(axis_0, axis_1)
        norm = get_norm(axis_0, axis_1)
        angle_agv = angle/math.pi*180 if norm > 0.1 else 0

        direction = int((angle_agv+22.5) // 45)
        direction = DIRECTION_MAP[direction] if norm > 0.1 else 'STOP'

        print("\rAxis 0: {:>6.3f} Axis 1: {:>6.3f} Angle: {:>6.3f} Direction: {:}".format(axis_0, axis_1, angle_agv, direction), end="\r")
        
        clock.tick(30)

print()
pygame.quit()



import serial
import time
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    while True:
        ser.write(b"Hello from Raspberry Pi!\n")
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)