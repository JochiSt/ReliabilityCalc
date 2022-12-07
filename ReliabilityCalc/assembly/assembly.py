# -*- coding: utf-8 -*-
"""

"""
import sys
sys.path.append("../../")
from components import component
from resistor.resistor import resistor

class assembly(component):
    def __init__(self, designator, T=None, deltaT=None):
        super().__init__(designator, 0, T, deltaT)
        self.components = []

    def FIT(self):
        FIT = 0
        for comp in self.components:
            try:
                FIT += comp.FIT()
            except:
                pass

        return FIT

    def addComponent(self, designator, value, T=None, deltaT=None):
        assert type(designator) == str

        comp = None

        if designator[0] == "R":
            comp = resistor(designator, value, T, deltaT)

        self.components.append(comp)
