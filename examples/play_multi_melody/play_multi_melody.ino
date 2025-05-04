#include "sound_fun_rtttl.h"
#include "melodies.h"

MelodyState melodyState1; // Twinkle Twinkle Little Star
MelodyState melodyState2; // Flight of the Bumblebee
MelodyState melodyState3; // R2-D2 Sounds

enum MelodySequence { PLAY_TWINKLE, PLAY_BUMBLEBEE, PLAY_R2D2, DONE };
MelodySequence currentMelody = PLAY_TWINKLE; 

void setup() {
  Serial.begin(9600);
  initSpeaker(); 
  Serial.println("Starting melody sequence");
  
  playMelody(melodyState1, const_cast<ToneFrequency*>(twinkleMelody), 
             const_cast<ToneDuration*>(twinkleDurations), 
             TWINKLE_MELODY_LENGTH, false, 3);
}

void loop() {
  switch (currentMelody) {
    case PLAY_TWINKLE:
      updateMelody(melodyState1);
      if (!melodyState1.isPlaying) {
        Serial.println("Twinkle melody finished. Starting Flight of the Bumblebee");
        playMelody(melodyState2, const_cast<ToneFrequency*>(flightOfTheBumblebeeMelody), 
                   const_cast<ToneDuration*>(flightOfTheBumblebeeDurations), 
                   FLIGHT_OF_THE_BUMBLEBEE_MELODY_LENGTH, false, 3);
        currentMelody = PLAY_BUMBLEBEE;
      }
      break;

    case PLAY_BUMBLEBEE:
      updateMelody(melodyState2);
      if (!melodyState2.isPlaying) {
        Serial.println("Bumblebee melody finished. Starting R2-D2");
        playMelody(melodyState3, const_cast<ToneFrequency*>(r2d2Melody), 
                   const_cast<ToneDuration*>(r2d2Durations), 
                   R2D2_MELODY_LENGTH, false, 3);
        currentMelody = PLAY_R2D2;
      }
      break;

    case PLAY_R2D2:
      updateMelody(melodyState3);
      if (!melodyState3.isPlaying) {
        Serial.println("R2-D2 melody finished. Sequence complete");
        currentMelody = DONE;
      }
      break;

    case DONE:
      
      Serial.println("All melodies completed");
      delay(1000); 
  }
}
