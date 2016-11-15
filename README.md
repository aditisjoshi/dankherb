# dankherb
### PoE project Fall 2016
November 14th, 2016

The following is the github repo for our final project for principles of engineering class Fall 2016 at Olin College of Engineering. Our project is an autonomous herb garden that takes care of your plants for you using a drip irrigation system and autonomous LED lighting system. The following is a readme for the github for the project. 

## website
The folder for the website includes the html, css, and images for the website.   

## Python Code (GUI)

### dependencies 
The python depends on the following libraries:

#### Python 
The code is programmed using Python 2.7. Use the instructions [here](https://www.python.org/downloads/) to download it if you do not have it.

#### Kivy
You can use `pip install kivy` to download this package. 

##### A Note About Pygame
You can use `pip install pygame` to download this package. 

#### Serial
You can use `pip install pyserial` to download this package. 

### To Run
In order to run the GUI, you must first run the Arduino code and then move over to python and run GardenaiApp.py. A window should appear that should give you information about the plants and their status. You can close the app when you are done with it.

#### A note about the serial name
You may need to change the name on the serial name depending on what your Arduino program names it. You should go to line 23 in the garden.py code and change the following line `ser = serial.Serial('/dev/cu.usbmodemFA131', 9600,timeout=5)` to whatever usbmodem name your Arduino has. 

## Arduino Code 
In order to run the Arduino code you should run collect_sensor_data.ino. You should hook up the Arduino based on the pin values mentioned in the code (it is currently set up for two soil sensors and two light sensors, making it two plants in all).
