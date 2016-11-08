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
    our_garden = Garden(2,["Tom Gore", "Mary Jane"], ["Thyme", "Cilantro"])

    # FOR TESTING WHEN WE ARE NOT HOOKED UP TO ARDUINO
    for plant in our_garden.plants:
        plant.get_soil_state()
        plant.get_light_state()


    # UNCOMMENT THIS LINE WHEN WE ARE HOOKED UP TO ARDUINO
    # our_garden.collect_data()


class HomeScreen(GridLayout):

    def __init__(self, **kwargs):
        # super(HomeScreen, self).__init__(**kwargs)
        # self.cols = 2
        # self.rows = 3
        # self.add_widget(Label(Text="Plant Name:"))
        # self.add_widget(Label(Text="Tom Gore"))
        # self.add_widget(Label(Text="Plant Type:"))
        # self.add_widget(Label(Text="Thyme"))
        pass 


class GardenaiApp(App):

    def build(self):
        return GardenaiGame()


if __name__ == '__main__':

    GardenaiApp().run()
    
