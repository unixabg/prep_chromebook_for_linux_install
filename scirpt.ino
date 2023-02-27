/*
DO NOT CHANGE void loop() to an int main() or it will lock up the Arduion centipede.
For use on chromebook in developer mode escalated as root.
*/

#include <Keyboard.h> // Include the virtual keyboard

#define slowMode 0 // [0,1] Set to 1 if Centipede appears to be moving too quickly at any screen. This will slow down the entire process
// Special Characters Definition
#define KEY_ENTER     0xB0

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
    // Add more command functions towards bottom or program and call them from this function
    enterCommandOne(); // Call function
    enterCommandTwo(); // Call function
    enterCommandThree(); // Call function
  };
  running = false;
}

// Using this function to compare performace between Keyboard.press() using the string like a list of characters
// and using the Keyboard.print() function
void enterCommandOne() {
  static String command_one = "flashrom --wp-status"; // Setting as static to help load into memory sooner
  //Uncomment the next 4 lines to try Keyboard.press()
  for(int i = 0; i < command_one.length(); i++) {
    wait(1);
    Keyboard.press(command_one[i]);
    Keyboard.releaseAll();
  }
  Keyboard.write(KEY_ENTER); // Press Enter
}

void enterCommandTwo() {
  static String command_two = "flashrom --wp-disable"; // Setting as static to help load into memory sooner
  for(int i = 0; i < command_two.length(); i++) {
    wait(1);
    Keyboard.press(command_two[i]);
    Keyboard.releaseAll();
  }
  Keyboard.write(KEY_ENTER); // Press Enter
}

void enterCommandThree() {
  static String command_three = "flashrom --wp-status"; // Setting as static to help load into memory sooner
  for(int i = 0; i < command_three.length(); i++) {
    wait(1);
    Keyboard.press(command_three[i]);
    Keyboard.releaseAll();
  }
  Keyboard.write(KEY_ENTER); // Press Enter
}

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
