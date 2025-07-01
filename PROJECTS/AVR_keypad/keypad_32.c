#include <avr/io.h>
#include <util/delay.h>

void command(char a);
void data(char a);


int main()
{ 
DDRC=0XFF;
DDRB=0X0F;
DDRD=0XFF;
command(0X38);
command(0X80);
command(0X01);
command(0X06);
command(0X0F);
    
while(1)
{
PORTB=0X0E;//FIRST ROW
if((PINB&0x10)==0)
{
data('1');
while((PINB&0x10)==0);
}
if((PINB&0x20)==0)
{
data('2');
while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
data('3');
while((PINB&0x40)==0);
}
if((PINB&0x80)==0)
{
data('+');
while((PINB&0x80)==0);
}
PORTB=0X0D;//SECOND ROW
if((PINB&0x10)==0)
{
data('4');
while((PINB&0x10)==0);
}
if((PINB&0X20)==0)
{
data('5');
while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
data('6');
while((PINB&0X40)==0);
}
if((PINB&0x80)==0)
{
data('-');
while((PINB&0x80)==0);
}
PORTB=0X0B;//THIRD ROW
if((PINB&0x10)==0)
{
data('7');
while((PINB&0x10)==0);
}
if((PINB&0x20)==0)
{
data('8');
while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
data('9');
while((PINB&0x40)==0);
}
if((PINB&0x80)==0)
{
data('*');
while((PINB&0x80)==0);
}
PORTB=0X07;//FOURTH ROW
if((PINB&0x10)==0)
{
command(0X01);
}
if((PINB&0x20)==0)
{
data('0');
while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
data('=');
while((PINB&0x40)==0);
}
if((PINB&0x80)==0)
{
data('/');
while((PINB&0x80)==0);
}
}



}
void command (char a)
{
PORTC=0x02;
PORTD=a;
_delay_ms(100);
PORTC=0x00;
}
void data(char a)
{
PORTC=0x03;
PORTD=a;
_delay_ms(100);
PORTC=0x01;
}



