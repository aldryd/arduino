/**
 * Motion Light
 *
 * This Arduino program detects motion from a PIR motion sensor and turns on an analog RGB strip
 * of LEDs to a dim red color. As long as it detects movemenet, the LEDs will stay lit. After
 * a specified length of time, the LEDs will dim and turn off.
 */

#include <LightChrono.h>

// Speed of the LEDs fading in and out
const int FADE_SPEED = 5;

// Represents how long to keep the LEDs active when motion is detected
const int MOTION_DELAY_MILLISECONDS = 10 * 1000;

// MUST be between 1 and 255
const int MAX_RED_VALUE = 150;

// Pin definitions
const int RED_PIN = 6;
const int MOTION_INPUT_PIN = 2;

// Track the current state of the lights
bool lightsAreOn = false;

// Timer to track how long no motion is detected
LightChrono timer;

void setup() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(MOTION_INPUT_PIN, INPUT);

    timer.restart();
}

void turnOn() {
    for (int red = 0; red <= MAX_RED_VALUE; red++) {
        analogWrite(RED_PIN, red);
        delay(FADE_SPEED);
    }

    lightsAreOn = true;
}

void turnOff() {
    for (int red = MAX_RED_VALUE; red >= 0; red--) {
        analogWrite(RED_PIN, red);
        delay(FADE_SPEED);
    }

    lightsAreOn = false;
}

void loop() {
    int pirValue = digitalRead(MOTION_INPUT_PIN);
    if (HIGH == pirValue) {
        // Detected motion
        if (false == lightsAreOn) {
            turnOn();
        }

        // As long as motion is detected, reset the timer
        timer.restart();
    } else {
        // No motion detected
        if (lightsAreOn && timer.hasPassed(MOTION_DELAY_MILLISECONDS, true)) {
            turnOff();
        }
    }
}



