#include <AccelStepper.h>

//Define defaults
#define SPOOL_WIDTH 73 //[mm]
#define SPOOL_PICKUP_DIAMETER 53 //[mm]
#define SPOOL_INNER_DIAMETER 100 //[mm]
#define SPOOL_OUTER_DIAMETER 200 //[mm]
#define SPOOL_SIDE_THICKNESS 3.5 //[mm]

//Define other process parameters
#define EXTRUSION_FEED 9.0 //[mm/s]
#define FILAMENT_DIAMETER 1.75 //[mm]
#define M12_PITCH 1.75 //[mm]
#define STEPS_PER_REVOLUTION 6400L //[steps]
#define MAX_GUIDE_POS 77 //[mm]
#define SETUP_MIN_MSG_LENGTH 14 //[bytes]

//Define stepper motor pins
#define STEPPER_SPOOL_STP 10 //Any digital pin 
#define STEPPER_SPOOL_DIR 9 //Any digital pin 
#define STEPPER_GUIDE_STP 12 //Any digital pin 
#define STEPPER_GUIDE_DIR 11 //Any digital pin 

//Define endstop pin 
#define ENDSTOP 13 //Any digital pin

//Define signal pins
#define INIT_SIGNAL 5 //Any digital pin 
#define REF_SIGNAL 6 //Any digital pin 
#define WINDUP_SIGNAL 7 //Any digital pin 

//Declare extruder process variables
int spoolWidth = SPOOL_WIDTH; 
int spoolPickupDiameter = SPOOL_PICKUP_DIAMETER;
int spoolInnerDiameter = SPOOL_INNER_DIAMETER;
int spoolOuterDiameter = SPOOL_OUTER_DIAMETER;
float endstopOffset = tan(0.87266) * (65 - spoolPickupDiameter) / 2 - 1.3 + SPOOL_SIDE_THICKNESS; //[mm]
long endstopOffsetSteps = endstopOffset / M12_PITCH * STEPS_PER_REVOLUTION; //[steps]
int speedOffset = 0;

//Declare stepper motors and corresponding variables
AccelStepper stepperSpool(1, STEPPER_SPOOL_STP, STEPPER_SPOOL_DIR);
AccelStepper stepperGuide(1, STEPPER_GUIDE_STP, STEPPER_GUIDE_DIR);
double windupSpeed = 0.0; //[1/min]
int turnsPerLayer = 0;
int stepsPerSecond = 0; //[1/s]
int currentLayer = -1;

void initMotors() {
  pinMode(STEPPER_SPOOL_STP, OUTPUT);
  pinMode(STEPPER_SPOOL_DIR, OUTPUT);
  pinMode(STEPPER_GUIDE_STP, OUTPUT); 
  pinMode(STEPPER_GUIDE_DIR, OUTPUT);
  stepperSpool.setMaxSpeed(10000); //[steps/s]
  stepperGuide.setMaxSpeed(10000); //[steps/s]
  windupSpeed = EXTRUSION_FEED / (SPOOL_INNER_DIAMETER * M_PI) * 60; //[1/min]
  stepsPerSecond = windupSpeed / 60 * STEPS_PER_REVOLUTION; //[1/s]
  stepperSpool.setCurrentPosition(0); //[steps]
}

void refStep() {
  stepperGuide.setSpeed(10000); //[steps/s]
  while(digitalRead(ENDSTOP) == LOW) {
    stepperGuide.runSpeed();
  }
  stepperGuide.setCurrentPosition(0); //[steps]
  stepperGuide.moveTo(- endstopOffsetSteps); //[steps]
  stepperGuide.setSpeed(-5000); //[steps/s]
  while(stepperGuide.currentPosition() != stepperGuide.targetPosition()) {
    stepperGuide.runSpeed();
  }
}

void calculateSpeed() {
  turnsPerLayer = (((spoolWidth + endstopOffset) > MAX_GUIDE_POS ? MAX_GUIDE_POS - endstopOffset : spoolWidth) - 2 * SPOOL_SIDE_THICKNESS) / FILAMENT_DIAMETER;
  windupSpeed = EXTRUSION_FEED / ((spoolInnerDiameter + currentLayer * 2 * FILAMENT_DIAMETER) * M_PI) * 60; //[1/min]
  windupSpeed = windupSpeed + (speedOffset / 100.0);
  stepsPerSecond = windupSpeed / 60 * STEPS_PER_REVOLUTION; //[1/s]
  stepperGuide.setSpeed(stepperGuide.speed() < 0 ? -stepsPerSecond : stepsPerSecond);
  stepperSpool.setSpeed(stepsPerSecond); 
  Serial.print(String(windupSpeed) + ";");
}

void windup() {
  if(stepperGuide.currentPosition() != stepperGuide.targetPosition()) {
    stepperGuide.runSpeed();
    stepperSpool.runSpeed();
  } else {
    currentLayer++;
    calculateSpeed();
    if(stepperGuide.currentPosition() == - endstopOffsetSteps) {
      stepperGuide.moveTo(- endstopOffsetSteps - (STEPS_PER_REVOLUTION * turnsPerLayer + FILAMENT_DIAMETER / 2));
      stepperGuide.setSpeed(- stepsPerSecond);
    } else {
      stepperGuide.moveTo(- endstopOffsetSteps);
      stepperGuide.setSpeed(stepsPerSecond);
    }
    stepperGuide.runSpeed();
    stepperSpool.moveTo(stepperSpool.currentPosition() + STEPS_PER_REVOLUTION * turnsPerLayer);
    stepperSpool.setSpeed(stepsPerSecond);
    stepperSpool.runSpeed();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ENDSTOP, INPUT);
  pinMode(INIT_SIGNAL, OUTPUT);
  pinMode(REF_SIGNAL, OUTPUT);
  pinMode(WINDUP_SIGNAL, INPUT);
  initMotors();
  digitalWrite(INIT_SIGNAL, HIGH);
  refStep();
  digitalWrite(REF_SIGNAL, HIGH);
  delay(100);
  digitalWrite(INIT_SIGNAL, LOW);
  digitalWrite(REF_SIGNAL, LOW);
}

void loop() {
  if(Serial.available() >= SETUP_MIN_MSG_LENGTH) {
    //String architecture: "SPOOL_WIDTH;SPOOL_PICKUP_DIAMETER;SPOOL_INNER_DIAMETER;SPOOL_OUTER_DIAMETER;SPEED_OFFSET;"
    spoolWidth = Serial.readStringUntil(';').toInt(); 
    spoolPickupDiameter = Serial.readStringUntil(';').toInt();
    spoolInnerDiameter = Serial.readStringUntil(';').toInt();
    spoolOuterDiameter = Serial.readStringUntil(';').toInt();
    speedOffset = Serial.readStringUntil(';').toInt();
    endstopOffset = tan(0.87266) * (65 - spoolPickupDiameter) / 2 - 1.3 + SPOOL_SIDE_THICKNESS; //[mm]
    endstopOffsetSteps = endstopOffset / M12_PITCH * STEPS_PER_REVOLUTION; //[steps]
    calculateSpeed();
  }
  if(digitalRead(WINDUP_SIGNAL) == HIGH) {
    windup();
  }
}
