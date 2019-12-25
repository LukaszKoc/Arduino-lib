#ifndef SpeedControl_h
#define SpeedControl_h 

float milisecPerCentimeter = 0.0;

float currentSpeedL = 0.0;
long previousMillisL = 0.0;
long milisNowL = 0.0;
int pulsesL, encoderAL, encoderBL;
int pulsesChangedL = 0;
void ICACHE_RAM_ATTR readSpeedLeft();

float currentSpeedR = 0.0;
long previousMillisR = 0.0;
long milisNowR = 0.0;
int pulsesR, encoderAR, encoderBR;
int pulsesChangedR = 0;
void ICACHE_RAM_ATTR readSpeedRight();

const int stepsPerCentyMeter = 12;
void redSencores(int encoderA, int encoderB, int &pulses);
float calculateSpeed(int &pulses, long &milisNow, long &previousMillis, int &pulsesChanged);

class SpeedControl {
  private:
    int read();
  public:
    void setup();
    SpeedControl() { }
    SpeedControl(int sencor1L_arg, int sencor2L_arg, int sencor1R_arg, int sencor2R_arg) {
      encoderAL = sencor1L_arg; 
      encoderBL = sencor2L_arg;
      encoderAR = sencor1R_arg; 
      encoderBR = sencor2R_arg;
    }
    float getSpeedL();  
    float getSpeedR();    
}; 

void SpeedControl::setup( ) {
  digitalWrite(encoderAL, HIGH);
  digitalWrite(encoderAL, HIGH);
  pinMode(encoderAL, INPUT_PULLUP);
  pinMode(encoderBL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAL), readSpeedLeft, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(encoderBL), readSpeedLeft, CHANGE);
  digitalWrite(encoderAR, HIGH);
  digitalWrite(encoderAR, HIGH);
  pinMode(encoderAR, INPUT_PULLUP);
  pinMode(encoderBR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAR), readSpeedRight, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(encoderBR), readSpeedRight, CHANGE);
}

float SpeedControl::getSpeedL() {
  if (pulsesChangedL != 0) {
    pulsesChangedL = 0;
    Serial.println(String("currentSpeedL: ") + currentSpeedL);
    Serial.println(String("pulsesL: ") + pulsesL);
    return currentSpeedL;
  }
}
float SpeedControl::getSpeedR() {
  if (pulsesChangedR != 0) {
    pulsesChangedR = 0;
    Serial.println(String("currentSpeedR: ") + currentSpeedR);
    Serial.println(String("pulsesR: ") + pulsesR);
    return currentSpeedR;
  }
}

void readSpeedLeft() {
  redSencores(encoderAL, encoderBL, pulsesL);
  currentSpeedL = calculateSpeed(pulsesL, milisNowL, previousMillisL, pulsesChangedL);
}
void readSpeedRight() {
  redSencores(encoderAR, encoderBR, pulsesR);
  currentSpeedR = calculateSpeed(pulsesR, milisNowR, previousMillisR, pulsesChangedR);
}

void redSencores(int encoderA, int encoderB, int &pulses) {
  if ( digitalRead(encoderB) == 0 ) {
    if ( digitalRead(encoderA) == 0 ) {
      // A fell, B is low
      pulses--; // Moving forward
    } else {
      // A rose, B is high
      pulses++; // Moving reverse
    }
  } else {
    if ( digitalRead(encoderA) == 0 ) {
      pulses++; // Moving reverse
    } else {
      // A rose, B is low
      pulses--; // Moving forward
    }
  }
}

float calculateSpeed(int &pulses, long &milisNow, long &previousMillis, int &speedChanged) {
  float currentSpeed = 0;
  if( pulses == stepsPerCentyMeter || pulses == -stepsPerCentyMeter) {
    speedChanged = 1;
    milisNow = millis();
    milisecPerCentimeter = (milisNow - previousMillis);
    if(milisecPerCentimeter > 700) {
      previousMillis =  milisNow;
      pulses = 0;
      return -1;
    }
    previousMillis = milisNow;
    currentSpeed = 0.01 /(milisecPerCentimeter/1000);
    speedChanged = 1;
    pulses = 0;
  }
  return currentSpeed;
}

#endif