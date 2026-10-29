#include <HCSR04.h>

byte trigPin = 5; //D1
byte echoPin1 = 12; //D6
byte echoPin2 = 13; //D7
byte redPin1 = 2; //D4
byte redPin2 = 15; //D8
byte greenPin1 = 14; //D5
byte greenPin2 = 16; //D0


HCSR04 hc(trigPin, new int[2]{echoPin1, echoPin2}, 2); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)


void setup(){

  byte reds[2] = {redPin1, redPin2};
  byte greens[2] = {greenPin1, greenPin2};

  Serial.begin(9600);
  int i;
  for (i = 0; i < 2; i++){
    pinMode(reds[i], OUTPUT);
    pinMode(greens[i], OUTPUT);
  }
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin, OUTPUT);
  }

void loop()
{

  float dist = hc.dist(0);
  if (dist <= 7.5 && dist > 0){
    digitalWrite(redPin1, HIGH);
    digitalWrite(greenPin1, LOW);
  } else {
    digitalWrite(redPin1, LOW);
    digitalWrite(greenPin1, HIGH);
  }

  /*int i;
    for (i = 0; i < 2; i++ ){
        Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(" :");
        Serial.println( hc.dist(i) );

    }*/ //return curent distance (cm) in serial for sensor 1 to 6
    delay(500);
}