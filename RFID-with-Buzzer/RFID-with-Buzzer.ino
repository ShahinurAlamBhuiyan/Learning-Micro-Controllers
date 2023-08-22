/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */

// ***showing everything

// #include <SPI.h>
// #include <MFRC522.h>

// #define RST_PIN         9          // Configurable, see typical pin layout above
// #define SS_PIN          10         // Configurable, see typical pin layout above

// MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// void setup() {
// 	Serial.begin(9600);		// Initialize serial communications with the PC
// 	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
// 	SPI.begin();			// Init SPI bus
// 	mfrc522.PCD_Init();		// Init MFRC522
// 	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
// 	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
// 	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
// }

// void loop() {
// 	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
// 	if ( ! mfrc522.PICC_IsNewCardPresent()) {
// 		return;
// 	}

// 	// Select one of the cards
// 	if ( ! mfrc522.PICC_ReadCardSerial()) {
// 		return;
// 	}

// if (mfrc522.PICC_ReadCardSerial()) {
//       Serial.println("Found a card!");
//       Serial.print("UID: ");
//       for (byte i = 0; i < mfrc522.uid.size; i++) {
//         Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//         Serial.print(mfrc522.uid.uidByte[i], HEX);
//       }
//       Serial.println();
//       mfrc522.PICC_HaltA();  // Halt PICC to prepare for next card
//       // Serial.print("kkkkkkkkkkkk");
//     }
// 	// Dump debug info about the card; PICC_HaltA() is automatically called
// 	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
//     Serial.println(mfrc522.PICC_ReadCardSerial() + "uhgfjgj");

// }


// ***only showing Card UID

// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN 10  // Slave Select pin
// #define RST_PIN 9  // Reset pin

// MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an instance of the MFRC522 library

// void setup() {
//   Serial.begin(9600);  // Initialize serial communication
//   SPI.begin();  // Initiate SPI bus
//   mfrc522.PCD_Init();  // Initiate MFRC522
//   Serial.println("Scan an RFID card");
// }

// void loop() {
//   // Look for new cards
//   if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
//     Serial.print("Card UID: ");
//     for (byte i = 0; i < mfrc522.uid.size; i++) {
//       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
//       Serial.print(mfrc522.uid.uidByte[i], HEX);
//     }
//     Serial.println();
    
//     mfrc522.PICC_HaltA();  // Halt the current card
//     mfrc522.PCD_StopCrypto1();  // Stop encryption on the card
//   }
// }

// ***storing the card UID and storing it in an array and then if the data match, buzzer will be on
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // Slave Select pin
#define RST_PIN 9  // Reset pin
#define BUZZER_PIN 7  // Buzzer pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an instance of the MFRC522 library

const int maxCards = 10;  // Maximum number of cards to store
String cardUIDs[maxCards];  // Array to store card UIDs
int cardCount = 0;  // Counter for stored card count

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();  // Initiate SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  Serial.println("Scan an RFID card");
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  String uidStr = "";  // Create an empty string to store the UID
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    
    
    // Convert each byte of UID to a two-digit hexadecimal string
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidStr += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uidStr += String(mfrc522.uid.uidByte[i], HEX);
    }
    
    // Store the UID string in the array
    if (cardCount < maxCards) {
      cardUIDs[cardCount] = uidStr;
      cardCount++;
      Serial.println("Card UID stored: " + uidStr);
    } else {
      Serial.println("Array is full. Cannot store more card UIDs.");
    }
    
    mfrc522.PICC_HaltA();  // Halt the current card
    mfrc522.PCD_StopCrypto1();  // Stop encryption on the card
  }
  if(uidStr == "dc7fba38"){
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else
    digitalWrite(BUZZER_PIN, LOW);
  delay(300);
}

