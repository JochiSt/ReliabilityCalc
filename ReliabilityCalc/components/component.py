# -*- coding: utf-8 -*-

class component:
    def __init__(self, T):
        print("init with temperature " + str(T) )
        self.T = T

    def FIT(self):
        return self.T
