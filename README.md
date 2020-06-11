# ReliabilityCalc
C++ realiability calculation framework, which can be used to calculate the lifetime of an electronics circuit

The parts, which are used are modelled from various sources. One source can be the datasheets, but also a "private" database with stored reliability data can be used.

## Citation
[![DOI](https://zenodo.org/badge/54101010.svg)](https://zenodo.org/badge/latestdoi/54101010)

## BuildStatus
[![Build Status](https://travis-ci.org/JochiSt/ReliabilityCalc.svg?branch=master)](https://travis-ci.org/JochiSt/ReliabilityCalc)

## Requirements
For full function the libraries of 
* **SQLite3** for given reliability data from private databases
* **CURL** for fetching the reliability data from e.g. Texas Instruments

are needed.

In order to install them, please install:
* libsqlite3-dev
* libcurl4-openssl-dev
* libgsl-dev (maybe libgsl0-dev when using Ubuntu)

the dependencies should be installed automaticly

For apt based environments (e.g. Debian), you can simply use:
```bash
apt-get install libsqlite3-dev libcurl4-openssl-dev libgsl-dev
```

## Example Usage

### Create Temperature database
There is the possibility to have a dedicated temperature for each component. 
For this a small database is used. There must not be any entry in this database, 
but in order to avoid erros, it is recommended to create this file. This can be 
done by calling
```
./createDeltaTDB.sh
```

For a more detailed explanation how this framework works, and how it can be used, 
please have a look at the [wiki](https://github.com/JochiSt/ReliabilityCalc/wiki)

###### Define the ambient (usage) temperature
```
component::setAmbientTemperature(45);
```

###### Define a schematic
```
schematic* example = new schematic("Example Board");
```

###### Add components to this schematic
```
example -> addComponent(new capacitor_WUERTH("C2", "WCAP-CSGP",  1*capacitor::uF, 14, 50));
example -> addComponent(new IC_TI("U101", "DS15EA101SQ/NOPB"));
```
**Note** schematics can also contain schematics, which makes it easy to structure even complicated projects

###### Calculate the total reliability of the schematic and (sub-) schematics
```
example -> getFIT();
```


