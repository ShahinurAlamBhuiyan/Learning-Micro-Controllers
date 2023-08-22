#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10  // Slave Select pin
#define RST_PIN 9  // Reset pin

LiquidCrystal_I2C lcd(0x3F, 16, 2);

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define the UID of the punched card
String punchedCardUID = "dc7fba38";

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();  // Initiate SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Scan an RFID card");
}

void loop() {
  String uidStr = "";  // Create an empty string to store the UID

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Store the UID as a string
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidStr += String(mfrc522.uid.uidByte[i], HEX);
    }

    // Print the UID
    Serial.println(uidStr);

    // Check if the scanned UID matches the specific card's UID
    if (uidStr == punchedCardUID) {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Card Punched");
    } else {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Not Punched");
    }

    mfrc522.PICC_HaltA();  // Halt the current card
    mfrc522.PCD_StopCrypto1();  // Stop encryption on the card
  }
}
