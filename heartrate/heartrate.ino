int LED = 8;
int pausePIN =2;
int resetPIN = 3;
int tach_f = 100;
int brad_f = 500;
int heartrate = 30;
int x = 0;
boolean pauseFlag = LOW;


void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pausePIN),pauseF,RISING); // Pauses Function
  attachInterrupt(digitalPinToInterrupt(resetPIN),reset,RISING); // Resets heart Rate information
}

void loop() {
if(pauseFlag == LOW){
  brady();
  tachy();
  }

}

// INTERRUPT FUNCTIONS
//set to 0 code runs, if interrupt fxn activate flag is 1 and code is paused
void pauseF (){
  pauseFlag = !pauseFlag;
}

// if button is pressed reset heart rate average information
void reset () {
  heartrate = 60;
}

// NORMAL FUNCTIONS: Flash lights Tachy at 10 Hz, Brady at 2 Hz
void tachy (){
if (heartrate> 180){
digitalWrite(LED,HIGH);
delay(tach_f); // delay for .1 Seconds or .5 Seconds
digitalWrite(LED,LOW);
delay(tach_f); // delay for .1 Seocnds or .5 seconds
  }
}

void brady (){
  if(heartrate <40){
digitalWrite(LED,HIGH);
delay(brad_f); // delay for .1 Seconds or .5 Seconds
digitalWrite(LED,LOW);
delay(brad_f); // delay for .1 Seocnds or .5 seconds
  }
}

