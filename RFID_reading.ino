#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS1_PIN          10         // Configurable, see typical pin layout above
#define SS2_PIN         11
#define SS3_PIN         12
#define SS4_PIN         13
#define SS5_PIN         14
#define SS6_PIN         15
#define SS7_PIN         16
#define SS8_PIN         17
#define SS9_PIN         18
#define SS10_PIN         19
#define SS11_PIN         20
#define SS12_PIN         21

MFRC522 mfrc522[12];
mfrc522[0] = (SS1_PIN, RST_PIN);
mfrc522[1] = (SS2_PIN, RST_PIN);
mfrc522[2] = (SS3_PIN, RST_PIN);
mfrc522[3] = (SS4_PIN, RST_PIN);
mfrc522[4] = (SS5_PIN, RST_PIN);
mfrc522[5] = (SS6_PIN, RST_PIN);
mfrc522[6] = (SS7_PIN, RST_PIN);
mfrc522[7] = (SS8_PIN, RST_PIN);
mfrc522[8] = (SS9_PIN, RST_PIN);
mfrc522[9] = (SS10_PIN, RST_PIN);
mfrc522[10] = (SS11_PIN, RST_PIN);
mfrc522[11] = (SS12_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  for(int i=0;i<12;i++){
  mfrc522[i].PCD_Init();   // Init MFRC522
  }
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  for(int i =0;i<12;i++){
  mfrc522[i].PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  }
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  for (int i = 0; i < 12; i++) {
    if ( ! mfrc522[i].PICC_IsNewCardPresent()) {
      return;
    }
  }

  // Select one of the cards
  for (int i = 0; i < 12; i++) {
    if ( ! mfrc522[i].PICC_ReadCardSerial()) {
      return;
    }
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  for (int i = 0; i < 12; i++) {
    mfrc522[i].PICC_DumpToSerial(&(mfrc522.uid));
  }
