#include <IRremote.hpp>

// IR Receiver and LED pins
#define IR_RECEIVE_PIN 2
#define LED_TEST_LIGHT_PIN 5

// Stepper motor pins
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Motor control variables
const int STEPS_PER_REVOLUTION = 4096;  // Full rotation for 28BYJ-48
int currentStep = 0;
boolean clockwise = true;

// Function prototype declaration
void moveStepperOneStep();

void setup() {
  Serial.begin(9600);
  Serial.println("IR Stepper Control Start");
  
  // Setup pins
  pinMode(LED_TEST_LIGHT_PIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    
    if (IrReceiver.decodedIRData.decodedRawData == 0xE916FF00) {
      digitalWrite(LED_TEST_LIGHT_PIN, HIGH);
      
      // Complete one full rotation
      for (int i = 0; i < STEPS_PER_REVOLUTION; i++) {
        moveStepperOneStep();
        delayMicroseconds(1200); // Optimal speed without missing steps
      }
      
      digitalWrite(LED_TEST_LIGHT_PIN, LOW);
      
      // Turn off all motor coils
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
    
    IrReceiver.resume();
  }
  delay(100);
}

// Function to move the stepper motor one step
void moveStepperOneStep() {
  switch (currentStep) {
    case 0:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 4:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 5:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 6:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 7:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
  }

  // Update step count for next step
  currentStep = (currentStep + (clockwise ? 1 : -1)) % 8;
  if (currentStep < 0) currentStep += 8; // Handle negative modulo
}