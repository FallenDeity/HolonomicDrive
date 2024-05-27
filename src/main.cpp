#include <Arduino.h>
#include <SoftwareSerial.h>

#include "base.h"
#include "x_drive.h"

XDrive::XDrive xDrive;
SoftwareSerial xDriveSerial(10, 11);

int speeds[4];

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing X-Drive...");
    BaseDrive::Motor motors[] = {
            BaseDrive::Motor(3, 2),
            BaseDrive::Motor(5, 4),
            BaseDrive::Motor(6, 7),
            BaseDrive::Motor(9, 8)};
    xDrive = XDrive::XDrive(motors, 4);
    Serial.println("X-Drive Initialized!");

    xDriveSerial.begin(9600);
    Serial.println("X-Drive Serial Initialized!");

    xDriveSerial.write("Hello from X-Drive!");
}

void loop() {
    if (xDriveSerial.available() > 0) {
        String data = xDriveSerial.readString();
        int commaIndex = data.indexOf(',');
        double x = data.substring(0, commaIndex).toDouble();
        double y = data.substring(commaIndex + 1).toDouble();
        Serial.print("X: ");
        Serial.print(x);
        Serial.print(", Y: ");
        Serial.println(y);
        xDrive.getSpeeds(speeds, x, y);
        xDrive.setSpeed(speeds);
    } else {
        xDrive.stop();
    }
}