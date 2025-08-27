#include <stdint.h>
#include "tm4c123gh6pm.h"
// Simple delay function to debounce button press
void delay(int time) {
volatile int i;
for (i = 0; i < time * 10000; i++);
}
int main(void) {
SYSCTL_RCGCGPIO_R |= 0x20;// Enable clock for Port F (bit 5 in RCGCGPIO register)
GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock Port F
GPIO_PORTF_CR_R = 0x1F; // Enable changes to PF0–PF4
GPIO_PORTF_DIR_R = 0x0E; //PF1 (Red), PF2 (Blue), PF3 (Green) as output; PF0 and PF4 as input
GPIO_PORTF_DEN_R = 0x1F; // Enable digital function for PF0–PF4
GPIO_PORTF_PUR_R = 0x11;// Enable pull-up resistors on PF0 and PF4 (buttons)
int state = 2; //Initialize
while (1) {
// Check if either button (PF0 or PF4) is pressed
if ((GPIO_PORTF_DATA_R & 0x11) != 0x11) {
delay(50);
while ((GPIO_PORTF_DATA_R & 0x11) != 0x11);// Wait until button is released
state = (state + 1) % 3;
switch (state) {
case 0: GPIO_PORTF_DATA_R = 0x02; break; // Red
case 1: GPIO_PORTF_DATA_R = 0x08; break; // Green
case 2: GPIO_PORTF_DATA_R = 0x04; break; // Blue
}
}
}
}