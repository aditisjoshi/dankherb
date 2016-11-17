import serial
import time
import math

perfect_soil_min = 325;
perfect_soil_max = 650;
perfect_sunlight_min = 950;

def collect_data():
    # setting up serial port
    ser = serial.Serial('/dev/cu.usbmodem61', 9600,timeout=5)  # open serial port
    #time.sleep(2)

    print("connected to: " + ser.portstr)

    data = []
    data_list = []
    light_vals = []
    soil_vals = []
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

        light_vals.append(int(data_list[0]))
        soil_vals.append(int(data_list[1].rstrip()))

    return [light_vals, soil_vals]

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


if __name__ == '__main__':
    [light_vals, soil_vals] = collect_data()
    print get_soil_state(get_data_average(soil_vals))
    print get_light_state(get_data_average(light_vals))

