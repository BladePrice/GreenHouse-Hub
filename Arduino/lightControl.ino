//Pins for named component.
const int relayPins[4] = {4, 7, 8, 12};
const int buttonPins[4] = {0, 1, 2, 3};
//For monitoring pin status, also used to flip state on button press.
int lastState[4] = {LOW, LOW, LOW, LOW};

//Variable to suppress prints when pulling a report.
bool suppressPrints = false;
//Flags for button pressing
volatile bool buttonFlag[4] = {false, false, false, false};

//Amount of time in ms before another button press is allowed to be registered; stops flickering of lights.
const unsigned long debounce = 200;
//Stored ms value for comparison
unsigned long lastPress[4] = {0, 0, 0, 0};

void setup() {
	//initialize serial
	Serial.begin(9600);
	//Initialize pin functionalities and ensure relays start off.
	for (int i = 0; i < 4; i++) {
		pinMode(relayPins[i], OUTPUT);
		pinMode(buttonPins[i], INPUT_PULLUP);
		digitalWrite(relayPins[i], LOW);
	}
	//Attaching interrupts to the button pins. Requires an arduino with more >= 4 hardware interupt pins.
	attachInterrupt(digitalPinToInterrupt(buttonPins[0]), buttonInt0, FALLING);
	attachInterrupt(digitalPinToInterrupt(buttonPins[1]), buttonInt1, FALLING);
	attachInterrupt(digitalPinToInterrupt(buttonPins[2]), buttonInt2, FALLING);
	attachInterrupt(digitalPinToInterrupt(buttonPins[3]), buttonInt3, FALLING);
}
//Update function for monitoring the state of the pins. Will only the changed pins to serial. Pi and python expected to keep values stored.
void update() {
	int currentState[4];
	for (int i = 0; i < 4; i++) {
		currentState[i] = digitalRead(relayPins[i]);
	}
	for (int i = 0; i < 4; i++) {
		if (currentState[i] != lastState[i]) {
			//Only prints to serial if not being suppressed - used for refresh button on webpage. **Space for easily splitting in python. 
			if (!suppressPrints) {
				Serial.print(i + 1);
				Serial.print(" ");
				Serial.println(currentState[i]);
			}
			//logs the read state as lastState. Used to flip on button press.
			lastState[i] = currentState[i];
		}
	}
}
//Used for refresh button on webpage. Prints all states in relay # order. **
void report() {
	for (int i = 0; i < 4; i++) {
		Serial.print(i + 1);
		Serial.print(" ");
		Serial.println(lastState[i]);
	}
}
//Respective button interupt turns respective button flag true for later use. 
void buttonInt0() {
	buttonFlag[0] = true;
}
void buttonInt1() {
	buttonFlag[1] = true;
}
void buttonInt2() {
	buttonFlag[2] = true;
}
void buttonInt3() {
	buttonFlag[3] = true;
}
//Monitors serial and buttons for respective events to flip bits.
void loop() {
	//Ensures the latest pins are sent before enacting commands. Might be best to put at the end? 
	update();
	//looking for a serial connection and pulling one character at a time off serial buffer. 
	if (Serial.available()) {
		char command = Serial.read();

		switch (command) {
			case '1': digitalWrite(relayPins[0], HIGH); break;
			case '2': digitalWrite(relayPins[1], HIGH); break;
			case '3': digitalWrite(relayPins[2], HIGH); break;
			case '4': digitalWrite(relayPins[3], HIGH); break;

			case '5': digitalWrite(relayPins[0], LOW); break;
			case '6': digitalWrite(relayPins[1], LOW); break;
			case '7': digitalWrite(relayPins[2], LOW); break;
			case '8': digitalWrite(relayPins[3], LOW); break;

			//reload function from webpage. Supresses prints inside of update as the report is about to send an entire report of all states. 
			case 'R':
			suppressPrints = true;
			update();
			suppressPrints = false;
			report();
			break;
		}
	}
	//monitors for button flag change
	for (int i = 0; i < 4; i++) {
		if (buttonFlag[i]) {
			//set button flag back
			buttonFlag[i] = false;
			//ensures button isn't bouncing
			if (millis() - lastPress[i] > debounce) {
				//sets new figure for comparing button bounce
				lastPress[i] = millis();
				//flips appropriate relay's state
				digitalWrite(relayPins[i], !lastState[i]);
			}
		}
	}
}