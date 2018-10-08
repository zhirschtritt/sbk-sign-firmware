#include "Particle.h"
#include "rgb-controls/rgb-controls.h"

using namespace RGBControls;

#define REDPIN D0
#define GREENPIN D2
#define BLUEPIN D1

Led led(REDPIN, GREENPIN, BLUEPIN);

Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);

Color colors[3] = {red, green, blue};

retained bool ledState = false;
int toggleOff();
int toggleOn();
int toggleLED(const char *event, const char *data);

int fadeState = 0;

void setup(){
  Particle.subscribe("sbkSign/toggleLight", toggleLED, MY_DEVICES);
  Particle.variable("lightState", ledState);
}

void loop(){
  if (fadeState == 0) {
    led.off();
  } else if (fadeState == 1) {
    led.fade(colors, 3, 3000);
  }
}

int toggleLED(const char *event, const char *data) {
  if (ledState) {
    if (toggleOff()) ledState = false;
    return 1;
  } else {
    if (toggleOn()) ledState = true;
    return 1;
  }
}

int toggleOn(){
  fadeState = 1;
  Particle.publish("sbkSign/lightState","on", 60, PRIVATE);
  return 1;
}

int toggleOff(){
  fadeState = 0;
  Particle.publish("sbkSign/lightState", "off", 60, PRIVATE);
  return 1;
}