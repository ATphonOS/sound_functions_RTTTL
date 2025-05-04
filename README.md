This documentation is also available in **[Spanish](./README.es.md)**.

# 🔊 sound_functions_RTTTL
## Overview
`SoundFunctions` is a C++ library designed for generating tones, alerts, and melodies (including RTTTL format) using a buzzer on Arduino-compatible microcontrollers. It provides non-blocking functions to support concurrent tasks, with features for playing single tones, tone series, beeps, sirens, and melodies with optional repeats. The library is optimized for memory-constrained environments and supports PROGMEM-stored RTTTL melodies.

Designed as a library for use in Arduino environments.

---

## ⚙️ Features

- Non-blocking tone generation for single tones, alerts, and melodies.
- Supports RTTTL (Ring Tone Text Transfer Language) melody parsing and playback.
- Includes predefined tone frequencies and durations for ease of use.
- Plays tone series with customizable frequency steps.
- Generates siren effects with alternating frequencies.
- Random tone generation within specified frequency and duration ranges.
- Supports PROGMEM for storing RTTTL melodies to save RAM.
- Configurable speaker pin with default setting.

> The non-blocking design ensures that tone playback does not interfere with other tasks, making it ideal for real-time applications. The RTTTL parser supports complex melodies with dynamic memory management, and PROGMEM support minimizes RAM usage on resource-constrained devices.

### 📌 Compatible Microcontrollers

Compatible with 8-bit AVR, 32-bit ARM Cortex-M, and Xtensa architectures, as long as they are compatible with the Arduino IDE.

---

## 📦 Installation

Option 1: Copy the files and include:

1. Copy the following file into your Arduino project or C++ embedded project:
   - `sound_fun_rtttl.h`

2. Include the header in your source file:
   ```cpp
   #include "sound_fun_rtttl.h"
   ```

Option 2: Install the library and include:

1. [Download](https://github.com/ATphonOS/sound-functions/archive/refs/heads/main.zip) the repo.
2. Open Arduino IDE.
3. Go to Sketch > `Include Library` > `Add ZIP libraries`... in the menu.
4. Select the ZIP file from the library.
5. Import the Library:

To use the library in your sketch, go to Sketch > `Include Library`.
Select the installed library from the list to add its `#include` directive to your code.
```cpp
   #include <sound_fun_rtttl.h>
```

---

## 📚 Library: `SoundFunctions`

### Key Definitions and Structures

```cpp
enum ToneFrequency { ... };
enum ToneDuration { ... };
struct ToneState { ... };
struct MelodyState { ... };
struct ToneSeriesState { ... };
struct AlertState { ... };
struct SirenState { ... };
```

| Definition | Description |
|------------|-------------|
| `ToneFrequency` | Enumerates predefined tone frequencies (e.g., `LOW_C = 261`, `MEDIUM_A = 880`, `PAUSE = 0`). |
| `ToneDuration` | Enumerates predefined durations (e.g., `VERY_SHORT_DURATION = 50`, `LONG_DURATION = 1000`). |
| `ToneState` | Manages state for non-blocking single tone playback. |
| `MelodyState` | Manages state for non-blocking melody playback, including RTTTL with repeat support. |
| `ToneSeriesState` | Manages state for non-blocking tone series playback. |
| `AlertState` | Manages state for non-blocking alert or beep sequences. |
| `SirenState` | Manages state for non-blocking siren effects. |

## 🔓 Public Functions

### Initialization and Configuration

```cpp
void initSpeaker(uint8_t pin = DEFAULT_PIN_SPEAKER);
uint8_t getSpeakerPin();
```

| Function | Description | Parameters | Returns |
|----------|-------------|------------|---------|
| `void initSpeaker(uint8_t pin = DEFAULT_PIN_SPEAKER)` | Initializes the speaker pin. | `pin (uint8_t)`: pin to use for the speaker (default: `DEFAULT_PIN_SPEAKER`) | `void` |
| `uint8_t getSpeakerPin()` | Returns the current speaker pin. | None | `uint8_t`: pin number used for the speaker |

### Tone Playback

```cpp
void playTone(ToneState& state, ToneFrequency toneFrequency, ToneDuration toneDuration);
void updateTone(ToneState& state);
void playRandomTone(ToneFrequency minFrequency, ToneFrequency maxFrequency, ToneDuration minDuration, ToneDuration maxDuration);
void stopTone();
```

| Function | Description | Parameters | Returns |
|----------|-------------|------------|---------|
| `void playTone(ToneState& state, ToneFrequency toneFrequency, ToneDuration toneDuration)` | Starts playing a single tone (non-blocking). | `state (ToneState&)`: tone state<br>`toneFrequency (ToneFrequency)`: frequency<br>`toneDuration (ToneDuration)`: duration | `void` |
| `void updateTone(ToneState& state)` | Updates the state of a playing tone. | `state (ToneState&)`: tone state | `void` |
| `void playRandomTone(ToneFrequency minFrequency, ToneFrequency maxFrequency, ToneDuration minDuration, ToneDuration maxDuration)` | Plays a random tone within specified ranges. | `minFrequency (ToneFrequency)`: minimum frequency<br>`maxFrequency (ToneFrequency)`: maximum frequency<br>`minDuration (ToneDuration)`: minimum duration<br>`maxDuration (ToneDuration)`: maximum duration | `void` |
| `void stopTone()` | Stops any tone currently playing. | None | `void` |

### Alert and Beep Playback

```cpp
void playAlert(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse);
void updateAlert(AlertState& state);
void playBeep(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse);
```

| Function | Description | Parameters | Returns |
|----------|-------------|------------|---------|
| `void playAlert(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse)` | Starts a sequence of alert tones (non-blocking). | `state (AlertState&)`: alert state<br>`nr (uint8_t)`: number of tones<br>`toneFrequency (ToneFrequency)`: frequency<br>`toneDuration (ToneDuration)`: duration<br>`lapse (uint16_t)`: time between tones | `void` |
| `void updateAlert(AlertState& state)` | Updates the state of an alert sequence. | `state (AlertState&)`: alert state | `void` |
| `void playBeep(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse)` | Starts a sequence of beeps (non-blocking, reuses `playAlert`). | Same as `playAlert` | `void` |

### Melody Playback

```cpp
void playMelody(MelodyState& state, ToneFrequency* melody, ToneDuration* durations, size_t length, bool isDynamic = false, uint8_t repeatCount = 1);
void updateMelody(MelodyState& state);
void playRTTTLMelody(MelodyState& state, const char* rtttl, bool isProgmem = false, uint8_t repeatCount = 1);
bool parseRTTTL(const char* rtttl, ToneFrequency*& melody, ToneDuration*& durations, size_t& length, bool isProgmem = false);
```

| Function | Description | Parameters | Returns |
|----------|-------------|------------|---------|
| `void playMelody(MelodyState& state, ToneFrequency* melody, ToneDuration* durations, size_t length, bool isDynamic = false, uint8_t repeatCount = 1)` | Starts playing a melody (non-blocking). | `state (MelodyState&)`: melody state<br>`melody (ToneFrequency*)`: frequency array<br>`durations (ToneDuration*)`: duration array<br>`length (size_t)`: number of notes<br>`isDynamic (bool)`: true if arrays are dynamic<br>`repeatCount (uint8_t)`: number of repeats | `void` |
| `void updateMelody(MelodyState& state)` | Updates the state of a playing melody. | `state (MelodyState&)`: melody state | `void` |
| `void playRTTTLMelody(MelodyState& state, const char* rtttl, bool isProgmem = false, uint8_t repeatCount = 1)` | Starts playing an RTTTL melody (non-blocking). | `state (MelodyState&)`: melody state<br>`rtttl (const char*)`: RTTTL string<br>`isProgmem (bool)`: true if RTTTL is in PROGMEM<br>`repeatCount (uint8_t)`: number of repeats | `void` |
| `bool parseRTTTL(const char* rtttl, ToneFrequency*& melody, ToneDuration*& durations, size_t& length, bool isProgmem = false)` | Parses an RTTTL string into melody and duration arrays. | `rtttl (const char*)`: RTTTL string<br>`melody (ToneFrequency*&)`: output melody array<br>`durations (ToneDuration*&)`: output duration array<br>`length (size_t&)`: number of notes<br>`isProgmem (bool)`: true if RTTTL is in PROGMEM | `bool`: true if parsing succeeded |

### Tone Series and Siren Playback

```cpp
void playToneSeries(ToneSeriesState& state, uint16_t startFrequency, uint16_t endFrequency, int16_t step, ToneDuration toneDuration);
void updateToneSeries(ToneSeriesState& state);
void playSiren(SirenState& state, ToneFrequency lowFrequency, ToneFrequency highFrequency, ToneDuration duration);
void updateSiren(SirenState& state);
```

| Function | Description | Parameters | Returns |
|----------|-------------|------------|---------|
| `void playToneSeries(ToneSeriesState& state, uint16_t startFrequency, uint16_t endFrequency, int16_t step, ToneDuration toneDuration)` | Starts a series of tones with frequency steps (non-blocking). | `state (ToneSeriesState&)`: series state<br>`startFrequency (uint16_t)`: starting frequency<br>`endFrequency (uint16_t)`: ending frequency<br>`step (int16_t)`: frequency step<br>`toneDuration (ToneDuration)`: duration per tone | `void` |
| `void updateToneSeries(ToneSeriesState& state)` | Updates the state of a tone series. | `state (ToneSeriesState&)`: series state | `void` |
| `void playSiren(SirenState& state, ToneFrequency lowFrequency, ToneFrequency highFrequency, ToneDuration duration)` | Starts a siren effect alternating frequencies (non-blocking). | `state (SirenState&)`: siren state<br>`lowFrequency (ToneFrequency)`: low frequency<br>`highFrequency (ToneFrequency)`: high frequency<br>`duration (ToneDuration)`: total duration | `void` |
| `void updateSiren(SirenState& state)` | Updates the state of a siren effect. | `state (SirenState&)`: siren state | `void` |

---

## 🧪 Example of Use

1. Plays RTTTL melody in PROGMEM 

```cpp
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

```

2. Play melody 

```cpp
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
```

3. Play several melodies

```cpp
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
```   
---

## 🧠 Design Notes

+ Non-blocking functions ensure compatibility with concurrent tasks, using state structures to track playback progress.
+ RTTTL parsing supports complex melodies with dynamic memory allocation, automatically freed after playback.
+ PROGMEM support for RTTTL strings reduces RAM usage on microcontrollers.
+ Frequency and duration validations prevent invalid inputs from causing unexpected behavior.
+ Modular design allows reuse of alert logic for beeps, minimizing code duplication.
+ Predefined `ToneFrequency` and `ToneDuration` enums simplify melody composition.

---

## 🔧 RTTTL especifications

```
RTTTL Format Specifications

RTTTL (RingTone Text Transfer Language) is the primary format used to distribute 
ringtones for Nokia phones. An RTTTL file is a text file, containing the 
ringtone name, a control section and a section containing a comma separated 
sequence of ring tone commands. White space must be ignored by any reader 
application. 

Example: 
Simpsons:d=4,o=5,b=160:32p,c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g

This file describes a ringtone whose name is 'Simpsons'. The control section 
sets the quarterNoteBeats per minute at 160, the default note length as 4, and the default 
scale as Octave 5. 
<RTX file> := <name> ":" [<control section>] ":" <tone-commands>

	<name> := <char> ; maximum name length 10 characters

	<control-section> := <control-pair> ["," <control-section>]

		<control-pair> := <control-name> ["="] <control-value>

		<control-name> := "o" | "d" | "b"
		; Valid in control section: o=default scale, d=default duration, b=default quarterNoteBeats per minute. 
		; if not specified, defaults are 4=duration, 6=scale, 63=quarterNoteBeats-per-minute
		; any unknown control-names must be ignored

		<tone-commands> := <tone-command> ["," <tone-commands>]

		<tone-command> :=<note> | <control-pair>

		<note> := [<duration>] <note> [<scale>] [<special-duration>] <delimiter>

			<duration> := "1" | "2" | "4" | "8" | "16" | "32" 
			; duration is divider of full note duration, eg. 4 represents a quarter note

			<note> := "P" | "C" | "C#" | "D" | "D#" | "E" | "F" | "F#" | "G" | "G#" | "A" | "A#" | "B" 

			<scale> :="4" | "5" | "6" | "7"
			; Note that octave 4: A=440Hz, 5: A=880Hz, 6: A=1.76 kHz, 7: A=3.52 kHz
			; The lowest note on the Nokia 61xx is A4, the highest is B7

			<special-duration> := "." ; Dotted note

; End of specification
```
From https://panuworld.net/nuukiaworld/download/nokix/rtttl.htm

https://www.mobilefish.com/tutorials/rtttl/rtttl_quickguide_specification.html

https://1j01.github.io/rtttl.js/#Birdy%20Song

## 🎵 RTTTL melodies 

https://www.arduinoblocks.com/web/help/rtttl

https://picaxe.com/rtttl-ringtones-for-tune-command/

http://www.fodor.sk/spectrum/rttl.htm


## 🎶 Online RTTTL player

https://eddmann.com/nokia-composer-web/

https://adamonsoon.github.io/rtttl-play/

## 🧾 License
This project is licensed under the MIT License — see the [LICENSE](https://github.com/ATphonOS/sound_functions/blob/main/LICENSE.md) file for details.
