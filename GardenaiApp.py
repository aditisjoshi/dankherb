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


from garden import Garden



class GardenaiGame(Widget):
    our_garden = ObjectProperty(None)
    our_garden = Garden(1,["Tom Gore"], ["Thyme"])

    # FOR TESTING WHEN WE ARE NOT HOOKED UP TO ARDUINO
    # for plant in our_garden.plants:
    #     # this is for testing
    #     plant.soil_vals = [400,500]
    #     plant.light_vals = [800,1000]
    #     plant.get_soil_state()
    #     plant.get_light_state()

    # UNCOMMENT THIS LINE WHEN WE ARE HOOKED UP TO ARDUINO
    our_garden.collect_data()


class GardenaiApp(App):

    def build(self):
        return GardenaiGame()


if __name__ == '__main__':

    GardenaiApp().run()
    
