# -*- coding: utf-8 -*-
"""

"""
from resistor import resistor

class resistor_MIL(resistor.resistor):

    def __init__(self, designator, value, T=None, deltaT=None):
        super().__init__( designator, value, T, deltaT)


