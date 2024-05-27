#ifndef HOLONOMIC_DRIVES_BASE_H
#define HOLONOMIC_DRIVES_BASE_H

#include <Arduino.h>

namespace BaseDrive {
    class Motor {
    public:
        int pwm;
        int dir;

        Motor(int pwm, int dir);

        void setSpeed(int speed) const;

        void stop() const;
    };

    class Base {
    public:
        explicit Base() = default;

        explicit Base(Motor *motors, int numMotors) : motors(motors), numMotors(numMotors) {}

        virtual ~Base() = default;

        virtual int *getSpeeds(int *arr, double x, double y) = 0;

        virtual int totalMotors() = 0;

        void setSpeed(int *speeds);

        void stop();

    protected:
        Motor *motors{};
        int numMotors{};

        static constexpr int MAX_SPEED = 255;
    };
}// namespace BaseDrive

#endif//HOLONOMIC_DRIVES_BASE_H
