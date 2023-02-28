/*
DO NOT CHANGE void loop() to an int main() or it will lock up the Arduion centipede.
For use on chromebook in developer mode escalated as root.
*/

#include <Keyboard.h> // Include the virtual keyboard

#define slowMode 0 // [0,1] Set to 1 if Centipede appears to be moving too quickly at any screen. This will slow down the entire process
// Special Characters Definition
#define KEY_ENTER 0xB0

//Add your command variables below
static String command_one = "flashrom --wp-status";
static String command_two = "flashrom --wp-disable";

int RXLED = 17;
static uint8_t __clock_prescaler = (CLKPR & (_BV(CLKPS0) | _BV(CLKPS1) | _BV(CLKPS2) | _BV(CLKPS3)));
bool running = true;

void setup() {
  setPrescaler(); //Set prescaler to highest clock speed
  Keyboard.begin(); //Initiate the keyboard emulator
  wait(5); //Wait for all services to finish loading
}

void loop() {
  if (running) { //Using this boolean to stop the loop from restarting
    // Add more runCommand function calls with your variable (added above) as a parameter 
    runCommand(command_one);
    runCommand(command_two);
    runCommand(command_one);
  };
  running = false;
}

void runCommand(String command) {
  for (int i = 0; i < command.length(); i++) {
    delay(50);
    Keyboard.press(command[i]);
    Keyboard.releaseAll();
  }
  Keyboard.write(KEY_ENTER);
}

// This function sets the clock of the arduino board 
void setPrescaler() {
  //Disable interrupts.
  uint8_t oldSREG = SREG;
  cli();

  // Enable change.
  CLKPR = _BV(CLKPCE); // write the CLKPCE bit to one and all the other to zero

  // Change clock division.
  CLKPR = 0x0; // write the CLKPS0..3 bits while writing the CLKPE bit to zero

  // Copy for fast access.
  __clock_prescaler = 0x0;

  // Recopy interrupt register.
  SREG = oldSREG;
}

void blink() {
  digitalWrite(RXLED, LOW);
  //  TXLED1;
  delay(250);
  digitalWrite(RXLED, HIGH);
  //  TXLED0;
  delay(250);
}

// Defines wait()
void wait(int cycles) {
  for (int i = 0; i < cycles; i++) {
    blink();
    if (slowMode) {
      delay(250);
    }
  }
}