#include <HCSR04.h>

byte trigPin = 5; //D1
byte echoPin1 = 12; //D6
byte echoPin2 = 13; //D7
byte redPin1 = 2; //D4
byte redPin2 = 15; //D8
byte greenPin1 = 14; //D5
byte greenPin2 = 16; //D0


HCSR04 hc(trigPin, new int[2]{echoPin1, echoPin2}, 2); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)

new byte reds[2] = {redPin1, redPin2};
new byte greens[2] = {greenPin1, greenPin2};

void setup(){
  Serial.begin(9600);
  int i;
  for (i = 0; i < 2; i++){
    pinMode(reds[i], OUTPUT);
    pinMOde(greens[i], OUTPUT);
  }
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin, OUTPUT);
  }

void loop()
{

  float dist = hc.dist(0);
  if (dist <= 10 && dist > 0){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
  }

  /*int i;
    for (i = 0; i < 2; i++ ){
        Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(" :");
        Serial.println( hc.dist(i) );

    }*/ //return curent distance (cm) in serial for sensor 1 to 6
    delay(500);                        // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
}