import json
import time
from datetime import datetime

#Declare globals
FILE = "settings.json"
unmod = {}
in_use = {}

#Function to convert stringed time to minutes after midnight
def time_to_minutes(time_string):
  #Splits string and declares each half
  hours, minutes = map(int, time_string.split(':'))
  #Mathmatical!
  return hours * 60 + minutes


#Loadin' the file
def load_file():
  #Opens the file in read
  with open(FILE, "r") as f:
    global in_use
    in_use = json.load(f)
    #Adjust the json values to ints and partially all to minutes
    for tree in in_use:
      in_use[tree]['time'] = time_to_minutes(in_use[tree]['time'])
      in_use[tree]['length'] = int(in_use[tree]['length'])
    print("File loaded...")

#Reads saved json and compares the file to the loaded content. 
def file_compare():
  #Opens the unmoddified file in read for comparison
  with open(FILE, "r") as g:
    global unmod
    unmod = json.load(g)
    #adjust the json like we do on initial load
    for tree in unmod:
      unmod[tree]['time'] = time_to_minutes(unmod[tree]['time'])
      unmod[tree]['length'] = int(unmod[tree]['length'])
  #Checks if settings file has changed
  #Eventually will have subprocess to force reload upon save button press
  if in_use != unmod:
    unmod = in_use
    print("File Updated...")
    return False
  return True
  print("File passed...")

#Fetches the current time in minutes after midnight
def local_time():
  return datetime.now().hour * 60 + datetime.now().minute

#Function for physical light control.
def light_control(name, toggle, time, length):

  #If lights are to be on, they will
  if toggle == True:
    end_time = length * 60 + time
    #Prints for debug. Note: Toggle being false results in these not being printed.
    #print(end_time)
    #print(local_time())
    #Check if current time falls within activation schedule and turn the lights on if so
    if time <= local_time() <= end_time:
      #For all following prints containing {name}*:
      #they will eventually be commands over serial to an Arduino.
      print(f"Turn the light on for {name}") 
      #Turns light off outside of time
    else:
      print(f"Turn the light off for {name}")
  #Verify that the light is off if it's supposed to be. 
  #I don't like my warning for the lights being off. 
  #I think I'll eventually have a live indicator on the webpage
  else:
    print(f"Turn the light off for {name}")
    #Except this one*
    print(f"!!! LIGHT {name} IS NOT ON !!!")

#Main program
if __name__ == "__main__":
  #initially loads the settings file
  load_file()
  while True:
    #For each table in the settings, we send all the data to light control.
    for name, settings in in_use.items():
      light_control(name, **settings)
    #Don't really like that it fetches every minute. Again, we'll have a save push thingy eventually
    file_compare()
    print(datetime.now())
    time_left = 60 - datetime.now().second
    time.sleep(time_left)
