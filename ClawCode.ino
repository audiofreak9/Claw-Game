// defines pins numbers

const int rightPin = 22;     // joystick pins
const int leftPin = 24;
const int forwardPin = 26;
const int backPin = 28;

const int clawPin = 30;     // pushbutton pins
const int modePin = 34;
const int startPin = 32;

int rightState = 0;         // variable for reading the joystick status
int leftState = 0;
int forwardState = 0;
int backState = 0;

int clawState = 0;          //variable for the claw button

int chanceState = 0;        //various game states
int startState = 1;
int modeState = 0;

const int stepX = 2;        // stepper pins
const int dirX  = 5;
const int stepY = 3;
const int dirY  = 6;
const int stepZ = 4;
const int dirZ  = 7;

const int enPin = 8;

void setup() {

  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(backPin, INPUT_PULLUP);
  pinMode(clawPin, INPUT_PULLUP);
  pinMode(modePin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP); 

  // Sets the two pins as Outputs
  pinMode(stepX,OUTPUT);
  pinMode(dirX,OUTPUT);
  pinMode(stepY,OUTPUT);
  pinMode(dirY,OUTPUT);
  pinMode(stepZ,OUTPUT);
  pinMode(dirZ,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  Serial.println("CHOOSE MODE | PRESS START...");
}

void moveStep(int stepPin) {
  for(int x = 0; x < 80; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000);
  }           
}

void readButtons() {
  rightState = digitalRead(rightPin);
  leftState = digitalRead(leftPin);
  forwardState = digitalRead(forwardPin);
  backState = digitalRead(backPin);
  clawState = digitalRead(clawPin);
}

void clawGrab() {
  Serial.println("CLAW DOWN");
  digitalWrite(dirZ,HIGH);
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepZ,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepZ,LOW);
    delayMicroseconds(1000);
  }
  delay(500);
  Serial.println("CLAW CLOSE");
  delay(2000);
  Serial.println("CLAW UP");
  digitalWrite(dirZ,LOW);
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepZ,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepZ,LOW);
    delayMicroseconds(1000);
  }
}

void loop() {
  
  if(startState == 1){
      startState = digitalRead(startPin);
      if (startState == LOW) {
        Serial.println("GAME READY...");
        startState = 0;
      }
      
  }else{

    readButtons();
    
    if(chanceState == 0) { 
      
      if (rightState == LOW) {
        Serial.println("RIGHT");
        digitalWrite(dirX,LOW);
        moveStep(stepX);
      }
      if (leftState == LOW) {
        Serial.println("LEFT");
        digitalWrite(dirX,HIGH);
        moveStep(stepX);
      }
      if (forwardState == LOW) {
        Serial.println("FORWARD");
        digitalWrite(dirY,LOW);
        moveStep(stepY);
      }
      if (backState == LOW) {
        Serial.println("BACK");
        digitalWrite(dirY,HIGH);
        moveStep(stepY);
      }
      if (clawState == LOW) {
        clawGrab();
        chanceState = 1; 
      }
      
    }else{ 
      
      Serial.println("RETURN HOME");
      delay(2000);
      Serial.println("CLAW OPEN");
      delay(2000);
      chanceState = 0;
      startState = 1;
      Serial.println("GAME OVER...");
      delay(800);
      Serial.println("CHOOSE MODE | PRESS START...");
    }
  }
}
