#include <MIDI.h>

const int MIDI_CHANNEL = 10; // the midi channel to read

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()  {
  setupMidi();
} 

void loop()  {
  MIDI.read();           
}

/**
 * Initialize the Midi functionality/listeners
 */
void setupMidi() {
    MIDI.begin(MIDI_CHANNEL);
    MIDI.turnThruOn();
    MIDI.setHandleNoteOn(handleMidiNoteOn);
    MIDI.setHandleNoteOff(handleMidiNoteOff);
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.setHandleProgramChange(handleProgramChange);
}

/***************************
 * INCOMING INSTRUCTIONS   *
 ***************************/
/**
 * Handle a midi note on command
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void handleMidiNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel == MIDI_CHANNEL) {
    
  }
}

/**
 * Handle a midi note off command
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void handleMidiNoteOff(byte channel, byte pitch, byte velocity) {
  if (channel == MIDI_CHANNEL) {
    
  }
}

/**
 * Handle a midi note off command
 * @arg {Byte} channel
 * @arg {Byte} number
 * @arg {Byte} value
 */
void handleControlChange(byte channel, byte number, byte value) {
  if (channel == MIDI_CHANNEL) {
    
  }
}

/**
 * Handle a midi note off command
 * @arg {Byte} channel
 * @arg {Byte} number
 */
void handleProgramChange(byte channel, byte number) {
  if (channel == MIDI_CHANNEL) {
    
  }
}
