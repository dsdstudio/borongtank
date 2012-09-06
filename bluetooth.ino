/**
// @Author dsdgun@gmail.com
// @site blog.dsdstudio.net
*/
#include <SoftwareSerial.h>

#define m1_pri_pin 8
#define m1_slv_pin 9
#define m2_pri_pin 10
#define m2_slv_pin 11

#define BT_RX_PIN 2
#define BT_TX_PIN 3

SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN); 

void setup() {
  pinMode(m1_pri_pin, OUTPUT);
  pinMode(m1_slv_pin, OUTPUT);
  pinMode(m2_pri_pin, OUTPUT);
  pinMode(m2_slv_pin, OUTPUT);
  
  Serial.begin(9600); 
  BTSerial.begin(9600);
}

/**
// from data Bluetooth virtual serial port
// to String Object
*/
String getSignalString(){
    String signal = "";
    while (BTSerial.available() > 0) {
      signal += (char)BTSerial.read();
    };
   return signal; 
}

void loop() { 
  if (BTSerial.available()){
    String signal = getSignalString();
    if ( signal.indexOf("#MHH") != -1 ){
       stop();
    }
    if ( signal.indexOf("#MFF") != -1 ){
      forward();
    }
    if ( signal.indexOf("#MBB") != -1 ){
      backword();
    }
    
    if ( signal.indexOf("#MBF") != -1 ) {
      left();
    }
    
    if ( signal.indexOf("#MFB") != -1 ) {
      right();
    }
    
    // signal Debugging Message
    Serial.println(signal);
  }
}

void forward_pwm(){ 
  analogWrite(m1_pri_pin, 100);
  analogWrite(m1_slv_pin, 0); 
  analogWrite(m2_pri_pin, 100);
  analogWrite(m2_slv_pin, 0); 
}

void stop(){
  digitalWrite(m1_pri_pin, LOW);
  digitalWrite(m1_slv_pin, LOW); 
  digitalWrite(m2_pri_pin, LOW);
  digitalWrite(m2_slv_pin, LOW); 
}
/*
// Move forward Tank
*/
void forward(){ 
  digitalWrite(m1_pri_pin, HIGH);
  digitalWrite(m1_slv_pin, LOW); 
  digitalWrite(m2_pri_pin, HIGH);
  digitalWrite(m2_slv_pin, LOW); 
}

/*
// Move backward Tank
*/
void backword() { 
  digitalWrite(m1_pri_pin, LOW);
  digitalWrite(m1_slv_pin, HIGH);
  digitalWrite(m2_pri_pin, LOW);
  digitalWrite(m2_slv_pin, HIGH);
}

/*
// Turn right Tank 
*/
void right(){
  digitalWrite(m1_pri_pin, LOW);
  digitalWrite(m1_slv_pin, HIGH);
  digitalWrite(m2_pri_pin, HIGH);
  digitalWrite(m2_slv_pin, LOW);  
}

/*
// Turn Left Tank
*/
void left(){
  digitalWrite(m1_pri_pin, HIGH);
  digitalWrite(m1_slv_pin, LOW);
  digitalWrite(m2_pri_pin, LOW);
  digitalWrite(m2_slv_pin, HIGH);

}
