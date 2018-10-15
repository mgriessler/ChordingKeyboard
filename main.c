#include <string.h>

#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                  // USB-specific functions
#include "USB_API/USB_HID_API/UsbHid.h"

#include "USB_app/keyboard.h"
/*
 * NOTE: Modify hal.h to select a specific evaluation board and customize for
 * your own board.
 */
#include "hal.h"



/*********** Application specific globals **********************/
volatile uint8_t buttonfarstate = TRUE;
volatile uint8_t buttoncenterstate = TRUE;
volatile uint8_t buttonnearstate = TRUE;
volatile uint8_t buttonindexstate = TRUE;
volatile uint8_t buttonmiddlestate = TRUE;
volatile uint8_t buttonringstate = TRUE;
volatile uint8_t buttonpinkystate = TRUE;
volatile uint8_t lastbuttonfarstate = TRUE;
volatile uint8_t lastbuttoncenterstate = TRUE;
volatile uint8_t lastbuttonnearstate = TRUE;
volatile uint8_t lastbuttonindexstate = TRUE;
volatile uint8_t lastbuttonmiddlestate = TRUE;
volatile uint8_t lastbuttonringstate = TRUE;
volatile uint8_t lastbuttonpinkystate = TRUE;
volatile uint16_t buttonMatrix = 0;
volatile uint8_t sendPress = 0;
volatile uint8_t keySendComplete = TRUE;
volatile uint8_t BUTTON_DOWN = 0;
volatile uint8_t BUTTON_UP = 1;
volatile uint8_t BUTTON1_POS = 0;
volatile uint8_t BUTTON2_POS = 1;
volatile uint8_t BUTTON_FAR_POS = 6;
volatile uint8_t BUTTON_CENTER_POS = 5;
volatile uint8_t BUTTON_NEAR_POS = 4;
volatile uint8_t BUTTON_INDEX_POS = 3;
volatile uint8_t BUTTON_MIDDLE_POS = 2;
volatile uint8_t BUTTON_RING_POS = 1;
volatile uint8_t BUTTON_PINKY_POS = 0;
volatile uint8_t shiftfix = 0;
volatile uint8_t numfix = 0;
volatile uint8_t numlock = 0;


#define SHIFTFIX_ON     1
#define SHIFTFIX_OFF    0
#define NUMFIX_ON       1
#define NUMFIX_OFF      0
#define NUMLOCK_ON      1
#define NUMLOCK_OFF     0
#define KEY__   0
#define KEY_A   'a'
#define KEY_B   'b'
#define KEY_C   'c'
#define KEY_D   'd'
#define KEY_E   'e'
#define KEY_F   'f'
#define KEY_G   'g'
#define KEY_H   'h'
#define KEY_I   'i'
#define KEY_J   'j'
#define KEY_K   'k'
#define KEY_L   'l'
#define KEY_M   'm'
#define KEY_N   'n'
#define KEY_O   'o'
#define KEY_P   'p'
#define KEY_Q   'q'
#define KEY_R   'r'
#define KEY_S   's'
#define KEY_T   't'
#define KEY_U   'u'
#define KEY_V   'v'
#define KEY_W   'w'
#define KEY_X   'x'
#define KEY_Y   'y'
#define KEY_Z   'z'
#define KEY_0   '0'
#define KEY_1   '1'
#define KEY_2   '2'
#define KEY_3   '3'
#define KEY_4   '4'
#define KEY_5   '5'
#define KEY_6   '6'
#define KEY_7   '7'
#define KEY_8   '8'
#define KEY_9   '9'
#define KEY_SPACE   ' '
#define KEY_LSBRKT   '['
#define KEY_RSBRKT   ']'
#define KEY_MINUS   '-'
#define KEY_BSLASH  '\\'
#define KEY_FSLASH  '/'
#define KEY_EQUAL   '='
#define KEY_TICK    '`'
#define KEY_DOLLAR  '$'
#define KEY_PERCENT '%'
#define KEY_QUEST   '?'
#define KEY_STAR    '*'
#define KEY_PLUS    '+'
#define KEY_CAPSLOCK    KEY_CAPS_LOCK
#define KEY_ENTER       KEY_RETURN
#define KEY_PG_DWN      KEY_PAGE_DOWN
#define KEY_PG_UP       KEY_PAGE_UP
#define MACRO_000   0xE0
#define MACRO_00    0xE1
#define MACRO_PARENS    0xE2
#define MACRO_QUOTES    0xE3


const uint16_t chordalpha[128] =
{
    KEY__,      //0 this can't happen
    KEY_W,      //1     --- ---P
    KEY_Y,      //2     --- --R-
    KEY_U,      //3     --- --RP
    KEY_R,      //4     --- -M--
    KEY__,      //5
    KEY_H,      //6     --- -MR-
    KEY_S,      //7     --- -MRP
    KEY_I,      //8     --- I---
    KEY_B,      //9     --- I--P
    KEY_K,      //10    --- I-R-
    KEY_Z,      //11    --- I-RP
    KEY_D,      //12    --- IM--
    KEY__,      //13
    KEY_E,      //14    --- IMR-
    KEY_T,      //15    --- IMRP
    KEY__,      //16
    KEY__,      //17
    KEY__,      //18
    KEY__,      //19
    KEY__,      //20
    KEY__,      //21
    KEY__,      //22
    KEY__,          //23
    KEY__,          //24
    KEY__,          //25
    KEY__,          //26
    KEY__,          //27
    KEY__,          //28
    KEY__,          //29
    KEY__,          //30
    KEY__,          //31
    KEY_SPACE,      //32    -C- ----
    KEY_F,          //33    -C- ---P
    KEY_G,          //34    -C- --R-
    KEY_V,      //35    -C- --RP
    KEY_C,      //36    -C- -M--
    KEY_RSBRKT,      //37   -C- -M-P
    KEY_P,      //38    -C- -MR-
    KEY_N,      //39    -C- -MRP
    KEY_L,      //40    -C- I---
    KEY__,      //41
    KEY_J,      //42    -C- I-R-
    KEY_Q,      //43    -C- I-RP
    KEY_M,      //44    -C- IM--
    KEY_LSBRKT,      //45   -C- IM-P
    KEY_A,      //46    -C- IMR-
    KEY_O,          //47    -C- IMRP
    KEY__,      //48
    KEY__,      //49
    KEY__,      //50
    KEY__,      //51
    KEY__,      //52
    KEY__,      //53
    KEY__,      //54
    KEY__,      //55
    KEY__,      //56
    KEY__,      //57
    KEY__,      //58
    KEY__,      //59
    KEY__,      //60
    KEY__,      //61
    KEY__,      //62
    KEY__,      //63
    KEY__,      //64
    KEY_ENTER,      //65
    KEY_RIGHT_ARROW,      //66
    KEY_DOWN_ARROW,      //67
    KEY_BACKSPACE,      //68
    KEY__,      //69
    KEY_DELETE,      //70
    KEY_PG_DWN,      //71
    KEY_LEFT_ARROW,      //72
    KEY_END,      //73
    KEY_TAB,      //74
    KEY_HOME,      //75
    KEY_UP_ARROW,      //76
    KEY__,      //77
    KEY_PG_UP,      //78
    KEY_CAPSLOCK,   //79    F-- IMRP
    KEY__,      //80
    KEY__,      //81
    KEY__,      //82
    KEY__,      //83
    KEY__,      //84
    KEY__,      //85
    KEY__,      //86
    KEY__,      //87
    KEY__,      //88
    KEY__,      //89
    KEY__,      //90
    KEY__,      //91
    KEY__,      //92
    KEY__,      //93
    KEY__,      //94
    KEY__,      //95
    KEY__,      //96
    KEY__,      //97
    KEY__,      //98
    KEY__,      //99
    KEY__,      //100
    KEY__,      //101
    KEY__,      //102
    KEY__,      //103
    KEY__,      //104
    KEY__,      //105
    KEY__,      //106
    KEY__,      //107
    KEY__,      //108
    KEY__,      //109
    KEY__,      //110
    KEY__,      //111
    KEY__,      //112
    KEY__,      //113
    KEY__,      //114
    KEY__,      //115
    KEY__,      //116
    KEY__,      //117
    KEY__,      //118
    KEY__,      //119
    KEY__,      //120
    KEY__,      //121
    KEY__,      //122
    KEY__,      //123
    KEY__,      //124
    KEY__,      //125
    KEY__,      //126
    KEY__       //127
};

const uint16_t chordnum[128] =
{
    KEY__,      //0 this can't happen
    KEY_5,      //1     --- ---P
    KEY_4,      //2     --- --R-
    MACRO_QUOTES,      //3  --- --RP
    KEY_3,      //4     --- -M--
    KEY__,      //5
    MACRO_00,      //6  --- -MR-
    KEY_MINUS,      //7 --- -MRP
    KEY_2,      //8     --- I---
    KEY_BSLASH,      //9    --- I--P
    KEY_DOLLAR,      //10   --- I-R-
    KEY_TICK,      //11     --- I-RP
    KEY_FSLASH,      //12   --- IM--
    KEY__,      //13
    KEY_EQUAL,      //14    --- IMR-
    MACRO_000,      //15    --- IMPR
    KEY__,      //16
    KEY__,      //17
    KEY__,      //18
    KEY__,      //19
    KEY__,      //20
    KEY__,      //21
    KEY__,      //22
    KEY__,          //23
    KEY__,          //24
    KEY__,          //25
    KEY__,          //26
    KEY__,          //27
    KEY__,          //28
    KEY__,          //29
    KEY__,          //30
    KEY__,          //31
    KEY_1,      //32    -C- ----
    KEY_9,          //33    -C- ---P
    KEY_8,          //34    -C- --R-
    KEY_RSBRKT,      //35   -C- --RP
    KEY_7,      //36    -C- -M--
    KEY_RSBRKT,      //37   -C- -M-P
    KEY_PERCENT,      //38 -C-  -MR-
    KEY_LSBRKT,      //39 -C-   -MRP
    KEY_6,      //40    -C- I---
    KEY__,      //41
    MACRO_PARENS,      //42 -C- I-R-
    KEY_QUEST,      //43    -C- I-RP
    KEY_STAR,      //44 -C- IM--
    KEY_LSBRKT,      //45   -C- IM-P
    KEY_PLUS,      //46 -C- IMR-
    KEY_0,          //47    -C- IMRP
    KEY__,      //48
    KEY__,      //49
    KEY__,      //50
    KEY__,      //51
    KEY__,      //52
    KEY__,      //53
    KEY__,      //54
    KEY__,      //55
    KEY__,      //56
    KEY__,      //57
    KEY__,      //58
    KEY__,      //59
    KEY__,      //60
    KEY__,      //61
    KEY__,      //62
    KEY__,      //63
    KEY__,      //64
    KEY__,      //65
    KEY__,      //66
    KEY__,      //67
    KEY__,      //68
    KEY__,      //69
    KEY__,      //70
    KEY__,      //71
    KEY__,      //72
    KEY__,      //73
    KEY__,      //74
    KEY__,      //75
    KEY__,      //76
    KEY__,      //77
    KEY__,      //78
    KEY__,   //79    F-- IMRP
    KEY__,      //80
    KEY__,      //81
    KEY__,      //82
    KEY__,      //83
    KEY__,      //84
    KEY__,      //85
    KEY__,      //86
    KEY__,      //87
    KEY__,      //88
    KEY__,      //89
    KEY__,      //90
    KEY__,      //91
    KEY__,      //92
    KEY__,      //93
    KEY__,      //94
    KEY__,      //95
    KEY__,      //96
    KEY__,      //97
    KEY__,      //98
    KEY__,      //99
    KEY__,      //100
    KEY__,      //101
    KEY__,      //102
    KEY__,      //103
    KEY__,      //104
    KEY__,      //105
    KEY__,      //106
    KEY__,      //107
    KEY__,      //108
    KEY__,      //109
    KEY__,      //110
    KEY__,      //111
    KEY__,      //112
    KEY__,      //113
    KEY__,      //114
    KEY__,      //115
    KEY__,      //116
    KEY__,      //117
    KEY__,      //118
    KEY__,      //119
    KEY__,      //120
    KEY__,      //121
    KEY__,      //122
    KEY__,      //123
    KEY__,      //124
    KEY__,      //125
    KEY__,      //126
    KEY__       //127
};

// PROTOTYPES
void sendChord(uint8_t key);
void sendMacro(uint16_t macro);

/*
 * ======== main ========
 */
void main (void){
     WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    PMM_setVCore(PMM_CORE_LEVEL_2);
    USBHAL_initPorts();           // Config GPIOS for low-power (output low)
    USBHAL_initClocks(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    USBHAL_initButtons();         // Init the two buttons
    Keyboard_init();       // Init keyboard report
    USB_setup(TRUE, TRUE); // Init USB & events; if a host is present, connect

    //set up key check timer
    //Start timer in continuous mode sourced by ACLK
    Timer_A_clearTimerInterrupt(TIMER_A1_BASE);

    Timer_A_initUpModeParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
    param.timerClear = TIMER_A_DO_CLEAR;
    param.timerPeriod = 1638;
    param.startTimer = true;
    Timer_A_initUpMode(TIMER_A1_BASE, &param);

    __enable_interrupt();  // Enable global interrupts

    while (1)
    {

        switch(USB_getConnectionState())
        {
            // This case is executed while your device is enumerated on the
            // USB host
            case ST_ENUM_ACTIVE:

                // Enter LPM0 w/interrupt, until a keypress occurs
                //__bis_SR_register(LPM0_bits + GIE);
                buttonfarstate = GPIO_getInputPinValue(BUTTON_FAR_PORT, BUTTON_FAR_PIN);
                buttoncenterstate = GPIO_getInputPinValue(BUTTON_CENTER_PORT, BUTTON_CENTER_PIN);
                buttonnearstate = GPIO_getInputPinValue(BUTTON_NEAR_PORT, BUTTON_NEAR_PIN);
                buttonindexstate = GPIO_getInputPinValue(BUTTON_INDEX_PORT, BUTTON_INDEX_PIN);
                buttonmiddlestate = GPIO_getInputPinValue(BUTTON_MIDDLE_PORT, BUTTON_MIDDLE_PIN);
                buttonringstate = GPIO_getInputPinValue(BUTTON_RING_PORT, BUTTON_RING_PIN);
                buttonpinkystate = GPIO_getInputPinValue(BUTTON_PINKY_PORT, BUTTON_PINKY_PIN);
                if(sendPress == 1)
                {
                    uint16_t key = 0;

                    //handle shift prefix
                    if(buttonMatrix == 1<<BUTTON_FAR_POS)
                    {
                        if(shiftfix == SHIFTFIX_ON)
                            shiftfix = SHIFTFIX_OFF;
                        else
                            shiftfix = SHIFTFIX_ON;
                    }
                    //handle num prefix
                    else if(buttonMatrix == 1<<BUTTON_NEAR_POS)
                    {
                        if(numfix == NUMFIX_ON)
                        {
                            numfix = NUMFIX_OFF;
                            key = 32;
                            sendChord(key);
                        }
                        else
                        {
                            numfix = NUMFIX_ON;
                        }
                    }
                    else if(buttonMatrix == (1<<BUTTON_NEAR_POS | 1<<BUTTON_INDEX_POS | 1<<BUTTON_MIDDLE_POS | 1<<BUTTON_RING_POS | 1<<BUTTON_PINKY_POS))
                    {
                        if(numlock == NUMLOCK_ON)
                            numlock = NUMLOCK_OFF;
                        else
                            numlock = NUMLOCK_ON;
                    }
                    else
                    {
                        if(numfix == NUMFIX_ON || numlock == NUMLOCK_ON)
                        {
                            key = chordnum[buttonMatrix];
                        }
                        else
                        {
                            key = chordalpha[buttonMatrix];
                        }
                        if(key < 0xE0)
                            sendChord(key);
                        else
                            sendMacro(key);
                    }

                    buttonMatrix = 0;
                    sendPress = 0;
                }
                break;
            // These cases are executed while your device is disconnected from
            // the host (meaning, not enumerated); enumerated but suspended
            // by the host, or connected to a powered hub without a USB host
            // present.
            case ST_PHYS_DISCONNECTED:
            case ST_ENUM_SUSPENDED:
            case ST_PHYS_CONNECTED_NOENUM_SUSP:
                __bis_SR_register(LPM3_bits + GIE);
                _NOP();
                break;

            // The default is executed for the momentary state
            // ST_ENUM_IN_PROGRESS.  Usually, this state only last a few
            // seconds.  Be sure not to enter LPM3 in this state; USB
            // communication is taking place here, and therefore the mode must
            // be LPM0 or active-CPU.
            case ST_ENUM_IN_PROGRESS:
            default:;
        }
    }  //while(1)
} //main()

void sendChord(uint8_t key)
{
    if(shiftfix == SHIFTFIX_ON)
    {
        Keyboard_press(KEY_LEFT_SHIFT);
        while(!keySendComplete);
        keySendComplete = FALSE;
    }
    if(numfix == NUMFIX_ON)
    {
        numfix = NUMFIX_OFF;
    }
    Keyboard_press(key);
    while(!keySendComplete);
    keySendComplete = FALSE;
    Keyboard_release(key);
    while(!keySendComplete);
    keySendComplete = FALSE;
    if(shiftfix == SHIFTFIX_ON)
    {
        Keyboard_release(KEY_LEFT_SHIFT);
        while(!keySendComplete);
        keySendComplete = FALSE;
        shiftfix = SHIFTFIX_OFF;
    }
    return;
}

void sendMacro(uint16_t macro)
{
    switch(macro)
    {
    case MACRO_000:
        Keyboard_press('0');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('0');
        while(!keySendComplete);
        keySendComplete = FALSE;

        Keyboard_press('0');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('0');
        while(!keySendComplete);
        keySendComplete = FALSE;

        Keyboard_press('0');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('0');
        while(!keySendComplete);
        keySendComplete = FALSE;
        break;
    case MACRO_00:
        Keyboard_press('0');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('0');
        while(!keySendComplete);
        keySendComplete = FALSE;

        Keyboard_press('0');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('0');
        while(!keySendComplete);
        keySendComplete = FALSE;
        break;
    case MACRO_PARENS:
        Keyboard_press('(');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('(');
        while(!keySendComplete);
        keySendComplete = FALSE;

        Keyboard_press(')');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release(')');
        while(!keySendComplete);
        keySendComplete = FALSE;

        Keyboard_press(KEY_LEFT_ARROW);
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release(KEY_LEFT_ARROW);
        while(!keySendComplete);
        keySendComplete = FALSE;
        break;
    case MACRO_QUOTES:
        Keyboard_press('"');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('"');
        while(!keySendComplete);
        keySendComplete = FALSE;

        Keyboard_press('"');
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release('"');
        while(!keySendComplete);
        keySendComplete = FALSE;

        Keyboard_press(KEY_LEFT_ARROW);
        while(!keySendComplete);
        keySendComplete = FALSE;
        Keyboard_release(KEY_LEFT_ARROW);
        while(!keySendComplete);
        keySendComplete = FALSE;
        break;
    default:
        break;
    }
}

/*
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
             UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is
            // suspended, a "bus error" can occur.  This generates an NMI.  If
            // USB is automatically disconnecting in your software, set a
            // breakpoint here and see if execution hits it.  See the
            // Programmer's Guide for more information.
            SYSBERRIV = 0; //clear bus error flag
            USB_disable(); //Disable
    }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A1_VECTOR)))
#endif
void TIMER1_A1_ISR (void)
{
    //Any access, read or write, of the TAIV register automatically resets the
    //highest "pending" interrupt flag
    switch ( __even_in_range(TA1IV,14) ){
        case  0: break;                          //No interrupt
        case  2: break;                          //CCR1 not used
        case  4: break;                          //CCR2 not used
        case  6: break;                          //CCR3 not used
        case  8: break;                          //CCR4 not used
        case 10: break;                          //CCR5 not used
        case 12: break;                          //CCR6 not used
        case 14:
            if(buttonfarstate != lastbuttonfarstate)
            {
                if(buttonfarstate == BUTTON_DOWN)
                    buttonMatrix |= 1 << BUTTON_FAR_POS;

                if(buttonfarstate == BUTTON_UP)
                    sendPress = 1;

                lastbuttonfarstate = buttonfarstate;
            }
            if(buttoncenterstate != lastbuttoncenterstate)
            {
                if(buttoncenterstate == BUTTON_DOWN)
                    buttonMatrix |= 1 << BUTTON_CENTER_POS;

                if(buttoncenterstate == BUTTON_UP)
                    sendPress = 1;

                lastbuttoncenterstate = buttoncenterstate;
            }
            if(buttonnearstate != lastbuttonnearstate)
            {
                if(buttonnearstate == BUTTON_DOWN)
                    buttonMatrix |= 1 << BUTTON_NEAR_POS;

                if(buttonnearstate == BUTTON_UP)
                    sendPress = 1;

                lastbuttonnearstate = buttonnearstate;
            }
            if(buttonindexstate != lastbuttonindexstate)
            {
                if(buttonindexstate == BUTTON_DOWN)
                    buttonMatrix |= 1 << BUTTON_INDEX_POS;

                if(buttonindexstate == BUTTON_UP)
                    sendPress = 1;

                lastbuttonindexstate = buttonindexstate;
            }
            if(buttonmiddlestate != lastbuttonmiddlestate)
            {
                if(buttonmiddlestate == BUTTON_DOWN)
                    buttonMatrix |= 1 << BUTTON_MIDDLE_POS;

                if(buttonmiddlestate == BUTTON_UP)
                    sendPress = 1;

                lastbuttonmiddlestate = buttonmiddlestate;
            }
            if(buttonringstate != lastbuttonringstate)
            {
                if(buttonringstate == BUTTON_DOWN)
                    buttonMatrix |= 1 << BUTTON_RING_POS;

                if(buttonringstate == BUTTON_UP)
                    sendPress = 1;

                lastbuttonringstate = buttonringstate;
            }
            if(buttonpinkystate != lastbuttonpinkystate)
            {
                if(buttonpinkystate == BUTTON_DOWN)
                    buttonMatrix |= 1 << BUTTON_PINKY_POS;

                if(buttonpinkystate == BUTTON_UP)
                    sendPress = 1;

                lastbuttonpinkystate = buttonpinkystate;
            }
            break;
        default: break;
    }
}

