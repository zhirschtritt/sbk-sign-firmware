#include "Particle.h"

#define BUTTONPIN D6
#define INDICATORLED D7

bool ledIndicatorOn = false;
int handleSignLightState(const char *event, const char *data);

void setup() {
  pinMode(INDICATORLED, OUTPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);

  Particle.subscribe("sbkSign/lightState", handleSignLightState, MY_DEVICES);
}

void loop() {
  if (digitalRead(BUTTONPIN) == LOW) {
    Particle.publish("sbkSign/toggleLight", PRIVATE);
    delay(200);
  } 

  if (ledIndicatorOn) {
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(D7, LOW);
  }
}

int handleSignLightState(const char *event, const char *data) {
  if (strcmp(data, "on") == 0) {
    ledIndicatorOn = true;
    return 1;
  } else {
    ledIndicatorOn = false;
    return 1;
  }
}