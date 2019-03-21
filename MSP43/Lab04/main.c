#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/* BIT0 -> SW1 -> P2.0
 * BIT1 -> SW2 -> P2.1
 * BIT2 -> SW3 -> P2.2
 * BIT3 -> SW4 -> P2.3
 *
 * piezzo -> P2.4
 *
 * LED1 ->BIT4 (Y) -> P3.0
 * LED2 ->BIT5 (R) -> P3.1
 * LED3 ->BIT6 (B) -> P3.2
 * LED4 ->BIT7 (G) -> P3.3
 */

#define d4 310;  //26 Ticks
#define g3 209;  //38 Ticks
#define g4 415;  //20 Ticks
#define b3 252;  //32 Ticks
unsigned int counter;



unsigned int sequence[100];
unsigned int user_input[100];
time_t t;
void init_game_LED(void);
int randomInt();
/*
 * Store the sequence into an int array and use helper method
 * to generate and store order.
 */


void brightLED(int LEDPos)
{
    switch(LEDPos)
    {
    case 0:
        P3OUT ^= BIT0;
        TA1CCR0 = d4;
        TA1CCTL0 ^= OUTMOD_4;
        __delay_cycles(100000);
        P3OUT ^= BIT0;
        break;
    case 1:
        P3OUT ^= BIT1;
        TA1CCR0 = g3;
        TA1CCTL0 ^= OUTMOD_4;
        __delay_cycles(100000);
        P3OUT ^= BIT1;
    case 2:
        P3OUT ^= BIT2;
        TA1CCR0 = g4;
        TA1CCTL0 ^= OUTMOD_4;
        __delay_cycles(100000);
        P3OUT ^= BIT2;
    /*
     * Missing switch atm so commented out.
    case 3:
        P3OUT ^= BIT3;
        TA1CCR0 = b3;
        TA1CCTL0 ^= OUTMOD_4;
        __delay_cycles(100000);
        P3OUT ^= BIT3;
    */
    }
}
void init_game_LED(void)
{
    int loop = 2;
    while(loop!=0)
    {
        P3OUT ^= BIT0;
        __delay_cycles(100000);
        P3OUT ^= BIT0;
        __delay_cycles(100000);
        P3OUT ^= BIT1;
        __delay_cycles(100000);
        P3OUT ^= BIT1;
        __delay_cycles(100000);
        P3OUT ^= BIT2;
        __delay_cycles(100000);
        P3OUT ^= BIT2;
        __delay_cycles(100000);
        loop= loop- 1;
    }//
}

void msp_init()
{
    WDTCTL = WDTPW | WDTHOLD;     // Stop watchdog timer
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1DIR |= BIT0;
    //-------------------------------------
    P2DIR &= ~(BIT0+BIT1+BIT2);               // Set pin P2.0,1,2 to be an input
    P2REN |=  (BIT0+BIT1+BIT2);               // Enable internal pullup/pulldown resistor on P2.0
    P2OUT |=  (BIT0+BIT1+BIT2);               // Pullup selected on P2.0
    P2IES |=  (BIT0+BIT1+BIT2);               // Make P2.0 interrupt happen on the falling edge
    P2IFG &= ~(BIT0+BIT1+BIT2);               // Clear the P2.0 interrupt flag
    P2IE  |=  (BIT0+BIT1+BIT2);               // Enable P2.0 interrupt
    P3DIR |=  (BIT0+BIT1+BIT2);             // Set pin 3.0,1,2 to be an output
    //-------------------------------------


    //-------------------------------------
    //-------------------------------------
    PM5CTL0 &= ~LOCKLPM5;         // Unlock ports from power manager

    __enable_interrupt();         // Set global interrupt enable bit in SR register
    //-------------------------------------
    //-------------------------------------
    init_game_LED();
    while(1)
    {
        //add random sequence to arr
        sequence[counter] = randomInt();
        int i;
        for(i =0; i < counter; i++)
        {
            brightLED(sequence[i]);
        }
        __delay_cycles(500000);
    }
//main program
}



#pragma vector = PORT2_VECTOR
__interrupt void p2_ISR()
{
    switch (P2IV)
    {
        case P2IV_NONE: break;
        case P2IV_P2IFG0:
            P3OUT ^= BIT0;
            __delay_cycles(200000); //bounce & show luminosity in press
            P3OUT ^= BIT0;
            break;
        case P2IV_P2IFG1:
            P3OUT ^= BIT1;
            __delay_cycles(200000); //bounce & show luminosity in press
            P3OUT ^= BIT1;
            break;
        case P2IV_P2IFG2:
            P3OUT ^= BIT2;
            __delay_cycles(200000); //bounce & show luminosity in press
            P3OUT ^= BIT2;
            break;
        case P2IV_P2IFG3: break;
        case P2IV_P2IFG4: break;
        case P2IV_P2IFG5: break;
        case P2IV_P2IFG6: break;
        case P2IV_P2IFG7: break;
        default:   break;
    }
}
int randomInt()
{
    int num = rand() % 3;
    return num;
}
void main(void)
{
    srand(time(0));
    msp_init();
    while(1)
        __bis_SR_register(LPM3_bits);  // Enter low power mode


}
