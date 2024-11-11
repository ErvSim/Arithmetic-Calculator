<br />

<img src="" height="20%" width="50%" alt="Disk Sanitization Steps"/>

<br />

<img src="" height="20%" width="50%" alt="Disk Sanitization Steps"/>

<br />

<img src="" height="20%" width="50%" alt="Disk Sanitization Steps"/>

<br />

<img src="" height="20%" width="50%" alt="Disk Sanitization Steps"/>

We are building a fully functional arithmetic calculator capable of performing addition, subtraction, multiplication, and division with no bugs. This project uses the EduBase-V2 board featuring the TM4C123GH6PM microcontroller. The EduBase-V2 provides essential components, including a 16x2 LCD display for output, a 4x4 keypad for input, a magnetic buzzer for audio feedback, among others. All programming is done in C using the Keil uVision 5 IDE, which allows us to ensure smooth operation and bug-free calculations.

<br />

<img src="https://github.com/user-attachments/assets/2641653d-a5e7-429b-8fd6-61214962ea75" height="20%" width="50%" alt="Disk Sanitization Steps"/>

For this project, we will be using the 4x4 keypad, Magnetic Buzzer, LED, and the 16x2 LCD display. After initilizing all of the parts mentioned, we need to prepare the the 4x4 to take the input from the user. After referring to the datasheet, we were able to create a user function to return a char depending on what the user pressed on the keypad
<br />

<img src="https://github.com/user-attachments/assets/8b7e657d-d1db-4a17-bb4b-8b861ae9dc65" height="60%" width="100%" alt="Disk Sanitization Steps"/>

This char is returned back into main where we check to see 
