

# this script creates a plant class for the gui
class Plant(object):

    def __init__(self, name, herb):
        # initalizing the plant object

        self.name = name
        self.herb = herb

        self.perfect_soil_min = 325;
        self.perfect_soil_max = 650;
        self.perfect_sunlight_min = 950;

        # this is for testing
        self.soil_vals = [400,500]
        self.light_vals = [800,1000]


    def get_data_average(self,data):
        return sum(data)/len(data)


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


    def get_light_state(self):
        light_avg = self.get_data_average(self.light_vals)
        if light_avg < self.perfect_sunlight_min:
            self.light_status = "There is not enough sunlight. Get lit."
            return 

        self.light_status = "The light shines brightly."
        return 