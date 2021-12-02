#pragma once
#include <xc.h>



int sw2(int fan);

int sw1(int shiftL);

int sw0(int counter);

void sw4();

void sw6();

void setupLCD();

void printToLCD(char str[], int line);

void busy();

void sendLCDPulse();

void clearLCD();

void writeMode(char mode[], char name[], int index, int value);

void sw5(); //will print Mode 5: Halt on the screen.

void sw7(); //will print Mode 7: Exit on the screen.

void shiftLCD();

void shiftLeftLCD(char str[],int index);

void shiftRightLCD(char str[],int index);

void resetShifts(); // reset global variables for shiftLCD
