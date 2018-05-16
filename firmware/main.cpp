#include "Particle.h"
#include "rgb-controls/rgb-controls.h"

using namespace RGBControls;

#define REDPIN D0
#define GREENPIN D1
#define BLUEPIN D2

Led led(REDPIN, GREENPIN, BLUEPIN);

Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);

Color colors[3] = {red, green, blue};

retained bool ledState = false;
int toggleOff();
int toggleOn();
int toggleLED(String command);

void setup(){
  Particle.function("toggleLights", toggleLED);
}

void loop(){}

int toggleLED(String command) {
  if (ledState) {
    if (toggleOff()) ledState = false;
    return 1;
  } else {
    if (toggleOn()) ledState = true;
    return 1;
  }
}

int toggleOn(){
  led.fade(colors, 3, 3000);
  return 1;
}

int toggleOff(){
  led.off();
  return 1;
}