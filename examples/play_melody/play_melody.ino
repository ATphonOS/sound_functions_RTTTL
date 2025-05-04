#include "sound_fun_rtttl.h"
#include "melodies.h"

MelodyState melodyState;

void setup() {
  Serial.begin(9600);
  initSpeaker();  
  playMelody(melodyState, const_cast<ToneFrequency*>(twinkleMelody), const_cast<ToneDuration*>(twinkleDurations), TWINKLE_MELODY_LENGTH, false, 3);
}
void loop() {
  updateMelody(melodyState);
}
