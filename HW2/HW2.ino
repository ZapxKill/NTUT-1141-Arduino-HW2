int pin[3] = {9, 10, 11};
unsigned int lastPressTime, moodDecreaseTime, t= 0;
byte mood, pressed = 0;
bool droppingMood = false;
const byte neutualMood = 10;
const byte maxMood = 20;
const float brightness = 255 / 10.0;
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<3;i++){
    pinMode(i, OUTPUT);
  }
  pinMode(2, INPUT);
  mood = neutualMood;
}

void loop() {
  t = millis();
  if(digitalRead(2) == 1){
    pressed = 0;
  }
  // put your main code here, to run repeatedly:
  if(digitalRead(2) == 0 &&  pressed == 0){
    lastPressTime = t; 
    pressed = 1;
  }
  if(pressed == 1 && t - lastPressTime > 50){
    
    lastPressTime = t;
    droppingMood = false;
    pressed = 2;
    mood = (mood < maxMood) ? ++mood : maxMood;
  }
  if(!droppingMood && t - lastPressTime > 5000){
    moodDecreaseTime = t;
    droppingMood = true;
  }
  if(droppingMood && t - moodDecreaseTime > 1000){
    moodDecreaseTime = t;
    mood = (mood > 0) ? --mood : 0;
  }
  
  
  if(mood >= neutualMood){
    setRGB(0,  brightness * (maxMood - mood), brightness * (mood - neutualMood));
  }
  else{
    setRGB(brightness * (neutualMood - mood), brightness * mood, 0);
  }
}

void setRGB(char R, char G, char B){
    analogWrite(9, 255 - R);
    analogWrite(10, 255 - G);
    analogWrite(11, 255 - B);
}
