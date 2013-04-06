/*
 * Copyright (c) 2013, Brock and Hannah Atchison
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int cyclePin = 6;
const int confirmPin = 7;

// variable to hold the value of the cyclePin
int cycleState = 0;

// variable to hold previous value of the cyclePin
int prevCycleState = 0;

int confirmState = 0;
int prevConfirmState = 0;

int choice = -1;

void setup() {
  // set up the number of columns and rows on the LCD 
  lcd.begin(16, 2);
  
  // set up the cyclePin and confirmPin as inputs
  pinMode(cyclePin, INPUT);
  pinMode(confirmPin, INPUT);
  
  lcd.print("Destination:");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
}

void loop() {
  // check the status of the switch
  cycleState = digitalRead(cyclePin);
  
  // See if the confirm button was pushed
  confirmState = digitalRead(confirmPin);

  // compare the cycleState to its previous state
  if (cycleState != prevCycleState) {
    // if the state has changed from HIGH to LOW
    if (cycleState == LOW) {
      lcd.noBlink();
      // set the cursor to column 0, line 0
      lcd.clear();
      lcd.setCursor(0, 0);
      
      lcd.print("Destination:");
      lcd.setCursor(0, 1);
      
      choice++;
      
      // Bounds check
      if (choice == 7) {
        choice = 0;
      }
      
      switch (choice) {
        case 0: {
          lcd.print("Earth");
          break;
        }
        
        case 1: {
          lcd.print("Mars");
          break;
        }
        
        case 2: {
          lcd.print("Jupiter");
          break;
        }
        
        case 3: {
          lcd.print("Andromeda Galaxy");
          break;
        }
        
        case 4: {
          lcd.print("Neptune");
          break;
        }
        
        case 5: {
          lcd.print("Center of galaxy");
          break;
        }
        
        case 6: {
          lcd.print("Orion Nebula");
          break;
        }
      }
    }
  } else if (confirmState != prevConfirmState) {
    if (confirmState == LOW) {
      // Destination confirmed!
      lcd.clear();
      lcd.setCursor(0, 0);
      
      lcd.print("Confirmed!");
      delay(1000);
      
      lcd.setCursor(0, 0);
      lcd.print("Countdown...");
      
      for (int ii = 5; ii > 0; ii--) {
        lcd.setCursor(0, 1);
        lcd.print(ii);
      
        delay(1000);
      }
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ENGAGE!");
    }
  }
  // save the current cycle state as the last state 
  prevCycleState = cycleState;
  
  prevConfirmState = confirmState;
}
