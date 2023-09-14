#include <Servo.h>

Servo myservo;  // create servo object to control a servo
const int trigPin = 4;  // define ultrasonic sensor pins
const int echoPin = 3;

// PID variables
float kp = 23;  // proportional gain
float ki = 0.1;  // integral gain
float kd = 300;  // derivative gain
float error = 0;
float integral = 0;
float derivative = 0;
float last_error = 0;
float setpoint = 15;  // target distance in cm
float output = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 8
  pinMode(trigPin, OUTPUT);  // sets the ultrasonic sensor pins as output and input
  pinMode(echoPin, INPUT);
  Serial.begin(9600);  // initialize serial communication
  myservo.write(90);
}

void loop() {
  long duration, distance;  // variables for ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // send ultrasonic pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // measure echo pulse duration
  distance = duration / 58.2;  // convert duration to distance in cm

  error = setpoint - distance;  // calculate error
  integral += error;  // calculate integral
  if(integral >100){
    integral = 100;    
  }  
  if(integral<-100){
    integral=-100;
  }
  derivative = error - last_error;  // calculate derivative
  output = kp * error + ki * integral + kd * derivative;  // calculate output
  last_error = error;  // save last error

  //if (output > 0 && output <= 180) {
   // move the servo to the new position


  
  Serial.println(output);
  int Fvalue = (int)output;
  //Serial.println(Fvalue);
  Fvalue = constrain(Fvalue,-70, 70);
  if (Fvalue>0){
    Fvalue = map(Fvalue, 0, 70, 90, 95);
  }
  else{
    Fvalue = map(Fvalue , -70 , 0 , 73 , 90);  
  }
  myservo.write(180 - Fvalue);

  //}
  //delay(10);  // wait for servo to move
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(", Setpoint: ");
  Serial.print(setpoint);
  Serial.print(", Error: ");
  Serial.print(error);
  Serial.print(", Output: ");
  Serial.println(Fvalue);  // print variables to serial monitor for debugging
}