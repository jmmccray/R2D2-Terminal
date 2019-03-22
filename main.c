#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define LEFT_BUTTON    BIT1

// THIS MACRO HAS TO BE DEFINED BY YOU
#define RIGHT_BUTTON   BIT4

#define LED1           BIT0

// THIS MACRO HAS TO BE DEFINED BY YOU
#define LED2_RED       BIT0

// THIS MACRO HAS TO BE DEFINED BY YOU
#define LED2_GREEN     BIT1

// THIS MACRO HAS TO BE DEFINED BY YOU
#define LED2_BLUE      BIT2

#define LED2_PURPLE   (BIT0|BIT2)

#define PRESSED 0

enum {RED, BLUE, GREEN, PURPLE, OFF} color = OFF;

void main(void) {

  WDT_A_hold(WDT_A_BASE);

  // Configure the pin connected to LED1 as output
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

  // Configures the pin connect to LED2 as output
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);

  // Configure the pin connected to left button (BTN1) as an input with pull-up resistor
  GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);

  // Configures the pin connected to right button (BTN2) as an input with pull-up resistor
  GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN4);

  unsigned char left_button_prev, left_button_cur;
  unsigned char right_button_prev, right_button_cur;

  // Sets initial state of LED1 to OFF.
  P1OUT = ~LED1;

  while(1) {
      // P1IN contains all the pins on port1
      // When we mask it with LEFT_BUTTON, all the port bits become 0 except for the one representing left button
      // When this masked value becomes 0, it means this button is pressed (grounded).
      left_button_cur = (P1IN & LEFT_BUTTON);

      // Configures
      right_button_cur = (P1IN & RIGHT_BUTTON);


      // We recall that "pushing a button" consists of pressing and then releasing it.
      // If the button "was" pressed, but now it "is not" pressed, it means the user has finished "pushing the button"
      if ((left_button_prev == PRESSED) &&
          (left_button_cur  != PRESSED)) {
          P1OUT ^= LED1; //toggle the LED
      }

      if ((right_button_prev == PRESSED) &&
          (right_button_cur != PRESSED)) {
           switch(color)
          {
          case OFF: //Turns LED2 OFF
              P2OUT = P2OUT&~LED2_RED&~LED2_GREEN&~LED2_BLUE;
              color = RED;
              break;
          case RED: //Turns LED2 RED
              P2OUT = LED2_RED;
              color = BLUE;
              break;
          case BLUE: //Turns LED2 BLUE
              P2OUT = LED2_BLUE;
              color = GREEN;
              break;
          case GREEN: //Turns LED2 GREEN
              P2OUT = LED2_GREEN;
              color = PURPLE;
              break;
          case PURPLE: //Turns LED2 PURPLE
              //P2OUT = LED2_RED|LED2_BLUE;
              P2OUT = LED2_PURPLE;
              color = RED;
              break;
          default: break;
          }
      }

      // Keep the history of this button1 & button2
      left_button_prev = left_button_cur;
      right_button_prev = right_button_cur;
  }
  
}
