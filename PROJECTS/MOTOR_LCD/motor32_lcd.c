#include <avr/io.h>
#include <util/delay.h>

void command(int cmd);
void data(char data);
void forward();
void reverse();
void stop();
void display(const char *p);

void command(int cmd) {
    PORTA = 0x02;      // RS = 0, E = 1 (for command mode)
    PORTC = cmd;
    _delay_ms(2);
    PORTA = 0x00;      // E = 0 to latch command
    _delay_ms(2);
}

void data(char data) {
    PORTA = 0x03;      // RS = 1, E = 1 (for data mode)
    PORTC = data;
    _delay_ms(2);
    PORTA = 0x01;      // E = 0 to latch data
    _delay_ms(2);
}

void forward(){
    PORTD = 0x1D;
}

void reverse(){
    PORTD = 0x2E;
}

void stop(){
    PORTD = 0x00;
}

void display(const char *p){
    while(*p != 0) {
        data(*p);
        p++;
    }
}

void main(void) {
    DDRD = 0xFF;       // Motor control pins as output
    DDRB = 0x00;       // Input for switches
    DDRC = 0xFF;       // Data bus for LCD as output
    DDRA = 0xFF;       // Control pins for LCD as output

    _delay_ms(20);

    // Initialize LCD
    command(0x38);     // 8-bit mode, 2 lines, 5x7 format
    command(0x0E);     // Display ON, Cursor ON
    command(0x06);     // Increment cursor
    command(0x01);     // Clear display

    while (1) {
        if ((PINB & 0x01) == 0) {       // Forward
            forward();
            command(0x80);              // Move cursor to the beginning of the first line
            display("FORWARD");
            _delay_ms(200);
            stop();
            command(0x01);              // Clear display
        } 
        else if ((PINB & 0x02) == 0) {  // Reverse
            reverse();
            command(0x80);              // Move cursor to the beginning of the first line
            display("REVERSE");
            _delay_ms(200);
            stop();
            command(0x01);              // Clear display
        } else {
            stop();
        }
    }
}
