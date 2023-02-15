#include "bot.h"


namespace Robot {
    /*  1         0
     *  2         3
    */


    void Bot::init() {
        for (auto &motor: this->motors) {
            pinMode(motor.motor, OUTPUT);
            pinMode(motor.pwm, OUTPUT);
        }
        pinMode(LED, OUTPUT);
        digitalWrite(LED, LOW);
        ps2.begin(115200);
        Serial.begin(9600);
        Serial.println("Bot initialized");
    }

    void Bot::read_joystick() {
        Serial.println(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS));
        Serial.println(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS));
    }

    void Bot::rotate(int v, boolean reverse) {
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) {
                digitalWrite(motors[i].motor, reverse);
                analogWrite(motors[i].pwm, v);
            } else {
                digitalWrite(motors[i].motor, !reverse);
                analogWrite(motors[i].pwm, v);
            }
        }
    }

    void Bot::linear_y(int v, boolean reverse) {
        for (int i = 0; i < 4; i++) {
            if (i == 2 || i == 3) {
                digitalWrite(motors[i].motor, !reverse);
                analogWrite(motors[i].pwm, v);
            } else {
                digitalWrite(motors[i].motor, reverse);
                analogWrite(motors[i].pwm, v);
            }
        }
    }

    void Bot::kill() {
        for (auto &motor: motors) {
            analogWrite(motor.pwm, 0);
        }
    }

    void Bot::linear_x(int v, boolean reverse) {
        for (int i = 0; i < 4; i++) {
            if (i == 1 || i == 2) {
                digitalWrite(motors[i].motor, reverse);
                analogWrite(motors[i].pwm, v);
            } else {
                digitalWrite(motors[i].motor, !reverse);
                analogWrite(motors[i].pwm, v);
            }
        }
    }

    void Bot::toggle_led() {
        digitalWrite(LED, !digitalRead(LED));
    }

    void Bot::run() {
        Serial.println("Bot running");
        if (!ps2.readButton(PS2_UP)) {
            Serial.println("Forward");
            linear_y(SPEED, false);
        } else if (!ps2.readButton(PS2_DOWN)) {
            Serial.println("Backward");
            linear_y(SPEED, true);
        } else if (!ps2.readButton(PS2_LEFT)) {
            Serial.println("Left");
            linear_x(SPEED, false);
        } else if (!ps2.readButton(PS2_RIGHT)) {
            Serial.println("Right");
            linear_x(SPEED, true);
        } else if (!ps2.readButton(PS2_LEFT_1)) {
            Serial.println("Rotate left");
            rotate(SPEED, false);
        } else if (!ps2.readButton(PS2_RIGHT_1)) {
            Serial.println("Rotate right");
            rotate(SPEED, true);
        } else if (!ps2.readButton(PS2_TRIANGLE)) {
            Serial.println("Toggle LED");
            toggle_led();
        } else {
            kill();
        }
    }

    Bot::Bot(MOTOR **motor_data, int speed, int rx, int tx) {
        if (motor_data != nullptr) {
            for (int i = 0; i < 4; i++) {
                motors[i] = *motor_data[i];
            }
        }
        SPEED = speed;
        ps2 = Cytron_PS2Shield(rx, tx);
    }
}