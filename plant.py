# this script creates a plant class for the gui
class Plant(object):

    def __init__(self, name, herb, standards=[325,650,.9]):
        # initalizing the plant object with a name and standards
        self.name = name
        self.herb = herb
        # un-packing a list of standards depending on the herb 
        self.perfect_soil_min = standards[0];
        self.perfect_soil_max = standards[1];
        self.perfect_sunlight_min = standards[2];

    # getting the averages of the light and soil values read from the arduino
    def get_data_average(self,data):
        return sum(data)/len(data)

    # writing the soil state depending on the values gathered and the standards for that plant
    def get_soil_state(self):
        soil_avg = self.get_data_average(self.soil_vals)
        if soil_avg < self.perfect_soil_min:
            self.soil_status = "Your soil is too dry. More moisture please."
            return 

        elif soil_avg>=self.perfect_soil_min and soil_avg<=self.perfect_soil_max:
            self.soil_status = "Your soil is perfect. You are perfect. Keep it up. ;)"
            return 

        else:
            self.soil_status = "Your soil is too moist. Please cool it with the watering."
            return 

    # writing the light state depending on the values gathered and the standards for that plant
    def get_light_state(self):
        light_avg = self.get_data_average(self.light_vals)
        if light_avg < self.perfect_sunlight_min:
            self.light_status = "There is not enough sunlight. Get lit."
            return 

        self.light_status = "The light shines brightly."
        return 

    # a method to change the plant name depending on what the user inputs
    def writeplantname(self,new_name):
        self.name = new_name

    # a method to change the plant type depending on what the user inputs
    def writeplanttype(self,new_type):
        self.type = new_type