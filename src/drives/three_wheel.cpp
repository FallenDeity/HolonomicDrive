#include "three_wheel.h"

#include <math.h>


namespace ThreeWheel {
    int *ThreeWheel::getSpeeds(int *arr, double x, double y) {
        /*
                       ---->
                       wheel_1
                       /    \
                      /      \
                     /        \
                    /          \
             ↗  wheel_3 ---- wheel_2  ↙
        */
        double angle = atan2(x, y);
        double speed = sqrt(x * x + y * y) * ThreeWheel::ThreeWheel::MAX_SPEED;
        arr[0] = static_cast<int>(speed * -sin(angle));
        arr[1] = static_cast<int>(speed * -sin(M_PI / 3 - angle));
        arr[2] = static_cast<int>(speed * sin(M_PI / 3 + angle));
        return arr;
    }

    int ThreeWheel::totalMotors() {
        return ThreeWheel::ThreeWheel::TOTAL_MOTORS;
    }
}// namespace ThreeWheel
