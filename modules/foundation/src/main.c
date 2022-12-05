#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdbool.h>

#include "defs.h"
#include "log_scale.h"
#include "setup.h"
#include "helpers.h"

/* https://en.wikipedia.org/wiki/Linear-feedback_shift_register */
/* https://datacipy.cz/lfsr_table.pdf */
void make_noise(void)
{
        static uint32_t lfsr = 0x12345678;
        uint32_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 6) ^ (lfsr >> 7)) & 1;
        lfsr = (lfsr >> 1) | (bit << 31);
        if(lfsr>>31)
                digital_write(noise_pin, true);
        else
                digital_write(noise_pin, false);
}

ISR(STRIKE)
{
        PWM_VALUE = 0;
        digital_write(pulse_pin, true);
        _delay_ms(1);
        uint8_t decay_value = read_decay();
        PWM_VALUE = pgm_read_byte(&log_scale[decay_value]);
        digital_write(pulse_pin, false);
}

int main(void) {
        setup();
        while (1)
                make_noise();
}
