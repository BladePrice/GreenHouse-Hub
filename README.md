# Introduction
This is the documentation of the creation of my greenhouse. This is my first dive into the programming world, I'm sure there will be inefficenies, but it's mine. This is a small greenhouse you can buy from Amazon, but I'm sure the same thing could be easily scaled up with the appropriate hardware. I'm not going to link things, I have very little intention to maintain the readme once it's done and I do not care to update links if they eventually stop working. I'll talk about how I set up my hardware, but this is not a how-to. I'm not going to be telling you what to put where or how to do it. I assume if this project interests you, you are plenty capable of figuring things out - I mean I did! This being said, I feel it's necessary for the obligitory warnings. *Do not play with what you do not understand* the power supply I use is not in a housing. For hopefully obvious reasons, you should not be poking around the power supply, or really anything, when it's live. 

Notes left with an * are to have updates when the system is live.

# Hardware
* Ohuhu Mini Greenhouse -- Amazon
* Arduino Leonardo -- Arduino      *Leonardo, or an arduino with four hardware interupts is required*
* Headerless Raspberry Pi Zero 2 W -- adafruit
* Mean Well USA Inc. PID-250B -- Digikey
  * Voltage: 24V/5V
  * Rated Current: 9.4A/5A
* Same Sky DC Axial Fan -- Digikey (2223-CFM-9225GB-270-585-ND)
* Cantherm Thermostat (35C) -- Digikey (317-1501-ND)
* namunanee Outdoor Electrical Box -- Amazon       *This thing kinda sucked. I'll explain more, but Only the box is okay*
  * Cold Rolled Steal plate
  * IP65 Waterproof
  * Temp Regulated
* LBW 2024 Grow Lights Tri-Head -- Amazon
* AITRIP Capacitive Soil Moisture Sensor -- Amazon

# Setup
We'll be discussing the various hardware setups. I've modified nearlly every piece and this is where I'll be discussing what I did. If the item is not listed it was not modified.
### Arduino & Pi
Originally, I soldered wires to the pads on the back of the headered raspberry pi, trying to leave the headers be. This did not last long. I ended up ripping the entire 5V pad from the Pi, resulting in a now non-operational micro usb power port. I soldered the wire to the 5V GPIO pin and hated how it looked, so I ened up buying a new headerless Pi Zero 2 off Amazon.

I soldered wires onto the GPIO pins, opting to go through the GPIO pins from the back so the wires can run beneath it.

Onto the back of the Arduino I soldered wires to the barrel plug. 

### PID-250B
I didn't modify the P/S in anyway. A 14AWG power cord supplies AC to the unit. 18AWG wires are used for the lights and arduinos. The fan is pinned in parallel with one of the lights. Besides the fan, each component was given it's own pins to avoid requiring a bus. 

### namunanee Outdoor Electrocal Box
The temp switch was not rated for DC current. I'm sure it'd be fine at the small DC current the fan would run through it, but instead of having to get a dc/dc converter to step down to 12V, I opted to get a new fan and a DC rated thermal switch. Additionally, this allowed me to get a fan with a somewhat decent static pressure. 

I had a coworker 3D print me some stand offs to mount the units to. I opted to have the Arduino and Raspberry Pi mounted below the P/S. THe P/S sits just above the air vents. I opted for the large heat sink to be mounted downwards, in hopes the fan will pull in enough air to cool*

I de-pinned the new fan connector and soldered the temp switch it inline to the fan.

Grounds were abundently used. The P/S has grounded mounting holes, grounding wires were run from each of the P/S mounts to the case and from the case to the mounting board.

