#include "Cytron_PS2Shield.h"
#include <Arduino.h>


struct MOTOR {
    int motor;
    int pwm;
};
MOTOR motor[4] = {{4,  5},
                  {7,  6},
                  {8,  9},
                  {10, 11}};
const int SPEED = 255;
const int LED = 13;
Cytron_PS2Shield ps2(2, 3);


void linear_y(int v, boolean reverse);

void linear_x(int v, boolean reverse);

void rotate(boolean direction);

void toggle_led();


void setup() {
    for (auto &i: motor) {
        pinMode(i.motor, OUTPUT);
        pinMode(i.pwm, OUTPUT);
    }
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    ps2.begin(115200);
    Serial.begin(9600);
}

void loop() {
    if (!ps2.readButton(PS2_UP)) {
        linear_y(SPEED, false);
    } else if (!ps2.readButton(PS2_DOWN)) {
        linear_y(SPEED, true);
    } else if (!ps2.readButton(PS2_LEFT)) {
        linear_x(SPEED, false);
    } else if (!ps2.readButton(PS2_RIGHT)) {
        linear_x(SPEED, true);
    } else if (!ps2.readButton(PS2_LEFT_1)) {
        rotate(true);
    } else if (!ps2.readButton(PS2_RIGHT_1)) {
        rotate(false);
    } else if (!ps2.readButton(PS2_TRIANGLE)) {
        toggle_led();
    } else {
        for (auto &i: motor) {
            analogWrite(i.pwm, 0);
        }
    }
}


void linear_y(int v, boolean reverse) {
    boolean direction = reverse != 1;
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            digitalWrite(motor[i].motor, direction);
            analogWrite(motor[i].pwm, v);
        } else {
            analogWrite(motor[i].pwm, 0);
        }
    }
}

void linear_x(int v, boolean reverse) {
    boolean direction = reverse != 1;
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 1) {
            digitalWrite(motor[i].motor, direction);
            analogWrite(motor[i].pwm, v);
        } else {
            analogWrite(motor[i].pwm, 0);
        }
    }
}

void rotate(boolean direction) {
    for (int i = 0; i < 4; i++) {
        if (i > 0 && i < 3) {
            digitalWrite(motor[i].motor, direction);
            analogWrite(motor[i].pwm, SPEED);
        } else {
            digitalWrite(motor[i].motor, !direction);
            analogWrite(motor[i].pwm, SPEED);
        }
    }
}

void toggle_led() {
    digitalWrite(LED, !digitalRead(LED));
}
