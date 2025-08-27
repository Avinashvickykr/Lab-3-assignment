#include <stdint.h>
#include "tm4c123gh6pm.h"
int main(void) {
SYSCTL_RCGCGPIO_R |= 0x20; // Enable clock to Port F
while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Wait for port to be ready
GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock GPIO Port F
GPIO_PORTF_CR_R |= 0x1F; // Allow changes to PF0-PF4
GPIO_PORTF_DIR_R |= 0x02; // PF1 as output (RED LED) // PF0 & PF4 as input (switches)
GPIO_PORTF_DEN_R |= 0x13; // Enable digital on PF0, PF1, PF4
GPIO_PORTF_PUR_R |= 0x11; // Enable pull-up on PF0, PF4
while (1) {
// Read switches (active low: 0 when pressed)
int sw1 = (GPIO_PORTF_DATA_R & 0x10) == 0; // PF4
int sw2 = (GPIO_PORTF_DATA_R & 0x01) == 0; // PF0
if (sw1 || sw2) {
GPIO_PORTF_DATA_R |= 0x02; // Turn on RED LED
} else {
GPIO_PORTF_DATA_R &= 0x0; // Turn off RED LED
}
}}