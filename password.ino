#include <Wire.h>
// Include LCD display library for I2C
#include <LiquidCrystal_I2C.h>
// Include Keypad library
#include <Keypad.h>
 
// Length of password + 1 for null character
#define Password_Length 7
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "123456";
 
// Pin connected to lock relay input

 
// Counter for character entries
byte data_count = 0;
 
// Character to hold key input
char customKey;
 
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;
 
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
 
// Connections to Arduino
byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 8, 1};
 
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
// Create LCD object
LiquidCrystal_I2C lcd(0x27, 20, 4);
 
void setup() {
  // Setup LCD with backlight and initialize
  lcd.backlight();
  lcd.init();
 
  // Set lockOutput as an OUTPUT pin
  
}
 
void loop() {
 
  // Initialize LCD and print
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
 
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }
 
  // See if we have reached the password length
  if (data_count == Password_Length - 1) {
    lcd.clear();
 
    if (!strcmp(Data, Master)) {
      // Password is correct
      lcd.setCursor(0, 0);
      lcd.print("Payment         ");
      lcd.setCursor(4,1);
      lcd.print("Successful!");
      delay(20000);
    
    }
    else {
      // Password is incorrect
      lcd.setCursor(0, 0);
      lcd.print("incorrect         ");
      lcd.setCursor(4,1);
      lcd.print("passcode");
      delay(1000);
    }
 
    // Clear data and LCD display
    lcd.clear();
    clearData();
    
  }
}
 
void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}
