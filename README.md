# ReliabilityCalc
C++ realiability calculation program, which can be used to calculate the lifetime of an electronics circuit

The parts, which are used are modelled from various sources. One source can be the datasheets, but also a "private" database with stored reliability data can be used.

## Requirements
For full function the libraries of 
* SQLite3
* CURL
are needed.

## Example Usage
1. Define the ambient (usage) temperature
> component::setAmbientTemperature(45);

2. Define a schematic
> schematic* example = new schematic("Example Board");

3. Add components to this schematic
> example -> addComponent(new capacitor_WUERTH("C2", "WCAP-CSGP",  1*capacitor::uF, 14, 50));
> example -> addComponent(new IC_TI("U101", "DS15EA101SQ/NOPB"));

**Note** schematics can also contain schematics, which makes it easy to structure even complicated schematics

4. Calculate the total reliability of the schematic and (sub-) schematics
> example -> getFIT();


