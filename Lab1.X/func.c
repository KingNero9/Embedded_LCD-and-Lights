#include "func.h"
#include <string.h>
#define SECOND_ROW 0x40
int boolean[3] = {0, 0, 0};
int lastSw4 = 0;
int lastSw6 = 0;
int shiftCounter = 0;
int shiftCounterStatus = 0; //0 right shift, 1 left shift

int sw2(int fan) {
    //LCD
    boolean[0] = 0;
    boolean[1] = 0;
    char mode[8] = {'M', 'o', 'd', 'e', ' ', '2', ':', '\0'};
    //LCD

    //switches
    if (PORTDbits.RD15) { //do reverse function (SW3)
        //LCD
        if (boolean[2] != 2 || lastSw4 != PORTDbits.RD14) {
            resetShifts();
            if (PORTDbits.RD14) {
                char name[16] = "Swing Down Fast";
                writeMode(mode, name, 2, 2);
            } else {
                char name[16] = "Swing Down Slow";
                writeMode(mode, name, 2, 2);
            }
            lastSw4 = PORTDbits.RD14;
        } else { // for shift left/ right
            if (PORTDbits.RD14) {
                char name[16] = "Swing Down Fast";
                shiftLCD(name);
            } else {
                char name[16] = "Swing Down Slow";
                shiftLCD(name);
            }
        }
        //LCD
        switch (fan) {
            case(0x18):
                PORTA = 0X81;
                return 0x81;
            case(0x24):
                PORTA = 0X18;
                return 0x18;
            case(0x42):
                PORTA = 0X24;
                return 0x24;
            case(0x81):
                PORTA = 0X42;
                return 0x42;
        }
    } else {
        //LCD
        if (boolean[2] != 1 || lastSw4 != PORTDbits.RD14) {
            resetShifts();
            if (PORTDbits.RD14) {
                char name[14] = "Swing Up Fast";
                writeMode(mode, name, 2, 1);
            } else {
                char name[14] = "Swing Up Slow";
                writeMode(mode, name, 2, 1);
            }
            lastSw4 = PORTDbits.RD14;
        } else { // for shift left/ right
            if (PORTDbits.RD14) {
                char name[14] = "Swing Up Fast";
                shiftLCD(name);
            } else {
                char name[14] = "Swing Up Slow";
                shiftLCD(name);
            }
        }
        //LCD
        switch (fan) {
            case(0x18):
                PORTA = 0X24;
                return 0x24;
            case(0x24):
                PORTA = 0X42;
                return 0x42;
            case(0x42):
                PORTA = 0X81;
                return 0x81;
            case(0x81):
                PORTA = 0X18;
                return 0x18;
        }
    }
    //switches

}

int sw1(int shiftL) {
    //LCD
    boolean[0] = 0; //disable boolean for sw0
    boolean[2] = 0;
    char mode[8] = {'M', 'o', 'd', 'e', ' ', '1', ':', '\0'};
    //LCD

    //switch
    if (PORTDbits.RD15) { //do reverse function (SW3)
        //LCD
        if (boolean[1] != 2 || lastSw4 != PORTDbits.RD14) {
            resetShifts();
            if (PORTDbits.RD14) {
                char name[17] = "Shift Right Fast";
                writeMode(mode, name, 1, 2);

            } else {
                char name[17] = "Shift Right Slow";
                writeMode(mode, name, 1, 2);
            }
            lastSw4 = PORTDbits.RD14;
        } else { // for shift left/ right
            if (PORTDbits.RD14) {
                char name[17] = "Shift Right Fast";
                shiftLCD(name);

            } else {
                char name[17] = "Shift Right Slow";
                shiftLCD(name);
            }
        }
        //LCD
        shiftL = shiftL / 2;
        if (shiftL < 1) {
            shiftL = 128;
        }
    } else { // do normal function
        //LCD
        if (boolean[1] != 1 || lastSw4 != PORTDbits.RD14) {
            resetShifts();
            if (PORTDbits.RD14) {
                char name[16] = "Shift Left Fast";
                writeMode(mode, name, 1, 1);

            } else {
                char name[16] = "Shift Left Slow";
                writeMode(mode, name, 1, 1);
            }
            lastSw4 = PORTDbits.RD14;
        } else { // for ShiftLCD
            if (PORTDbits.RD14) {
                char name[16] = "Shift Left Fast";
                shiftLCD(name);

            } else {
                char name[16] = "Shift Left Slow";
                shiftLCD(name);
            }
        }
        //LCD
        if (shiftL == 0) //first runtime
            shiftL = 1;
        else {
            shiftL = shiftL * 2;
            if (shiftL > 128)
                shiftL = 1;
        }
    }
    PORTA = shiftL; //shiftL is being used as ShifttR currently 
    return shiftL;
    //switch
}

int sw0(int counter) {
    //LCD
    boolean[1] = 0; //disable boolean for sw0
    boolean[2] = 0;
    char mode[8] = {'M', 'o', 'd', 'e', ' ', '0', ':', '\0'};
    //LCD

    //switch
    if (PORTDbits.RD15) { //do reverse function (SW3)
        //LCD
        if (boolean[0] != 2 || lastSw4 != PORTDbits.RD14) {
            resetShifts();
            if (PORTDbits.RD14) {
                char name[17] = "Counter Down Fast";
                writeMode(mode, name, 0, 2);
            } else {
                char name[17] = "Counter Down Slow";
                writeMode(mode, name, 0, 2);
            }
            lastSw4 = PORTDbits.RD14;
        } else { // for ShiftLCD
            if (PORTDbits.RD14) {
                char name[17] = "Counter Down Fast";
                shiftLCD(name);
            } else {
                char name[17] = "Counter Down Slow";
                shiftLCD(name);
            }
        }
        //LCD
        counter--;
    } else {
        //LCD
        if (boolean[0] != 1 || lastSw4 != PORTDbits.RD14) {
            resetShifts();
            if (PORTDbits.RD14) {
                char name[16] = "Counter Up Fast";
                writeMode(mode, name, 0, 1);
            } else {
                char name[16] = "Counter Up Slow";
                writeMode(mode, name, 0, 1);
            }
            lastSw4 = PORTDbits.RD14;
        } else { // for ShiftLCD
            if (PORTDbits.RD14) {
                char name[16] = "Counter Up Fast";
                shiftLCD(name);
            } else {
                char name[16] = "Counter Up Slow";
                shiftLCD(name);
            }
        }
        //LCD
        counter++;
    }
    PORTA = counter;
    return counter;
    //switch
}

void sw4() { // decide Loop speed
    int j, temp = 120000;
    if (PORTDbits.RD14 != lastSw4) {
        lastSw4 = PORTDbits.RD14;
    }

    if (PORTDbits.RD14) { //SW4 ON?
        temp = 0;
    }
    if (PORTBbits.RB10) { // SW 6 ON? (buzzer)
        for (j = 0; j <= 150000 + temp; j++) {
            if (j % 440 == 0)
                sw6();
        }
        // buzzer LCD and ShiftLCD
        char name[10] = "Beep Mode";
        if (lastSw6 != PORTBbits.RB10) { 
            resetShifts();
            char mode[8] = {'M', 'o', 'd', 'e', ' ', '6', ':', '\0'};
            clearLCD();
            printToLCD(mode, 0); //0 for first line
            printToLCD(name, 1); //0 for first line
            lastSw6 = PORTBbits.RB10;
        } else {
            shiftLCD(name);
        }
        // buzzer LCD and ShiftLCD
    } else {
        lastSw6 = PORTBbits.RB10; // PORTBbits.RB10 == 0 
        for (j = 0; j <= 150000 + temp; j++);
    }

}

void sw5() {
    char mode[8] = {'M', 'o', 'd', 'e', ' ', '5', ':', '\0'};
    char name[5] = "Halt";
    clearLCD();
    printToLCD(mode, 0); //0 for first line
    printToLCD(name, 1); //1 for second line
    resetShifts();

}

void sw6() { //sound
    LATBbits.LATB14 ^= 1; //XOR 
}

void sw7() {
    char mode[8] = {'M', 'o', 'd', 'e', ' ', '7', ':', '\0'};
    char name[5] = "Exit";
    clearLCD();
    printToLCD(mode, 0); //0 for first line
    printToLCD(name, 1); //0 for first line
    while (1) {
        shiftLCD(name);
    }
}

void setupLCD() {
    TRISBbits.TRISB15 = 0; // RB15 (DISP_RS) set as an output
    ANSELBbits.ANSB15 = 0; // disable analog functionality on RB15 (DISP_RS)
    TRISDbits.TRISD5 = 0; // RD5 (DISP_RW) set as an output
    TRISDbits.TRISD4 = 0; // RD4 (DISP_EN) set as an output  
    TRISE &= 0xff00;
    ANSELEbits.ANSE2 = 0; //Disable Analog
    ANSELEbits.ANSE4 = 0; //Disable Analog
    ANSELEbits.ANSE5 = 0; //Disable Analog
    ANSELEbits.ANSE6 = 0; //Disable Analog
    PORTBbits.RB15 = 0; //rs=0
    PORTDbits.RD5 = 0; //w=0
    ANSELEbits.ANSE7 = 0;
    // second line 0xc0
    // first line 0x80 - 0x8f
    //char control[] = {0b00111000, 0b00111000, 0b00111000, 0b00001110, 0b00000110, 0b00000001};
    char control[] = {0x38, 0x38, 0x38, 0xe, 0x6, 0x1};

    // Prepare control functions and send them to the LCD controller and waits for it to finish
    for (int i = 0; i < sizeof (control); i++) {
        PORTE = control[i];
        sendLCDPulse();
    }
}

void printToLCD(char str[], int line) {
    PORTBbits.RB15 = 0; // transferring instruction in order to write further commands later on
    if (line == 0) { //0x80 - first line, 0xc0 - second line
        PORTE = 0x80;
    } else {
        PORTE = 0xc0;
    }
    sendLCDPulse(); // Pulse - Whenever transferring a new command we pulse (=refresh)
    PORTBbits.RB15 = 1; // RS = 1 transferring data - what we want the LCD to display
    PORTDbits.RD5 = 0; // Write 
    for (int i = 0; i < strlen(str); i++) {
        PORTE = str[i];
        sendLCDPulse();
    }
}

void busy() {
    int j;
    for (j = 0; j <= 16000; j++) {
    }
}

void clearLCD() {
    PORTBbits.RB15 = 0; //DISP_RS -> Low for instruction Transfer
    PORTDbits.RD5 = 0; //DISP_RW -> Low for write mode
    PORTE = 0b1; // 10110001(2), 177(10)
    sendLCDPulse();
}

void sendLCDPulse() {
    PORTDbits.RD4 = 1; // Pulse
    PORTDbits.RD4 = 0;
    busy();
}

void writeMode(char mode[], char name[], int index, int value) { // index->boolean array index, value -> 1 normal/ 2 reverse
    //LCD
    clearLCD();
    printToLCD(mode, 0); //0 for first line
    printToLCD(name, 1); //0 for first line
    boolean[index] = value;
    //LCD
}

void shiftLCD(char name[]) {
    if (shiftCounter + strlen(name) >= 0x10) {
        shiftCounterStatus = 1;
    }
    if (shiftCounterStatus) {
        shiftLeftLCD(name, shiftCounter);
        if (shiftCounter)
            shiftCounter--;
        else
            shiftCounterStatus = 0;
    } else {
        shiftRightLCD(name, shiftCounter);
        shiftCounter++;
    }
}

void shiftRightLCD(char str[], int index) {
    PORTBbits.RB15 = 0; // transferring instruction in order to write further commands later on
    PORTE = 0xc0 + index; //first char of the last word
    sendLCDPulse(); // Pulse - Whenever transferring a new command we pulse (=refresh)

    PORTBbits.RB15 = 1; // RS = 1 transferring data - what we want the LCD to display
    PORTDbits.RD5 = 0; // Write 
    for (int j = 0; j <= strlen(str); j++) {
        PORTE = ' ';
        sendLCDPulse();
    }

    PORTBbits.RB15 = 0; // transferring instruction in order to write further commands later on
    PORTE = 0xc0 + index + 1; //first char of the last word
    sendLCDPulse(); // Pulse - Whenever transferring a new command we pulse (=refresh)
    PORTBbits.RB15 = 1; // RS = 1 transferring data - what we want the LCD to display
    for (int i = 0; i < strlen(str); i++) { //write the word at index +1
        PORTE = str[i];
        sendLCDPulse();
    }
}

void shiftLeftLCD(char str[], int index) {
    PORTBbits.RB15 = 0; // transferring instruction in order to write further commands later on
    PORTE = 0xc0 + index; //first char of the last word
    sendLCDPulse(); // Pulse - Whenever transferring a new command we pulse (=refresh)

    PORTBbits.RB15 = 1; // RS = 1 transferring data - what we want the LCD to display
    PORTDbits.RD5 = 0; // Write 
    for (int j = 0; j <= strlen(str); j++) { //clear the last word
        PORTE = ' ';
        sendLCDPulse();
    }

    PORTBbits.RB15 = 0;
    PORTE = 0xc0 + index;
    sendLCDPulse();
    PORTBbits.RB15 = 1;

    for (int i = 0; i < strlen(str); i++) { // write the word at index
        PORTE = str[i];
        sendLCDPulse();
    }
}

void resetShifts() {
    shiftCounter = 0;
    shiftCounter = 0;
}
