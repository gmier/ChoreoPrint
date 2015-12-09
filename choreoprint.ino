// Giovi Mier, Lucie Randall, Nina-Marie Amadeo
// ChoreoPrint
// CS 320 Project

// First version of code, LED lights respond to pressure sensor input.

//The following code was written with the reference of the online links mentioned below.
//https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr
//http://www.instructables.com/id/Force-sensitive-resistor-activated-led/
 
int sensorPin0 = 0;    // force sensitive resistor connected to analog pin 0
int sensorPin1 = 1;
int sensorPin2 = 2;
int sensorPin3 = 3;
int ledPin0 = 9;     //LED pin connected to digital pin 9
int ledPin1 = 10;    //LED pin connected to digital pin 10
int ledPin2 = 11;    //LED pin connected to digital pin 11
int ledPin3 = 12;
int sensorValue0 = 0;  
int sensorValue1 = 0;  
int sensorValue2 = 0;
int sensorValue3 = 0;
 
void setup() // This funtion runs once the sketch starts up.
// We'll be using pin 9, 10 and 11 to light the LED so it's important
//to refer to it as an output. We've named it ledPin.
{
  Serial.begin(9600); // starting up your serial monitor to view varying values
  pinMode(ledPin0, OUTPUT); //9
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}
 
void loop()  // This funtion runs repeatedly after setup()is completed
{
  sensorValue0 = analogRead(sensorPin0); //reading the values from the analog pin of the sensor
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  // and throwing it out as a value
  Serial.print("Force value 0 = ");  //Display value "Force value"
  Serial.println(sensorValue0);
  
  Serial.print("Force value 1 = ");  //Display value "Force value"
  Serial.println(sensorValue1);
  
  Serial.print("Force value 2 = ");  //Display value "Force value"
  Serial.println(sensorValue2);
  
  Serial.print("Force value 3 = ");  //Display value "Force value"
  Serial.println(sensorValue3);
  
  if(sensorValue0 > 0) {
    digitalWrite(ledPin0, HIGH);
  } else digitalWrite(ledPin0, LOW);
  
  if(sensorValue1 > 0) {
    digitalWrite(ledPin1, HIGH);
  } else digitalWrite(ledPin1, LOW);
  
  if(sensorValue2 > 0) {
    digitalWrite(ledPin2, HIGH);
  } else digitalWrite(ledPin2, LOW);
  
  if(sensorValue3 > 0) {
    digitalWrite(ledPin3, HIGH);
  } else digitalWrite(ledPin3, LOW);
}


