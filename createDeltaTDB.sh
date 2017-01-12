#!/bin/bash

sqlite3 temperatures.db  "CREATE TABLE Tincrease (partname VARCHAR(32), deltaT float);"
