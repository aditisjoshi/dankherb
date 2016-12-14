import serial
import time
import math

import kivy
kivy.require('1.0.6') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.properties import NumericProperty, ReferenceListProperty, ObjectProperty
from kivy.uix.textinput import TextInput

from garden import Garden


class GardenaiGame(Widget):

    our_garden = Garden(4)

    # FOR TESTING WHEN WE ARE NOT HOOKED UP TO ARDUINO
    # for plant in our_garden.plants:
    #     # this is for testing
    #     plant.soil_vals = [300,400,500,600]
    #     plant.light_vals = [1,2,3,2]
    #     plant.get_soil_state()
    #     plant.get_light_state()

    # UNCOMMENT THIS LINE WHEN WE ARE HOOKED UP TO ARDUINO
    our_garden.collect_data()


class GardenaiApp(App):

    def build(self):
        # reading the labels and updating the values based on the GUI
        w = GardenaiGame()
        return w


if __name__ == '__main__':

    GardenaiApp().run()
    
