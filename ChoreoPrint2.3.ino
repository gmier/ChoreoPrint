// Giovi Mier, Lucie Randall, Nina-Marie Amadeo
// ChoreoPrint
// CS 320 Project
// 
//The following code was written with the reference of the online links mentioned below.
//https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr
//http://www.instructables.com/id/Force-sensitive-resistor-activated-led/
//http://courses.ischool.berkeley.edu/i262/f13/content/chrisfan/labhw5-simple-simon-says

// INITIALIZE VARIABLES
// force sensitive resistor connected to analog pin 0
int sensorPin0 = 0;    
int sensorPin1 = 1;
int sensorPin2 = 2;
int sensorPin3 = 3;

// LED pin connect to digital pin 9 (etc)
int ledPin0 = 9;
int ledPin1 = 10;  
int ledPin2 = 11;    
int ledPin3 = 12;
int ledPinGreen = 5;
int ledPinRed = 6;
// set pin for potentiometer
int potPin = 8;     

// initialize sensor values to zero
int sensorValue0 = 0;  
int sensorValue1 = 0;  
int sensorValue2 = 0;
int sensorValue3 = 0;

// analogInput arrays must all be the same size!
char analogInput[250]; // Array will store key input presses (sensor 0) with 1 equal pressed and 0 equal not pressed
char analogInput1[250]; // Array to store above for sensor 1
char analogInput2[250]; // Array to store above for sensor 2
char analogInput3[250]; // Array to store above for sensor 3

int serByte = -1;
char serInString[100];  // array that will hold the different bytes of the string. 100=100characters;
int timeAccuracy = 25; // time interval to measure force input in milliseconds
 
void setup() // This funtion runs once the sketch starts up.
// We'll be using pin 9, 10 and 11 to light the LED so it's important
// to refer to it as an output. We've named it ledPin.
{
  Serial.begin(9600); // starting up your serial monitor to view varying values
  pinMode(ledPin0, OUTPUT); // digital pin 9
  pinMode(ledPin1, OUTPUT); // digital pin 10
  pinMode(ledPin2, OUTPUT); // digital pin 11
  pinMode(ledPin3, OUTPUT); // digital pin 12
  pinMode(ledPinGreen, OUTPUT); // digital pin 2
  pinMode(ledPinRed, OUTPUT); // digital pin 3
}
 
void loop()  // This funtion runs repeatedly after setup()is completed
{ 
  // digitalWrite(ledPinGreen, HIGH); 
  // digitalWrite(ledPinRed, HIGH);
  
  //reading the values from the analog pin of the sensor
  sensorValue0 = analogRead(sensorPin0); 
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

  // and throwing it out as a value to the serial monitor
//  Serial.print("Force value 0 = ");  //Display value "Force value"
//  Serial.println(sensorValue0);
//  
//  Serial.print("Force value 1 = ");  //Display value "Force value"
//  Serial.println(sensorValue1);
//  
//  Serial.print("Force value 2 = ");  //Display value "Force value"
//  Serial.println(sensorValue2);
//  
//  Serial.print("Force value 3 = ");  //Display value "Force value"
//  Serial.println(sensorValue3);

  // Zero out serial input and analog input buffers
  memset(serInString, -1, 100);  
  memset(analogInput, -1, sizeof(analogInput));
  memset(analogInput1, -1, sizeof(analogInput1));
  memset(analogInput2, -1, sizeof(analogInput2));
  memset(analogInput3, -1, sizeof(analogInput3));

  readSerialString(serInString); // 
  serByte = serInString[0];

  Serial.println(analogRead(potPin));

  // blinking LED pattern for "wait" mode 
  blinkTopRight();
  blinkBottomLeft();
  blinkBottomRight();
  blinkTopLeft();

  // See if a character is entered in the serial console to trigger record sequence
  if (serByte!=-1 || analogRead(potPin) > 60){ // recording sequence triggers with potentiometer turned 
    //printInput(analogInput);// Print
    analogWrite(ledPin0, 0); 
    analogWrite(ledPin1, 0); 
    analogWrite(ledPin2, 0);
    analogWrite(ledPin3, 0); 
   
    Serial.println("Capturing input. Countdown in");
    blink(ledPinRed,1, 1500);
   
    //Print out count down to recording start
    for (int counter = 5; counter > 0; counter--){
      Serial.print(">>>");
      Serial.println(counter);
      blink(ledPinRed, 1, 50);
      delay(1000);
    }
    analogWrite(ledPinRed, 0);
   
    // Begin Recording 
    Serial.println("Start!!");    
    analogWrite(ledPinGreen,175);
    for (int counter = 0; counter < sizeof(analogInput); counter ++) {
      
        // read pressure sensors
        int readForce = analogRead(sensorPin0);
        int readForce1 = analogRead(sensorPin1);
        int readForce2 = analogRead(sensorPin2);
        int readForce3 = analogRead(sensorPin3);

        Serial.println("sensor = ");
        Serial.println(readForce3);

        // write to corresponding LEDs
        if(readForce > 100) {
          digitalWrite(ledPin0, HIGH);
        } else digitalWrite(ledPin0, LOW);
  
        if(readForce1 > 100) {
          digitalWrite(ledPin1, HIGH);
        } else digitalWrite(ledPin1, LOW);
  
        if(readForce2 > 200) {
          digitalWrite(ledPin2, HIGH);
        } else digitalWrite(ledPin2, LOW);
  
        if(readForce3 > 165) {
          digitalWrite(ledPin3, HIGH);
        } else digitalWrite(ledPin3, LOW);    

        // if sensor values are large enough, store in corresponding arrays
        if (readForce > 100) {
          analogInput[counter] = char(1);
        } else {
          analogInput[counter]=char(0);
        }
        
        if (readForce1 > 100) {
          analogInput1[counter] = char(1);
        } else{
          analogInput1[counter]=char(0);
        }

        if (readForce2 > 200) {
          analogInput2[counter] = char(1);
        } else{
          analogInput2[counter]=char(0);
        }

        if (readForce3 > 165) {
          analogInput3[counter] = char(1);
        } else{
          analogInput3[counter]=char(0);
        }
                 
        delay(timeAccuracy);
    }  
    analogWrite(ledPin0, 0); 
    analogWrite(ledPin1, 0); 
    analogWrite(ledPin2, 0);
    analogWrite(ledPin3, 0);  
    analogWrite(ledPinGreen,0);
    Serial.println("End!!!");      
   // printInput(analogInput);// Print
   
   // show sequence in blinking LED
   Serial.println("Start Blink");
   blink(ledPinGreen, 8, 20);
   delay(2000);
   Serial.println("Now");
   for (int counter = 0; counter < sizeof(analogInput); counter++) {
      // retrieve blink values from analogInput arrays
      int blinkValue = analogInput[counter];
      int blinkValue1 = analogInput1[counter];
      int blinkValue2 = analogInput2[counter];
      int blinkValue3 = analogInput3[counter];

      // if blinkValue is not zero, illuminate corresponding LED
      if (blinkValue > 0) {
        digitalWrite(ledPin0, HIGH);      
      } else {
        analogWrite(ledPin0, 0);                         
      }
      
      if (blinkValue1 > 0) {
        digitalWrite(ledPin1, HIGH);      
      } else {
        analogWrite(ledPin1, 0);                         
      }

      if (blinkValue2 > 0) {
        digitalWrite(ledPin2, HIGH);      
      } else {
        analogWrite(ledPin2, 0);                         
      }

      if (blinkValue3 > 0) {
        digitalWrite(ledPin3, HIGH);      
      } else {
        analogWrite(ledPin3, 0);                         
      }
      
      delay(timeAccuracy);
   } 
   
  delay(2000);
  
  } //end of if() recording session
  analogWrite(ledPin0, 0);  
  analogWrite(ledPin1, 0);
  analogWrite(ledPin2, 0);  
  analogWrite(ledPin3, 0);          
  analogWrite(ledPinRed, 0);                
  analogWrite(ledPinGreen, 0);    
  delay(100);                   // rest a little...
}

// -----------------------------------------------------------------
// HELPER METHODS
// -----------------------------------------------------------------
// simple function takes a pin and triggers blinking sequence
void blink(int ledPin, int intervals, int duration ){
    for(int counter = 0; counter < intervals; counter ++){
          analogWrite(ledPin, 175);      
          delay(duration);
          analogWrite(ledPin, 0);
          delay(100);
    }
}
 
// prints the analog input buffer 
void printInput(char *intArray){
  Serial.println("Values for input");
  for( int counter = 0; counter <sizeof(analogInput); counter ++){
    Serial.print(int(analogInput[counter]));          
  }  
  Serial.println();
}
 
//read a string from the serial and store it in an array
//you must supply the array variable
void readSerialString (char *strArray) {
  int i = 0;
  if(!Serial.available()) {
    return;
  }
  while (Serial.available()) {
    strArray[i] = Serial.read();
    i++;
  }
}

void blinkTopLeft() {
  //top left
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  delay(555);
}

void blinkTopRight() {
  //top right
  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  delay(553);
}

void blinkBottomRight() {
   //bottom right
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, LOW);
  delay(500);
}

void blinkBottomLeft() {
  //bottom left
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, HIGH);
  delay(550);
}

