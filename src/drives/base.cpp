#include "base.h"


namespace BaseDrive {
    Motor::Motor(int pwm, int dir) : pwm(pwm), dir(dir) {
        pinMode(pwm, OUTPUT);
        pinMode(dir, OUTPUT);
    }

    void Motor::setSpeed(int speed) const {
        if (speed > 0) {
            digitalWrite(dir, HIGH);
            analogWrite(pwm, speed);
        } else if (speed < 0) {
            digitalWrite(dir, LOW);
            analogWrite(pwm, -speed);
        } else {
            stop();
        }
    }

    void Motor::stop() const {
        digitalWrite(pwm, LOW);
    }

    void Base::setSpeed(int *speeds) {
        for (int i = 0; i < this->totalMotors(); i++) {
            motors[i].setSpeed(speeds[i]);
        }
    }

    void Base::stop() {
        for (int i = 0; i < this->totalMotors(); i++) {
            motors[i].stop();
        }
    }
}// namespace BaseDrive
