const int ledPin =  13;
int ledState = LOW;

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0) {
    char command = Serial.read();
    if(command == '2') {
      // mad emostion 
      digitalWrite(6, HIGH);//vibration 
      digitalWrite(ledPin, LOW);//heatpad 
      delay(60000);
      digitalWrite(6, LOW);
      digitalWrite(ledPin, HIGH);
    }
    else if(command == '3'){
      for(int i = 0; i<55;i++){
       digitalWrite(ledPin,HIGH);
       digitalWrite(6, HIGH);
       delay(3000);
       digitalWrite(ledPin,LOW);
       digitalWrite(6, LOW);
      delay(1000);
      }
  }

   else if(command == '4') {

    digitalWrite(6, HIGH);
  }
}
}
