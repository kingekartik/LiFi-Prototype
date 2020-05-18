/*
  
  Prototype to transfer ASCII encoded characters from transmitter to receiver via Visible Light Communication.

  Encodes characters to its assigned code and transmitts it to white LED.
  Reads an analog input pin (A0), Compare the threshold value to recognise high bit or low bit.
  Prints the results to the Serial Monitor.

  The circuit:
  -1x Solar Panal
  -3x LED
  -1x Resistance 330 Ohm
  -1x Arduino USB Cable
  -1x Arduino Uno R3
  -Some wires and a breadboard

  created 22 April. 2019
  by Kartik Kinge

  This code is in the public domain.
  https://github.com/kingekartik/LiFi-Prototype
*/

static int TRESHOLD = 70;
static unsigned int standardDelay = 10000; //10000 is limit
byte i; // Declare a global 'i' such that the loop function is able to use its inherent property of infinite looping.
        // Also, i always has a value less than 255, so use 'byte' to reduce memory usage.
void setup() {
  Serial.begin(9600); // 9600 bits per second
  pinMode(3,OUTPUT); //digital PWM 3 on output
  i = 97;
}

void loop() {
  //high A0 value is one, low A0 value is zero
  if(i == 123)
    i = 97; // Re-initialize 'i';
  else{
    LightFlash(i);
    i += 1;
  }
}

/*
void WriteChar(byte str){ // Changed the signature of parameter from 'int' to 'byte'
  switch (str){
    case 97:
      //code for a is 011 0001
      LightFlash(false, true, true, false, false, false, true);
      break;
    case 98:
      //code for b is 011 0010
      LightFlash(false, true, true, false, false, true, false);
      break;
    case 99:
      //code for c is 011 0011
      LightFlash(false, true, true, false, false, true, true);
      break;
    case 100:
      //code for d is 011 0100
      LightFlash(false, true, true, false, true, false, false);
      break;
    case 101:
      //code for e is 011 0101
      LightFlash(false, true, true, false, true, false, true);
      break;
    case 102:
      //code for f is 011 0110
      LightFlash(false, true, true, false, true, true, false);
      break;
    case 103:
      //code for g is 011 0111
      LightFlash(false, true, true, false, true, true, true);
      break;
    case 104:
      //code for h is 011 1000
      LightFlash(false, true, true, true, false, false, false);
      break;
    case 105:
      //code for i is 011 1001
      LightFlash(false, true, true, true, false, false, true);
      break;
    case 106:
      //code for j is 011 1010
      LightFlash(false, true, true, true, false, true, false);
      break;
    case 107:
      //code for k is 011 1011
      LightFlash(false, true, true, true, false, true, true);
      break;
    case 108:
      //code for l is 011 1100
      LightFlash(false, true, true, true, true, false, false);
      break;
    case 109:
      //code for m is 011 1101
      LightFlash(false, true, true, true, true, false, true);
      break;
    case 110:
      //code for n is 011 1110
      LightFlash(false, true, true, true, true, true, false);
      break;
    case 111:
      //code for o is 011 1111
      LightFlash(false, true, true, true, true, true, true);
      break;
    case 112:
      //code for p is 100 0000
      LightFlash(true, false, false, false, false, false, false);
      break;
    case 113:
      //code for q is 100 0001
      LightFlash(true, false, false, false, false, false, true);
      break;
    case 114:
      //code for r is 100 0010
      LightFlash(true, false, false, false, false, true, false);
      break;
    case 115:
      //code for s is 100 0011
      LightFlash(true, false, false, false, false, true, true);
      break;
    case 116:
      //code for t is 100 0100
      LightFlash(true, false, false, false, true, false, false);
      break;
    case 117:
      //code for u is 100 0101
      LightFlash(true, false, false, false, true, false, true);
      break;
    case 118:
      //code for v is 100 0110
      LightFlash(true, false, false, false, true, true, false);
      break;
    case 119:
      //code for w is 100 0111
      LightFlash(true, false, false, false, true, true, true);
      break;
    case 120:
      //code for x is 100 1000
      LightFlash(true, false, false, true, false, false, false);
      break;
    case 121:
      //code for y is 100 1001
      LightFlash(true, false, false, true, false, false, true);
      break;
    case 122:
      //code for z is 100 1010
      LightFlash(true, false, false, true, false, true, false);
      break;
    default:
      Serial.println(str);
      Serial.println("CAME IN DEFAULT IN WRITECHAR");
      break;
  }
}
*/
void LightFlash(byte num){

  /*
  Loop Invariant of LightFlash function : 
  digitalWrite(3, LOW);
  unsigned long int prod = 1;
  for i = 6 to 0 do:
    if ith bit of your ascii character is 1, then digitalWrite(3, HIGH);
    delayMicroseconds(standardDelay / 2);
    sensorValue += ((AnalogRead(A0) < THRESHOLD)*prod); // This step reads the analog light signal, and adds to sensor value which is used for identification of light.
    prod *= 10; 
  PrintChar(sensorValue);
  */

  // Convert byte into binary. And then explore the AnalogRead Portion
  // The function with the loops takes the same amount of time as compared to the switch case statement which is comparatively difficult to manage.

  unsigned long int prod = 1000000;
  unsigned long int sensorValue = 0;
  byte binary[7];
  for(byte j = 0; j <= 6; j += 1){
    if(num % 2 == 0) binary[j] = true;
    else binary[j] = false;
    num /= 2;
  }
  for(byte j = 0; j < 7; j++){
    digitalWrite(3, LOW);
    if(binary[j] == true)
      digitalWrite(3, HIGH);
    sensorValue += ((AnalogRead(A0) < THRESHOLD)*prod);
    prod /= 10;
    delayMicroseconds(standardDelay / 2);
  }

  PrintChar(result);


//////////////////////////////////////////////////////////////
  /*
  digitalWrite(3,LOW);
  if (a == true){
    digitalWrite(3,HIGH);
  }
  delayMicroseconds(standardDelay/2);
  boolean sensorValue1 = (analogRead(A0)<TRESHOLD);
  delayMicroseconds(standardDelay/2);

  digitalWrite(3,LOW);
  if (b == true){
    digitalWrite(3,HIGH);
  }
  delayMicroseconds(standardDelay/2);
  boolean sensorValue2 = (analogRead(A0)<TRESHOLD);
  delayMicroseconds(standardDelay/2);

  digitalWrite(3,LOW);
  if (c == true){
    digitalWrite(3,HIGH);
  }
  delayMicroseconds(standardDelay/2);
  boolean sensorValue3 = (analogRead(A0)<TRESHOLD);
  delayMicroseconds(standardDelay/2);

  digitalWrite(3,LOW);
  if (d == true){
    digitalWrite(3,HIGH);
  }
  delayMicroseconds(standardDelay/2);
  boolean sensorValue4 = (analogRead(A0)<TRESHOLD);
  delayMicroseconds(standardDelay/2);

  digitalWrite(3,LOW);
  if (e == true){
    digitalWrite(3,HIGH);
  }
  delayMicroseconds(standardDelay/2);
  boolean sensorValue5 = (analogRead(A0)<TRESHOLD);
  delayMicroseconds(standardDelay/2);

  digitalWrite(3,LOW);
  if (f == true){
    digitalWrite(3,HIGH);
  }
  delayMicroseconds(standardDelay/2);
  boolean sensorValue6 = (analogRead(A0)<TRESHOLD);
  delayMicroseconds(standardDelay/2);

  digitalWrite(3,LOW);
  if (g == true){
    digitalWrite(3,HIGH);
  }
  delayMicroseconds(standardDelay/2);
  boolean sensorValue7 = (analogRead(A0)<TRESHOLD);
  delayMicroseconds(standardDelay/2);
  delayMicroseconds(3*standardDelay); //1 second passed

  long result = 0;
  
  result = 1000000*sensorValue1 + 100000*sensorValue2 + 10000*sensorValue3
  + 1000*sensorValue4 + 100*sensorValue5 + 10*sensorValue6 + 1*sensorValue7;
  
  //Serial.println(result);
  PrintChar(result);
  */
}

void PrintChar(long binary){
  switch (binary){
    case 110001:
      //code for a is 011 0001
      Serial.println("a");
      break;
    case 110010:
      //code for b is 011 0010
      Serial.println("b");
      break;
    case 110011:
      //code for c is 011 0011
      Serial.println("c");
      break;
    case 110100:
      //code for d is 011 0100
      Serial.println("d");
      break;
    case 110101:
      //code for e is 011 0101
      Serial.println("e");
      break;
    case 110110:
      //code for f is 011 0110
      Serial.println("f");
      break;
    case 110111:
      //code for g is 011 0111
      Serial.println("g");
      break;
    case 111000:
      //code for h is 011 1000
      Serial.println("h");
      break;
    case 111001:
      //code for i is 011 1001
      Serial.println("i");
      break;
    case 111010:
      //code for j is 011 1010
      Serial.println("j");
      break;
    case 111011:
      //code for k is 011 1011
      Serial.println("k");
      break;
    case 111100:
      //code for l is 011 1100
      Serial.println("l");
      break;
    case 111101:
      //code for m is 011 1101
      Serial.println("m");
      break;
    case 111110:
      //code for n is 011 1110
      Serial.println("n");
      break;
    case 111111:
      //code for o is 011 1111
      Serial.println("o");
      break;
    case 1000000:
      //code for p is 100 0000
      Serial.println("p");
      break;
    case 1000001:
      //code for q is 100 0001
      Serial.println("q");
      break;
    case 1000010:
      //code for r is 100 0010
      Serial.println("r");
      break;
    case 1000011:
      //code for s is 100 0011
      Serial.println("s");
      break;
    case 1000100:
      //code for t is 100 0100
      Serial.println("t");
      break;
    case 1000101:
      //code for u is 100 0101
      Serial.println("u");
      break;
    case 1000110:
      //code for v is 100 0110
      Serial.println("v");
      break;
    case 1000111:
      //code for w is 100 0111
      Serial.println("w");
      break;
    case 1001000:
      //code for x is 100 1000
      Serial.println("x");
      break;
    case 1001001:
      //code for y is 100 1001
      Serial.println("y");
      break;
    case 1001010:
      //code for z is 100 1010
      Serial.println("z");
      break;
    case 11000:
      Serial.println("Debug 1: character not recognised");
      break;
    case 1011001:
      Serial.println("Debug 2: character not recognised");
      break;
    case 100001:
      Serial.println("Debug 3: character not recognised");
      break;
    case 1011000:
      Serial.println("Debug 4: character not recognised");
      break;
    default:
      //Serial.println(binary);
      Serial.println("CAME IN DEFAULT ON PRINTCHAR");
      break;
  }
}
