
// CONFIG1
#pragma config FOSC = INTOSC    //  (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"


#define CORE_COUNT 0x100
#define MAX_BLINK 1000

typedef struct BlinkInfoData {
    byte portspec;
    word blinktime;
} BlinkInfo;

const BlinkInfo blinks[] = { 
    {1, 2},
    {3, 4},
    {5, 6} 
};



int main(void) {

    CLRWDT();
    
    // Oscillator
    OSCCON = 0b01111010;
    
    // PORT SETUP
    INLVLA = 0;
    ANSELA = 0;
    //TRISA0 = 0; // STATUS OUT
    //TRISA1 = 0; // LATCH
    //TRISA2 = 1; // SPEED POTENTIOMETER IN
    //TRISA4 = 0; // DATA OUT
    //TRISA5 = 0; // DATA CLK OUT
    TRISA = 0b00000000;
    ODA1 = 0;
    SLRA1 = 0;
    WPUA = 0;
    LATA0 = 0;
    ANSELA = 0b00000000;
    ADCON0 = 0b00000000;
    ADCON1 = 0b01100000;
    ADCON2 = 0b00000000;  
    FVRCON = 0b00110000;
    
    // TIMER0 SETUP    
    OPTION_REG = 0b11011000;
    TMR0 = 0;   

    
    // INTERRUPT SETUP
//    IOCAP = 0b00000000;
//    IOCAN = 0b00001000;
//    IOCAF = 0b00001000;
//    IOCIE = 1;
//    TMR0IE = 0;
  
    GIE = 1;
    
    
    word count = CORE_COUNT;
    word blink = 0;
    
    LATA0 = 1;
    LATA1 = 1;
    LATA2 = 1;
    LATA4 = 1;
    LATA5 = 1;
    
    while (1) {                        
        
        _delaywdt(1000000);    
        count--;
        if (count == 0) {
            count = CORE_COUNT;
            blink++;            
            
            for (byte i = 0; i < sizeof(blinks) / sizeof(BlinkInfo); i++) {
                
                if (blinks[i].blinktime == blink) {                    
                    LATA = LATA & (~blinks[i].portspec);                    
                }
                
                if (blinks[i].blinktime + 1 == blink) {                    
                    LATA = LATA | blinks[i].portspec;                    
                }
                
            }            
            
            if (blink >= MAX_BLINK) {
                blink = 0;
            }
            
        }   
               

    }
}

void __interrupt() isr() {
    
  
               
}


