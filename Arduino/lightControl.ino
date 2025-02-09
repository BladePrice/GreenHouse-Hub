const int relayPins[4] = {4, 7, 8, 12};
const int buttonPins[4] = {0, 1, 2, 3};
int lastState[4] = {LOW, LOW, LOW, LOW};

bool suppressPrints = false;
volatile bool buttonFlag[4] = {false, false, false, false};

const unsigned long debounce = 200;
unsigned long lastPress[4] = {0, 0, 0, 0};

void setup() {
	Serial.begin(9600);
	for (int i = 0; i < 4; i++) {
		pinMode(relayPins[i], OUTPUT);
		pinMode(buttonPins[i], INPUT_PULLUP);
		digitalWrite(relayPins[i], LOW);
	}
	attachInterrupt(digitalPinToInterrupt(buttonPins[0]), buttonInt0, FALLING);
	attachInterrupt(digitalPinToInterrupt(buttonPins[1]), buttonInt1, FALLING);
	attachInterrupt(digitalPinToInterrupt(buttonPins[2]), buttonInt2, FALLING);
	attachInterrupt(digitalPinToInterrupt(buttonPins[3]), buttonInt3, FALLING);
}
void update() {
	int currentState[4];
	for (int i = 0; i < 4; i++) {
		currentState[i] = digitalRead(relayPins[i]);
	}
	for (int i = 0; i < 4; i++) {
		if (currentState[i] != lastState[i]) {
			if (!suppressPrints) {
				Serial.print(i + 1);
				Serial.print(" ");
				Serial.println(currentState[i]);
			}
			lastState[i] = currentState[i];
		}
	}
}
void report() {
	for (int i = 0; i < 4; i++) {
		Serial.print(i + 1);
		Serial.print(" ");
		Serial.println(lastState[i]);
	}
}
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
void loop() {
	update();
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

			case 'R':
			suppressPrints = true;
			update();
			suppressPrints = false;
			report();
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (buttonFlag[i]) {
			buttonFlag[i] = false;
			if (millis() - lastPress[i] > debounce) {
				lastPress[i] = millis();
				digitalWrite(relayPins[i], !lastState[i]);
			}
		}
	}
}