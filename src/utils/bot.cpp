#include "bot.h"


namespace Robot {


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

    void Bot::linear_x(int v, boolean reverse) {
        boolean direction = reverse != 1;
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 1) {
                digitalWrite(motors[i].motor, direction);
                analogWrite(motors[i].pwm, v);
            } else {
                analogWrite(motors[i].pwm, 0);
            }
        }
    }

    void Bot::linear_y(int v, boolean reverse) {
        boolean direction = reverse != 1;
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) {
                digitalWrite(motors[i].motor, direction);
                analogWrite(motors[i].pwm, v);
            } else {
                analogWrite(motors[i].pwm, 0);
            }
        }
    }

    void Bot::rotate(boolean direction) {
        for (int i = 0; i < 4; i++) {
            if (i > 0 && i < 3) {
                digitalWrite(motors[i].motor, direction);
                analogWrite(motors[i].pwm, SPEED);
            } else {
                digitalWrite(motors[i].motor, !direction);
                analogWrite(motors[i].pwm, SPEED);
            }
        }
    }

    void Bot::toggle_led() {
        digitalWrite(LED, !digitalRead(LED));
    }

    void Bot::run() {
        Serial.println("Bot running");
        Serial.println(ps2.readAllButton());
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
            for (auto &motor: motors) {
                analogWrite(motor.pwm, 0);
            }
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