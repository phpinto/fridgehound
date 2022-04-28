# FridgeHound - The Smart Tupperware

### Authors:
Orlando G. Rodriguez, Pedro Henrique Ribeiro Pinto

## Description

Have you ever forgot something on the fridge and by time you opened it the food had gone bad? Or maybe you opened a tupperware and wasn't too sure if the food was still good? Well, you are not alone. The average american household wastes around 25% of the food they purchase. This was the main reason why we decide to create FridgeHound. FridgeHound is a Smart Tupperware that uses the mq-135 gas sensor to track your food. With an easy to use interface you can store different type of foods and the sensor will estimate how much time you have left. We also added a thermometer so you can keep track of your fridge's temperature. The best part is that you can access all this information from a web application anywhere you go. The gas sensor and thermometer send information via serial usb to a Raspberry Pi 2, which sends that information to our web application's database. This way, you always have the most up to date information anywhere you go.

## System Diagram

<p align="center"><img src="images/system_diagram.png" alt="system_diagram" style="width: 800px;"/></p>


## Hardware Components

<p align="center"><img src="images/fridgehound_parts.png" alt="hardware_components" style="width: 750px;"/></p>

## Hardware Prototype

<p align="center"><img src="images/hw_prototype.png" alt="prototype" style="width: 750px;"/></p>

## Pin-out Connections

- ### Gas Sensor (MQ-135):

| Mbed     | SD      |
| ------------- | ------------- |
| p15        | out         |
| GND         | GND         |
| Vout         | Vcc         |
| VU         | 5V         |

- ### Temperature sensor (TMP-36):

| Mbed     | MQ-135      |
| ------------- | ------------- |
| GND        | GND         |
| Vout         | 3.3V         |
| P18         | Out         |

- ### uLCD Connections:

| Mbed     | uLCD      |
| ------------- | ------------- |
| VU        | 5V         |
| GND         | GND         |
| Tx=P9         | RX         |
| Rx=P10         | TX         |
| P11         | Reset         |

- ### Up Pushbutton Connections:

| Mbed     | Up Pushbutton      |
| ------------- | ------------- |
| P8        | P1         |
| GND         | P2         |

- ### Down Pushbutton Connections:

| Mbed     | Down Pushbutton      |
| ------------- | ------------- |
| P28        | P1         |
| GND         | P2         |

- ### Left Pushbutton Connections:

| Mbed     | Left Pushbutton      |
| ------------- | ------------- |
| P29        | P1         |
| GND         | P2         |

- ### Right Pushbutton Connections:

| Mbed     | Right Pushbutton      |
| ------------- | ------------- |
| P24        | P1         |
| GND         | P2         |

- ### Select Pushbutton Connections:

| Mbed     | Select Pushbutton      |
| ------------- | ------------- |
| P20        | P1         |
| GND         | P2         |

- ### Homepage Pushbutton Connections:

| Mbed     | Homepage Pushbutton      |
| ------------- | ------------- |
| P19        | P1         |
| GND         | P2         |

- ### USB Serial Connection:

| Mbed     | Raspberry Pi      |
| ------------- | ------------- |
| USB mini Out  | USB 2.0 In         |

## Demos

- ### Smart Tupperware:

- ### Web Interface:
