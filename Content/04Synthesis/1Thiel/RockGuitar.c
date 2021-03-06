// RockGuitar.cpp : Derived from EXPE8.asm in GV100

//#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "pablio.h"

#define SAMPLE_RATE   6000
#define NUM_FRAMES    1000

unsigned char TuneScripts[6][46] =
{
//TUNE0
	{	0xF1,0x73,0xC3,0x73,0xC3,0xF2,
		0x73,0xC3,0xF1,0x73,0xC3,0xF2,
		0x73,0xC3,0xF1,0x73,0xC3,0xF2,
		0x03,0x23,0x53,0x73,0x73,
		0xC3,0x73,0xC3,0xF3,0x73,0xC3,
		0xF2,0x73,0xC3,0xF3,0x53,0x23,
		0x73,0x53,0xA3,0x74,0x54,0x03,
		0xF2,0xA3,0x71,0xFF},
//TUNE1
	{	0xF1,0x72,0x53,0x23,0x72,0xC2,
		0x73,0x73,0x53,0x32,0x73,0x53,0xC2,
		0x72,0x53,0x23,0x53,0x73,0xA3,
		0xF2,0x03,0x23,0x53,0x73,0xA3,
		0xF3,0x03,0x23,0x53,0xA3,0xFF},
//TUNE2
	{	0xF1,0x73,0x53,0x73,0xAC,0xF2,
		0x03,0xF1,0xA3,0xF2,0x03,0xF1,
		0x51,0x73,0x53,0xA3,0x73,0xF2,
		0x03,0xF1,0xA3,0xF2,0x23,0x03,
		0x53,0x23,0x73,0x53,0xA3,0x73,
		0xF3,0x03,0xF2,0xA3,0xF3,0x23,
		0x03,0x53,0x23,0x73,0x53,0xA3,
		0xFF},
//TUNE3
	{	0xF1,0x72,0xF2,0x72,0xF1,0x42,
		0xF2,0x42,0xF1,0x52,0xF2,0x52,
		0xF1,0x62,0xF2,0x62,0xF1,0x73,
		0x53,0xF2,0x0E,0xF1,0xA3,0xF2,
		0x23,0x03,0x73,0x53,0xA3,0x73,
		0xF3,0x03,0xF2,0xA3,0xF3,0x23,
		0x03,0x73,0x53,0xFF},
//TUNE4
	{	0xF3,0x73,0x23,0x03,
		0xF2,0xA3,0xF3,0x03,
		0xF2,0xA3,0x73,0x23,
		0x53,0x72,0xC4,0x54,
		0x77,0x57,0x77,
		0xA7,0x77,0xA7,
		0xF3,0x07,0xF2,0xA7,0xF3,0x07,	
		0x27,0x07,0x27,
		0xFF},
//TUNE5
	{	0xF1,0x73,0x53,0x73,0xAC,0x73,0x53,
		0x57,0xA7,0xF2,0x07,0xF1,
		0x73,0xA3,0xF2,0x03,0x23,0x08,0x28,0x58,
		0x74,0xA4,0xF3,0x04,0x24,
		0xF2,0xA8,0xF3,0x08,0x28,0x04,0x24,0x54,0x74,
		0xFF}
};	//TuneScripts[6][48]


unsigned short PitchIncrements [] = {	//Equal temperment wavetable pointer increments for top octave
		0x4AFB,0x4F6D,0x5428,0x5928,	// c,	c#,	d,	d#
		0x5E75,0x6413,0x6A07,0x7054,	// e,	f,	f#,	g
		0x7703,0x7E16,0x8595,0x8D86,	// g#,	a,	a#,	b			
		0x0000
};
unsigned char Durations [] = {
		0x60,0x30,0x18,0x0C,0x06,	//whole, half, eighth, sixteenth, thirty second note durations
		0x20,0x10,0x08,0x04,0x02,	//whole, half, eighth, sixteenth, thirty second Triplet note durations
		0x90,0x48,0x24,0x12,0x09	//dotted whole, half, eighth, sixteenth, thirty second note durations
};

// XXX perhaps we should generate this...
unsigned char SineWave[] ={	//8 bit unsigned sine wave
		0xFE,0xFE,0xFE,0xFE,
		0xFE,0xFD,0xFD,0xFD,
		0xFC,0xFB,0xFB,0xFA,
		0xF9,0xF8,0xF7,0xF6,
		0xF5,0xF4,0xF2,0xF1,
		0xF0,0xEE,0xED,0xEB,
		0xE9,0xE7,0xE6,0xE4,
		0xE2,0xE0,0xDE,0xDC,
		0xD9,0xD7,0xD5,0xD3,
		0xD0,0xCE,0xCB,0xC9,
		0xC6,0xC4,0xC1,0xBE,
		0xBC,0xB9,0xB6,0xB3,
		0xB0,0xAE,0xAB,0xA8,
		0xA5,0xA2,0x9F,0x9C,
		0x99,0x96,0x93,0x8F,
		0x8C,0x89,0x86,0x83,
		0x80,0x7D,0x7A,0x77,
		0x73,0x70,0x6D,0x6A,
		0x67,0x64,0x61,0x5E,
		0x5B,0x58,0x55,0x52,
		0x4F,0x4C,0x4A,0x47,
		0x44,0x41,0x3F,0x3C,
		0x39,0x37,0x34,0x32,
		0x2F,0x2D,0x2B,0x28,
		0x26,0x24,0x22,0x20,
		0x1E,0x1C,0x1A,0x18,
		0x16,0x15,0x13,0x11,
		0x10,0x0E,0x0D,0x0C,
		0x0A,0x09,0x08,0x07,
		0x06,0x05,0x05,0x04,
		0x03,0x03,0x02,0x02,
		0x01,0x01,0x01,0x01,
		0x01,0x01,0x01,0x01,
		0x01,0x02,0x02,0x02,
		0x03,0x04,0x04,0x05,
		0x06,0x07,0x08,0x09,
		0x0A,0x0B,0x0D,0x0E,
		0x0F,0x11,0x12,0x14,
		0x16,0x18,0x19,0x1B,
		0x1D,0x1F,0x21,0x23,
		0x26,0x28,0x2A,0x2C,
		0x2F,0x31,0x34,0x36,
		0x39,0x3B,0x3E,0x41,
		0x43,0x46,0x49,0x4C,
		0x4F,0x51,0x54,0x57,
		0x5A,0x5D,0x60,0x63,
		0x66,0x69,0x6C,0x70,
		0x73,0x76,0x79,0x7C,
		0x7F,0x82,0x85,0x88,
		0x8C,0x8F,0x92,0x95,
		0x98,0x9B,0x9E,0xA1,
		0xA4,0xA7,0xAA,0xAD,
		0xB0,0xB3,0xB5,0xB8,
		0xBB,0xBE,0xC0,0xC3,
		0xC6,0xC8,0xCB,0xCD,
		0xD0,0xD2,0xD4,0xD7,
		0xD9,0xDB,0xDD,0xDF,
		0xE1,0xE3,0xE5,0xE7,
		0xE9,0xEA,0xEC,0xEE,
		0xEF,0xF1,0xF2,0xF3,
		0xF5,0xF6,0xF7,0xF8,
		0xF9,0xFA,0xFA,0xFB,
		0xFC,0xFC,0xFD,0xFD,
		0xFE,0xFE,0xFE,0xFE
};

void BassDrumSynthesizer(unsigned short *BassDrumPointerIncrement,unsigned short *BassDrumOutput,unsigned char *BassDrumIsOn)
{
unsigned char  WaveTableIndex;
unsigned short static BassDrumWavePointer = 0;

	BassDrumWavePointer += *BassDrumPointerIncrement;
	WaveTableIndex = BassDrumWavePointer >> 8;	
	*BassDrumOutput = SineWave[WaveTableIndex];
	*BassDrumOutput = *BassDrumOutput >> 1;
	if( !*BassDrumIsOn ) *BassDrumOutput = 0;
	if(--(*BassDrumPointerIncrement) == 0) *BassDrumIsOn = 0;//when Pitch Increment goes to 0 then turn bass drum output off
};

int main(int argc, char* argv[]) {
   unsigned char	TuneSelection;
   unsigned char	CurrentOctave;
   unsigned char	ScriptIndex;
   unsigned char	BassDrumIsOn;
   unsigned short       BassDrumPointerIncrement;
   unsigned char	BassDrumDurationCount;
   unsigned short       BassDrumOutput;

   unsigned char	CurrentNoteEvent;
   unsigned char	NoteDurationCount;
   unsigned char	NoteIndex;
   unsigned short       NotePointerIncrement;
   unsigned short       NoteWavePointer;
   unsigned short       NoteAndBDOutput;
   unsigned char	NoteSynthOutput;

   unsigned short       TempoCounter;
   unsigned short       OverFlow;
   unsigned char	*WaveRAM;
   unsigned char	WaveINDEX;
   unsigned char        temp1 = 255;
   signed char temp2;
   short buffer[NUM_FRAMES];
   PABLIO_Stream *outStream;

   if (argc != 2){
     //printf("RockGuitar: Needs number 0-5\n");
     exit;
   } 
   temp2 = temp1;
   //wave table data for note synthesizer has the routine variables as its origin
   WaveRAM = &TuneSelection;
   OpenAudioStream(&outStream, SAMPLE_RATE, paInt16, PABLIO_WRITE|PABLIO_MONO);
   printf("Starting Synthesis!\n");
   //client input, tune selector Jukebox
   TuneSelection = (unsigned char) atoi (argv[1]);
   printf("Selected Tune Script is %d\n",TuneSelection);

   //first time initialization
   CurrentOctave            = 3;	//octave state
   ScriptIndex              = 0;	//index to Tune script elements
   BassDrumIsOn             = 0xff;	//0xff = True, 0x00 = False
   BassDrumPointerIncrement = 0x07ff;	//pitch for first bass drum event
   BassDrumDurationCount    = 0x30;	//duration for Bass Drum event

   CurrentNoteEvent = TuneScripts[TuneSelection][ScriptIndex++];	//prime pump, Sequencer gets first script element
   while(CurrentNoteEvent != 0xff){ //0xff is the end of script element
      if( ((CurrentNoteEvent & 0xf0)) == 0xf0){
   	 // control element  only octave is currently defined
   	 if( (CurrentNoteEvent & 0x0f) < 8){ // if note event
   	    CurrentOctave = CurrentNoteEvent & 0x0f;
   	    CurrentOctave = 7 - CurrentOctave;	//invert it no division for top octave
   	 }
      } else { // note event, set it up and synthesize
   	 //number of ticks for this note event
   	 NoteDurationCount = Durations[ (CurrentNoteEvent & 0x0f)];	
   	 NoteIndex = (CurrentNoteEvent&0xf0)>>4;
	 
   	 NotePointerIncrement = PitchIncrements[NoteIndex] >> CurrentOctave;
   	 while(NoteDurationCount){
   	    //synthesis loop|PABLIO_MONO

   	    //synthesize bass drum
   	    BassDrumSynthesizer(&BassDrumPointerIncrement,&BassDrumOutput,
	                        &BassDrumIsOn);
	    NoteAndBDOutput = BassDrumOutput;

   	    //FuzzGuitar tone generator
   	    NoteWavePointer += NotePointerIncrement;
   	    WaveINDEX = NoteWavePointer >> 8;	
	    NoteSynthOutput = *(WaveRAM+(WaveINDEX));

   	    //power of two mixing
   	    NoteAndBDOutput += NoteSynthOutput >> 1;
	    //write 8 bit unsigned raw Output to file for 6000 kHz playback sampling rate
	    buffer[0] =  (short)((NoteAndBDOutput - 0x7F)<<8);
	    WriteAudioStream(outStream, buffer, 1);

   	    //scale tick to provide tempo control
   	    OverFlow = TempoCounter;
   	    TempoCounter += 0x0301;
   	    if(TempoCounter < OverFlow){
   	       //OverFlow overflowed so a tick has occurred
   	       if(--BassDrumDurationCount == 0){
   		  //time for new bass drum
   		  BassDrumDurationCount = 0x30;
   		  BassDrumIsOn = 0xFF;
   		  BassDrumPointerIncrement = 0x07FF;
   	       }
   	       //2 tick separation of each note event
   	       if(NoteDurationCount == 2)
   		  NotePointerIncrement = 0;
   	       NoteDurationCount--;
   	    }
      	 }
      }// note event, set it up and synthesize
      //get next script element		
      CurrentNoteEvent = TuneScripts[TuneSelection][ScriptIndex++];	
   } //end of CurrentNoteEvent != 0xff
   CloseAudioStream(outStream);
return 0;
}

