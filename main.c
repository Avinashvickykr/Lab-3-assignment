#include <stdint.h>
#include "tm4c123gh6pm.h"

void delayMs(int n);

int main(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;              // Enable clock to Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);  // Wait until ready

    GPIO_PORTF_LOCK_R = 0x4C4F434B;         // Unlock Port F
    GPIO_PORTF_CR_R |= 0x1F;                // Allow changes on PF0–PF4

    GPIO_PORTF_DIR_R |= 0x0E;               // PF1, PF2, PF3 = outputs (LEDs)
    GPIO_PORTF_DIR_R &= ~0x11;              // PF0, PF4 = inputs (switches)

    GPIO_PORTF_DEN_R |= 0x1F;               // Enable digital pins PF0–PF4
    GPIO_PORTF_PUR_R |= 0x11;               // Pull-up on switches PF0, PF4

    while (1) {
        int sw1 = (GPIO_PORTF_DATA_R & 0x10) == 0; // SW1 (PF4)
        int sw2 = (GPIO_PORTF_DATA_R & 0x01) == 0; // SW2 (PF0)

        if (sw1 && sw2) {
            // Both pressed -> Blink BLUE
            GPIO_PORTF_DATA_R |= 0x04;  // ON BLUE (PF2)
            delayMs(200);
            GPIO_PORTF_DATA_R &= ~0x04; // OFF BLUE
            delayMs(200);
        }
        else if (sw1) {
            // Left switch -> Blink GREEN
            GPIO_PORTF_DATA_R |= 0x08;  // ON GREEN (PF3)
            delayMs(200);
            GPIO_PORTF_DATA_R &= ~0x08; // OFF GREEN
            delayMs(200);
        }
        else if (sw2) {
            // Right switch -> Blink RED
            GPIO_PORTF_DATA_R |= 0x02;  // ON RED (PF1)
            delayMs(200);
            GPIO_PORTF_DATA_R &= ~0x02; // OFF RED
            delayMs(200);
        }
        else {
            // No switch pressed -> all OFF
            GPIO_PORTF_DATA_R &= ~0x0E;
        }
    }
}

void delayMs(int n) {
    volatile int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3180; j++) {}  // ~1ms delay at 16 MHz
}
