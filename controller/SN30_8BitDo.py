import pygame
import pygame.locals as pgl
import numpy as np

class SN30_8BitDO():
    def __init__(self) -> None:
        pygame.init()

        
        
        self.axis = np.zeros(6)
        self.button = np.zeros(11)
        self.hat = np.zeros(1)
    def update(self):
        self.joystick = pygame.joystick.Joystick(0)
        joystick_count = pygame.joystick.get_count()
        #print(joystick_count)
        #print()
        self.joystick.init()
        """for event in pygame.event.get():
            if event.type == pygame.JOYAXISMOTION:
                self.axis[event.axis] = event.value
            elif event.type == pygame.JOYBUTTONDOWN:
                self.button[event.button] = 1
            elif event.type == pygame.JOYBUTTONUP:
                self.button[event.button] = 0
            elif event.type == pygame.JOYHATMOTION:
                self.hat[event.hat] = event.value"""
        axis0 = self.joystick.get_axis(0)
        axis1 = self.joystick.get_axis(1)
        axes = self.joystick.get_numaxes()
        print("\r", axes,axis0, axis1, end='')


if __name__ == "__main__":
    sn30 = SN30_8BitDO()
    clock = pygame.time.Clock()
    while True:
        for event in pygame.event.get(): # User did something.
            if event.type == pygame.QUIT: # If user clicked close.
                done = True # Flag that we are done so we exit this loop.

        if event.type == pgl.KEYDOWN and event.key == pgl.K_q:
            done = True
        sn30.update()
        clock.tick(30)
