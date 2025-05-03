/**
 * @file rtttl_melodies.h
 * @brief Contains definitions of various ringtones in RTTTL format, stored in PROGMEM.
 * @link https://en.wikipedia.org/wiki/Ring_Tone_Text_Transfer_Language
 */

#ifndef RINGTONES_H
#define RINGTONES_H

/**
 * @brief NOKIA ringtone definition in RTTTL format.
 * This ringtone is in the RTTTL (Ring Tone Transfer Language) format: "Nokia:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a",
 * where each note and its duration are specified.
 */

const char NOKIA[] PROGMEM =
  "Nokia:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a";
  const char XFILES[] PROGMEM =
"Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";

#endif  //RINGTONES_H

/*
const char MISSION[] PROGMEM = 
"MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";

const char XFILES[] PROGMEM =
"Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";

const char SIMPSONS[] PROGMEM =
"The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";

const char GADGET[] PROGMEM =
"Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";

const char CANON[] PROGMEM =
"Canon:d=16,o=6,b=125:8a#.,g.,g#.,8a#.,g.,g#.,a#.,a#.5,c.,d.,d#.,f.,g.,g#.,8g.,d#.,f.,8g.,g.5,g#.5,a#.5,c.,a#.5,g#.5,a#.5,g.5,g#.5,a#.5,8g#.5,c.,a#.5,8g#.5,g.5,f.5,g.5,f.5,d#.5,f.5,g.5,g#.5,a#.5,c.,8g#.5,c.,a#.5,8c.,d.,d#.,a#.5,c.,d.,d#.,f.,g.,g#.,8a#";

const char SUPERMARIO[] PROGMEM =
"smwwd1:d=4,o=5,b=125:a,8f.,16c,16d,16f,16p,f,16d,16c,16p,16f,16p,16f,16p,8c6,8a.,g,16c,a,8f.,16c,16d,16f,16p,f,16d,16c,16p,16f,16p,16a#,16a,16g,2f,16p,8a.,8f.,8c,8a.,f,16g#,16f,16c,16p,8g#.,2g,8a.,8f.,8c,8a.,f,16g#,16f,8c,2c6";
*/