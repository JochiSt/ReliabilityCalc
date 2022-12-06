# -*- coding: utf-8 -*-
"""

"""
import sys
sys.path.append("../../")
from components import component

class resistor(component):

    partcnt = 0;

    def __init__(self, value, T=None, deltaT=None):
        super().__init__(T, deltaT)
        assert value
        self.value = value

        __class__.partcnt += 1

        self.stress = 0

    def setStress(self, stress):
        self.stress = stress

    def setStress(self, ratedPower, usedPower):
        self.stress = usedPower / ratedPower

    @staticmethod
    def getPartCnt():
        return __class__.partcnt
