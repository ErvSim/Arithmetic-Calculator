#include "TM4C123GH6PM.h"
#include "stdio.h"																														// due to the use of sprintf
#include <stdbool.h>																													// for boolean

void LCD_init(void);
void LCD_nibble_write(char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(char data);
void delayMs(int ms);
void keypad_init(void);
char keypad_getkey(void);
void delayUs(int ttime);
void buzzerAndLed_init(void);
void buzzerSound(char key);
void handleDivisionByZeroError();
void clearError();
void buzzerSiren();
void blinkLEDs();

char getOperation(void);
void performCalculation(char op, int num1, int num2);
void clearDisplay(void);
void displayNumber(int num);
void displayAnswer(double num);
void displayChar(char c);
void displayMultipleNumbers(int num1, int num2, char op);

bool isNum2 = false;

int main(void) 
{
    char key;
    char op;
    int num1 = 0;
    int num2 = 0;
    bool isNum1 = true;


		// initilization of keypad, LCD, Buzzer and LED before we start
    keypad_init();
    LCD_init();
		buzzerAndLed_init();

    while (1) 
	{
        key = keypad_getkey();											// call keypad_getkey function to see what char to store in variable
        if (key) 
		{
            if (key >= '0' && key <= '9') 									// check to see if the char stored are between 0 and 9
		{
                if (isNum1) 											// isNum1 is set true since this is our first number
			{
				num1 = num1 * 10 + (key - '0');							// num 1 code. (key - '0') is a way to change char to and int.
				displayNumber(num1);								// displays num1
				buzzerSound(key);								// makes buzzer sound depending on char (refer to DTMF telephone keypad)
                	} 
			else 											// isNum1 false meaning it is second number.
			{
                  		num2 = num2 * 10 + (key - '0');							// num2 code
                  		displayMultipleNumbers(num1,num2,op);						// displays entire equation
				isNum2 = true;									// Now we have a second number
				buzzerSound(key);								// makes buzzer sound depending on char of key for num2 (refer to DTMF telephone keypad)
                	}
            	} 
						// The order for A-D is based off My Dear Aunt Sally.
		else if (key == 'A' && isNum1 == true) 								// Multiplication 													
		{
                	op = '*';																			
                	isNum1 = false;										// puts isNum1 to false so we can now get into the else code for above
                	displayChar(op);									// displays char
			buzzerSound(key);									// plays specific frequency depending on char
		}
		else if (key == 'B' && isNum1 == true) 								// division
		{
                	op = '/';
                	isNum1 = false;
                	displayChar(op);
			buzzerSound(key);
		}
		else if (key == 'C' && isNum1 == true) 								// Addition
		{
                	op = '+';
                	isNum1 = false;
                	displayChar(op);
			buzzerSound(key);
		}
		else if (key == 'D' && isNum1 == true) 								// subtraction
		{
                	op = '-';
                	isNum1 = false;
                	displayChar(op);
			buzzerSound(key);
            
		} 
		else if (key == '#' && isNum1 == false && isNum2 == true) 					// button for equal sign. Performs claculation and resets everything
		{
                	performCalculation(op, num1, num2);
                	num1 = 0;
                	num2 = 0;
                	isNum1 = true;
			buzzerSound(key);
            } 
		else if (key == '*')                              						// button for reseting everything back to normal
		{
                	clearDisplay();
                	num1 = 0;
                	num2 = 0;
                	isNum1 = true;
			buzzerSound(key);
            }
        }		
    }
}
// code for calculations -----------------------------------------------------------------------
char keypad_getkey(void) 
{		
    const char keys[4][4] = 
		{
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    }; 																										//creates a 4x4 matrix with the same format as the one shown on the board

    int row, col;
    for (col = 0; col < 4; col++) 												// nested for loop to enter the matrix. Start from columns
		{
				
        GPIOA->DATA = (1 << (col + 2));  									// Set one column high at a time
        delayMs(1);  																			// Allow the signal to settle

        for (row = 0; row < 4; row++) 										// for loop to check rows
			{
            if ((GPIOD->DATA & (1 << row)) != 0) 					// Check if any row is high
						{  
                while ((GPIOD->DATA & (1 << row)) != 0);  // Wait for key release
								return keys[row][col];										// return char of row and column value from keys
            }
        }
    }
    return 0;  // No key pressed
}
void displayNumber(int num) 
{
    char buffer[16];															// create array called buffer that allocates 16 char elements
    sprintf(buffer, "%d", num);										// Print num to buffer
    clearDisplay();																// clears display
    for (int i = 0; buffer[i] != '\0'; i++) 			// Display each character in the buffer , strings/chars end with '\0' which is null character. Saying != means we haven't reach the end of the string
		{
        LCD_data(buffer[i]);
    }
}
void displayMultipleNumbers(int num1, int num2, char op) 
{
    char buffer[16];																	// create array called buffer that allocates 16 char elements
    int index = 0;

    
    index += sprintf(buffer + index, "%d", num1);			// Print num1 to buffer

    
    index += sprintf(buffer + index, "%c", op);				// Print operation symbol to buffer

    
    sprintf(buffer + index, "%d", num2);							// Print num2 to buffer

    clearDisplay();																		// clears display shown from displayNumber() funcion
	
    for (int i = 0; buffer[i] != '\0'; i++) 					// // Display each character in the buffer , strings/chars end with '\0' which is null character. Saying != means we haven't reach the end of the string
		{
        LCD_data(buffer[i]);
    }
}
void displayAnswer(double num) 
{
    LCD_command(0xC0); 													// Move cursor to the second row
    LCD_data('=');															// displays = sign to show LCD is now providing the answer
		char buffer[16];														// create array called buffer that allocates 16 char elements
    
    if (num == (double)num)											// Checks if the number has a fractional part
		{
        sprintf(buffer, "%.10g", num); 					// "%.10g" formats with up to 10 significant digits

        
        for (int i = 0; buffer[i] != '\0'; i++) // Display each character in the buffer, strings end with '\0' which is null character. Saying != means we haven't reach the end of the string
			  {
            LCD_data(buffer[i]);
        }
    } 
		else 																				// It's a whole number, display without decimal places
		{
        
        sprintf(buffer, "%.0f", num); 					// "%.0f" formats without decimal places

        
        for (int i = 0; buffer[i] != '\0'; i++) // Display each character in the buffer , strings end with '\0' which is null character. Saying != means we haven't reach the end of the string
				{
            LCD_data(buffer[i]);
        }
    }
}
void performCalculation(char op, int num1, int num2) 
{
    double result = 0.0;
    switch (op) 
		{
        case '+':																				// in case user wants to add
            result = num1 + num2;												// adds both numbers
						displayAnswer(result);											// calls displayAnswer function to show answer on LCD
            break;
        case '-':																				// in case user wants to subtract
            result = num1 - num2;												// subtracts both numbers
						displayAnswer(result);											// calls displayAnswer function to show answer on LCD
            break;
        case '*':																				// in case user wants to multiple
            result = num1 * num2;												// multiplies both numbers
						displayAnswer(result);											// calls displayAnswer function to show answer on LCD
            break;
        case '/':																				// in case user wants to divide
            if (num2 != 0)															// check to make sure we aren't dividing by zero
						{
                result = (double)num1 / (double)num2;		// divides both numebers 
								displayAnswer(result);									// calls displayAnswer function to show answer on LCD
						}
            else
                handleDivisionByZeroError(); 						// Handle division by zero
            break;
        default:
            break;
    }
}
void clearDisplay() 
{
    LCD_command(0x01); 				// clear screen, move cursor to home
}

void displayChar(char c) 			// writes onto screen
{
    LCD_data(c);
}
//DIV/0 code --------------------------------------------------------------------------------------
void handleDivisionByZeroError() 
{ 
    LCD_command(0xC0);																// Move cursor to the second row

    
    char errorMsg[] = "DIV/0 ERR";										// Display the error message
    for (int i = 0; errorMsg[i] != '\0'; i++) 				// strings/char end with '\0' which is null character. Saying != means we haven't reach the end of the string
		{
        LCD_data(errorMsg[i]);
    }

    
    while (1) 																				// Start the buzzer and LED blinking
		{
        if (keypad_getkey() == '*') 									// See if user has pressed '*' to clear
				{
            clearError();															// Calls function clearError() which makes calculator start fresh
            return;
        }
        buzzerSiren();																// Calls function to turn on buzzer for siren sounds
        blinkLEDs();																	// calls function to make LEDS blink like crazy
    }
}
void clearError() 
{
    clearDisplay(); 							//calls clearDisplay function to clear display
    GPIOC->DATA &= ~0x10; 				// Turn off the buzzer
    GPIOB->DATA &= ~0x0F;				  // Turn off all LEDs
    delayMs(5); 									// Small delay to allow clearing the state
		isNum2 = false;
}

void buzzerSiren() 
{
    int sirenDelay1 = 1000;															// Us delay , chosen by trial and error whatever sounded cool
    int sirenDelay2 = 750;															// ^^

    for (int i = 0; i < 50; i++) 												// 50 was chosen by trial and error
		{
        GPIOC->DATA |= 0x10; 														// PC4: HIGH
        delayUs(sirenDelay1); 													// half period for first frequency
        GPIOC->DATA &= ~0x10; 													// PC4: LOW
        delayUs(sirenDelay1);
        
        GPIOC->DATA |= 0x10; 														// PC4: HIGH
        delayUs(sirenDelay2); 													// half period for second frequency
        GPIOC->DATA &= ~0x10; 													// PC4: LOW
			delayUs(sirenDelay2);	
    }
}

void blinkLEDs() 
{
    GPIOB->DATA ^= 0x0F; 						// Toggle LEDs on pins 3-0
    delayMs(100); 									// Short delay for blinking effect
}
void buzzerSound(char key)
{
    int highFreq = 0, lowFreq = 0;

    // Get the corresponding frequencies for the pressed key
    switch (key) 																								//All frequencies information was received from source 
    {
        case '1': lowFreq = 697; highFreq = 1209; break;
        case '2': lowFreq = 697; highFreq = 1336; break;
        case '3': lowFreq = 697; highFreq = 1477; break;
				case 'A': lowFreq = 697; highFreq = 1633; break;
        case '4': lowFreq = 770; highFreq = 1209; break;
        case '5': lowFreq = 770; highFreq = 1336; break;
        case '6': lowFreq = 770; highFreq = 1477; break;
				case 'B': lowFreq = 770; highFreq = 1633; break;
        case '7': lowFreq = 852; highFreq = 1209; break;
        case '8': lowFreq = 852; highFreq = 1336; break;
        case '9': lowFreq = 852; highFreq = 1477; break;
				case 'C': lowFreq = 852; highFreq = 1633; break;
				case '*': lowFreq = 941; highFreq = 1209; break;
				case '0': lowFreq = 941; highFreq = 1336; break;
				case '#': lowFreq = 941; highFreq = 1477; break;
				case 'D': lowFreq = 941; highFreq = 1633; break;
        default: return; // No sound for other characters
    }

    // Calculate delay times for half periods
    int highDelay = 1000000 / highFreq;					// converts frequency to time (in seconds), then multiplies to get Us
    int lowDelay = 1000000 / lowFreq;						// converts frequency to time (in seconds), then multiplies to get Us

    for (int i = 0; i < 75; i++)
    {
        GPIOC->DATA |= 0x10; 										// PC4: HIGH
        delayUs(highDelay); 										// high frequency period
        GPIOC->DATA &= ~0x10; 									// PC4: LOW
        delayUs(lowDelay); 											// low frequency period
			
    }
}
//keypad, buzzer and LED initilization ----------------------------------------------------------
void buzzerAndLed_init(void)
{
	SYSCTL->RCGCGPIO |= 0X04; 				// ENABLE CLOCK TO GPIOC
	GPIOC->AMSEL &= ~0X10; 						// DISABLE ANALOG FUNCTION
	GPIOC->DIR |= 0x10; 							// set PC4 as output pin
	GPIOC->DEN |= 0x10; 							// set PC4 as digital pin

	SYSCTL->RCGCTIMER |= 1;						// enable clock to timer 0
	TIMER0->CTL = 0;									// disable timer 0
	TIMER0->CFG = 0x04;								// select 16 bit mode
	TIMER0->TAMR = 0x02;							// select periodic mode
	TIMER0->TAILR = 16 - 1;						// load value
	TIMER0->ICR = 0x1;								// clear timer 0 interuppt
	TIMER0->CTL |= 0x01;							// enable timer
	

	SYSCTL->RCGCGPIO |= 0X02;					// enable clock to GPIOB
	GPIOB->DIR |= 0x0F;								// set pins 3-0 as output pins
	GPIOB->DEN |= 0x0F;								// set pins 3-0 as digital pins
}
void keypad_init(void) 
{
    SYSCTL->RCGCGPIO |= 0x09;       // Enable clock to GPIOA and GPIOD
    while ((SYSCTL->PRGPIO & 0x09) == 0);  // Allow time for clock to stabilize

    GPIOA->DIR |= 0x3C;             // Set PA2-PA5 as outputs (columns)
    GPIOA->DEN |= 0x3C;             // Enable digital function on PA2-PA5

    GPIOD->DIR &= ~0x0F;            // Set PD0-PD3 as inputs (rows)
    GPIOD->DEN |= 0x0F;             // Enable digital function on PD0-PD3
}
//Basic Initizlation for LCD ----------------------------------------------------------------------------------------
void LCD_init(void) 
{
    SYSCTL->RCGCGPIO |= 0x01; 			// Enable clock to GPIOA
    SYSCTL->RCGCGPIO |= 0x10;				// Enable clock to GPIOE
    SYSCTL->RCGCGPIO |= 0x04;				// Enable clock to GPIOC

    GPIOA->AMSEL &= ~0x3C; 					// turn off analog functionality
    GPIOA->DIR |= 0x3C; 						// set pins as output
    GPIOA->DEN |= 0x3C; 						// set pins as digital

    GPIOE->AMSEL &= ~0x01;; 				// turn off analog functionality
    GPIOE->DIR |= 0x01; 						// set pins as output
    GPIOE->DEN |= 0x01; 						// set pins as digital
    GPIOE->DATA |= 0x01;						// set portE pin 0 high to make sure incomingdata is display data  

    GPIOC->AMSEL &= ~0x40;
    GPIOC->DIR |= 0x40;
    GPIOC->DEN |= 0x40;
    GPIOC->DATA &= ~0x40;

    // LCD initialization sequence
    delayMs(20);
    LCD_nibble_write(0x30, 0);
    delayMs(5);
    LCD_nibble_write(0x30, 0);
    delayMs(1);
    LCD_nibble_write(0x30, 0);
    delayMs(1);

    LCD_nibble_write(0x20, 0);		 // use 4-bit data mode
    delayMs(1);
    LCD_command(0x28); 						 // set 4-bit data, 2-line, 5x7 font
    LCD_command(0x06); 						 // move cursor right
    LCD_command(0x01);						 // clear screen, move cursor to home
    LCD_command(0x0F);						 // turn on LCD
}

void LCD_nibble_write(char data, unsigned char control) 
{
    GPIOA->DATA &= ~0x3C; 							// clearing the line
    GPIOA->DATA |= (data & 0xF0) >> 2;  // extracting the upper nibble
    if (control & 1)
        GPIOE->DATA |= 0x01; 						// RS = 1 for data
    else
        GPIOE->DATA &= ~0x01; 					// RS = 0 for command

    GPIOC->DATA |= 0x40; 								// E = 1
    delayMs(0);
    GPIOC->DATA &= ~0x40; 							// E = 0
}

void LCD_command(unsigned char command) 
{
    LCD_nibble_write(command & 0xF0, 0); // upper nibble
    LCD_nibble_write(command << 4, 0); // lower nibble
    if (command < 3)
        delayMs(2); //maximum delay of 2 ms for the first two instructions
    else
        delayMs(1); //maximum delay of 1 ms for all other instructions
}

void LCD_data(char data) 
{
    LCD_nibble_write(data & 0xF0, 1); // upper nibble
    LCD_nibble_write(data << 4, 1); // lower nibble
    delayMs(1);
}

void delayMs(int ms) 
{
    int i, j;
    for(i = 0 ; i< ms; i++)
        for(j = 0; j < 3135; j++)
            {}  // do nothing for 1 ms
}
void delayUs(int ttime) 
{
    int i;
    for(i = 0; i < ttime; i++) 
	{
			while ((TIMER0->RIS & 0x1) == 0); // wait for TimerA timeout flag
			TIMER0->ICR = 0x1; // clear the TimerA timeout flag
	}
}
