# -*- coding: utf-8 -*-
import sys
sys.path.append("../../")
from components import component

class inductor(component):
    def __init__(self, value, T=None, deltaT=None):
        super().__init__(T, deltaT)
        assert value
        self.value = value

