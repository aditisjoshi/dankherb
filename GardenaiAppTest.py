import serial
import time
import math

import kivy
kivy.require('1.0.6') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout



perfect_soil_min = 325;
perfect_soil_max = 650;
perfect_sunlight_min = 950;



def collect_data():
    # setting up serial port
    ser = serial.Serial('/dev/cu.usbmodemFA131', 9600,timeout=5)  # open serial port
    #time.sleep(2)

    print("connected to: " + ser.portstr)

    data = []
    data_list = []
    light_vals1 = []
    soil_vals1 = []
    light_vals2 = []
    soil_vals2 = []
    datacollection = True

    while datacollection:
        # print ser.readline()
        data.append(ser.readline())

        if (len(data) == 10):
            datacollection = False
        else:
            pass


    for datum in data:
        data_list = datum.split("/")
        #print data_list

        light_vals1.append(int(data_list[0]))
        soil_vals1.append(int(data_list[1]))
        light_vals2.append(int(data_list[2]))
        soil_vals2.append(int(data_list[3]).rstip())

    return [light_vals1, soil_vals1, light_vals2, soil_vals2]

def get_data_average(data):
    return sum(data)/len(data)

def get_soil_state(soil_avg):
    if soil_avg < perfect_soil_min:
        return "Your soil is too dry. More moisture please."

    elif soil_avg>=perfect_soil_min and soil_avg<=perfect_soil_max:
        return "Your soil is perfect. You are perfect. Keep it up. ;)"

    else:
        return "Your soil is too moist. Please cool it with the watering."

def get_light_state(light_avg):
    if light_avg < perfect_sunlight_min:
        return "There is not enough sunlight. Get lit."

    return "The light shines brightly."



class HomeScreen(GridLayout):

    def __init__(self, **kwargs):
        super(HomeScreen, self).__init__(**kwargs)
        self.cols = 2
        self.add_widget(Label(Text="Plant Name:"))
        self.add_widget(Label(Text="Tom Gore"))
        self.add_widget(Label(Text="Plant Type:"))
        self.add_widget(Label(Text="Thyme"))

class GardenaiApp(App):

    def build(self):
        # [light_vals, soil_vals] = collect_data()
        # return Label(text=get_soil_state(get_data_average(soil_vals))+"\n"+get_light_state(get_data_average(light_vals)))

        return Label(text="TOM GORE:"+"\n"+get_soil_state((600))+"\n"+get_light_state((900))+"\n"+"MARY JANE:"+"\n"+get_soil_state((800))+"\n"+get_light_state((400)))



if __name__ == '__main__':

    GardenaiApp().run()
    
