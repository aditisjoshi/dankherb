
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

        for i in range(0,self.no_plants):
            self.plants.append(Plant(plant_names[i], plant_types[i],self.herbs.get(plant_types[i],None)))



    def collect_data(self):
        # setting up serial port
        ser = serial.Serial('/dev/cu.usbmodem61', 9600,timeout=5)  # open serial port
        #time.sleep(2)

        print("connected to: " + ser.portstr)

        data = []
        data_list = []

        for i in range(0,self.no_plants):
            # light_vals + str(i) = []
            # soil_vals + str(i) = []
            self.plants[i].light_vals = []
            self.plants[i].soil_vals = []

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
            data_list[-1].rstrip()
            #print data_list

        for i,datum in enumerate(data_list):
            plant_no = i / 2
            if (i % 2) == 0:
                self.plants[plant_no].light_vals.append(int(datum))
            else:
                self.plants[plant_no].soil_vals.append(int(datum))

            # light_vals1.append(int(data_list[0]))
            # soil_vals1.append(int(data_list[1]))
            
            # light_vals2.append(int(data_list[2]))
            # soil_vals2.append(int(data_list[3]))

        for plant in self.plants:
            plant.get_soil_state()
            plant.get_light_state()

        return

