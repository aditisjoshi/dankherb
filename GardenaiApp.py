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

    our_garden = Garden(4,["Tom Gore", "Mary Jane", "Marvin", "December"], ["Thyme", "Cilantro", "Thyme", "Cilantro"])


    # FOR TESTING WHEN WE ARE NOT HOOKED UP TO ARDUINO
    for plant in our_garden.plants:
        # this is for testing
        plant.soil_vals = [300,400,500,600]
        plant.light_vals = [800,900,1000,1100]
        plant.get_soil_state()
        plant.get_light_state()

    # UNCOMMENT THIS LINE WHEN WE ARE HOOKED UP TO ARDUINO
    #our_garden.collect_data()


class GardenaiApp(App):

    def build(self):
        w = GardenaiGame()
        w.plant0name = w.our_garden.plants[0].name
        w.plant1name = w.our_garden.plants[1].name
        w.plant2name = w.our_garden.plants[2].name
        w.plant3name = w.our_garden.plants[3].name
        w.plant0type = w.our_garden.plants[0].herb
        w.plant1type = w.our_garden.plants[1].herb
        w.plant2type = w.our_garden.plants[2].herb
        w.plant3type = w.our_garden.plants[3].herb
        return w


if __name__ == '__main__':

    GardenaiApp().run()
    
