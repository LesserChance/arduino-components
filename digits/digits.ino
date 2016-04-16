
/**
 * Use this to handle a 4-digit 7-segment display through two shift registers
 * requires only 3 pins
 * https://www.sparkfun.com/products/9483
 */
#include <SPI.h>

// connections
const int DIGIT_LATCH_PIN = 8;        // B0 - Pin for the digit SR latch
const int DIGIT_CLOCK_PIN = 13;       // Pin for the digit SR clock
const int DIGIT_DATA_PIN = 11;        // Pin for the digit SR data

// variables
byte dataCharacter;
byte dataDigit;
byte dataArrayCharacter[15];
byte dataArrayDigit[4];

void setup()  {
  initDigits();
} 

void loop()  {
  //some examples
  outputString("88:88");
//  outputString("1234");
//  outputString("123'4");
//  outputString("9.87.6");
//  outputString("501.0");
//  outputString("5  .2");
//  outputString("53: 4");
//  outputString("8.1.:9.'7.");
}

/**
 * Initialize the variables to set digits
 */
void initDigits() {
  pinMode(DIGIT_LATCH_PIN, OUTPUT);
  pinMode(DIGIT_CLOCK_PIN, OUTPUT);
  pinMode(DIGIT_DATA_PIN, OUTPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(20000000, LSBFIRST, SPI_MODE0));
  
  //ABCDEFGH, 1 = segment off
  dataArrayCharacter[0] = B00000011;
  dataArrayCharacter[1] = B10011111;
  dataArrayCharacter[2] = B00100101;
  dataArrayCharacter[3] = B00001101;
  dataArrayCharacter[4] = B10011001;
  dataArrayCharacter[5] = B01001001;
  dataArrayCharacter[6] = B01000001;
  dataArrayCharacter[7] = B00011111;
  dataArrayCharacter[8] = B00000001;
  dataArrayCharacter[9] = B00011001;

  // other characters
  dataArrayCharacter[10] = B11111101; // "-"
  dataArrayCharacter[11] = B11111111; // " "

  //X1234CAX, 1 = on
  dataArrayDigit[0] = B01000000;
  dataArrayDigit[1] = B00100000;
  dataArrayDigit[2] = B00010000;
  dataArrayDigit[3] = B00001000;
}

/**
 * Output the ~4 character numeric string to the 4 digit display
 *  - can use colon by putting a colon into the string
 *  - can use apostrophe by putting an apostrophe into the string
 *  - available non numeric characters include " " and "-"
 *  - can use decimals
 * @param String output
 */
void outputString(String output) {
  bool hasColon = (output.indexOf(':') > -1);
  if (hasColon) {
    output.remove(output.indexOf(':'), 1);
  }
  
  bool hasApos = (output.indexOf('\'') > -1);
  if (hasApos) {
    output.remove(output.indexOf('\''), 1);
  }
  
  for (int i = 0; i < 4; i++) {
    dataDigit = dataArrayDigit[i];

    if (i == 0) {
      if (hasColon) {
        //turn on the colon
        dataDigit = dataDigit + B00000100;
      }
      if (hasApos) {
        //turn on the apostrophe
        dataDigit = dataDigit + B00000010;
      }
    }
    
    char showChar = output.charAt(i);

    switch (showChar) {
      case '-':
        dataCharacter = dataArrayCharacter[10];
        break;
      case ' ':
        dataCharacter = dataArrayCharacter[11];
        break;
      default:
        dataCharacter = dataArrayCharacter[showChar - '0'];
        break;
    }
    
    if (output.charAt(i+1) == '.') {
      //turn on the decimal
      dataCharacter = dataCharacter - B00000001;
      output.remove(i+1, 1);
    }

    PORTB |= _BV(PB0); // latch pin HIGH
    SPI.transfer(dataDigit);
    SPI.transfer(dataCharacter);
    PORTB &= ~_BV(PB0); // latch pin LOW
  }
}

