# dankherb
### PoE project Fall 2016
December 6th, 2016

The following is the github repo for our final project for principles of engineering class Fall 2016 at Olin College of Engineering. Our project is an autonomous herb garden that takes care of your plants for you using a drip irrigation system and autonomous LED lighting system. The following is a readme for the github for the project. 

## website
The folder for the website includes the html, css, and images for the website. You can visit http://poe.olin.edu/2016/gardenai/ to see our working website in action.   

## Python Code (GUI)

### dependencies 
The python depends on the following libraries:

#### Python 
The code is programmed using Python 2.7. Use the instructions [here](https://www.python.org/downloads/) to download it if you do not have it.

#### Kivy
You can use `$pip install kivy` to download this package. 

##### A Note About Pygame
You can use `$pip install pygame` to download this package. 

#### Serial
You can use `$pip install pyserial` to download this package. 

### To Run
In order to run the GUI, you must first run the Arduino code and then move over to python and run GardenaiApp.py. A window should appear that should give you information about the plants and their status. You can close the app when you are done with it.

#### A note about the serial name
You will need to change the name on the serial name depending on what your Arduino program names it. You should go to line 23 in the garden.py code and change the following line `ser = serial.Serial('/dev/cu.usbmodemFA131', 9600,timeout=5)` to whatever usbmodem name your Arduino has. 

## Arduino Code 
In order to run the Arduino code you should run reciever_control.ino. You should attach the usb from the system into a port into your computer and change the port on your arduino IDE and then run the appropriate code. 

### Reciever
The reciever code can be found in reciever_control.ino. This code controls everything for the water part of the system. It consists of an Arduino and an Adafruit motor shield. The motor shield controls the pump, using the Adafruit Motorshield library, by initalizing it as a motor. The four sensors that control the pump are in analog inputs 0-3. If the average of these values is below a certain threshold, then the pump turns off. 
This code also recieves control from the writer and then prints the 8 different sensor values (the 4 soil sensors and the 4 light sensors) to the serial monitor which the Python GUI code then reads to give the user the information.

### Writer
The writer code can be found in writer_control.ino. This code controls everything for the light part of the system. The lights that we are using are individually adressable leds from Adafruit Neopixels. In order to control these we use the the Neopixel library. We are using DLI to control the lights. The code reads the light values from the four sensors in analog inputs 0-3. 

