
// CNC Shield Stepper  Control Demo
// Superb Tech
// www.youtube.com/superbtech

const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
/*
const int StepZ = 4;
const int DirZ = 7;
*/

void setup() {
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
  pinMode(StepY,OUTPUT);
  pinMode(DirY,OUTPUT);

}

void loop() {
 digitalWrite(DirX, HIGH); // set direction, HIGH for clockwise, LOW for anticlockwise
 digitalWrite(DirY, HIGH);
 
 for(int x = 0; x<20; x++) { // loop for 200 steps
  digitalWrite(StepX,HIGH);
  delayMicroseconds(15000);
  digitalWrite(StepX,LOW); 
  delayMicroseconds(15000);
 }
 delay(1000); // delay for 1 second

 for(int x = 0; x<20; x++) { // loop for 200 steps
  digitalWrite(StepY,HIGH);
  delayMicroseconds(15000);
  digitalWrite(StepY,LOW); 
  delayMicroseconds(15000);
 }
 delay(1000); // delay for 1 second

 digitalWrite(DirX, LOW); // set direction, HIGH for clockwise, LOW for anticlockwise
 digitalWrite(DirY, LOW);
 
 for(int x = 0; x<20; x++) { // loop for 200 steps
  digitalWrite(StepX,HIGH);
  delayMicroseconds(15000);
  digitalWrite(StepX,LOW); 
  delayMicroseconds(15000);
 }
 delay(1000); // delay for 1 second

 for(int x = 0; x<20; x++) { // loop for 200 steps
  digitalWrite(StepY,HIGH);
  delayMicroseconds(15000);
  digitalWrite(StepY,LOW); 
  delayMicroseconds(15000);
 }
 delay(1000); // delay for 1 second

}
