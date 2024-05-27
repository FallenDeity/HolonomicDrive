#ifndef HOLONOMIC_DRIVES_THREE_WHEEL_H
#define HOLONOMIC_DRIVES_THREE_WHEEL_H

#include "base.h"

#include "Arduino.h"


namespace ThreeWheel {
    class ThreeWheel : public BaseDrive::Base {
    public:
        ThreeWheel(BaseDrive::Motor *motors, int numMotors) : BaseDrive::Base(motors, numMotors) {
            if (numMotors != ThreeWheel::ThreeWheel::TOTAL_MOTORS) {
                Serial.println("Invalid number of motors for ThreeWheel");
                exit(1);
            }
        }

        ThreeWheel() = default;

        int *getSpeeds(int *arr, double x, double y) override;

        int totalMotors() override;

    private:
        static constexpr int TOTAL_MOTORS = 3;
    };
}// namespace ThreeWheel

#endif//HOLONOMIC_DRIVES_THREE_WHEEL_H
