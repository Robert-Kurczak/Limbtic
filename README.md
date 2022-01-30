# Limbtic
Project Limbtic is an attempt to build a robotic arm that you can control using you own hand. Robotic arm can be bigger, stronger, more precise,
creating many application possibilities.

## Table of Contents
* [General info](#general-info)
* [Hardware](#hardware)

## General info
This project is currently more hardware focused, as I am working on circuit that can handle reading a lot of analog sensors, transform reading into binary form and
send it further so the data can be appropriately proccesed. This circuit have to be fast, precise and noise-resistant.
This kind of circuit have potential on its own as it can be used for example as VR hand controller.

## Hardware
### Sensor Reader
##### Schematic
![Sensor Reader Schematic](/Images/Sensor_Reader_Schematic.png)
##### PCB project
![Sensor Reader PCB project](/Images/Sensor_Reader_PCB.png)
##### Real photo
![Sensor Reader Photo](pic_link)

#### How does it work?
I want to read arm joints angles using some flexible pressure sensors as they're far cheaper than bend sensors, and can be cut to different sizes.
The more you bend sensor, the lesser resistance it have. Using array of resistors on board I create voltage dividers so I can convert resistance to voltage.
After buffering signal to lower impedance, I use low-pass filters to cut off noise above 160kHz. That prepared signal is being read and coverted to binary form by
ADS7841E analog to digital converter and sent futher, for exeample to arduino board, by SPI communication.

### Sensor Reader Connector
##### Schematic
![Sensor Reader Connector Schematic](/Images/Sensor_Connector_Schematic.png)
##### PCB project
![Sensor Reader Connector PCB project](/Images/Sensor_Connector_PCB.png)
##### Real photo
![Sensor Reader Connector Photo](pic_link)

#### How does it work?
Due to the spacing issues on Sensor Reader board I created little connector that goes on top of it.
It makes sensor connectors be in correct order, from left to right. It also makes connection with main board more solid, as instead of using 2 pin connectors for each sensor,
I can directly solder sensor wires to the header.
