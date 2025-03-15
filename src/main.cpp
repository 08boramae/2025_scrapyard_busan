#include <Arduino.h>
#include <IRremote.hpp>

// IR Receiver and LED pins
#define IR_RECEIVE_PIN 2
#define LED_TEST_LIGHT_PIN 5

// Stepper motor pins
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Motor control pins
#define MOTOR_LEFT 3
#define MOTOR_RIGHT 4

// Relay pin
#define RELAY_PIN 7

void setup() {  
  Serial.begin(9600);
  Serial.println("System started");
  
  pinMode(LED_TEST_LIGHT_PIN, OUTPUT);
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);
  pinMode(IN3, INPUT);
  pinMode(IN4, INPUT);

  IrReceiver.begin(IR_RECEIVE_PIN);
  IrReceiver.enableIRIn();
}

void loop() {
  // IR signal received
  if (IrReceiver.decode()) {
    uint32_t irCode = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("IR code received: 0x");
    Serial.println(irCode, HEX);
    
    // Forward command
    if (irCode == 0xE916FF00) {
      Serial.println("Water pump");
      
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(LED_TEST_LIGHT_PIN, HIGH);
      delay(1000);
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_TEST_LIGHT_PIN, LOW);
      IrReceiver.resume();
    }
    else if (irCode == 0x7E755452) {
      Serial.println("Go Forward");
      digitalWrite(MOTOR_LEFT, HIGH);
      digitalWrite(MOTOR_RIGHT, HIGH);
      delay(1000);
      digitalWrite(MOTOR_LEFT, LOW);
      digitalWrite(MOTOR_RIGHT, LOW);
      IrReceiver.resume();
    }
  }
  delay(200);
}