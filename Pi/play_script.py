import json
import time

file = "settings.json"

def filecheck():

  with open(file, "r") as g:
  	unmod = json.load(g)

  with open(file, "r") as f:
  	modded = json.load(f)
  modded['tree2']['toggle'] = True

  if modded == unmod:
  	print(True)
  else:
  	print(False)







def light_control(name, toggle, time, length):
	#If lights are to be on, they will
	if toggle = True
		for