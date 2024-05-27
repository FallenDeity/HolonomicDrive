#ifndef HOLONOMIC_DRIVES_X_DRIVE_H
#define HOLONOMIC_DRIVES_X_DRIVE_H

#include "base.h"

#include "Arduino.h"


namespace XDrive {
    class XDrive : public BaseDrive::Base {
    public:
        XDrive(BaseDrive::Motor *motors, int numMotors) : BaseDrive::Base(motors, numMotors) {
            if (numMotors != XDrive::XDrive::TOTAL_MOTORS) {
                Serial.println("Invalid number of motors for XDrive");
                exit(1);
            }
        }

        XDrive() = default;

        int *getSpeeds(int *arr, double x, double y) override;

        int totalMotors() override;

    private:
        static constexpr int TOTAL_MOTORS = 4;
    };
}// namespace XDrive

#endif//HOLONOMIC_DRIVES_X_DRIVE_H
