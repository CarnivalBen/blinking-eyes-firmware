
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


#define MAX_BLINK 1000

typedef struct BlinkInfoData {
    byte portspec;
    word blinktime;
} BlinkInfo;

const BlinkInfo blinks[] = { 
    { 0b000001, 28},
    { 0b000001, 46},
    { 0b000001, 49},
    { 0b000001, 55},
    { 0b000001, 79},
    { 0b000001, 123},
    { 0b000001, 127},
    { 0b000001, 161},
    { 0b000001, 196},
    { 0b000001, 200},
    { 0b000001, 241},
    { 0b000001, 291},
    { 0b000001, 340},
    { 0b000001, 345},
    { 0b000001, 363},
    { 0b000001, 402},
    { 0b000001, 404},
    { 0b000001, 407},
    { 0b000001, 418},
    { 0b000001, 444},
    { 0b000001, 475},
    { 0b000001, 519},
    { 0b000001, 565},
    { 0b000001, 597},
    { 0b000001, 638},
    { 0b000001, 686},
    { 0b000001, 688},
    { 0b000001, 692},
    { 0b000001, 736},
    { 0b000001, 748},
    { 0b000001, 769},
    { 0b000001, 814},
    { 0b000001, 828},
    { 0b000001, 866},
    { 0b000001, 907},
    { 0b000001, 931},
    { 0b000001, 976},

    { 0b000010, 11},
    { 0b000010, 48},
    { 0b000010, 56},
    { 0b000010, 103},
    { 0b000010, 119},
    { 0b000010, 161},
    { 0b000010, 183},
    { 0b000010, 206},
    { 0b000010, 233},
    { 0b000010, 249},
    { 0b000010, 280},
    { 0b000010, 296},
    { 0b000010, 310},
    { 0b000010, 315},
    { 0b000010, 321},
    { 0b000010, 348},
    { 0b000010, 368},
    { 0b000010, 396},
    { 0b000010, 428},
    { 0b000010, 460},
    { 0b000010, 501},
    { 0b000010, 549},
    { 0b000010, 568},
    { 0b000010, 615},
    { 0b000010, 618},
    { 0b000010, 620},
    { 0b000010, 646},
    { 0b000010, 654},
    { 0b000010, 702},
    { 0b000010, 710},
    { 0b000010, 757},
    { 0b000010, 787},
    { 0b000010, 825},
    { 0b000010, 852},
    { 0b000010, 872},
    { 0b000010, 888},
    { 0b000010, 898},
    { 0b000010, 928},
    { 0b000010, 940},
    { 0b000010, 958},
    { 0b000010, 975},
    
    { 0b000100, 20},
    { 0b000100, 57},
    { 0b000100, 116},
    { 0b000100, 157},
    { 0b000100, 176},
    { 0b000100, 212},
    { 0b000100, 249},
    { 0b000100, 267},
    { 0b000100, 291},
    { 0b000100, 332},
    { 0b000100, 370},
    { 0b000100, 402},
    { 0b000100, 425},
    { 0b000100, 463},
    { 0b000100, 474},
    { 0b000100, 488},
    { 0b000100, 500},
    { 0b000100, 515},
    { 0b000100, 555},
    { 0b000100, 566},
    { 0b000100, 600},
    { 0b000100, 634},
    { 0b000100, 654},
    { 0b000100, 662},
    { 0b000100, 673},
    { 0b000100, 717},
    { 0b000100, 736},
    { 0b000100, 742},
    { 0b000100, 759},
    { 0b000100, 771},
    { 0b000100, 784},
    { 0b000100, 827},
    { 0b000100, 835},
    { 0b000100, 842},
    { 0b000100, 878},
    { 0b000100, 897},
    { 0b000100, 927},
    { 0b000100, 948},
    { 0b000100, 964},
    { 0b000100, 991},

    { 0b010000, 48},
    { 0b010000, 88},
    { 0b010000, 91},
    { 0b010000, 132},
    { 0b010000, 160},
    { 0b010000, 182},
    { 0b010000, 211},
    { 0b010000, 238},
    { 0b010000, 274},
    { 0b010000, 294},
    { 0b010000, 336},
    { 0b010000, 363},
    { 0b010000, 401},
    { 0b010000, 404},
    { 0b010000, 448},
    { 0b010000, 460},
    { 0b010000, 464},
    { 0b010000, 484},
    { 0b010000, 531},
    { 0b010000, 568},
    { 0b010000, 591},
    { 0b010000, 630},
    { 0b010000, 655},
    { 0b010000, 671},
    { 0b010000, 688},
    { 0b010000, 718},
    { 0b010000, 720},
    { 0b010000, 750},
    { 0b010000, 783},
    { 0b010000, 805},
    { 0b010000, 829},
    { 0b010000, 860},
    { 0b010000, 899},
    { 0b010000, 945},
    { 0b010000, 985},
    
    { 0b100000, 22},
    { 0b100000, 26},
    { 0b100000, 46},
    { 0b100000, 89},
    { 0b100000, 104},
    { 0b100000, 149},
    { 0b100000, 174},
    { 0b100000, 198},
    { 0b100000, 208},
    { 0b100000, 233},
    { 0b100000, 239},
    { 0b100000, 247},
    { 0b100000, 278},
    { 0b100000, 327},
    { 0b100000, 372},
    { 0b100000, 379},
    { 0b100000, 427},
    { 0b100000, 448},
    { 0b100000, 477},
    { 0b100000, 520},
    { 0b100000, 543},
    { 0b100000, 555},
    { 0b100000, 575},
    { 0b100000, 611},
    { 0b100000, 643},
    { 0b100000, 674},
    { 0b100000, 708},
    { 0b100000, 743},
    { 0b100000, 788},
    { 0b100000, 793},
    { 0b100000, 796},
    { 0b100000, 843},
    { 0b100000, 864},
    { 0b100000, 890},
    { 0b100000, 920},
    { 0b100000, 935},
    { 0b100000, 937},
    { 0b100000, 946},
    { 0b100000, 953}

};



int main(void) {

    CLRWDT();
    
    // Oscillator
    OSCCON = 0b01111010;
    
    // PORT SETUP
    INLVLA = 0;
    ANSELA = 0;
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
 
    GIE = 0;
    

    word blink = 0;
    LATA = 0b110111;
   
    while (1) {                        
        
        _delaywdt(1000000);    

        blink++;
        for (byte i = 0; i < sizeof(blinks) / sizeof(BlinkInfo); i++) {

            if (blinks[i].blinktime == blink) LATA = LATA & (~blinks[i].portspec);
            if (blinks[i].blinktime + 1 == blink) LATA = LATA | blinks[i].portspec;                    
            
        }            

        if (blink >= MAX_BLINK) blink = 0;
        
    }
}