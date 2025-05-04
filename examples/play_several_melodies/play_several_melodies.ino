#include "sound_fun_rtttl.h"

// Declare state structures for each type of playback
ToneState toneState;
AlertState alertState;
AlertState beepState;
ToneSeriesState seriesState;
SirenState sirenState;
MelodyState rtttlState;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for the serial port to be ready
  }
  initSpeaker(); // Initialize the speaker pin to the default pin
  Serial.println(F("SoundFunctions Example without playMelody"));

  // 1. Play a single tone
  Serial.println(F("Playing a single tone (MEDIUM_A, SHORT_DURATION)"));
  playTone(toneState, MEDIUM_A, SHORT_DURATION);
  while (toneState.isPlaying) {
    updateTone(toneState);
  }
  delay(500); // Short pause between examples

  // 2. Play an alert sequence
  Serial.println(F("Playing an alert sequence (3 tones, HIGH_C, MEDIUM_DURATION, 300ms lapse)"));
  playAlert(alertState, 3, HIGH_C, MEDIUM_DURATION, 300);
  while (alertState.isPlaying) {
    updateAlert(alertState);
  }
  delay(500);

  // 3. Play a beep sequence
  Serial.println(F("Playing a beep sequence (5 beeps, LOW_G, VERY_SHORT_DURATION, 200ms lapse)"));
  playBeep(beepState, 5, LOW_G, VERY_SHORT_DURATION, 200);
  while (beepState.isPlaying) {
    updateAlert(beepState);
  }
  delay(500);

  // 4. Play a tone series
  Serial.println(F("Playing a tone series (500Hz to 1000Hz, 50Hz steps, SHORT_DURATION)"));
  playToneSeries(seriesState, 500, 1000, 50, SHORT_DURATION);
  while (seriesState.isPlaying) {
    updateToneSeries(seriesState);
  }
  delay(500);

  // 5. Play a siren effect
  Serial.println(F("Playing a siren effect (LOW_C to HIGH_C, LONG_DURATION)"));
  playSiren(sirenState, LOW_C, HIGH_C, LONG_DURATION);
  while (sirenState.isPlaying) {
    updateSiren(sirenState);
  }
  delay(500);

  // 6. Play an RTTTL melody
  Serial.println(F("Playing an RTTTL melody (Nokia tune)"));
  const char* nokiaTune = "Nokia:d=4,o=5,b=225:8e6,8d6,f#,g#";
  playRTTTLMelody(rtttlState, nokiaTune, false, 2); // Play twice
  while (rtttlState.isPlaying) {
    updateMelody(rtttlState);
  }
  delay(500);

  // 7. Play a random tone
  Serial.println(F("Playing a random tone (LOW_C to HIGH_C, VERY_SHORT_DURATION to MEDIUM_DURATION)"));
  playRandomTone(LOW_C, HIGH_C, VERY_SHORT_DURATION, MEDIUM_DURATION);
  delay(500); // Wait for the random tone to finish (non-blocking)

  // 8. Demonstrate stopping a tone
  Serial.println(F("Starting a long tone and stopping it after 500ms"));
  playTone(toneState, MEDIUM_E, LONG_DURATION);
  delay(500); // Wait 500ms
  stopTone();
  Serial.println(F("Tone stopped"));
}

void loop() {
  // Empty loop, the example runs entirely in setup()
}