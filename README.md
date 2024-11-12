<br />

<img src="" height="20%" width="50%" alt="Disk Sanitization Steps"/>

<br />

<img src="" height="20%" width="50%" alt="Disk Sanitization Steps"/>





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

<img src="https://github.com/user-attachments/assets/308a1201-ef35-4124-b0b4-cba87ae35bbd" height="20%" width="50%" alt="Disk Sanitization Steps"/>
