#include "sound_fun_rtttl.h"
#include "rtttl_PROGMEM_melodies.h"

MelodyState melodyState;

void setup() {
  Serial.begin(9600);
  initSpeaker();  
  
 // Start playing the melody from PROGMEM
  playRTTTLMelody(melodyState, NOKIA, true, 2);  // Play 2 times
}

void loop() {
  updateMelody(melodyState);
}
