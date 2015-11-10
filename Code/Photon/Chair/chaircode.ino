#include "MQTT.h"
#define BUTTONTHRESHOLD 1
#define BUTTONDELAY 500
#define BUTTONPIN A0

int num = 1;
int sensorPin = A1;
int sensorValue = 0;
int sensorReading = 0;

char subscribedChannel[] = "rob/in";
char publishChannel[] = "ZPM";
char clientID[] = "rob1"; // set a unique name for each device connected to the broker

int state;

void callback(char* topic, byte* payload, unsigned int length); //declare the call backe

MQTT client("broker.i-dat.org", 80, callback); //client object - what we will talk to

//triggered when a message is recieved on a subscribed channel
void callback(char* topic, byte* payload, unsigned int length) {
    // handle message
  //  Serial.println("Message Recieved");
  //  Serial.println(topic);

    //converts payload into usable string
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);
  //  Serial.println(message);

    //check the topic - use this is you want to sunbscribe to more than one channel
    if (String(topic) == String(subscribedChannel)){
      //do stuff

      //change the LED Pin on/off
      //state = !state;
      //digitalWrite(LEDPIN, state);
  }
}

void connectToBroker(){
  delay(10000);
//  Serial.println("Connecting");
  //connect to the broker
  delay(10000);
    if (client.connect(clientID)) {

      //send a test message
      //Serial.println("Connected!");
      client.publish("mqtt/debug","set a nice test message here");
      //subscribe to a channel
      //client.subscribe(subscribedChannel);

    } else{
      //Serial.println("Connection Error");
    }

}

void setup() {
    //open the serial port for debugging
    //Serial.begin(9600);
    //Serial.println("setup");

    connectToBroker();
}

void loop() {
    //check and maintain the connection to the broker
    if(!client.isConnected()){
       //Serial.println("Disconnected");
       connectToBroker();
    }else{
      client.loop();
    }

    sensorReading = analogRead(sensorPin);

    //Serial.print("Analog reading = ");
    //Serial.println(sensorReading); // the raw analog reading

    //we need to convert a number into a char array to send it over MQTT:
    char buffer [4];
    sprintf (buffer, "%03i",num );
    if (sensorReading<3300){

      client.publish("relax/chair",buffer);
      delay(100000);


    }
    delay(1000);


    /*if (sensorReading >= threshold){
      client.publish("state","HIGH");

    }
    else {
      client.publish("state","LOW");

    }*/


  }
