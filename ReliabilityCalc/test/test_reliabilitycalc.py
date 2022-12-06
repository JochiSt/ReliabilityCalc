# -*- coding: utf-8 -*-
"""

"""

import sys
sys.path.append("../")

from components import *

R = resistor(None)
U = ic(300)
I = inductor(300)

print(R.getTemperature())

component.setGlobalTemperature(300)

print(R.getTemperature())