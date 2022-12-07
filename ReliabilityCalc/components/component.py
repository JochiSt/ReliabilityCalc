# -*- coding: utf-8 -*-

class component:

    T = 293 # global temperature

    def __init__(self, designator, value, T=None, deltaT=None):
        """
        Parameters
        ----------
        designator : str
            designator of the component, typ. R1, U2 etc.
        value : str
            value of the component
        T : float, optional
            local device temperature. If None, the global temperature is used.
            The default is None.
        deltaT : float, optional
            difference to global temperature. Only taken into account, when
            global temperature is used. The default is None.

        Returns
        -------
        None.

        """

        self.designator = designator
        self.value = value

        if T is None:
            self.useGlobalT = True
        else:
            self.useGlobalT = False
            self.T = T

        if deltaT is None:
            self.deltaT = 0
        else:
            self.deltaT = deltaT


    def FIT(self):
        """
        Returns
        -------
        float
            FIT - Failure in Time
        """
        return -1

    @staticmethod
    def setGlobalTemperature(T):
        """
        Parameters
        ----------
        T : float
            global Temperature of all devices

        Returns
        -------
        None.

        """
        __class__.T = T

    @staticmethod
    def getGlobalTemperature():
        """
        Returns
        -------
        float
            global temperature of all devices

        """
        return __class__.T

    def getTemperature(self):
        """
        Returns
        -------
        float
            Temperature of device. Either global temperature + deltaT or local
            temperature.
        """
        if self.useGlobalT:
            return __class__.T + self.deltaT
        else:
            return self.T


