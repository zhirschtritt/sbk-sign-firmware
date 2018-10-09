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

bool signLedsOn = false;
int toggleOff();
int toggleOn();
int toggleSignLeds(const char *event, const char *data);

void setup()
  Particle.publish("sbkSign/lightState", "off", 60, PRIVATE);
  Particle.subscribe("sbkSign/toggleLight", toggleSignLeds, MY_DEVICES);
  Particle.variable("lightState", signLedsOn);
}

void loop(){
  if (signLedsOn) {
    led.fade(colors, 3, 3000);
  } else {
    led.off();
  }
}

int toggleSignLeds(const char *event, const char *data) {
  if (signLedsOn) {
    toggleOff();
    return 1;
  } else {
    toggleOn();
    return 1;
  }
}

int toggleOn(){
  signLedsOn = true;
  Particle.publish("sbkSign/lightState","on", 60, PRIVATE);
  return 1;
}

int toggleOff(){
  signLedsOn = false;
  Particle.publish("sbkSign/lightState", "off", 60, PRIVATE);
  return 1;
}