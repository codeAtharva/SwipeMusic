#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
int FADESPEED = 5;     // make s higher to slow down
const int audioAmp = A0;
int reading = 0;
int data[500];
int items = 0;
int maxValue = 0;
int maxAmp = 0;
int volumelevel = 0;

int average() {
  int sum = 0;
  int counter = 0;
  int ans = 0;
  for (int i = 0; i < 500; i++) {
    sum += data[i]; 
    counter++;
  }
  ans = sum/counter;
  return ans;
}

void reset() {
  for (int i = 0; i< 500; i++) {
    data[i] = 0;
  }
  items = 0;
  maxValue = 0;
  maxAmp = 0;
}


void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
   pinMode(audioAmp, INPUT);
  Serial.begin(9600);
}


void loop() {
  Serial.println("start");
for (int i = 0; i < 500; i++) { //gathering 500 values in data
    data[i] = analogRead(audioAmp);
    items++;
    if (abs(data[i]) > abs(maxValue))
      maxValue = abs(data[i]);         //getting the maximum value, maxValue is always positive
  }
  int baseline = average();
  //Serial.println(baseline);
  maxAmp = maxValue - baseline;
  volumelevel = maxAmp;
  //Serial.println(maxAmp);
  reset();
  delay(10);




  ////
  int r, g, b;
if(volumelevel < 280 )
  FADESPEED = 500;
else if(volumelevel < 310 )
  FADESPEED = 100;
else if(volumelevel < 360 )
  FADESPEED = 50;
else if(volumelevel < 400)
  FADESPEED = 1;
else {
  FADESPEED = 1;
  
}
Serial.print("delay:");
Serial.println(FADESPEED);
Serial.print("volumelevel: ");
Serial.println(volumelevel);
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
    
  } 
  delay(FADESPEED);
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    
  } 
  delay(FADESPEED);
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    
  } 
  delay(FADESPEED);
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
   
  } 
   delay(FADESPEED);
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
   
  } 
   delay(FADESPEED);
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
   
  }
   delay(FADESPEED); 
  Serial.print("end");
}
//speaker code at the bottom 










