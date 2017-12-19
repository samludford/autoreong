#include "Timer.h"

int solenoid_pins[] = {13, 12, 11, 10};
int play_speeds[] = {0, 0, 0, 0};

int fsr_pins[] = {0, 1, 2, 3};
int fsr_readings[4];

const int rev_time = 50;  // <- must be < hit_delay
const int hit_delay = 100;

int counter = 0;

Timer t1;

void setup() {
  
  for(int i=0 ; i < 1 ; i++) {
    pinMode(solenoid_pins[i], OUTPUT);
  }

  Serial.begin(9600);
  t1.every(hit_delay, hit_on);
 
}

void loop() {

  t1.update();

  for (int i=0 ; i < 4 ; i++) {
    fsr_readings[i] = analogRead(fsr_pins[i]);
  }

  log_fsr_readings();

  for(int i=0 ; i < 4 ; i++) {
    set_play_speed(i, fsr_readings[i]);
  }
  
}

void set_play_speed(int solenoid_pos, int fsr_reading) {
  if(fsr_reading < 100) {
    play_speeds[solenoid_pos] = 10;
  } else if (fsr_reading < 300) {
    play_speeds[solenoid_pos] = 9;
  } else if (fsr_reading < 400) {
    play_speeds[solenoid_pos] = 8;
  } else if (fsr_reading < 500) {
    play_speeds[solenoid_pos] = 7;
  } else if (fsr_reading < 600) {
    play_speeds[solenoid_pos] = 6;
  } else if (fsr_reading < 700) {
    play_speeds[solenoid_pos] = 5;
  } else if (fsr_reading < 800) {
    play_speeds[solenoid_pos] = 4;
  } else if (fsr_reading < 900) {
    play_speeds[solenoid_pos] = 3;
  } else if (fsr_reading < 950) {
    play_speeds[solenoid_pos] = 2;
  } else if (fsr_reading < 1000) {
    play_speeds[solenoid_pos] = 1;
  } 
}

void hit_on() {

  for(int i=0 ; i < 4 ; i++) {
    
    int solenoid_pin = solenoid_pins[i];
    int play_speed = play_speeds[i];
  
    if(play_speed != 10) {
      if(counter % play_speed == 0) {
        digitalWrite(solenoid_pin, HIGH);     
      }
    }
    
  }

  delay(rev_time);

  for(int i=0 ; i < 4 ; i++) {
    int solenoid_pin = solenoid_pins[i];
    int play_speed = play_speeds[i];
  
    if(play_speed =! 10) {
      if(counter % play_speed == 0) {
        digitalWrite(solenoid_pin, LOW);     
      }
    } 
  }
  
  counter++;
  
}

void log_fsr_readings() {
  Serial.println("analog readings: ");
  for (int i=0 ; i < 4 ; i++) {
    Serial.println(fsr_readings[i]);
  }  
  Serial.println("-----");
  Serial.println();
}

