from plant import Plant
import serial

# this script creates a garden class for the gui
class Garden(object):

    def __init__(self, no_plants, plant_names, plant_types):
        # initalizing the garden object
        self.no_plants = no_plants
        self.plants = []
        # dictionary of standards for the different herbs
        # [soil min, soil max, sunlight min]
        self.herbs = {"Thyme":[325,650,950], "Cilantro":[325,650,950]}
        # creating plant objects
        for i in range(0,self.no_plants):
            self.plants.append(Plant(plant_names[i], plant_types[i],self.herbs.get(plant_types[i],None)))


    # getting the data from arduino
    def collect_data(self):
        # setting up serial port
        ser = serial.Serial('/dev/cu.usbmodemFD121', 9600,timeout=5)  # open serial port

        print("connected to: " + ser.portstr)

        # creating empty lists to populate later on 
        data = []
        data_list = []
        for i in range(0,self.no_plants):
            self.plants[i].light_vals = []
            self.plants[i].soil_vals = []

        datacollection = True

        while datacollection:
            data.append(ser.readline())
            # if it has collected all necessary data, it turns off reading from the serial monitor
            if (len(data) == 10):
                datacollection = False
            else:
                pass

        # spliting the different values from each other
        for datum in data:
            data_list = datum.split("/")
            data_list[-1].rstrip()
            print data_list

        # depending on when it was printed to the serial monitor, it writes the value to the appropriate plant
        for i,datum in enumerate(data_list):
            plant_no = i / 2
            if (i % 2) == 0:
                self.plants[plant_no].light_vals.append(int(datum))
            else:
                self.plants[plant_no].soil_vals.append(int(datum))

        # getting the states for the plants depending on what the program read from arduino
        for plant in self.plants:
            plant.get_soil_state()
            plant.get_light_state()

        return

