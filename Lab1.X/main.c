#include <xc.h>
#include "func.h"
#include <stdio.h>

#pragma config JTAGEN = OFF
#pragma config FWDTEN = OFF
#pragma config FNOSC = FRCPLL
#pragma config FSOSCEN = OFF
#pragma config POSCMOD = EC
#pragma config OSCIOFNC = ON
#pragma config FPBDIV = DIV_1
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1

int lastSw5 = 0;

void main() {
    int counter = 0, shiftL = 0, fan = 0x18;
    TRISA &= 0xff00;
    TRISFbits.TRISF3 = 1; // RF3 (SW0) configured as input
    TRISFbits.TRISF5 = 1; // RF5 (SW1) configured as input
    TRISFbits.TRISF4 = 1; // RF4 (SW2) configured as input
    TRISDbits.TRISD15 = 1; // RD15 (SW3) configured as input
    TRISDbits.TRISD14 = 1; // RD14 (SW4) configured as input
    TRISBbits.TRISB11 = 1; // RB11 (SW5) configured as input
    ANSELBbits.ANSB11 = 0; // RB11 (SW5) disabled analog
    TRISBbits.TRISB10 = 1; // RB10 (SW6) configured as input
    ANSELBbits.ANSB10 = 0; // RB10 (SW6) disabled analog
    TRISBbits.TRISB9 = 1; // RB9 (SW7) configured as input
    ANSELBbits.ANSB9 = 0; // RB9 (SW7) disabled analog
    TRISBbits.TRISB14 = 0; //buzzer configured as output
    ANSELBbits.ANSB14 = 0; //buzzer disabled analog
    PORTBbits.RB14 = 0;

    setupLCD();
    while (1) {
        if (PORTBbits.RB9) {//SW7 ON?
            sw7();
            break;
        }
        if (!PORTBbits.RB11) { // if SW5 is off  
            lastSw5 = PORTBbits.RB11;
            if (PORTFbits.RF4) {// RF4 (SW2) configured as input 
                fan = sw2(fan);
            } else if (PORTFbits.RF5) {// RF5 (SW1) configured as input
                shiftL = sw1(shiftL);
            } else if (PORTFbits.RF3) // RF3 (SW0) configured as input 
                counter = sw0(counter);
        } else if (lastSw5 != PORTBbits.RB11 && !PORTBbits.RB10) {//sw5 is on and beep is off
            sw5();
            lastSw5 = PORTBbits.RB11;     
        }
        else{
            char name[5] = "Halt";
            shiftLCD(name);
        }
        sw4();
    }

}

//PORTAbits.RA0=PORTFbits.RF3 ; // RF3 (SW0) configured as input
//PORTAbits.RA1=PORTFbits.RF5 ; // RF5 (SW1) configured as input
//PORTAbits.RA2=PORTFbits.RF4; // RF4 (SW2) configured as input
//PORTAbits.RA3=PORTDbits.RD15 ; // RD15 (SW3) configured as input
//PORTAbits.RA4=PORTDbits.RD14; // RD14 (SW4) configured as input
//PORTAbits.RA5=PORTBbits.RB11 ; // RB11 (SW5) configured as input
//PORTAbits.RA6=PORTBbits.RB10 ; // RB10 (SW6) configured as input
//PORTAbits.RA7=PORTBbits.RB9 ; // RB9 (SW7) configured as input

