# -*- coding: utf-8 -*-
"""

"""

import sys
sys.path.append("../")

from components import *

R1 = resistor("R1", 20)
R2 = resistor_MIL("R2", 20)

U1 = ic("U1", 300)
U2 = ic_TI("U2", 300)

L1 = inductor("L1", 300)

print(R1.getTemperature())

component.setGlobalTemperature(300)

print(R1.getTemperature())


A1 = assembly("A1")
A1.addComponent("R1", 10)

print(A1.FIT())

print("Number of resistors: ", resistor.getPartCnt())