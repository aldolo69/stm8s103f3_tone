//board stm8s103f3
//compile with https://github.com/tenbaht/sduino/raw/master/package_sduino_stm8_index.json
//connect a piezo buzzer to pin PC4 (D6 in arduino definition)


//timer1: PWM for PC3, PC4, on alternate mapping PC6, PC7, could be used for ADC
//DIGITAL PIN 6=A0=PC4=TONE PIN. connect a 

#include <Arduino.h>
 
void stm8NoTone(void);
void stm8Tone(int);
/*****************************/

//music&code found at
//https://github.com/flickerfly/Music_Box/blob/master/play_rtttl.ino
//https://gist.github.com/dglaude/71525a07f5e24888a3f098fba3abf29b


#define OCTAVE_OFFSET 0
  int play_rtttl(void);
  int play_rtttl_stop();
  int play_rtttl_start(int song);
  void play_rtttl_start_no_repeat(int);
 int play_rtttl_song();
// These values can also be found as constants in the Tone library (Tone.h)
int notes[] = { 0,
                262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
                523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
                1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
                2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
              };

//add here a nokia tone. remember to update the "song" array below
const char song0[] =
  "Let It Snow:d=4,o=5,b=125:8c,8c,8c6,8c6,a#,a,g,f,2c,8c,16c,g.,8f,g.,8f,e,2c,d,8d6,8d6,c6,a#,a,2g.,8e.6,16d6,c6,8c.6,16a#,a,8a#.,16a,2f.,c,8c6,8c6,a#,a,g,f,2c,8c.,16c,g.,8f,g.,8f,e,2c,d,8d6,8d6,c6,a#,a,2g.,8e.6,16d6,c6,8c.6,16a#,a,8a.,16g,2f. ";
const char song1[] =
  "Silent Night:d=4,o=5,b=90:a.,16b,a,4f#,p,a.,16b,a,4f#,p,e.6,16d#6,e6,4c#6,p,d.6,16c#6,d6,4a";
const char song2[] =
  "Rudolph the Red Nose Reindeer:d=4,o=5,b=125:8g.,16a,8p,16g.,e,c6,a,2g.,8g.,16a,8g.,16a,g,c6,1b,8f.,16g,8p,16f.,d,b,a,2g.,8g.,16a,8g.,16a,g,a,1e,8g.,16a,8p,16g.,e,c6,a,1g,8g.,16a,8g.,16a,g,c6,1b,8f.,16g,8p,16f.,d,b,a,1g,8g.,16a,8g.,16a,g,d6,1c6,a,a,c6,a,g,8e.,2g,f,a,g,8f.,1e,d,e,g,a,b,8b.,1b,c6,8p,16c6,b,a,g,8f.,2d";
const char song3[] =
  "We Wish You A Merry Christmas:d=4,o=5,b=200:d,g,8g,8a,8g,8f#,e,e,e,a,8a,8b,8a,8g,f#,d,d,b,8b,8c6,8b,8a,g,e,d,e,a,f#,2g,d,g,8g,8a,8g,8f#,e,e,e,a,8a,8b,8a,8g,f#,d,d,b,8b,8c6,8b,8a,g,e,d,e,a,f#,1g,d,g,g,g,2f#,f#,g,f#,e,2d,a,b,8a,8a,8g,8g,d6,d,d,e,a,f#,2g";
const char song4[] =
  "Happy New Year:d=4,o=5,b=125:a5,d.,8d,d,f#,e.,8d,e,8f#,8e,d.,8d,f#,a,2b.,b,a.,8f#,f#,d,e.,8d,e,8f#,8e,d.,8b5,b5,a5,2d,16p";
const char song5[] =
  "Santa Clause is Coming Tonight:d=4,o=5,b=200:g,8e,8f,g,g.,8g,8a,8b,c6,2c6,8e,8f,g,g,g,8a,8g,f,2f,e,g,c,e,d,2f,b4,1c,p,g,8e,8f,g,g.,8g,8a,8b,c6,2c6,8e,8f,g,g,g,8a,8g,f,f,e,g,c,e,d,2f,b4,1c,p,c6,d6,c6,b,c6,a,2a,c6,d6,c6,b,c6,2a.,d6,e6,d6,c#6,d6,b,b,b,8b,8c6,d6,c6,b,a,g,p,g.,8g,8e,8f,g,g.,8g,8a,8b,c6,2c6,8e,8f,g,g,g,8a,8g,8f,2f,e,g,c,e,d,2f,d6,1c6.";
const char song6[] =
  "Jingle Bells:d=4,o=5,b=125:8g,8e6,8d6,8c6,2g,8g,8e6,8d6,8c6,2a,8a,8f6,8e6,8d6,8b,8g,8b,8d6,8g.6,16g6,8f6,8d6,2e6,8g,8e6,8d6,8c6,2g,16f#,8g,8e6,8d6,8c6,2a,8a,8f6,8e6,8d6,8g6,16g6,16f#6,16g6,16f#6,16g6,16g#6,8a.6,16g6,8e6,8d6,c6,g6,8e6,8e6,8e.6,16d#6,8e6,8e6,8e.6,16d#6,8e6,8g6,8c.6,16d6,2e6,8f6,8f6,8f.6,16f6,8f6,8e6,8e6,16e6,16e6,8e6,8d6,8d6,8e6,2d6";
const char song7[] =
  "O Christmas Tree:d=4,o=5,b=140:c,8f.,16f,f,g,8a.,16a,a.,8p,8a,8g,8a,a#,e,g,f";

const  char *  const song[] =
{
  song0, song1, song2, song3, song4, song5, song6, song7
};


//scorro la canzone da questo indice in avanti. quando la nota che sto suonando finisce passo alla successiva richiamando play_rtttl
//la funzione decide per quanto tempo devo tenere la nota. finita la nota
//si passa alla nota successiva
int songIndex = 0; //indice della nota che sto suonando adesso
int songFreq = 0; //frequenza della nota che sto suonando adesso
unsigned long songTime = 0; //durata della nota che sto suonando adesso
int songbpm = 63;
unsigned char songdefault_dur = 4;
unsigned char songdefault_oct = 6;
long songwholenote;
int songNumber = 0;

unsigned char songEnabled = 0;
unsigned char songAutoRepeat = 0;



char songCache[8];
int songCacheIndex = -99;
int songCacheNumber = -99;

int play_rtttl_song()
{
  return songNumber;
}

char * songCacheRead(int iNumber, int iIndex)
{
  if (songCacheNumber != iNumber) //changed song?
  {
    songCacheIndex = -99; //discard old cache
  }

  if (iIndex >= (songCacheIndex + 8)) //out of boundaries?
  {
    songCacheIndex = -99; //discard old cache
  }
  if (songCacheIndex < 0)
  {
    songCacheIndex = iIndex;
    memcpy((void *)songCache, (void *)(song[songNumber] + iIndex), 8);
  }

  return songCache + (iIndex - songCacheIndex);

}

#define isdigit(n) (n >= '0' && n <= '9')

int play_rtttl()
{

  char *p;//next byte!!
  int num;

  long duration;
  unsigned char note;
  unsigned char scale;

  if (songEnabled == 0) return 0;


  p = songCacheRead(songNumber, songIndex);
  if (*p == 0)
  {
    if (songAutoRepeat != 0)

    {
      return 1; //end of song
    }
    else
    {
      return 0; //end of song, but do not notify so end forever

    }
  }

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  if (songIndex == 0) //begin of song
  {

    songbpm = 63;
    songdefault_dur = 4;
    songdefault_oct = 6;


    while (*p != ':')
    {
      // ignore name
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }
    // skip ':'
    songIndex++;
    p = songCacheRead(songNumber, songIndex);
    // get default duration
    if (*p == 'd')
    {

      // skip "d="
      songIndex++;
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
      num = 0;
      while (isdigit(*p))
      {
        num = (num * 10) + (*p - '0');
        songIndex++;
        p = songCacheRead(songNumber, songIndex);
      }
      if (num > 0) songdefault_dur = num;
      // skip comma
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }

    // Serial.print("ddur: "); Serial.println(songdefault_dur, 10);

    // get default octave
    if (*p == 'o')
    {
      // skip "o="
      songIndex++;
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
      num = *p - '0';
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
      if (num >= 3 && num <= 7) songdefault_oct = num;
      // skip comma
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }

    //Serial.print("doct: "); Serial.println(songdefault_oct, 10);

    // get BPM
    if (*p == 'b')
    {
      // skip "b="
      songIndex++;
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
      num = 0;
      while (isdigit(*p))
      {
        num = (num * 10) + (*p - '0');
        songIndex++;
        p = songCacheRead(songNumber, songIndex);
      }
      songbpm = num;
      // skip colon
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }

    //Serial.print("bpm: "); Serial.println(songbpm, 10);

    // BPM usually expresses the number of quarter notes per minute
    songwholenote = (60 * 1000L / songbpm) * 4;  // this is the time for whole note (in milliseconds)

    //Serial.print("wn: "); Serial.println(songwholenote, 10);
  }


  // now begin note loop
  while (*p)
  {
    // first, get note duration, if available
    num = 0;
    while (isdigit(*p))
    {
      num = (num * 10) + (*p - '0');
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }

    if (num) duration = songwholenote / num;
    else duration = songwholenote / songdefault_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch (*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    songIndex++;
    p = songCacheRead(songNumber, songIndex);
    // now, get optional '#' sharp
    if (*p == '#')
    {
      note++;
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }

    // now, get optional '.' dotted note
    if (*p == '.')
    {
      duration += duration / 2;
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }

    // now, get scale
    if (isdigit(*p))
    {
      scale = *p - '0';
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }
    else
    {
      scale = songdefault_oct;
    }

    scale += OCTAVE_OFFSET;

    if (*p == ',')
    {
      // skip comma for next note (or we may be at the end)
      songIndex++;
      p = songCacheRead(songNumber, songIndex);
    }
    // now play the note

    if (note)
    {
      //  Serial.print("Playing: ");
      //  Serial.print(scale, 10); Serial.print(' ');
      //  Serial.print(note, 10); Serial.print(" (");
      //  Serial.print(notes[(scale - 4) * 12 + note], 10);
      //  Serial.print(") ");
      //  Serial.println(duration, 10);

      songFreq = notes[(scale - 4) * 12 + note];
      stm8Tone(songFreq);

      //next time this function will be called...
      songTime = millis() + (duration * 12) / 10; //      delay(duration);
    }
    else
    {
      songFreq = 0;
      //Serial.print("Pausing: ");
      //Serial.println(duration, 10);
      //                   delay(duration);
      stm8NoTone();
      songTime = millis() + (duration * 12) / 10; //
    }


    return 0;

  }



  return 1;

}


int play_rtttl_stop()
{
  stm8NoTone();
  songEnabled = 0;
  return 0;
}

int play_rtttl_start(int song)
{
  stm8NoTone();
  songNumber = song;
  songIndex = 0;
  songEnabled = 1;
  songAutoRepeat = 1;
  songTime = 0;
  return 0;
}

void play_rtttl_start_no_repeat(int song)
{
  play_rtttl_start(song);
  songAutoRepeat = 0;
}




/*****************************/





void stm8Tone(int freq)
{
  TIM1_DeInit();
  //void TIM1_TimeBaseInit(uint16_t TIM1_Prescaler,
  //                       TIM1_CounterMode_TypeDef TIM1_CounterMode,
  //                       uint16_t TIM1_Period, uint8_t TIM1_RepetitionCounter);
  int periodo = 25000 / (freq / 10);

  TIM1_TimeBaseInit(63, TIM1_COUNTERMODE_UP, periodo, 0);//-->980hz = 16M/64/255=980

  TIM1_OC4Init(
    TIM1_OCMODE_PWM1,
    TIM1_OUTPUTSTATE_ENABLE,
    127, // 50% duty cycle
    TIM1_OCPOLARITY_HIGH,
    TIM1_OCIDLESTATE_SET
  );

  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);

}
void stm8NoTone()
{
  digitalWrite(6, LOW);
}





void setup() {
  play_rtttl_start(0);
}

void loop() {
  if (millis() > songTime)
  {
    //time to play next tone?
    if (play_rtttl() == 1)//end of sound???
    {
      stm8NoTone();
      delay(1000);
      songNumber++;
      if (songNumber == 8) songNumber = 0;
      play_rtttl_start(songNumber);
    }
  }

 
}
