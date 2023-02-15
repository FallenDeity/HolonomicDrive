#ifndef HOLONOMIC_BOT_H
#define HOLONOMIC_BOT_H
#pragma once

#include <Arduino.h>
#include "Cytron_PS2Shield.h"

namespace Robot {
    struct MOTOR {
        int motor;
        int pwm;
    };

    class Bot {
    public:
        explicit Bot(MOTOR *motor_data[4] = nullptr, int speed = 255, int rx = 2, int tx = 3);

        void linear_x(int v, boolean reverse);

        void linear_y(int v, boolean reverse);

        void rotate(boolean direction);

        void init();

        void run();

        static void toggle_led();

    private:
        int SPEED = 255;
        static const int LED = 13;
        MOTOR motors[4] = {{4,  5},
                           {7,  6},
                           {8,  9},
                           {10, 11}};
        Cytron_PS2Shield ps2;
    };
}
#endif //HOLONOMIC_BOT_H
