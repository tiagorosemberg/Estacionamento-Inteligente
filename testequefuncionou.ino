#include <HCSR04.h>

HCSR04 hc(5, new int[2]{12, 13}, 2); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)

void setup()
{ Serial.begin(9600); }

void loop()
{
  int i;
    for (i = 0; i < 2; i++ ){
        Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(" :");
        Serial.println( hc.dist(i) );

    } //return curent distance (cm) in serial for sensor 1 to 6
    delay(500);                        // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
}