# -*- coding: utf-8 -*-
"""

"""

import sys
sys.path.append("../")

from components import *

R = resistor(None)
U = ic(293)
I = inductor(293)

print(R.FIT())