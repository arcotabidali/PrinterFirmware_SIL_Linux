
import numpy as np

class PaperFeedPlant:
    def __init__(self, base_load=0.5):
        self.load = base_load

    def disturb(self, magnitude):
        self.load += magnitude
        if self.load < 0:
            self.load = 0

class HeaterPlant:
    def __init__(self, ambient_c=25.0):
        self.ambient = ambient_c
