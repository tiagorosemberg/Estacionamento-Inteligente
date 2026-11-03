#include <HCSR04.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

byte trigPin = 5; //D1
byte echoPin1 = 12; //D6
byte echoPin2 = 13; //D7
byte redPin1 = 2; //D4
byte redPin2 = 15; //D8
byte greenPin1 = 14; //D5
byte greenPin2 = 16; //D0


HCSR04 hc(trigPin, new int[2]{echoPin1, echoPin2}, 2);


byte reds[2] = {redPin1, redPin2};
byte greens[2] = {greenPin1, greenPin2};

const char* ssid = "Vasco";
const char* password = "iphone-11";

const char* mqtt_server = "mqtt-dashboard.com";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("usuario", "hello world");
      // ... and resubscribe
      client.subscribe("estacionamento/vagas");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setup(){


  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

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

  if (!client.connected()){
    reconnect();
  }
  client.loop();

  float dist;
  int i = 0;
  int vagas[2] = {0, 0};
  
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    for(i = 0; i < 2; i++){
      dist = hc.dist(i);
      if (dist <= 7.5 && dist > 0){
        digitalWrite(reds[i], HIGH);
        digitalWrite(greens[i], LOW);
        vagas[i] = 0;
      } else {
        digitalWrite(reds[i], LOW);
        digitalWrite(greens[i], HIGH);
        vagas[i] = 1;
      }
    }
      
      snprintf (msg, 50, "{\"esp\":1,\"vagas\":[%d,%d]}", vagas[0], vagas[1]);
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish("estacionamento/vagas", msg);
  }

    delay(500);
}
