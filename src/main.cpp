#include "Arduino.h"
#include "utils/bot.h"


Robot::Bot bot = Robot::Bot();

void setup() {
    bot.init();
}


void loop() {
    bot.run();
}
