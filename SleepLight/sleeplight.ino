/**
 * Fall Asleep Light
 *
 * This is designed to run on a device that will help you fall asleep. LEDs will slowly brighten
 * and dim. As the light gets brighter, you inhale. As the light dims, you exhale. Over the
 * given timeframe, the frequency of the pulses will get slower and slower to reduce your
 * number of breaths per minute.
 *
 * Based on the FADing Fall Asleep Device by Youz:
 * http://www.instructables.com/id/FADing-Fall-Asleep-Device/
 */

#define LED_PIN 5
#define GREEN_BUTTON 21
#define BLUE_BUTTON 22

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(GREEN_BUTTON, INPUT);
    pinMode(BLUE_BUTTON, INPUT);
}

void loop() {
    bool green_button_pressed = false;
    bool blue_button_pressed = false;

    if (HIGH == digitalRead(GREEN_BUTTON)) {
        green_button_pressed = true;
        Serial.print("##### Green button was pressed!\n");
    }

    if (HIGH == digitalRead(BLUE_BUTTON)) {
        blue_button_pressed = true;
        Serial.print("##### Blue button was pressed!\n");
    }
    
    int number_of_blinks = 0;
    if (true == green_button_pressed) {
        number_of_blinks = 2;
    } else if (true == blue_button_pressed) {
        number_of_blinks = 5;
    }

    for (int ii = 0; ii < number_of_blinks; ii++) {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
    }
}
