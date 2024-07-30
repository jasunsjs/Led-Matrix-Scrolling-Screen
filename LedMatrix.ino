/*
Title: LED Matrix Scrolling Display
Description: Scrolls the letter "J" from right to left repeatedly.
Updated 2023-05-19
Author: Jason Sun
Version 2.0
*/

const int SCROLL_TIME = 10;

byte outputLetter[8]{ // For outputting
  B11111111,
  B11100000,
  B11111101,
  B11111101,
  B11111101,
  B11101101,
  B11110011,
  B11111111,
};

byte letterJ[8]{ // For storage
  B11111111,
  B11100000,
  B11111101,
  B11111101,
  B11111101,
  B11101101,
  B11110011,
  B11111111,
};

void setup() {
  DDRF = B11111111;
  DDRK = B11111111;
  PORTF = B11111111; // rows, 0 means on
  PORTK = B00000000; // columns, 1 means on
  // Serial.begin(9600);
}

void loop() {
  scroll();
  rescroll();
}

// Methods--------------------------------------------------------------------------
// Rescrolling from left side of the screen
void rescroll(){
  int n=4;
  for (int n=4; n>=0; n--){
    for (int i=0; i<n; i++){ // right shifting the bits a total of n times
      for (int j=0; j<8; j++){
        outputLetter[j] = (outputLetter[j] >> 1) + 128;
      }
    }
    output(outputLetter);
    resetLetterJ();
  }
}

// Scrolling left from original position
void scroll(){
  for (int j=0; j<8; j++){ // left shifting the bits
    for (int i=0; i<8; i++){
      outputLetter[i] = (outputLetter[i] << 1) + 1;
    }
    output(outputLetter);
  }
}

void output(byte ar[]){
  for (int i=0; i<SCROLL_TIME; i++){
    for (int i=0; i<8; i++){
      PORTF = ar[7-i];
      PORTK = B00000001 << i;
      delay(1);
    }
  }
}

void resetLetterJ(){
  for (int i=0; i<8; i++){
    outputLetter[i] = letterJ[i];
  }
}
