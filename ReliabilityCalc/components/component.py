# -*- coding: utf-8 -*-

class component:

    T = 293 # global temperature

    def __init__(self, T):
        print("init with temperature " + str(T) )
        if T is None:
            self.useGlobalT = True
        else:
            self.useGlobalT = False
            self.T = T

    def FIT(self):
        return -1

    @staticmethod
    def setGlobalTemperature(T):
        __class__.T = T

    def getGlobalTemperature(T):
        return __class__.T

    def getTemperature(self):
        if self.useGlobalT:
            return __class__.T
        else:
            return self.T


