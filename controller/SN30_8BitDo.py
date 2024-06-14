import pygame
import pygame.locals as pgl
import numpy as np

class SN30_8BitDO():
    def __init__(self) -> None:
        pygame.init()

        joystick_count = pygame.joystick.get_count()
        if joystick_count == 0:
            return
        self.joystick = pygame.joystick.Joystick(0)
        self.joystick.init()
        pygame.event.get()

        self.name = self.joystick.get_name()
        self.num_buttons = self.joystick.get_numbuttons()
        self.num_axes = self.joystick.get_numaxes()
        self.num_hats = self.joystick.get_numhats()
        self.axis = np.zeros(self.num_axes)
        self.button = np.zeros(self.num_buttons)
        self.hat = np.zeros((self.num_hats, 2))
    
    def update(self):
        events = pygame.event.get()
        for event in events:
            if event.type == pgl.KEYDOWN and event.key == pgl.K_q:
                return
        for i in range(self.num_axes):
            self.axis[i] = self.joystick.get_axis(i)
        for i in range(self.num_buttons):
            self.button[i] = self.joystick.get_button(i)
        for i in range(self.num_hats):
            self.hat[i] = self.joystick.get_hat(i)
        return events
    
    def get_axis(self, idx):
        return self.axis[idx]
    
    def get_button(self, idx):
        return self.button[idx]
    
    def get_hat(self, idx):
        return self.hat[idx]    


