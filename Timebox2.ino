#include <Time.h>
#include <TimeAlarms.h>
#include <Servo.h>
 
Servo servo;

const int port_button_one_min = 5;  //D5
const int port_button_five_min = 7; //D7
const int port_servo = 9;           //D9 
const int port_speaker = 3;         //D3    

int nCounterButton = 0;
int nCounterMinutes = 0;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int melodyTakeOnMe[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

int durationsTakeOnMe[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

void setup() {
  pinMode(port_button_one_min, INPUT_PULLUP);
  pinMode(port_button_five_min, INPUT_PULLUP);
  Serial.begin(9600);

  servo.attach(port_servo);

  Alarm.timerRepeat(60, minuteLoop);            // timer for every 60 seconds
  servoOpen();

  Serial.println("Setup done");
  speaker(3);
}

void loop() {
  if (digitalRead(port_button_one_min) == LOW) {
      speaker(1);
      nCounterButton += 1;
      nCounterMinutes = 0;
      servoInstantOpen();
      Serial.println("Button 1 min pressed, Counter:");
      Serial.println(nCounterButton);
      Alarm.delay(1000);
      Serial.println("Button wieder frei");
   }

   if (digitalRead(port_button_five_min) == LOW) {
      speaker(5);
      nCounterButton += 5;
      nCounterMinutes = 0;
      servoInstantOpen();
      Serial.println("Button 5 min pressed, Counter:");
      Serial.println(nCounterButton);
      Alarm.delay(1000);
      Serial.println("Button wieder frei");
   }

   Alarm.delay(0);
}

void minuteLoop () {
  nCounterMinutes++;
  
  Serial.println("minuteLoop");
  Serial.println(nCounterMinutes);

 if (nCounterButton > 0 && nCounterButton == nCounterMinutes) {
  servoClose();
  nCounterButton = 0;
  nCounterMinutes = 0;
  
  takeOnMe();
 }
}

void servoOpen () {
  Serial.println("servoOpen");
  for (int i= 50; i<=110;i++) {
    servo.write(i);
    Alarm.delay(20);
  }
}

void servoInstantOpen () {
  Serial.println("servoInstantOpen");
  servo.write(110);
}

void servoClose () {
  Serial.println("servoClose");
   for (int i=110; i>=50;i--) {
    servo.write(i);
    Alarm.delay(1);
  }
}

void servoInstantClose () {
  Serial.println("servoInstantClose");
  servo.write(50);
}

void takeOnMe() {
  for (int thisNote = 0; thisNote < sizeof(melodyTakeOnMe)/sizeof(melodyTakeOnMe[0]); thisNote++){
    int duration = 1000/ durationsTakeOnMe[thisNote];
    tone(port_speaker, melodyTakeOnMe[thisNote], duration);
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(port_speaker);
  }
}

void speaker(int nCount) {
  for (int i=0; i<nCount; i++) {
    tone(port_speaker, NOTE_FS5);
    Alarm.delay (100);
    noTone(port_speaker);
    Alarm.delay (100);
  }
}
