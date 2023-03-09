/*
DO NOT CHANGE void loop() to an int main() or it will lock up the Arduion centipede.
For use on chromebook in developer mode escalated as root.
*/

#include <Keyboard.h> // Include the virtual keyboard

#define slowMode 0 // [0,1] Set to 1 if Centipede appears to be moving too quickly at any screen. This will slow down the entire process
//================================================================================
//================================================================================
//  Keyboard

/*
//As of 20230228 the below is what is in the Keyboard.h file.
// Modifiers
#define KEY_LEFT_CTRL     0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT      0x82
#define KEY_LEFT_GUI      0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT     0x86
#define KEY_RIGHT_GUI     0x87

// Misc keys
#define KEY_UP_ARROW      0xDA
#define KEY_DOWN_ARROW    0xD9
#define KEY_LEFT_ARROW    0xD8
#define KEY_RIGHT_ARROW   0xD7
#define KEY_BACKSPACE     0xB2
#define KEY_TAB           0xB3
#define KEY_RETURN        0xB0
#define KEY_MENU          0xED // "Keyboard Application" in USB standard
#define KEY_ESC           0xB1
#define KEY_INSERT        0xD1
#define KEY_DELETE        0xD4
#define KEY_PAGE_UP       0xD3
#define KEY_PAGE_DOWN     0xD6
#define KEY_HOME          0xD2
#define KEY_END           0xD5
#define KEY_CAPS_LOCK     0xC1
#define KEY_PRINT_SCREEN  0xCE // Print Screen / SysRq
#define KEY_SCROLL_LOCK   0xCF
#define KEY_PAUSE         0xD0 // Pause / Break

// Numeric keypad
#define KEY_NUM_LOCK      0xDB
#define KEY_KP_SLASH      0xDC
#define KEY_KP_ASTERISK   0xDD
#define KEY_KP_MINUS      0xDE
#define KEY_KP_PLUS       0xDF
#define KEY_KP_ENTER      0xE0
#define KEY_KP_1          0xE1
#define KEY_KP_2          0xE2
#define KEY_KP_3          0xE3
#define KEY_KP_4          0xE4
#define KEY_KP_5          0xE5
#define KEY_KP_6          0xE6
#define KEY_KP_7          0xE7
#define KEY_KP_8          0xE8
#define KEY_KP_9          0xE9
#define KEY_KP_0          0xEA
#define KEY_KP_DOT        0xEB

// Function keys
#define KEY_F1            0xC2
#define KEY_F2            0xC3
#define KEY_F3            0xC4
#define KEY_F4            0xC5
#define KEY_F5            0xC6
#define KEY_F6            0xC7
#define KEY_F7            0xC8
#define KEY_F8            0xC9
#define KEY_F9            0xCA
#define KEY_F10           0xCB
#define KEY_F11           0xCC
#define KEY_F12           0xCD
#define KEY_F13           0xF0
#define KEY_F14           0xF1
#define KEY_F15           0xF2
#define KEY_F16           0xF3
#define KEY_F17           0xF4
#define KEY_F18           0xF5
#define KEY_F19           0xF6
#define KEY_F20           0xF7
#define KEY_F21           0xF8
#define KEY_F22           0xF9
#define KEY_F23           0xFA
#define KEY_F24           0xFB

*/

//Add your command variables below
static String command_one = "chronos";
static String command_two = "sudo -i";
static String command_three = "cd /tmp";
static String command_four = "flashrom --wp-status";
static String command_five = "flashrom --wp-disable";
//static String command_six = "flashrom -r bios.bin";
static String command_seven = "/usr/share/vboot/bin/set_gbb_flags.sh 0x19";
static String command_eight = "flashrom --wp-enable --wp-range 0x00000000 0x00200000";
//static String command_nine = "flashrom --wp-enable";
static String command_ten = "flashrom --wp-status";
static String command_eleven = "shutdown -h now";

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
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F3);
    Keyboard.releaseAll();
    wait(3); //Wait for the terminal to appear loading
    // Add more runCommand function calls with your variable (added above) as a parameter
    runCommand(command_one);
    runCommand(command_two);
    runCommand(command_three);
    runCommand(command_four);
    runCommand(command_five);
    //runCommand(command_six);
    runCommand(command_seven);
    runCommand(command_eight);
//    runCommand(command_nine);
    runCommand(command_ten);
    runCommand(command_eleven);
  };
  running = false;
}

void runCommand(String command) {
  wait(5); //Wait for the terminal to appear loading
  for (int i = 0; i < command.length(); i++) {
    delay(50);
    Keyboard.press(command[i]);
    Keyboard.releaseAll();
  }
  Keyboard.write(KEY_RETURN);
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
