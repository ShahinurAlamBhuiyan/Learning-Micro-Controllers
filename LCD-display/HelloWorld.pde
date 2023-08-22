
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("hello UIU!");
  // lcd.setCursor(2,1);
  // lcd.print("");
  //  lcd.setCursor(0,2);
  // lcd.print("I Love You");
  //  lcd.setCursor(2,3);
  // lcd.print("Arduino LCM IIC 2004");
}


void loop()
{
}

// for checking the port
// #include <Wire.h>

// void setup() {
//   Wire.begin();
//   Serial.begin(9600);
//   while (!Serial);
// }

// void loop() {
//   for (byte address = 1; address < 127; ++address) {
//     Wire.beginTransmission(address);
//     if (Wire.endTransmission() == 0) {
//       Serial.print("I2C device found at address 0x");
//       Serial.println(address, HEX);
//     }
//   }
//   delay(500);  
// }