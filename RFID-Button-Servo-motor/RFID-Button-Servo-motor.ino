#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10  // Slave Select pin
#define RST_PIN 9   // Reset pin
#define BUTTON_PIN 2 // Button pin

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;

bool buttonActive = false; // Button activation flag
bool buttonState = false; // Button state
bool servoTurnedRight = false; // Servo position flag

String authorizedCardUID = "dc7fba38";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  servo.attach(7); // Attach the servo to pin 3
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Input pin with pull-up resistor
  servo.write(90); // Set the initial servo position to 90 degrees (centered)
  delay(500); // Delay for the servo to reach the initial position
  Serial.println("Place an authorized RFID card to activate the button.");
}

void loop() {
  String uidStr = "";

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidStr += String(mfrc522.uid.uidByte[i], HEX);
    }
    
    if (uidStr == authorizedCardUID) {
      Serial.println("Authorized card detected.");
      buttonActive = !buttonActive; // Toggle button activation
    }
    
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    buttonState = !buttonState; // Toggle button state
    delay(250); // Debounce
  }

  // Control servo based on button press and button activation
  if (buttonActive) {
    if (buttonState) {
      if (!servoTurnedRight) {
        servo.write(180); // Move servo 90 degrees right
        servoTurnedRight = true;
      } else {
        servo.write(0); // Move servo 90 degrees left
        servoTurnedRight = false;
      }
    }
  }
}
