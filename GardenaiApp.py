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
    our_garden = Garden(2)

    # our_garden.plant1.name
    # our_garden.plant1.type = Plant("Tom Gore", "Thyme")
    our_garden.plants[1].name = "Mary Jane" 
    our_garden.plants[1].herb = "Cilantro"


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
        # this is what we should actually use 
        # [light_vals1, soil_vals1, light_vals2, soil_vals2] = collect_data()
        # return Label(text="TOM GORE:"+"\n"+get_soil_state(get_data_average(soil_vals1))+"\n"+get_light_state(get_data_average(light_vals1))+"\n"+"MARY JANE:"+"\n"+get_soil_state(get_data_average(soil_vals2))+"\n"+get_light_state(get_data_average(light_vals2)))

        # this is for testing without arduino
        # return Label(text="TOM GORE:"+"\n"+get_soil_state((600))+"\n"+get_light_state((900))+"\n"+"MARY JANE:"+"\n"+get_soil_state((800))+"\n"+get_light_state((400)))

        return GardenaiGame()


if __name__ == '__main__':

    GardenaiApp().run()
    
