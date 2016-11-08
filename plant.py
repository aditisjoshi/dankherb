

# this script creates a plant class for the gui
class Plant(object):

    def __init__(self, name, herb, standards):
        # initalizing the plant object

        self.name = name
        self.herb = herb

        self.perfect_soil_min = standards[0];
        self.perfect_soil_max = standards[1];
        self.perfect_sunlight_min = standards[2];


    # def update_soil_standards(self,soil_min,soil_max):
    #     self.perfect_soil_min = soil_min
    #     self.perfect_soil_max = soil_max


    # def update_light_standards(self,sunlight_min):
    #     self.perfect_sunlight_min = sunlight_min


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