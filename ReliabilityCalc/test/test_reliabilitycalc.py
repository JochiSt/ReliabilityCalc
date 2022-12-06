# -*- coding: utf-8 -*-
"""

"""

import sys
sys.path.append("../")

from components import *

R1 = resistor(20)
R2 = resistor_MIL(20)

U1 = ic(300)

I = inductor(300)

print(R1.getTemperature())

component.setGlobalTemperature(300)

print(R1.getTemperature())

print("Number of resistors: ", resistor.getPartCnt())