
// CNC Shield Stepper  Control Demo
// Superb Tech
// www.youtube.com/superbtech
String inString = "";
int stringToInteger;
int motorVariables[6] = {0, 0, 0, 0, 0, 0};


const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
/*
const int StepZ = 4;
const int DirZ = 7;
*/

void setup() {
   Serial.begin(9600);
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
  pinMode(StepY,OUTPUT);
  pinMode(DirY,OUTPUT);

}

void loop() {
  int counter = 0;
  while (Serial.available() > 0)
    {
  
      int inChar  = Serial.read();
      // Returns first token
      if (isDigit(inChar))inString += (char)inChar;
      
      if (inChar == '\n')
      {
        stringToInteger = inString.toInt();
  
        motorVariables[counter] = stringToInteger;
        Serial.println(counter);
        Serial.println(motorVariables[counter]);
        inString = "";
        counter++;
      }
    }

 digitalWrite(DirX, bool(motorVariables[0])); // set direction, HIGH for clockwise, LOW for anticlockwise
 digitalWrite(DirY, bool(motorVariables[3]));
 
 for(int x = 0; x<int(motorVariables[1]); x++) { // loop for 200 steps
  digitalWrite(StepX,HIGH);
  delayMicroseconds(int(motorVariables[2]));
  digitalWrite(StepX,LOW); 
  delayMicroseconds(int(motorVariables[2]));
 }
 delay(1000); // delay for 1 second
Serial.println("ff");
 for(int x = 0; x<int(motorVariables[4]); x++) { // loop for 200 steps
  digitalWrite(StepY,HIGH);
  delayMicroseconds(int(motorVariables[5]));
  digitalWrite(StepY,LOW); 
  delayMicroseconds(int(motorVariables[5]));
 }
 delay(1000); // delay for 1 second

}
