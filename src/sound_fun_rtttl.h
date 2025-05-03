/**
 * @file sound_fun_rtttl.h
 * @brief Header file for sound generation functions.
 * This file contains functions for generating tones, playing alerts, and RTTTL melodies (including PROGMEM-stored) using a buzzer.
 * Functions are designed to be non-blocking to support concurrent tasks, with support for repeating RTTTL melodies.
 * @author ATphonOS LLC
 * @date 2024
 * MIT license
 */

#ifndef SOUNDFUNCTIONS_H
#define SOUNDFUNCTIONS_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <math.h>

/** @brief Octave offset for tone frequencies. */
#define OCTAVE 0
#define DEFAULT_PIN_SPEAKER 14
/** @brief Minimum allowable frequency for tones (Hz). */
#define MIN_FREQUENCY 31
/** @brief Maximum allowable frequency for tones (Hz). */
#define MAX_FREQUENCY 65535
/** @brief Maximum number of notes in an RTTTL melody. */
#define MAX_RTTTL_NOTES 100

extern uint8_t speakerPin = DEFAULT_PIN_SPEAKER; /**< Global variable for speaker pin */

/**
 * @brief Initialize the speaker pin.
 * @param pin The pin to use for the speaker (default: DEFAULT_PIN_SPEAKER).
 */
void initSpeaker(uint8_t pin = DEFAULT_PIN_SPEAKER) {
  speakerPin = pin;
  pinMode(speakerPin, OUTPUT);
}

/**
 * @brief Get the current speaker pin.
 * @return The pin number used for the speaker.
 */
uint8_t getSpeakerPin() {
  return speakerPin;
}

/**
* @brief Enumeration of tone frequencies.
* This enumeration defines various tone frequencies for generating tones.
*/
enum ToneFrequency {
  LOW_C = 261,
  LOW_C_SHARP = 277,
  LOW_D = 294,
  LOW_D_SHARP = 311,
  LOW_E = 330,
  LOW_F = 349,
  LOW_F_SHARP = 370,
  LOW_G = 392,
  LOW_G_SHARP = 415,
  LOW_A = 440,
  LOW_A_SHARP = 466,
  LOW_B = 494,
  MEDIUM_C = 523,
  MEDIUM_C_SHARP = 554,
  MEDIUM_D = 587,
  MEDIUM_D_SHARP = 622,
  MEDIUM_E = 659,
  MEDIUM_F = 698,
  MEDIUM_F_SHARP = 740,
  MEDIUM_G = 784,
  MEDIUM_G_SHARP = 831,
  MEDIUM_A = 880,
  MEDIUM_A_SHARP = 932,
  MEDIUM_B = 988,
  HIGH_C = 1047,
  HIGH_C_SHARP = 1109,
  HIGH_D = 1175,
  HIGH_D_SHARP = 1245,
  HIGH_E = 1319,
  HIGH_F = 1397,
  HIGH_F_SHARP = 1480,
  HIGH_G = 1568,
  HIGH_G_SHARP = 1661,
  HIGH_A = 1760,
  HIGH_A_SHARP = 1865,
  HIGH_B = 1976,
  VERY_LOW_C = 130,
  VERY_LOW_C_SHARP = 138,
  VERY_LOW_D = 147,
  VERY_HIGH_C = 4186,
  VERY_HIGH_C_SHARP = 4435,
  VERY_HIGH_D = 4699,
  PAUSE = 0 /**< Frequency for a pause (no sound). */
};

/**
 * @brief Enumeration of tone durations.
 * This enumeration defines various durations for playing tones.
 */
enum ToneDuration {
  VERY_SHORT_DURATION = 50,
  SHORT_DURATION = 200,
  MEDIUM_DURATION = 500,
  LONG_DURATION = 1000
};

/**
 * @brief Structure to manage tone playback state.
 * Used for non-blocking tone generation.
 */
struct ToneState {
  bool isPlaying;          /**< Whether a tone is currently playing. */
  uint32_t startTime;      /**< Start time of the current tone (ms). */
  ToneFrequency frequency; /**< Frequency of the current tone. */
  ToneDuration duration;   /**< Duration of the current tone. */
};

/**
 * @brief Structure to manage melody playback state.
 * Used for non-blocking melody playback, including RTTTL melodies with repeat support.
 */
struct MelodyState {
  bool isPlaying;          /**< Whether a melody is currently playing. */
  size_t currentNote;      /**< Index of the current note. */
  uint32_t lastNoteTime;   /**< Time the last note started (ms). */
  ToneFrequency* melody;   /**< Array of melody frequencies (dynamic for RTTTL). */
  ToneDuration* durations; /**< Array of note durations (dynamic for RTTTL). */
  size_t length;           /**< Total number of notes in the melody. */
  bool isDynamic;          /**< Whether the melody arrays are dynamically allocated (for RTTTL). */
  uint8_t currentRepeat;   /**< Current repeat count. */
  uint8_t totalRepeats;    /**< Total number of times to repeat the melody. */
};

/**
 * @brief Structure to manage tone series playback state.
 * Used for non-blocking tone series playback.
 */
struct ToneSeriesState {
  bool isPlaying;           /**< Whether a tone series is currently playing. */
  int16_t currentFrequency; /**< Current frequency in the series. */
  uint32_t lastToneTime;    /**< Time the last tone started (ms). */
  uint16_t endFrequency;    /**< End frequency of the series. */
  int16_t step;             /**< Frequency step (positive or negative). */
  ToneDuration duration;    /**< Duration of each tone. */
};

/**
 * @brief Structure to manage alert or beep playback state.
 * Used for non-blocking alert or beep sequences.
 */
struct AlertState {
  bool isPlaying;          /**< Whether an alert or beep sequence is currently playing. */
  uint8_t currentCount;    /**< Current number of tones played. */
  uint8_t totalCount;      /**< Total number of tones to play. */
  uint32_t lastToneTime;   /**< Time the last tone started (ms). */
  ToneFrequency frequency; /**< Frequency of the tones. */
  ToneDuration duration;   /**< Duration of each tone. */
  uint16_t lapse;          /**< Time lapse between tones (ms). */
};

/**
 * @brief Structure to manage siren playback state.
 * Used for non-blocking siren effect.
 */
struct SirenState {
  bool isPlaying;              /**< Whether the siren is currently playing. */
  bool isLowFrequency;         /**< Whether the low frequency is currently playing. */
  uint32_t startTime;          /**< Start time of the siren effect (ms). */
  uint32_t lastSwitchTime;     /**< Time of the last frequency switch (ms). */
  ToneFrequency lowFrequency;  /**< Low frequency of the siren. */
  ToneFrequency highFrequency; /**< High frequency of the siren. */
  ToneDuration duration;       /**< Total duration of the siren effect. */
};

/**
 * @brief Parse an RTTTL string into melody and duration arrays.
 * Converts an RTTTL string (RAM or PROGMEM) into arrays of ToneFrequency and ToneDuration.
 * The caller is responsible for freeing the allocated memory.
 * @param rtttl The RTTTL string (e.g., "Nokia:d=4,o=5,b=225:8e6,8d6,f#,g#").
 * @param melody Pointer to store the allocated ToneFrequency array.
 * @param durations Pointer to store the allocated ToneDuration array.
 * @param length Pointer to store the number of notes parsed.
 * @param isProgmem True if the RTTTL string is stored in PROGMEM.
 * @return True if parsing was successful, false otherwise.
 */
bool parseRTTTL(const char* rtttl, ToneFrequency*& melody, ToneDuration*& durations, size_t& length, bool isProgmem = false) {
  if (!rtttl) {
    length = 0;
    return false;
  }

  ToneFrequency tempMelody[MAX_RTTTL_NOTES];
  ToneDuration tempDurations[MAX_RTTTL_NOTES];
  size_t noteCount = 0;

  char rtttlCopy[256];
  if (isProgmem) {
    strncpy_P(rtttlCopy, rtttl, sizeof(rtttlCopy) - 1);
  } else {
    strncpy(rtttlCopy, rtttl, sizeof(rtttlCopy) - 1);
  }
  rtttlCopy[sizeof(rtttlCopy) - 1] = '\0';

  char* headerEnd = strchr(rtttlCopy, ':');
  if (!headerEnd) return false;
  char* settings = headerEnd + 1;
  char* notes = strchr(settings, ':');
  if (!notes) return false;
  notes++;

  uint8_t defaultDuration = 4;
  uint8_t defaultOctave = 6;
  uint16_t bpm = 120;

  char settingsCopy[32];
  strncpy(settingsCopy, settings, notes - settings - 1);
  settingsCopy[notes - settings - 1] = '\0';
  char* token = strtok(settingsCopy, ",");
  while (token) {
    if (token[0] == 'd') defaultDuration = atoi(token + 2);
    else if (token[0] == 'o') defaultOctave = atoi(token + 2);
    else if (token[0] == 'b') bpm = atoi(token + 2);
    token = strtok(NULL, ",");
  }

  uint32_t quarterNoteDuration = 60000 / bpm;

  char* ptr = notes;
  while (*ptr && noteCount < MAX_RTTTL_NOTES) {
    while (*ptr == ',') ptr++;

    uint8_t duration = defaultDuration;
    if (isdigit(*ptr)) {
      duration = atoi(ptr);
      while (isdigit(*ptr)) ptr++;
    }

    char note = tolower(*ptr++);
    bool isSharp = (*ptr == '#');
    if (isSharp) ptr++;

    bool isDotted = false;
    uint8_t octave = defaultOctave;
    if (isdigit(*ptr)) {
      octave = *ptr - '0';
      ptr++;
    }

    if (*ptr == '.') {
      isDotted = true;
      ptr++;
    }

    ToneFrequency frequency = PAUSE;
    if (note != 'p') {
      uint16_t baseFrequencies[12] = { 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 };
      int noteIndex = -1;
      switch (note) {
        case 'c': noteIndex = 0; break;
        case 'd': noteIndex = 2; break;
        case 'e': noteIndex = 4; break;
        case 'f': noteIndex = 5; break;
        case 'g': noteIndex = 7; break;
        case 'a': noteIndex = 9; break;
        case 'b': noteIndex = 11; break;
      }
      if (isSharp && noteIndex >= 0) noteIndex++;
      if (noteIndex >= 0 && noteIndex < 12) {
        uint32_t rawFreq = static_cast<uint32_t>(round(baseFrequencies[noteIndex] * pow(2, octave - 4)));
        if (rawFreq >= MIN_FREQUENCY && rawFreq <= MAX_FREQUENCY) {
          frequency = static_cast<ToneFrequency>(rawFreq);
        }
      }
    }

    uint32_t noteDuration = quarterNoteDuration * 4 / duration;
    if (isDotted) noteDuration += noteDuration / 2;
    if (noteDuration > UINT16_MAX) noteDuration = UINT16_MAX;

    tempMelody[noteCount] = frequency;
    tempDurations[noteCount] = static_cast<ToneDuration>(noteDuration);
    noteCount++;
  }

  melody = new ToneFrequency[noteCount];
  durations = new ToneDuration[noteCount];
  for (size_t i = 0; i < noteCount; i++) {
    melody[i] = tempMelody[i];
    durations[i] = tempDurations[i];
  }
  length = noteCount;
  return true;
}

/**
 * @brief Play a single tone (non-blocking).
 * This function starts playing a tone and updates its state for non-blocking operation.
 * Call updateTone() in the main loop to manage tone completion.
 * @param state The ToneState structure to manage the tone.
 * @param toneFrequency The frequency of the tone to be played.
 * @param toneDuration The duration of the tone to be played.
 */
void playTone(ToneState& state, ToneFrequency toneFrequency, ToneDuration toneDuration) {
  if (toneFrequency < MIN_FREQUENCY || toneFrequency > MAX_FREQUENCY || toneDuration <= 0) {
    state.isPlaying = false;
    return;
  }
  state.isPlaying = true;
  state.startTime = millis();
  state.frequency = toneFrequency;
  state.duration = toneDuration;
  if (toneFrequency != PAUSE) {
    tone(getSpeakerPin(), static_cast<uint16_t>(toneFrequency));
  } else {
    noTone(getSpeakerPin());
  }
}

/**
 * @brief Update the state of a playing tone.
 * Checks if the tone duration has elapsed and stops the tone if necessary.
 * Must be called repeatedly in the main loop.
 * @param state The ToneState structure to update.
 */
void updateTone(ToneState& state) {
  if (state.isPlaying && millis() - state.startTime >= static_cast<uint16_t>(state.duration)) {
    noTone(getSpeakerPin());
    state.isPlaying = false;
  }
}

/**
 * @brief Play an alert tone sequence (non-blocking).
 * This function starts a sequence of alert tones and updates its state.
 * Call updateAlert() in the main loop to manage the sequence.
 * @param state The AlertState structure to manage the alert.
 * @param nr The number of tones in the sequence.
 * @param toneFrequency The frequency of the alert tone.
 * @param toneDuration The duration of each alert tone.
 * @param lapse The time lapse between consecutive tones.
 */
void playAlert(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse) {
  if (nr == 0 || toneFrequency < MIN_FREQUENCY || toneFrequency > MAX_FREQUENCY || toneDuration <= 0) {
    state.isPlaying = false;
    return;
  }
  state.isPlaying = true;
  state.currentCount = 0;
  state.totalCount = nr;
  state.lastToneTime = millis();
  state.frequency = toneFrequency;
  state.duration = toneDuration;
  state.lapse = lapse;
}

/**
 * @brief Update the state of an alert sequence.
 * Manages tone playback and pauses for the alert sequence.
 * Must be called repeatedly in the main loop.
 * @param state The AlertState structure to update.
 */
void updateAlert(AlertState& state) {
  if (!state.isPlaying || state.currentCount >= state.totalCount) {
    state.isPlaying = false;
    noTone(getSpeakerPin());
    return;
  }

  uint32_t currentTime = millis();
  if (currentTime - state.lastToneTime >= state.lapse && !state.isPlaying) {
    tone(getSpeakerPin(), static_cast<uint16_t>(state.frequency));
    state.isPlaying = true;
    state.lastToneTime = currentTime;
  }
  if (currentTime - state.lastToneTime >= state.duration && state.isPlaying) {
    noTone(getSpeakerPin());
    state.isPlaying = false;
    state.currentCount++;
    state.lastToneTime = currentTime;
  }
}

/**
 * @brief Play a melody (non-blocking).
 * This function starts playing a melody (standard or RTTTL) and updates its state.
 * Call updateMelody() in the main loop to manage note progression.
 * For RTTTL melodies, set isDynamic to true and free melody/durations after playback.
 * @param state The MelodyState structure to manage the melody.
 * @param melody Array of ToneFrequency values representing the melody.
 * @param durations Array of ToneDuration values representing the durations.
 * @param length The number of notes in the melody.
 * @param isDynamic True if the melody arrays are dynamically allocated (e.g., from RTTTL).
 * @param repeatCount Number of times to repeat the melody (default: 1).
 */
void playMelody(MelodyState& state, ToneFrequency* melody, ToneDuration* durations, size_t length, bool isDynamic = false, uint8_t repeatCount = 1) {
  if (length == 0 || melody == nullptr || durations == nullptr) {
    state.isPlaying = false;
    return;
  }
  state.isPlaying = true;
  state.currentNote = 0;
  state.lastNoteTime = millis();
  state.melody = melody;
  state.durations = durations;
  state.length = length;
  state.isDynamic = isDynamic;
  state.currentRepeat = 0;
  state.totalRepeats = (repeatCount > 0) ? repeatCount : 1;
  ToneState toneState = { false, 0, melody[0], durations[0] };
  playTone(toneState, melody[0], durations[0]);
}

/**
 * @brief Update the state of a melody.
 * Advances to the next note when the current note’s duration has elapsed.
 * Handles melody repeats and frees dynamic memory for RTTTL melodies after completion.
 * Must be called repeatedly in the main loop.
 * @param state The MelodyState structure to update.
 */
 /*
void updateMelody(MelodyState& state) {
  if (!state.isPlaying) {
    return;
  }

  if (state.currentNote >= state.length) {
    if (state.currentRepeat + 1 < state.totalRepeats) {
      // Restart melody for the next repeat
      state.currentRepeat++;
      state.currentNote = 0;
      state.lastNoteTime = millis();
      ToneState toneState = { false, 0, state.melody[0], state.durations[0] };
      playTone(toneState, state.melody[0], state.durations[0]);
      return;
    }
    // Melody and repeats complete
    if (state.isDynamic) {
      delete[] state.melody;
      delete[] state.durations;
      state.melody = nullptr;
      state.durations = nullptr;
    }
    state.isPlaying = false;
    noTone(getSpeakerPin());
    return;
  }

  uint32_t currentTime = millis();
  if (currentTime - state.lastNoteTime >= static_cast<uint16_t>(state.durations[state.currentNote]) + 50) {
    state.currentNote++;
    if (state.currentNote < state.length) {
      ToneState toneState = { false, 0, state.melody[state.currentNote], state.durations[state.currentNote] };
      playTone(toneState, state.melody[state.currentNote], state.durations[state.currentNote]);
      state.lastNoteTime = currentTime;
    }
  }
}*/

void updateMelody(MelodyState& state) {
  //Serial.print("isPlaying: "); Serial.println(state.isPlaying);
  if (!state.isPlaying) {
    return;
  }

  //Serial.print("currentNote: "); Serial.println(state.currentNote);
  //Serial.print("currentRepeat: "); Serial.println(state.currentRepeat);
  //Serial.print("totalRepeats: "); Serial.println(state.totalRepeats);

  if (state.currentNote >= state.length) {
    //Serial.println("Reached end of melody");
    if (state.currentRepeat + 1 < state.totalRepeats) {
      //Serial.println("Starting repeat");
      state.currentRepeat++;
      state.currentNote = 0;
      state.lastNoteTime = millis();
      ToneState toneState = { false, 0, state.melody[0], state.durations[0] };
      playTone(toneState, state.melody[0], state.durations[0]);
      return;
    }
    //Serial.println("Melody complete");
    if (state.isDynamic) {
      delete[] state.melody;
      delete[] state.durations;
      state.melody = nullptr;
      state.durations = nullptr;
    }
    state.isPlaying = false;
    noTone(getSpeakerPin());
    return;
  }

  uint32_t currentTime = millis();
  if (currentTime - state.lastNoteTime >= static_cast<uint16_t>(state.durations[state.currentNote]) + 50) {
    state.currentNote++;
    Serial.print("Advancing to note: "); Serial.println(state.currentNote);
    if (state.currentNote < state.length) {
      ToneState toneState = { false, 0, state.melody[state.currentNote], state.durations[state.currentNote] };
      playTone(toneState, state.melody[state.currentNote], state.durations[state.currentNote]);
      state.lastNoteTime = currentTime;
    }
  }
}

/**
 * @brief Play an RTTTL melody (non-blocking) with optional repeats.
 * This function parses an RTTTL string (RAM or PROGMEM) and starts playing the melody.
 * Call updateMelody() in the main loop to manage note progression.
 * @param state The MelodyState structure to manage the melody.
 * @param rtttl The RTTTL string (e.g., "Nokia:d=4,o=5,b=225:8e6,8d6,f#,g#").
 * @param isProgmem True if the RTTTL string is stored in PROGMEM.
 * @param repeatCount Number of times to repeat the melody (default: 1).
 */
void playRTTTLMelody(MelodyState& state, const char* rtttl, bool isProgmem = false, uint8_t repeatCount = 1) {
  ToneFrequency* melody = nullptr;
  ToneDuration* durations = nullptr;
  size_t length = 0;
  if (parseRTTTL(rtttl, melody, durations, length, isProgmem)) {
    playMelody(state, melody, durations, length, true, repeatCount);
  } else {
    state.isPlaying = false;
  }
}

/**
 * @brief Play a series of tones with a specified frequency change (non-blocking).
 * This function starts a series of tones and updates its state.
 * Call updateToneSeries() in the main loop to manage the series.
 * @param state The ToneSeriesState structure to manage the series.
 * @param startFrequency The starting frequency of the tone series.
 * @param endFrequency The ending frequency of the tone series.
 * @param step The frequency increment (positive for rising, negative for falling).
 * @param toneDuration The duration of each tone.
 */
void playToneSeries(ToneSeriesState& state, uint16_t startFrequency, uint16_t endFrequency, int16_t step, ToneDuration toneDuration) {
  if (startFrequency < MIN_FREQUENCY || startFrequency > MAX_FREQUENCY || endFrequency < MIN_FREQUENCY || endFrequency > MAX_FREQUENCY || step == 0 || toneDuration <= 0) {
    state.isPlaying = false;
    return;
  }
  state.isPlaying = true;
  state.currentFrequency = static_cast<int16_t>(startFrequency);
  state.endFrequency = endFrequency;
  state.step = step;
  state.duration = toneDuration;
  state.lastToneTime = millis();
  tone(getSpeakerPin(), startFrequency);
}

/**
 * @brief Update the state of a tone series.
 * Advances to the next frequency when the current tone’s duration has elapsed.
 * Must be called repeatedly in the main loop.
 * @param state The ToneSeriesState structure to update.
 */
void updateToneSeries(ToneSeriesState& state) {
  if (!state.isPlaying) {
    return;
  }

  uint32_t currentTime = millis();
  if (currentTime - state.lastToneTime >= static_cast<uint16_t>(state.duration)) {
    state.currentFrequency += state.step;
    if ((state.step > 0 && state.currentFrequency > state.endFrequency) || (state.step < 0 && state.currentFrequency < state.endFrequency)) {
      state.isPlaying = false;
      noTone(getSpeakerPin());
      return;
    }
    tone(getSpeakerPin(), static_cast<uint16_t>(state.currentFrequency));
    state.lastToneTime = currentTime;
  }
}

/**
 * @brief Play a beeping sound (non-blocking).
 * This function starts a sequence of beeps and updates its state.
 * Call updateAlert() in the main loop to manage the sequence (reuses AlertState).
 * @param state The AlertState structure to manage the beeps.
 * @param nr The number of beeps.
 * @param toneFrequency The frequency of the beep.
 * @param toneDuration The duration of each beep.
 * @param lapse The time lapse between consecutive beeps.
 */
void playBeep(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse) {
  playAlert(state, nr, toneFrequency, toneDuration, lapse);
}

/**
 * @brief Play a random tone.
 * This function plays a random tone with a frequency and duration within specified ranges.
 * Includes validation to ensure frequencies are within safe limits.
 * @param minFrequency The minimum frequency of the random tone.
 * @param maxFrequency The maximum frequency of the random tone.
 * @param minDuration The minimum duration of the random tone.
 * @param maxDuration The maximum duration of the random tone.
 */
void playRandomTone(ToneFrequency minFrequency, ToneFrequency maxFrequency, ToneDuration minDuration, ToneDuration maxDuration) {
  if (minFrequency < MIN_FREQUENCY || maxFrequency > MAX_FREQUENCY || minFrequency > maxFrequency || minDuration <= 0 || maxDuration <= 0 || minDuration > maxDuration) {
    return;
  }
  ToneFrequency randomFrequency = static_cast<ToneFrequency>(random(static_cast<uint16_t>(minFrequency), static_cast<uint16_t>(maxFrequency) + 1));
  ToneDuration randomDuration = static_cast<ToneDuration>(random(static_cast<uint16_t>(minDuration), static_cast<uint16_t>(maxDuration) + 1));
  ToneState toneState = { false, 0, randomFrequency, randomDuration };
  playTone(toneState, randomFrequency, randomDuration);
}

/**
 * @brief Play a siren effect (non-blocking).
 * This function starts a siren effect by alternating between two frequencies.
 * Call updateSiren() in the main loop to manage the effect.
 * The siren alternates frequencies every duration/10 milliseconds.
 * @param state The SirenState structure to manage the siren.
 * @param lowFrequency The lower frequency of the siren.
 * @param highFrequency The higher frequency of the siren.
 * @param duration The total duration of the siren effect.
 */
void playSiren(SirenState& state, ToneFrequency lowFrequency, ToneFrequency highFrequency, ToneDuration duration) {
  if (lowFrequency < MIN_FREQUENCY || highFrequency > MAX_FREQUENCY || duration <= 0) {
    state.isPlaying = false;
    return;
  }
  state.isPlaying = true;
  state.startTime = millis();
  state.lastSwitchTime = state.startTime;
  state.lowFrequency = lowFrequency;
  state.highFrequency = highFrequency;
  state.duration = duration;
  state.isLowFrequency = true;
  tone(getSpeakerPin(), static_cast<uint16_t>(lowFrequency));
}

/**
 * @brief Update the state of a siren effect.
 * Switches between low and high frequencies until the total duration has elapsed.
 * Must be called repeatedly in the main loop.
 * @param state The SirenState structure to update.
 */
void updateSiren(SirenState& state) {
  if (!state.isPlaying || millis() - state.startTime >= static_cast<uint32_t>(state.duration)) {
    state.isPlaying = false;
    noTone(getSpeakerPin());
    return;
  }

  uint32_t currentTime = millis();
  if (currentTime - state.lastSwitchTime >= static_cast<uint16_t>(state.duration) / 10) {
    state.isLowFrequency = !state.isLowFrequency;
    tone(getSpeakerPin(), state.isLowFrequency ? static_cast<uint16_t>(state.lowFrequency) : static_cast<uint16_t>(state.highFrequency));
    state.lastSwitchTime = currentTime;
  }
}

/**
 * @brief Stop playing the tone.
 * This function stops any tone currently being played.
 */
void stopTone() {
  noTone(getSpeakerPin());
}

// Define the melody and durations for a sample melody (non-RTTTL)
const ToneFrequency melody[] = {
  MEDIUM_C, MEDIUM_D, MEDIUM_E, MEDIUM_F, MEDIUM_G
};

const ToneDuration durations[] = {
  MEDIUM_DURATION, MEDIUM_DURATION, MEDIUM_DURATION, MEDIUM_DURATION, MEDIUM_DURATION
};

// Calculate the length of the melody.
const size_t melodyLength = sizeof(melody) / sizeof(melody[0]);

#endif  // SOUNDFUNCTIONS_H