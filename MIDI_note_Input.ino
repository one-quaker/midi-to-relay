#include <MIDI.h> // Midi Library https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/4.2

// Relay module pins
#define R1 9
#define R2 10
#define R3 11
#define R4 12

#define LED 13

// MIDI Note codes
#define NOTE01 40
#define NOTE02 41
#define NOTE03 43
#define NOTE04 45


//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(LED, OUTPUT); // Set Arduino board pin 13 to output
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  digitalWrite(R1, !LOW); // relay module with optocoupler, inverted signal
  digitalWrite(R2, !LOW); // relay module with optocoupler, inverted signal
  digitalWrite(R3, !LOW); // relay module with optocoupler, inverted signal
  digitalWrite(R4, !LOW); // relay module with optocoupler, inverted signal


  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
  // MIDI.setHandleControlChange(MyCCFunction); // This command tells the MIDI Library
  // the function you want to call when a Continuous Controller command
  // is received. In this case it's "MyCCFunction".

  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it
  // to respond to notes on channel 2 only.
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.
}

// MyCCFunction is the function that will be called by the Midi Library
// when a Continuous Controller message is received.
// It will be passed bytes for Channel, Controller Number, and Value
// It checks if the controller number is within the 22 to 27 range
// If it is, light up the corresponding LED with the PWM brightness equal to the Value byte
void MyHandleNoteOn(byte channel, byte note, byte velocity) {
    switch (note) {
      case NOTE01:
        relayControl(R1, HIGH);
        break;
      case NOTE02:
        relayControl(R2, HIGH);
        break;
      case NOTE03:
        relayControl(R3, HIGH);
        break;
      case NOTE04:
        relayControl(R4, HIGH);
        break;
    }
}

void MyHandleNoteOff(byte channel, byte note, byte velocity) {
    switch (note) {
      case NOTE01:
        relayControl(R1, LOW);
        break;
      case NOTE02:
        relayControl(R2, LOW);
        break;
      case NOTE03:
        relayControl(R3, LOW);
        break;
      case NOTE04:
        relayControl(R4, LOW);
        break;
    }
}

void relayControl(int _pin, int _state) {
    digitalWrite(LED, _state);
    digitalWrite(_pin, !_state); // relay module with optocoupler, inverted signal
}
