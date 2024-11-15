We are building a fully functional arithmetic calculator capable of performing addition, subtraction, multiplication, and division with no bugs. This project uses the EduBase-V2 board featuring the TM4C123GH6PM microcontroller. The EduBase-V2 provides essential components, including a 16x2 LCD display for output, a 4x4 keypad for input, a magnetic buzzer for audio feedback, among others. All programming is done in C using the Keil uVision 5 IDE, which allows us to ensure smooth operation and bug-free calculations.

<br />

<img src="https://github.com/user-attachments/assets/2641653d-a5e7-429b-8fd6-61214962ea75" height="20%" width="50%" alt="Disk Sanitization Steps"/>

For this project, we will be using the 4x4 keypad, magnetic buzzer, LED, and 16x2 LCD display. After initializing these components, we set up the 4x4 keypad to accept user input. By referring to the datasheet, we created a function that returns a character based on the key pressed by the user.
<br />

<img src="https://github.com/user-attachments/assets/8b7e657d-d1db-4a17-bb4b-8b861ae9dc65" height="60%" width="100%" alt="Disk Sanitization Steps"/>

The character returned from the keypad function is sent back to the main program, where we can identify the key pressed and perform actions based on it. The program structure follows the sequence: "Num1, Operation, Num2," and pressing the '#' key resets everything and displays the calculation result. Due to time constraints, I did not implement a "go left" or "go right" feature for correcting mistakes. Instead, pressing the '*' key clears the entire input, allowing us to start from the beginning if an error is made.

Examples of how to use the calculator are shown below. For instance, to perform the calculation 12 x 3, we would press the sequence: '1', '2' → 'A' (for multiplication) → '3' → '#'. Pressing '#' will reset the calculator and display the result.

The 4x4 keypad used in this project follows the layout of a standard DTMF telephone keypad. I based the coding on this layout, where the letters A-D correspond to the operations based on the mnemonic "My Dear Aunt Sally." Specifically, 'A' represents multiplication, 'B' stands for division, 'C' for addition, and 'D' for subtraction.
<br />

<img src="https://github.com/user-attachments/assets/f72d7dcf-ab85-4a50-8fc4-7bb516a95905" height="20%" width="50%" alt="Disk Sanitization Steps"/>

Another example is performing the calculation 15 / 9. We would press '1', '5' → 'B' (for division) → '9' → '#'. The result is displayed as a double with up to 10 significant digits. However, If the answer is an integer, it will be shown as a whole number without any unnecessary trailing zeros.
<br />

<img src="https://github.com/user-attachments/assets/5a1fe401-386d-42c2-b979-379e16dfcbaa" height="20%" width="50%" alt="Disk Sanitization Steps"/>

During debugging, we first addressed the issue of multiple inputs when a user held down a button. We fixed this by adding a while loop to ensure that the keypad value toggled from 0 to 1 and back to 0, allowing only one input per button press. The second issue was allowing the sequence "num1, operation, num2, operation," which was incorrect. I resolved this by preventing any further operation buttons from being pressed after the first one. The final debug focused on handling division by zero errors. We created a user function to check if the operation is division and if num2 is 0, and in that case, we activated all LEDs and triggered the buzzer to play an alarm sound. An example of the division by zero error is shown below.

<br />

<img src="https://github.com/user-attachments/assets/742560bf-25b0-4b6f-b444-1ff400902bd1" height="20%" width="50%" alt="Disk Sanitization Steps"/>

In addition, every button on the keypad is programmed to play a specific tone through the magnetic buzzer. The frequency of the high and low tones corresponds to the DTMF (Dual-tone multi-frequency) standard, providing an audible feedback for each key press.
