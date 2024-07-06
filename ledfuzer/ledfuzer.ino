#define ledNum 8
#define sound_sensor 15

const int ledarray[] = { 2, 0, 4, 16, 17, 5, 18, 19 };
const int IR_pin = 15;
bool led_states[] = { false };

void initLed() {
  for (int i = 0; i < ledNum; ++i) {
    pinMode(ledarray[i], OUTPUT);
  }
  turnOnAll();
  delay(1000);
  turnOffAll();
}

void ledON(int n) {
  led_states[n - 1] = true;
  digitalWrite(ledarray[n - 1], HIGH);
}

void ledOFF(int n) {
  led_states[n - 1] = false;
  digitalWrite(ledarray[n - 1], LOW);
}

void turnOnAll() {
  for (int i = 0; i < ledNum; ++i) {
    ledON(i + 1);
  }
}

void turnOffAll() {
  for (int i = 0; i < ledNum; ++i) {
    ledOFF(i + 1);
  }
}


void setup() {
  initLed();
  pinMode(sound_sensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(sound_sensor), P15_ISR, CHANGE);
  // lehet benne kene hagyni, ez egy interrupt engedelyezese
}

int futo = 1;
bool elert = false;
volatile bool clapped = false;

void P15_ISR() { // lehet benne kene hagyni, ez egy interrupt
  if (digitalRead(sound_sensor) == HIGH) {
    turnOffAll();
    clapped = !clapped;
  }
}


void loop() {
  if (clapped) {
    ledON(futo);
    delay(200);
    ledOFF(futo);
    delay(200);

    if (futo == 8) {
      elert = true;
    }

    if (elert && futo == 1) {
      elert = false;
    }

    if (elert) {
      futo--;
    } else {
      futo++;
    }
  }
  else{
    turnOnAll();
    delay(500);
    turnOffAll();
    delay(500);
  }
}