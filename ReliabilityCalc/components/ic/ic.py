# -*- coding: utf-8 -*-
import sys
sys.path.append("../../")
from components import component

class ic(component):

    partcnt = 0

    @staticmethod
    def getPartCnt():
        return __class__.partcnt

    def __init__(self, value, T=None, deltaT=None):
        super().__init__(T, deltaT)
        assert value
        self.value = value

        __class__.partcnt += 1

