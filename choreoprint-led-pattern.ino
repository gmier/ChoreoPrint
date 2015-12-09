// Giovi Mier, Lucie Randall, Nina-Marie Amadeo
// ChoreoPrint
// CS 320 Project

// LEDs display a pattern, representative of a sample "dance".

//The following code was written with the reference of the online links mentioned below.
//https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr
//http://www.instructables.com/id/Force-sensitive-resistor-activated-led/

int sensorPin0 = 0;    // force sensitive resistor connected to analog pin 0
int sensorPin1 = 1;
int sensorPin2 = 2;
int sensorPin3 = 3;
int ledPin0 = 9;    //LED pin connected to digital pin 9
int ledPin1 = 10;    //LED pin connected to digital pin 10
int ledPin2 = 11;    //LED pin connected to digital pin 11
int ledPin3 = 12;
int sensorValue0 = 0;  
int sensorValue1 = 0;  
int sensorValue2 = 0;
int sensorValue3 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // starting up your serial monitor to view varying values
  pinMode(ledPin0, OUTPUT); //9
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
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

  // blinking LED pattern  
  blinkTopLeft();
  blinkBottomRight();
  //digitalWrite(ledPin1, LOW);
  //blinkBottomRight();
  blinkTopRight();
  blinkBottomLeft();
  blinkBottomRight();
  blinkBottomLeft();
  blinkBottomRight();
  blinkBottomLeft();
  blinkTopRight();
  blinkBottomLeft();
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

