#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // Slave Select pin
#define RST_PIN 9  // Reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();  // Initiate SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  Serial.println("Scan an RFID card to punch it.");
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
    Serial.println("Card Punched - UID: " + uidStr);

    mfrc522.PICC_HaltA();  // Halt the current card
    mfrc522.PCD_StopCrypto1();  // Stop encryption on the card
  }
}
