#include "x_drive.h"

#include <math.h>


namespace XDrive {
    int *XDrive::getSpeeds(int *arr, double x, double y) {
        /*
                               angle = 0
                             x = 0, y = 1
                     wheel_1 ------------ wheel_2
                        |                    |
        angle = 270     |                    |    angle = 90
        x = -1, y = 0   |                    |  x = 1, y = 0
                        |                    |
                    wheel_4 ------------ wheel_3
                               angle = 180
                            x = 0, y = -1
         */
        double angle = atan2(x, y);
        double speed = sqrt(x * x + y * y) * XDrive::XDrive::MAX_SPEED;
        arr[0] = static_cast<int>(speed * sin(angle + M_PI / 4));
        arr[1] = static_cast<int>(speed * cos(angle + M_PI / 4));
        arr[2] = static_cast<int>(speed * sin(angle + M_PI / 4));
        arr[3] = static_cast<int>(speed * cos(angle + M_PI / 4));
        return arr;
    }

    int XDrive::totalMotors() {
        return XDrive::XDrive::TOTAL_MOTORS;
    }
}// namespace XDrive
