#include <Adafruit_CircuitPlayground.h>
#include <Arduino.h>
#include "math.h"
#include <Adafruit_ZeroFFT.h>

#define sampleRate 100
# define conf_len 21 // for a minute window on confirming tremor
# define demo_len 3 // for a 10 sec window on confirming tremor

// Check if arrray members >1100 used to tell if a tremor is happening over 1 min

int checkArr(float arr[], int size) {
    int cnt = 0;
    for (int i = 0; i < size; i++) {
        if(arr[i]>1100){
          cnt++;
        }
    }
    if (cnt == conf_len){
      return 1;
    }
    return 0;
}

int16_t buffer[sampleRate] = {0}; // Buffer to store resultant magnitudes
uint8_t bufferIndex = 0; // Index for buffer array
float tremor_conf[conf_len] ={0}; // Array to store avg of tremor intensity 3-6 hz for 1 min
int trem_count =0; //Index for intensity array
int trem_detect = 0; // Flag to indicate if tremor is detected
bool dataReady = false; // Flag to indicate that data is ready to be sent
float X, Y, Z;

void setupTimer();

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  setupTimer();
  DDRC |= 0b10000000; //led set up as output
  DDRF &= ~(1<<PF4);
}

ISR(TIMER0_COMPA_vect){
  // Calculate resultant magnitude from 3-axis readings
    float resultant = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
    // Store the resultant in the buffer and increment the buffer index
    buffer[bufferIndex] = static_cast<int16_t>(resultant*100); //Cast buffer as int and scale for FFT
    bufferIndex++;
    // Reset buffer index to prevent overflow
    if (bufferIndex >= sampleRate) {
        bufferIndex = 0;
        dataReady = true; //set data ready true
        TIMSK0 &= ~(1 << OCIE0A); //disable interrupt
    }
}

void loop() {
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  
  if (trem_detect) { //if tremor detected light up led
    PORTC |= 0b10000000;

    float sum = 0;

    for (int a = 3; a < 7; a++) {
      sum += (buffer[a]);
    }
    float avg = sum / 4;

    if (avg >= 1100 && avg < 1400) { // Light tremor
      CircuitPlayground.setPixelColor(0, 0, 225, 0);
      CircuitPlayground.setPixelColor(1, 0, 225, 0);
      CircuitPlayground.setPixelColor(2, 0, 0, 0);
      CircuitPlayground.setPixelColor(3, 0, 0, 0);
      CircuitPlayground.setPixelColor(4, 0, 0, 0);
      CircuitPlayground.setPixelColor(5, 0, 0, 0);
      CircuitPlayground.setPixelColor(6, 0, 0, 0);
      CircuitPlayground.setPixelColor(7, 0, 0, 0);
      CircuitPlayground.setPixelColor(8, 0, 0, 0);
      CircuitPlayground.setPixelColor(9, 0, 0, 0);
      CircuitPlayground.playTone(600, 700);
    } else if (avg >= 1400 && avg < 1700) { // Slight tremor
      CircuitPlayground.setPixelColor(0, 255, 225, 0);
      CircuitPlayground.setPixelColor(1, 255, 225, 0);
      CircuitPlayground.setPixelColor(2, 255, 225, 0);
      CircuitPlayground.setPixelColor(3, 255, 225, 0);
      CircuitPlayground.setPixelColor(4, 0, 0, 0);
      CircuitPlayground.setPixelColor(5, 0, 0, 0);
      CircuitPlayground.setPixelColor(6, 0, 0, 0);
      CircuitPlayground.setPixelColor(7, 0, 0, 0);
      CircuitPlayground.setPixelColor(8, 0, 0, 0);
      CircuitPlayground.setPixelColor(9, 0, 0, 0);
      CircuitPlayground.playTone(600, 500);
    } else if (avg >= 1700 && avg < 2000) { // Medium tremor
      CircuitPlayground.setPixelColor(0, 255, 0, 0);
      CircuitPlayground.setPixelColor(1, 255, 0, 0);
      CircuitPlayground.setPixelColor(2, 255, 0, 0);
      CircuitPlayground.setPixelColor(3, 255, 0, 0);
      CircuitPlayground.setPixelColor(4, 255, 0, 0);
      CircuitPlayground.setPixelColor(5, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 0, 0, 0);
      CircuitPlayground.setPixelColor(7, 0, 0, 0);
      CircuitPlayground.setPixelColor(8, 0, 0, 0);
      CircuitPlayground.setPixelColor(9, 0, 0, 0);
      CircuitPlayground.playTone(600, 300);
    } else if (avg >= 2000 && avg < 2400) { // Severe tremor
      CircuitPlayground.setPixelColor(0, 255, 56, 5);
      CircuitPlayground.setPixelColor(1, 255, 56, 5);
      CircuitPlayground.setPixelColor(2, 255, 56, 5);
      CircuitPlayground.setPixelColor(3, 255, 56, 5);
      CircuitPlayground.setPixelColor(4, 255, 56, 5);
      CircuitPlayground.setPixelColor(5, 255, 56, 5);
      CircuitPlayground.setPixelColor(6, 255, 56, 5);
      CircuitPlayground.setPixelColor(7, 255, 56, 5);
      CircuitPlayground.setPixelColor(8, 0, 0, 0);
      CircuitPlayground.setPixelColor(9, 0, 0, 0);
      CircuitPlayground.playTone(800, 100);
      
    } else if (avg > 2400) { // Serious tremor
      CircuitPlayground.setPixelColor(0, 255, 0, 0);
      CircuitPlayground.setPixelColor(1, 255, 0, 0);
      CircuitPlayground.setPixelColor(2, 255, 0, 0);
      CircuitPlayground.setPixelColor(3, 255, 0, 0);
      CircuitPlayground.setPixelColor(4, 255, 0, 0);
      CircuitPlayground.setPixelColor(5, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 255, 0, 0);
      CircuitPlayground.setPixelColor(7, 255, 0, 0);
      CircuitPlayground.setPixelColor(8, 255, 0, 0);
      CircuitPlayground.setPixelColor(9, 255, 0, 0);
      CircuitPlayground.playTone(1000, 50);
    }

  }
  else{
   PORTC &= ~(1<<7);
      CircuitPlayground.setPixelColor(0, 0, 0, 0);
      CircuitPlayground.setPixelColor(1, 0, 0, 0);
      CircuitPlayground.setPixelColor(2, 0, 0, 0);
      CircuitPlayground.setPixelColor(3, 0, 0, 0);
      CircuitPlayground.setPixelColor(4, 0, 0, 0);
      CircuitPlayground.setPixelColor(5, 0, 0, 0);
      CircuitPlayground.setPixelColor(6, 0, 0, 0);
      CircuitPlayground.setPixelColor(7, 0, 0, 0);
      CircuitPlayground.setPixelColor(8, 0, 0, 0);
      CircuitPlayground.setPixelColor(9, 0, 0, 0);
      CircuitPlayground.playTone(0, 0);
  }
    if (dataReady) { //Check if data is ready
      ZeroFFT(buffer,sampleRate);// Perform FFT
      //Add the avg of 3-6 hz intensity to tremor confirmation array

      float sum =0;

      for(int a = 3; a<7; a++){
        sum += (buffer[a]);
      }
      float avg = sum/4;
      tremor_conf[trem_count] = avg;// add the average intensity to 1 min window array
      trem_count++;

      //Reset so doesnt overflow:
      if(trem_count >= conf_len){
        trem_count = 0;
      }

      trem_detect = checkArr(tremor_conf,conf_len); //check if all averages is highet than 1100 in 1 min indicating tremor
      for(int i=0; i<conf_len; i++){
        Serial.println(tremor_conf[i]); // print 1 min array of tremor averages
      }
      dataReady = false; // Reset dataReady flag
      TIMSK0 |= (1 << OCIE0A); //re-enable compare match interrupt
    }
    
}

void setupTimer(){
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR0A |= (1 << WGM01); //CTC mode
  TCCR0B |= (1<<CS02)| (1<<CS00); //prescaler 1024
  TIMSK0 |= (1 << OCIE0A); //enable compare match interrupt
  OCR0A = (F_CPU / (sampleRate * 1024)) - 1; //set compare match register
}