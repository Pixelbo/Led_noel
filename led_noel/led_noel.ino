#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 6
#define PIXEL_COUNT 100

#define VAGUE_LENGHT 7
int vague_r[VAGUE_LENGHT] = {250, 200, 150, 0, 150, 200, 250};

boolean arrayIncludeElement(int array[], int element);
boolean arrayIncludeElement(int array[], int element) {
  if (array[element] == 1) {
    return true;
  }
    return false;
}

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_RGB + NEO_KHZ800);

byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}


void off_start(int delai){
  for(int i = 0 ; i <= PIXEL_COUNT-1 ; i++){
       strip.setPixelColor(i, 0, 0, 0);
       strip.show();
       delay(delai); 
    }
}

void off_end(int delai){
  for(int i = PIXEL_COUNT-1 ; i >= 0 ; i--){
       strip.setPixelColor(i, 0, 0, 0);
       strip.show();
       delay(delai); 
    }
}

void off_extremity(int delai){
  int k = PIXEL_COUNT;
  for(int i = 0 ; i <= PIXEL_COUNT/2 ; i++){
    Serial.println(k);
    strip.setPixelColor(i, 0);
    strip.setPixelColor(k, 0);
    strip.show();
    k--;
    delay(delai);
  }
}

void led_run(int r, int g, int b, int delai){
     int r2,g2,b2;

     for(int k = PIXEL_COUNT-1 ; k >= 0 ; k--){
      if(r==0 && g==0 && b==0){
        r2 = random(0,255);
        g2 = random(0,255);
        b2 = random(0,255);
      }else{
        r2 = r;
        g2 = g;
        b2 = b;
      }
       for(int i = 0 ; i <= k ; i++){
         strip.setPixelColor(i, r2, g2, b2);
         strip.setPixelColor(i-1, 0, 0, 0);
         strip.show();
         delay(delai); 
       }
    }
}

void fill_(int r, int g, int b, int delai){
  int r2,g2,b2;

  for(int i = 0 ; i <= PIXEL_COUNT-1 ; i++){
      if(r==0 & g==0 & b==0){
        r2 = random(0,255);
        g2 = random(0,255);
        b2 = random(0,255);
      }else{
        r2 = r;
        g2 = g;
        b2 = b;
      }
       strip.setPixelColor(i, r2, g2, b2);
       strip.show();
       delay(delai); 
    }
}

void wave(int r, int g, int b, int delai){
  for(int i = 0 ; i <= PIXEL_COUNT+VAGUE_LENGHT ; i++){
       for(int k=0 ; k < VAGUE_LENGHT ; k++){
         strip.setPixelColor(i-k, r!=0 ? r-vague_r[k] : 0, g!=0 ? r-vague_r[k] : 0, b!=0 ? r-vague_r[k] : 0);
         strip.setPixelColor(i-(VAGUE_LENGHT+1), 0, 0, 0);
         strip.show();
       }
       delay(delai); 
    }
}

void fill_middle(int r, int g, int b, int delai){
  int k = PIXEL_COUNT/2;
  for(int i = PIXEL_COUNT/2 ; i >= 0 ; i--){
    Serial.println(k);
    strip.setPixelColor(i, r, g, b);
    strip.setPixelColor(k, r, g, b);
    strip.show();
    k++;
    delay(delai);
  }
}

void fill_extremity(int r, int g, int b, int delai){
  int k = 0;
  for(int i = PIXEL_COUNT ; i >= PIXEL_COUNT /2 ; i--){
    Serial.println(k);
    strip.setPixelColor(i, r, g, b);
    strip.setPixelColor(k, r, g, b);
    strip.show();
    k++;
    delay(delai);
  }
}
  
void circus(int r1, int g1, int b1, int r2, int g2, int b2, int delai){
  for(int k = 0 ; k <= 20 ; k++){
  	for(int i = 0 ; i <= PIXEL_COUNT-1 ; i++){
  		if(i&1 == 1){
  			strip.setPixelColor(i, k&1==1 ? r1:r2, k&1==1 ? g1:g2, k&1==1 ? b1:b2);
  		}else{
        strip.setPixelColor(i, k&1==1 ? r2:r1, k&1==1 ? g2:g1, k&1==1 ? b2:b1);
  		}
      strip.show();
  	}
   delay(delai);
  }
}

void random_on(int delai){
  int rand_[PIXEL_COUNT] = {};
  int randnum = random(0 , PIXEL_COUNT);
  for(int i = 0; i<PIXEL_COUNT ; i++){
    while(arrayIncludeElement(rand_, randnum)) randnum = random(0 , PIXEL_COUNT);
    rand_[randnum] = 1;
    Serial.println(i);
    strip.setPixelColor(randnum, random(0,255), random(0,255), random(0,255));
    strip.show();
    delay(delai);
  }
  Serial.println("exit");
}

void random_off(int delai){
  int rand2_[PIXEL_COUNT] = {};
  int randnum = random(0 , PIXEL_COUNT);
  Serial.println("test");
  for(int i = 0; i<PIXEL_COUNT ; i++){
    while(arrayIncludeElement(rand2_, randnum)) randnum = random(0 , PIXEL_COUNT); 

    rand2_[randnum] = 1;
    strip.setPixelColor(randnum, 0,0,0);
    strip.show();
    delay(delai);
  }
}
void setup() {
   Serial.begin(9600);
   Wire.begin();
   strip.begin(); // Lance la connection
   strip.show(); // Initialise toute les led à 'off'

}

void loop() {
  circus(0,0,255,255,0,0,50);
  wave(0,0,255,20);
  led_run(0,0,0,0);
  off_start(20);
  random_on(50);
  random_off(20);
  fill_extremity(0,0,255,50);
  off_extremity(50);
  fill_middle(0,0,255,50);
  off_end(20);
}
