Esta documentación también está disponible en **[Inglés](./README.md)**.

# 🔊 sound_functions_RTTTL
## Resumen
`SoundFunctions` es una biblioteca C++ diseñada para generar tonos, alertas y melodías (incluyendo el formato RTTTL) utilizando un zumbador en microcontroladores compatibles con Arduino. Proporciona funciones no bloqueantes para soportar tareas concurrentes, con características para reproducir tonos individuales, series de tonos, pitidos, sirenas y melodías con repeticiones opcionales. La biblioteca está optimizada para entornos con memoria limitada y soporta melodías RTTTL almacenadas en PROGMEM.

Diseñada como una biblioteca para su uso en entornos Arduino.

---

## ⚙️ Características

- Generación de tonos no bloqueante para tonos individuales, alertas y melodías.
- Soporta análisis y reproducción de melodías RTTTL (Ring Tone Text Transfer Language).
- Incluye frecuencias y duraciones de tonos predefinidas para facilitar su uso.
- Reproduce series de tonos con pasos de frecuencia personalizables.
- Genera efectos de sirena con frecuencias alternantes.
- Generación de tonos aleatorios dentro de rangos de frecuencia y duración especificados.
- Soporta PROGMEM para almacenar melodías RTTTL y ahorrar RAM.
- Pin de altavoz configurable con valor predeterminado.

> El diseño no bloqueante asegura que la reproducción de tonos no interfiera con otras tareas, lo que la hace ideal para aplicaciones en tiempo real. El analizador RTTTL soporta melodías complejas con gestión dinámica de memoria, y el soporte para PROGMEM minimiza el uso de RAM en dispositivos con recursos limitados.

### 📌 Microcontroladores Compatibles

Compatible con arquitecturas AVR de 8 bits, ARM Cortex-M de 32 bits y Xtensa, siempre que sean compatibles con el IDE de Arduino.

---

## 📦 Instalación

Opción 1: Copiar los archivos e incluirlos:

1. Copia el siguiente archivo en tu proyecto Arduino o proyecto C++ embebido:
   - `sound_fun_rtttl.h`

2. Incluye el encabezado en tu archivo fuente:
   ```cpp
   #include "sound_fun_rtttl.h"
   ```

Opción 2: Instalar la biblioteca e incluirla:

1. [Descarga](https://github.com/ATphonOS/sound-functions/archive/refs/heads/main.zip) el repositorio.
2. Abre el IDE de Arduino.
3. Ve a Sketch > `Incluir Biblioteca` > `Añadir biblioteca ZIP`... en el menú.
4. Selecciona el archivo ZIP de la biblioteca.
5. Importa la Biblioteca:

Para usar la biblioteca en tu sketch, ve a Sketch > `Incluir Biblioteca`.
Selecciona la biblioteca instalada de la lista para añadir su directiva `#include` a tu código.
```cpp
   #include <sound_fun_rtttl.h>
```

---

## 📚 Biblioteca: `SoundFunctions`

### Definiciones y Estructuras Clave

```cpp
enum ToneFrequency { ... };
enum ToneDuration { ... };
struct ToneState { ... };
struct MelodyState { ... };
struct ToneSeriesState { ... };
struct AlertState { ... };
struct SirenState { ... };
```

| Definición | Descripción |
|------------|-------------|
| `ToneFrequency` | Enumera frecuencias de tonos predefinidas (por ejemplo, `LOW_C = 261`, `MEDIUM_A = 880`, `PAUSE = 0`). |
| `ToneDuration` | Enumera duraciones predefinidas (por ejemplo, `VERY_SHORT_DURATION = 50`, `LONG_DURATION = 1000`). |
| `ToneState` | Gestiona el estado para la reproducción no bloqueante de tonos individuales. |
| `MelodyState` | Gestiona el estado para la reproducción no bloqueante de melodías, incluyendo RTTTL con soporte para repeticiones. |
| `ToneSeriesState` | Gestiona el estado para la reproducción no bloqueante de series de tonos. |
| `AlertState` | Gestiona el estado para secuencias de alertas o pitidos no bloqueantes. |
| `SirenState` | Gestiona el estado para efectos de sirena no bloqueantes. |

## 🔓 Funciones Públicas

### Inicialización y Configuración

```cpp
void initSpeaker(uint8_t pin = DEFAULT_PIN_SPEAKER);
uint8_t getSpeakerPin();
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void initSpeaker(uint8_t pin = DEFAULT_PIN_SPEAKER)` | Inicializa el pin del altavoz. | `pin (uint8_t)`: pin a usar para el altavoz (predeterminado: `DEFAULT_PIN_SPEAKER`) | `void` |
| `uint8_t getSpeakerPin()` | Devuelve el pin del altavoz actual. | Ninguno | `uint8_t`: número del pin usado para el altavoz |

### Reproducción de Tonos

```cpp
void playTone(ToneState& state, ToneFrequency toneFrequency, ToneDuration toneDuration);
void updateTone(ToneState& state);
void playRandomTone(ToneFrequency minFrequency, ToneFrequency maxFrequency, ToneDuration minDuration, ToneDuration maxDuration);
void stopTone();
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void playTone(ToneState& state, ToneFrequency toneFrequency, ToneDuration toneDuration)` | Inicia la reproducción de un tono individual (no bloqueante). | `state (ToneState&)`: estado del tono<br>`toneFrequency (ToneFrequency)`: frecuencia<br>`toneDuration (ToneDuration)`: duración | `void` |
| `void updateTone(ToneState& state)` | Actualiza el estado de un tono en reproducción. | `state (ToneState&)`: estado del tono | `void` |
| `void playRandomTone(ToneFrequency minFrequency, ToneFrequency maxFrequency, ToneDuration minDuration, ToneDuration maxDuration)` | Reproduce un tono aleatorio dentro de rangos especificados. | `minFrequency (ToneFrequency)`: frecuencia mínima<br>`maxFrequency (ToneFrequency)`: frecuencia máxima<br>`minDuration (ToneDuration)`: duración mínima<br>`maxDuration (ToneDuration)`: duración máxima | `void` |
| `void stopTone()` | Detiene cualquier tono en reproducción. | Ninguno | `void` |

### Reproducción de Alertas y Pitidos

```cpp
void playAlert(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse);
void updateAlert(AlertState& state);
void playBeep(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse);
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void playAlert(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse)` | Inicia una secuencia de tonos de alerta (no bloqueante). | `state (AlertState&)`: estado de la alerta<br>`nr (uint8_t)`: número de tonos<br>`toneFrequency (ToneFrequency)`: frecuencia<br>`toneDuration (ToneDuration)`: duración<br>`lapse (uint16_t)`: tiempo entre tonos | `void` |
| `void updateAlert(AlertState& state)` | Actualiza el estado de una secuencia de alerta. | `state (AlertState&)`: estado de la alerta | `void` |
| `void playBeep(AlertState& state, uint8_t nr, ToneFrequency toneFrequency, ToneDuration toneDuration, uint16_t lapse)` | Inicia una secuencia de pitidos (no bloqueante, reutiliza `playAlert`). | Igual que `playAlert` | `void` |

### Reproducción de Melodías

```cpp
void playMelody(MelodyState& state, ToneFrequency* melody, ToneDuration* durations, size_t length, bool isDynamic = false, uint8_t repeatCount = 1);
void updateMelody(MelodyState& state);
void playRTTTLMelody(MelodyState& state, const char* rtttl, bool isProgmem = false, uint8_t repeatCount = 1);
bool parseRTTTL(const char* rtttl, ToneFrequency*& melody, ToneDuration*& durations, size_t& length, bool isProgmem = false);
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void playMelody(MelodyState& state, ToneFrequency* melody, ToneDuration* durations, size_t length, bool isDynamic = false, uint8_t repeatCount = 1)` | Inicia la reproducción de una melodía (no bloqueante). | `state (MelodyState&)`: estado de la melodía<br>`melody (ToneFrequency*)`: array de frecuencias<br>`durations (ToneDuration*)`: array de duraciones<br>`length (size_t)`: número de notas<br>`isDynamic (bool)`: verdadero si los arrays son dinámicos<br>`repeatCount (uint8_t)`: número de repeticiones | `void` |
| `void updateMelody(MelodyState& state)` | Actualiza el estado de una melodía en reproducción. | `state (MelodyState&)`: estado de la melodía | `void` |
| `void playRTTTLMelody(MelodyState& state, const char* rtttl, bool isProgmem = false, uint8_t repeatCount = 1)` | Inicia la reproducción de una melodía RTTTL (no bloqueante). | `state (MelodyState&)`: estado de la melodía<br>`rtttl (const char*)`: cadena RTTTL<br>`isProgmem (bool)`: verdadero si RTTTL está en PROGMEM<br>`repeatCount (uint8_t)`: número de repeticiones | `void` |
| `bool parseRTTTL(const char* rtttl, ToneFrequency*& melody, ToneDuration*& durations, size_t& length, bool isProgmem = false)` | Analiza una cadena RTTTL en arrays de melodía y duración. | `rtttl (const char*)`: cadena RTTTL<br>`melody (ToneFrequency*&)`: array de melodía de salida<br>`durations (ToneDuration*&)`: array de duración de salida<br>`length (size_t&)`: número de notas<br>`isProgmem (bool)`: verdadero si RTTTL está en PROGMEM | `bool`: verdadero si el análisis fue exitoso |

### Reproducción de Series de Tonos y Sirenas

```cpp
void playToneSeries(ToneSeriesState& state, uint16_t startFrequency, uint16_t endFrequency, int16_t step, ToneDuration toneDuration);
void updateToneSeries(ToneSeriesState& state);
void playSiren(SirenState& state, ToneFrequency lowFrequency, ToneFrequency highFrequency, ToneDuration duration);
void updateSiren(SirenState& state);
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void playToneSeries(ToneSeriesState& state, uint16_t startFrequency, uint16_t endFrequency, int16_t step, ToneDuration toneDuration)` | Inicia una serie de tonos con pasos de frecuencia (no bloqueante). | `state (ToneSeriesState&)`: estado de la serie<br>`startFrequency (uint16_t)`: frecuencia inicial<br>`endFrequency (uint16_t)`: frecuencia final<br>`step (int16_t)`: paso de frecuencia<br>`toneDuration (ToneDuration)`: duración por tono | `void` |
| `void updateToneSeries(ToneSeriesState& state)` | Actualiza el estado de una serie de tonos. | `state (ToneSeriesState&)`: estado de la serie | `void` |
| `void playSiren(SirenState& state, ToneFrequency lowFrequency, ToneFrequency highFrequency, ToneDuration duration)` | Inicia un efecto de sirena alternando frecuencias (no bloqueante). | `state (SirenState&)`: estado de la sirena<br>`lowFrequency (ToneFrequency)`: frecuencia baja<br>`highFrequency (ToneFrequency)`: frecuencia alta<br>`duration (ToneDuration)`: duración total | `void` |
| `void updateSiren(SirenState& state)` | Actualiza el estado de un efecto de sirena. | `state (SirenState&)`: estado de la sirena | `void` |

---

## 🧪 Ejemplo de Uso

1. Reproduce una melodía RTTTL en PROGMEM

```cpp
#include "sound_fun_rtttl.h"
#include "rtttl_PROGMEM_melodies.h"

MelodyState melodyState;

void setup() {
  Serial.begin(9600);
  initSpeaker();  
  
  // Inicia la reproducción de la melodía desde PROGMEM
  playRTTTLMelody(melodyState, NOKIA, true, 2);  // Reproduce 2 veces
}

void loop() {
  updateMelody(melodyState);
}
```

2. Reproduce una melodía

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

3. Reproduce varias melodías

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
  Serial.println("Iniciando secuencia de melodías");
  
  playMelody(melodyState1, const_cast<ToneFrequency*>(twinkleMelody), 
             const_cast<ToneDuration*>(twinkleDurations), 
             TWINKLE_MELODY_LENGTH, false, 3);
}

void loop() {
  switch (currentMelody) {
    case PLAY_TWINKLE:
      updateMelody(melodyState1);
      if (!melodyState1.isPlaying) {
        Serial.println("Melodía Twinkle terminada. Iniciando Flight of the Bumblebee");
        playMelody(melodyState2, const_cast<ToneFrequency*>(flightOfTheBumblebeeMelody), 
                   const_cast<ToneDuration*>(flightOfTheBumblebeeDurations), 
                   FLIGHT_OF_THE_BUMBLEBEE_MELODY_LENGTH, false, 3);
        currentMelody = PLAY_BUMBLEBEE;
      }
      break;

    case PLAY_BUMBLEBEE:
      updateMelody(melodyState2);
      if (!melodyState2.isPlaying) {
        Serial.println("Melodía Bumblebee terminada. Iniciando R2-D2");
        playMelody(melodyState3, const_cast<ToneFrequency*>(r2d2Melody), 
                   const_cast<ToneDuration*>(r2d2Durations), 
                   R2D2_MELODY_LENGTH, false, 3);
        currentMelody = PLAY_R2D2;
      }
      break;

    case PLAY_R2D2:
      updateMelody(melodyState3);
      if (!melodyState3.isPlaying) {
        Serial.println("Melodía R2-D2 terminada. Secuencia completada");
        currentMelody = DONE;
      }
      break;

    case DONE:
      Serial.println("Todas las melodías completadas");
      delay(1000); 
      break;
  }
}
```
4. Múltiples métodos

```cpp
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
```

---

## 🧠 Notas de Diseño

+ Las funciones no bloqueantes aseguran compatibilidad con tareas concurrentes, utilizando estructuras de estado para rastrear el progreso de la reproducción.
+ El análisis RTTTL soporta melodías complejas con asignación dinámica de memoria, liberada automáticamente tras la reproducción.
+ El soporte para PROGMEM en cadenas RTTTL reduce el uso de RAM en microcontroladores.
+ Las validaciones de frecuencia y duración previenen comportamientos inesperados por entradas inválidas.
+ El diseño modular permite reutilizar la lógica de alertas para pitidos, minimizando la duplicación de código.
+ Los enums predefinidos `ToneFrequency` y `ToneDuration` simplifican la composición de melodías.

---

## 🔧 Especificaciones RTTTL

```
Especificaciones del Formato RTTTL

RTTTL (RingTone Text Transfer Language) es el formato principal utilizado para distribuir tonos de llamada para teléfonos Nokia. Un archivo RTTTL es un archivo de texto que contiene el nombre del tono, una sección de control y una sección con una secuencia de comandos de tono separados por comas. Los espacios en blanco deben ser ignorados por cualquier aplicación lectora.

Ejemplo:
Simpsons:d=4,o=5,b=160:32p,c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g

Este archivo describe un tono de llamada cuyo nombre es 'Simpsons'. La sección de control establece los pulsos por minuto de la negra a 160, la duración predeterminada de la nota como 4, y la escala predeterminada como Octava 5.
<Archivo RTX> := <nombre> ":" [<sección de control>] ":" <comandos de tono>

	<nombre> := <char> ; longitud máxima del nombre 10 caracteres

	<sección de control> := <par de control> ["," <sección de control>]

		<par de control> := <nombre de control> ["="] <valor de control>

		<nombre de control> := "o" | "d" | "b"
		; Válido en la sección de control: o=escala predeterminada, d=duración predeterminada, b=pulsos por minuto de la negra.
		; Si no se especifica, los valores predeterminados son 4=duración, 6=escala, 63=pulsos por minuto
		; Cualquier nombre de control desconocido debe ser ignorado

		<comandos de tono> := <comando de tono> ["," <comandos de tono>]

		<comando de tono> := <nota> | <par de control>

		<nota> := [<duración>] <nota> [<escala>] [<duración especial>] <delimitador>

			<duración> := "1" | "2" | "4" | "8" | "16" | "32"
			; La duración es un divisor de la duración de la nota completa, por ejemplo, 4 representa una negra

			<nota> := "P" | "C" | "C#" | "D" | "D#" | "E" | "F" | "F#" | "G" | "G#" | "A" | "A#" | "B"

			<escala> := "4" | "5" | "6" | "7"
			; Nota que octava 4: A=440Hz, 5: A=880Hz, 6: A=1.76 kHz, 7: A=3.52 kHz
			; La nota más baja en el Nokia 61xx es A4, la más alta es B7

			<duración especial> := "." ; Nota con puntillo

; Fin de la especificación
De https://panuworld.net/nuukiaworld/download/nokix/rtttl.htm
```
https://www.mobilefish.com/tutorials/rtttl/rtttl_quickguide_specification.html

https://1j01.github.io/rtttl.js/#Birdy%20Song

## 🎵 Melodías RTTTL

https://www.arduinoblocks.com/web/help/rtttl

https://picaxe.com/rtttl-ringtones-for-tune-command/

http://www.fodor.sk/spectrum/rttl.htm

## 🎶 Reproductor RTTTL en Línea

https://eddmann.com/nokia-composer-web/

https://adamonsoon.github.io/rtttl-play/

## 🧾 Licencia
Este proyecto está licenciado bajo la Licencia MIT — consulta el archivo [LICENSE](https://github.com/ATphonOS/sound_functions/blob/main/LICENSE.md) para más detalles.
