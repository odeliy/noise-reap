#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "helpers.h"

void digital_write(uint8_t pin, bool state)
{
        if(state == true)
                PORTB |= (1<<pin);
        else
                PORTB &= ~(1<<pin);
}

uint8_t read_decay(void)
{
        ADCSRA |= (1 << ADSC);
        loop_until_bit_is_clear(ADCSRA, ADSC);
        return ADCH >> 1;
}
