const int switchPins[] = {16, 17, 5};  // Array of switch pins
const unsigned long debounceDelay = 50;
static int previousSwitchState[3] = {0};  // Array to store previous switch states
static unsigned long previousMillis[3] = {0}; // Array to store previous millis for each switch

void setupSwitches() {
  for (int i = 0; i < 3; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }
}

void checkSwitchChange()
{
  for (int i = 0; i < 3; i++) {
    int switchState = !digitalRead(switchPins[i]);  // Read switch state
    unsigned long currentMillis = millis();

    // Check if enough time has passed since last change
    if (currentMillis - previousMillis[i] >= debounceDelay) {
      // Check if the switch state has changed
      if (switchState != previousSwitchState[i]) {
        previousSwitchState[i] = switchState;  // Update previous switch state
      }
      // Update previous millis
      previousMillis[i] = currentMillis;
    }
  }

  muted = !previousSwitchState[0];
}