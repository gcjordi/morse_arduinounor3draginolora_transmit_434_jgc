/*
   RadioLib Morse Transmit Example
   This example sends Morse code message using
   SX1278's FSK modem.
   Other modules that can be used for Morse Code:
    - SX127x/RFM9x
    - RF69
    - SX1231
    - CC1101
    - SX126x
    - nRF24
*/

// include the library
#include <RadioLib.h>

// SX1278 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// DIO1 pin:  3
SX1278 fsk = new Module(10, 2, 3);

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1278 fsk = RadioShield.ModuleA;

// create Morse client instance using the FSK module
MorseClient morse(&fsk);

void setup() {
  Serial.begin(9600);

  // initialize SX1278
  Serial.print(F("[SX1278] Initializing ... "));
  // carrier frequency:           434.0 MHz
  // bit rate:                    48.0 kbps
  // frequency deviation:         50.0 kHz
  // Rx bandwidth:                125.0 kHz
  // output power:                13 dBm
  // current limit:               100 mA
  // sync word:                   0x2D  0x01
  int state = fsk.beginFSK();

  // when using one of the non-LoRa modules for Morse code
  // (RF69, CC1101, etc.), use the basic begin() method
  // int state = fsk.begin();

  if(state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }

  // initialize Morse client
  Serial.print(F("[Morse] Initializing ... "));
  // base frequency:              434.0 MHz
  // speed:                       20 words per minute
  state = morse.begin(434.0);
  if(state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}

void loop() {
  Serial.print(F("[MORSE LORA TRANSMISSION IN TESTS. IF YOU RECEIVE IT CONTACT ME AT INFO AT JORDIGARCIA POINT EU] Sending Morse data ... "));

  // MorseClient supports all methods of the Serial class
  // NOTE: Characters that do not have ITU-R M.1677-1
  //       representation will not be sent! Lower case
  //       letters will be capitalized.

  // send start signal first
  morse.startSignal();

  Serial.println(F("done!"));

  // wait for a five minutes before transmitting again
  delay(300000);
}
