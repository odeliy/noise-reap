#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include "setup.h"
#include "defs.h"

void pin_setup(void)
{
        DDRB |=  (1 << pwm_pin);
        DDRB |=  (1 << pulse_pin);
        DDRB &= ~(1 << trig_pin);
        DDRB &= ~(1 << decay_pin);
        DDRB |=  (1 << noise_pin);
}

void timer0_pwm_setup(void)
{
        TCCR0A |= (1 << COM0A1);
        TCCR0A |= (1 << WGM00);
        TCCR0A |= (1 << WGM01);
        TCCR0B |= (1 << CS00);
}

void adc_setup(void)
{
        ADMUX  |= (1 << MUX0);
        ADMUX  |= (1 << MUX1);
        ADMUX  |= (1 << ADLAR);
        ADCSRA |= (1 << ADPS0);
        ADCSRA |= (1 << ADPS1);
        ADCSRA |= (1 << ADEN);
}

void interrupt_setup(void)
{
        MCUCR |= (1 << ISC01);
        GIMSK |= (1 << INT0);
}

void setup(void)
{
        cli();
        clock_prescale_set(clock_div_1);
        pin_setup();
        timer0_pwm_setup();
        adc_setup();
        interrupt_setup();
        sei();
}
