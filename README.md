# DT8025

-------------

*In this course there are 5 assignments*

-------------

# Assignment 1
<details><summary>See more</summary>
<p>
Attached Files:
File resetbit.c (957 B)
File helloworld.img (16.656 KB)

-------------

### Objectives

* Set up and familiarise with the lab environment (e.g., Raspberry Pi (RPi) and ARM Cross Compiler).

* Familiarise and understand the basic C programming concepts required for the rest of the course.

* To acquire a basic skill for the Raspberry Pi bare-metal programming.

-------------


### Content

* Assignment 1 starts with preparations for the actual assignment, including 2 parts.
* Part 1 is about implementing bitwise operations in C and exploring how to exchange data between the RPi and a PC using
  serial UART communication.
* Part 2 is about implementing a firmware/kernel to control a LED via the RPi GPIO.
* Instructions for Part 1 and Part 2 are further down on this page.
* Part 1 and Part 2 results will be graded, and each group will submit the implemented results according to the
  deadline.

-------------

### Grading and Deadline

* Assignment 1 will be graded during the Grading Session on Friday, September 16th from 15:15.
The deadline for developed results is Thursday, September 15th at 15:00.
* Q&A
* Questions will be addressed during the supervision sessions.
* Questions or comments relevant to other students shall be posted on the Discussions forum.
* Please, don't post source code.
* Required equipment and software

-------------

### Lab kit
* Raspberry Pi OS
* A serial console software, such as PuTTY.
* PuTTY, an SSH, Telnet, and serial communication client that works on Windows, macOS, and Linux.

-------------

### References
* Valvers Bare Metal Programming in C
* Cambridge Baking Pi
* C reference (Wagner recommends ;D)

-------------

### Preparation 1: C Programming

1. Make sure the RPi can boot the Raspberry Pi OS.
   * Otherwise, it is part of the assignment to install the Raspberry Pi OS. Please, check the installation guide.
2. Writing and compiling C code.
   * Some students might use the RPi as a development environment to write and compile code.
     * Writing and compiling code on another PC would probably be more convenient for the actual assignments. However, you
   can write and test functions using RPi.
   * Web-based compilers for C can also be used to write and test C code.
   * Using a text or code editor, open the attached resetbit.c file.
   * Try to understand what the program does. Some of the logic will be useful during this assignment.
   * To compile the program, type the following command in the command line:
   `gcc /PATH_TO_C_FILE/C_FILE.c -o /PATH_TO_EXECUTATLE/EXECUTABLE`
      * For example: `gcc resetbit.c -o resetbit`
   * If the compilation succeeds, run the executable.
-------------
### Preparation 2: Bare-Metal Programming for Raspberry Pi
   *Bare-metal programming is a term used to describe software development without an operating system's support.
   Bare-metal software executes at the hardware level and is built to specific hardware. Embedded systems and real-time
   operating systems (RTOS) are examples of bare-metal software.

#### 1. Cross compiler for ARM
   * To compile a .c code to execute bare metal on the RPis 3, a bare metal C compiler for embedded ARM chips using
   Cortex-R/M processors is needed. The GNU Arm Embedded Toolchain is a ready-to-use, open-source suite of tools for C,
   C++ and assembly programming.
   * **Writing and compiling code on another PC than the RPi would probably be more convenient for the actual assignments.**
#### Windows OS
   * Download and install the gcc-arm-embedded Arm Cross Compiler Toolchain.
   * Download and install the Make for Windows. Make is a tool that automates building programs.
   * **NOTE:** it is important that your Windows PATH variable includes the path to gcc-arm-none-eabi and make bin folders.
#### Raspberry Pi OS
   * Install the gcc-arm-none-eabi GCC cross compiler using the command
      * sudo apt-get install gcc-arm-none-eabi
#### Compiling source code
   * To compile code, we use the gcc-arm-embedded Arm Cross Compiler Toolchain and the provided makefile in the
   assignments.
     * You will find a Makefile file in the directory of every code connected to the assignments. The Makefile file takes
   care of all compiler options so that you only have to execute the following command in the command prompt to generate
   a .img file, which is pre-configured to be rteskernel.img.
        * make run
####  Changing the kernel to be loaded
 *  Make sure you read about the RPi configuration files
 *  A few files of the Raspberry Pi OS are stored on the MicroSD card. Some of these files contain the actual kernel to
   be loaded, while others are for configuration.
      * The kernel.img and kernel7.img files are the kernel to be loaded to the boot partition. The kernel.img file is the
   default kernel for Pi 1 and Pi Zero, while the kernel7.img is the default for Pi 2 and Pi 3.
      * The configuration file config.txt is used to configure different boot options. Among the options, the kernel option
   indicates the filename on the boot partition when loading the kernel.
        * To indicate that rteskernel.img shall be loaded instead of the default kernel, add a line to config.txt such as:
   `kernel=rteskernel.img`
        * Every time you want to load a new kernel, you must ensure the option kernel indicates the kernel to be loaded.
* Given that the command make run succeeded and that it created a new .img file
   * Copy the new .img file into the MicroSD card.
   * Change the config.txt file in the MicroSD card by changing the value of the property kernel to the new .img file
name.
* Remove the micro SD card from the computer and insert it into the RPi.
* Power on the RPi.
* The new kernel shall now execute on the RPi.
-------------
### Preparation 3: Bare-Metal Serial Communication
* With Raspberry Pi OS, one can communicate with the RPi via traditional I/O devices (i.e., USB keyboard and mouse and
screen) or the network. Another approach is to use a TTL USB serial cable.
* In the assignments, students will exploit a library that enables bi-directional communication between RPi and a PC
using the TTL USB serial cable. The library explores serial UART communication using RPi's serial port.
* Students will need the provided TTL USB serial cable and a serial console software, such as PuTTY, installed on the
PC.
#### 1. Connecting the TTL USB serial cable to the RPi
   * To connect the TTL USB serial cable to the RPi.
      * Connect the black cable (GND groun) to GPIO pin 6.
      * Connect the white cable (TXD transmission communication) to GPIO pin 8
      * Connect the green cable (RXD receiving communication) to GPIO pin 10.
      * DON'T connect the red cable (VCC power) because you will power the RPi using the power supply with the micro-USB
   cable. You should not have both.
   * On the Pi 3 and 4 the UART is, by default, used for Bluetooth. Thus, you may need to add the following lines to "
   `/boot/config.txt"`.
      * `enable_uart=1`
      * `dtoverlay=disable-bt`
#### 2. Testing
   1. Install a serial console software, such as PuTTY, on the PC.
   2. Connect the TTL USB serial cable to the PC.
       * A device driver might be needed.
   3. Check which serial port was attributed to the TTL USB serial cable.
   4. Execute the installed serial console software
       * Configure the serial line to connect to the TTL USB serial cable serial port using a baud rate (speed) of 115200.
   5. Start/open the serial communication session.
   6. Copy the attached `helloworld.img` file into the MicroSD card.
   7. Change the value of the property kernel to `helloworld.img` in the config.txt file in the MicroSD.
   8. Remove the micro SD card from the computer and insert it into the RPi.
   9. Power on the RPi.
   10. The new kernel shall now execute on the RPi.
      * Expected result
      BILD ATT LÄGGA TILL
-------------

## Assignment 1 - Part 1 (click to submit results)
Attached Files:
File a1p1.zip (34.57 KB)

* Bitwise operators in C
* Bitwise operators are commonly used to manipulate bit sets and bit masks.
The objectives of Part 1 are to learn how to use bitwise operators and encapsulate them into functions. More
specifically:
* Include the required documentation as comments in `iregister.h.`
* Implement the functions, including post- and pre-conditions, in `iregister.c.`
* Implement a user interface showing the result of each function.
#### REMEMBER
C declarations and macro definitions are placed in a header file (.h).
Documentation of function declarations include: WHAT the function does, parameters and return value.
The actual implementation is included in the .c files and documentation includes the logic of HOW a function does
something.

1. Download a1p1.zip and uncompress it.
2. Getting familiar with the iregister.h file
   Start the assignment by getting familiar if the iRegister data structure and the functions declarations that can
   modify and display a iRegister data structure.
   Please, check the "void resetBit(int, iRegister *)" function declaration in iregister.h. It exemplifies the task that
   you are expected to achieve.
3. Documenting the functions in iregister.h
   Before each function declaration, students should:
   Put a comment block giving a brief description.
   Describe all of the parameters of the function.
   Describe the return value.
   Pre-condition: what should the input parameters represent/satisfy?
   Post-condition: what will hold after calling the function?
   Properties: specify at least some properties that the function should satisfy.
   Again, check the "void resetBit(int, iRegister *)" function declaration in iregister.h for reference.
4. Implementing the functions in iregister.c
   Refer to the iregister.h file, where the declaration and purpose of each function is given.
   Implement all functions declared at iregister.h in the iregister.c file.
   As it is, the iregister.c file contains an example of the implementation of the resetBit function.
5. Using the functions in a1p1.c
   In a1p1.c, you shall use all the functions and show their result.
   The user must be able to enter an integer, the bit and nibble to manipulate, and the number of bits to shift.
   Example

Once your code is complete, compile it and boot the RPi using the newly created kernel, i.e., aip1.img.
NOTE: If the Lab Kit includes the TTL USB serial (yes, the cables have not arrived yet!), it is suggested to input and
output data via the serial console. The a1p1.c file hints at two functions in uart.h that can be used for input and
output. The idea here is to learn how to use serial communication for debugging purposes. Bare metal debugging is tricky
and the easiest way, not close to the best, is to dump what you want to know on UART.
NOTE: If the Lab Kit does not include the TTL USB serial, check the resetbit.c file included in the preparation for
Assignment 1. In this case, use standard gcc to compile the code that will run with support of the Raspberry Pi OS.

6. Submitting results
   For Assignment 1 Part 1, one student in the group must upload (click on the title of this section) the following
   files:
   iregister.c
   iregister.h
   a1p1.c
   DON'T submit compressed files, i.e., .zip or .rar files.
   All students in the group are equally responsible for the submitted source code.
   The group ensures that the submitted code does not include cheating and plagiarism issues.
   Congratulations!!!!!

-------------
 
  ## Assignment 1 - Part 2 (click to submit results)
   Attached Files:
   File a1p2.zip (28.984 KB)

   Bare-metal LED control via the Raspberry Pi GPIO

1. Lighting a LED
   Using the breadboard, the 270Ω (ohm) resistor, LED and cables included in Lab Kit, wire the circuit described in
   Raspberry Pi Learning Resources.
   If RPi’s +3.3v and 0v pins are properly connected to the breadboard, the LED will light when you turn the RPi on.
   Note: this is just to test the circuit.
2. Theory for controlling a LED via the RPi GPIO
   A LED can be controlled by any GPIO pin.
   The numbering of the GPIO pins is available in RPi's GPIO usage guide. Alternatively, RPi Pinout.
   Thus, to turn an LED on or off via software, you need to set the GPIO pin as an output (set the respective bit of the
   GPIO Function Select Register from the base address 0x3F200000).
   Note: Typically, embedded programming involves getting familiar with the hardware architecture you are working with.
   This means that reading datasheets is quite common. In Part 2, students are recommended to refer to the RPi datasheet
   regarding the chip BCM2837 ARM Peripheral, which is used to control different peripherals in the RPi, such as GPIO
   and serial interfaces. In that datasheet, please refer to page 90.
   Now that you are more familiar with the hardware platform, to turn the LED on and off, you will need to iteratively
   set the respective bit of the GPIO Output Set, and GPIO Output Clear registers with some delay in between.
3. Controlling a LED via the RPi GPIO
   Connect the breadboard to GPIO16 and GND pin 39.
   Download a1p2.zip and uncompress it.
   Compile the code using make, change the config.txt file accordingly, and boot the RPi.
   Momentarily, the LED will light.
4. GPIO-controlled LED
   In led.c, implement the function led_blink(), so the LED turns on and off with a delay before and after turning the
   LED off.
   Make sure you understand the code in the functions led_on() and led_off().
   I.e., how to work with the GPIO and to set the outputs low and high.
   The actual blink is achieved by setting the respective bit of the GPIO Output Set, and GPIO Output Clear registers
   with a delay before and after setting the Output Clear register.
   Use a delay of 0.5 seconds.
   To create the delay, use the function RPI_WaitMicroSeconds defined in lib/rpi-systimer.h.
   In a1p2.c, in the main function, call the function led_blink() inside of an infinite loop.
   Once your code is complete, compile it and boot the RPi using the newly created kernel, i.e., aip2.img.
   As a result, the LED will blink every second.
   BTW, check the Makefile to understand how you make it output a file named aip2.img.
5. Submitting results
   For Assignment 1 Part 2, one student in the group must upload (click on the title of this section) the following
   files:
   ledblink.c
   a1p2.c
   DON'T submit compressed files, i.e., .zip or .rar files.
   All students in the group are equally responsible for the submitted source code.
   The group ensures that the submitted code does not include cheating and plagiarism issues.
   Congratulations!!!!!
</p>
</details>

-------------

# Assignment 2
<details><summary>See more</summary>
<p>

-------------

### Objectives

* Straighten your skills in working with the Raspberry Pi, particularly concerning input and output.
* Experiment with concurrency (without any underlying support) and observe the main issues.

-------------

### Content

* Assignment 2 includes 3 parts.
* In Part 1, implement C library functions for the PiFace Control and Display.
* In Part 2, implement Taylor Expansion and display results in the PiFace Display.
* In Part 3, implement manual interleaving of two tasks.

-------------

### Grading and Deadline

* Assignment 2 will be graded during the Grading Session on Friday, September 23th from 13:15.
* The deadline for developed results is Thursday, September 22th at 15:00.

-------------

### Q&A

* Questions will be addressed during the supervision sessions.
* Questions or comments relevant to other students shall be posted on the Discussions forum.
* Please, don't post source code.
* Required equipment and software

-------------

### Lab kit

* PiFace Control and Display + breadboard circuit for the LED.
* Raspberry Pi OS (if you are compiling the code on it)
* For debugging, maybe a serial console software, such as PuTTY.
* PuTTY, is an SSH, Telnet, and serial communication client that works on Windows, macOS, and Linux.

-------------

### References

* Valvers Bare Metal Programming in C
* Cambridge Baking Pi
* C reference (Wagner recommends ;D)
* HD44780U LCD's specification
* Taylor series

-------------

## Assignment 2 - Part 1 (click to submit results)

Attached Files:
File a2p1.zip (31.117 KB)

-------------

### PiFace Control and Display

The PiFace Control and Display allows the display of 16 characters by 2 lines. Please, refer to the PiFace Control and
Display website for more information about it.

The objective of Part 1 is to complete the implementation of a C library for the PiFace Control and Display.

1. Download a2p1.zip and uncompress it.
2. Get familiar with the piface C library

* PiFace Control and Display uses the HD44780 LCD to display alphanumeric characters. The HD44780 LCD sits on top of an
  MCP23S17 general purpose I/O expander, which operates in sequential mode to communicate with the Raspberry Pi's SPI
  interface.

    * It operates in 4-bit mode and has two communication channels.

    * One channel is used to transmit commands and another channel to send data.
  
* Showing some characters on the PiFace's display requires writing the respective value into the expander's data
  register. This can be done using the following provided methods:
   ```c
  static void lcd_write_cmd(uint8_t cmd)
  static void lcd_write_data(uint8_t data)
  ```

  Among others, the respective commands for clearing the display and moving the cursor can be found in the HD44780 LCD's
  specification.

4. Complete the implementation of piface
   Implement the following functions in the file piface.c
   ```c
   void piface_putc(char c);
   void piface_puts(char s[]);
   void piface_clear(void);
   ```
3. Use the functions in a2p1.c
   Connect the PiFace Control and Display to the RPi's GPIO.
   In a2p1.c, write the code for a program that repeatedly displays an arbitrary text and clears the LCD.
   See a2p1.c for string examples.
   Once the code is complete, compile it and boot the RPi using the newly created kernel, i.e., a2p1.img.
4. Submitting results
   For Assignment 1 Part 2, one student in the group must upload (click on the title of this section) the following
   files:
   piface.c
   piface.h
   a2p1.c
   **DON'T submit compressed files, i.e., .zip or .rar files.**
   All students in the group are equally responsible for the submitted source code.
   The group ensures that the submitted code does not include cheating and plagiarism issues.


-------------

   Congratulations!!!!!


 
-------------

## Assignment 2 - Part 2 (click to submit results)
   Attached Files:
   File a2p2.zip (42.849 KB)

-------------

   ### Taylor expansion of e^x
   The value of the exponential function e^x can be expressed using Taylor Series. Its algorithm has a linear time
   complexity O(n), i.e., it is proportionally longer to complete as the input grows. For example, computing e^1 is 10
   times faster than e^10.

   The Taylor expansion of e^x will be used in Part 3 to concurrently execute with another task.
   
   Thus, the objective of Part 2 is to implement the Taylor expansion of e^x. More specifically:

-------------

### 1. Write the specification (description, pre-and post-condition) for the function iexp()in expstruct.h
   Use the following signature:
   ```c
   struct expStruct {
   int expInt;
   int expFraction;
   };

   typedef struct expStruct ExpStruct;

   ExpStruct* iexp ( int );
   ```

### 2. Implement the function iexp() in expstruct.c
   The iexp() function is supposed to calculate the value of e^n (n = the input parameter) with two degrees of precision
   and return it in a struct comprising its integer and fractional parts, where the fractional part comprises two digits
   after the ".", i.e., the decimal separator.
   Consider this description of the exponential function (at point a=0) and the first (n+1) terms to calculate e^n.

### 3. Use the functions in a2p2.c
   In a2p2.c, write the code for a program that shows the values of the exponential function for natural numbers,
   starting from 1 and moving upwards up to 21.
   The program must show the values on the PiFace Display connected to RPi GPIO.
   Once your code is complete, compile it and boot the RPi using the newly created kernel, i.e., a2p2.img.
   Because the RPi can calculate e^n rather fast, you might add a delay in each iteration of the sum of terms to be able
   to visualize results.

### 4. Submitting results
   For Assignment 2 Part 2, one student in the group must upload (click on the title of this section) the following
   files:
   ```c
   expstruct.c
   expstruct.h
   piface.h
   piface.h
   a2p2.c
   ```
   **DON'T submit compressed files, i.e., .zip or .rar files.**

   All students in the group are equally responsible for the submitted source code.
   The group ensures that the submitted code does not include cheating and plagiarism issues.
 
-------------

**Congratulations!!!!!**


-------------

## Assignment 2 - Part 3 (click to submit results)
   Attached Files:
   File a2p3.zip (42.506 KB)
   File TheoryA2.pdf (379.763 KB)

-------------

  ### Manual Interleaving
   Embedded systems are said to be "event-driven", i.e., the primary function is to respond to "events". But how does
   the program become aware of changes in the system’s environment? How does it respond to events? Two approaches:
  * Status-driven using polling (busy waiting)
  * Interrupts driven

   In Part 3, students will build kernels that execute two tasks according to an offline scheduler, i.e., tasks are
   executed in sequence at a fixed rate in a big loop. Possibly, limit certain tasks to every N turns of the loop only.
   
   Please, refer to the attached TheoryA2.pdf, which motivates the need for an automatic interleaving approach.
   
   The goal is to build a kernel that calculates and displays the result e^n while blinking the LED at a constant rate.

-------------

### 1. Hardware setup
   Remove all components connected to the RPi GPIO.
   Connect the breadboard circuit assessed in Assignment 1 to GPIO16 and GND pin 39.
   Alight and connect the stacking header to the PiFace Control and Display.
   Now, connect the elevated PiFace Control and Display to the RPi GPIO.

-------------

### 2. Download a2p3.zip and uncompress it.
   Add the C library files you developed to blink the LED into \lib.
   Add the C library files you developed for the PiFace into \lib.

-------------

### 3. Cyclic execution in a2p3.c
   Write a program that combines the blinking of LED (a1p2) and the exponential function (a2p2) to:
   Turn the LED ON,
   Calculate the exponential function, and
   Turn the LED OFF.
   Once your code is complete, compile it and boot the RPi using the newly created kernel, i.e., a2p2.img.
   The LED will blink at a similar rate as the PiFace LCD displays the result of e^n. As n increases, the time between
   LED on and off will also increase. The provided a2p3.cyclic.img kernels exemplied this behavior.
   Question: how to make the LED blink at a constant rate?

-------------

### 4. Manual interleaving
   Observing the previous result, the LED blinks more slowly than it should as the exponential value of the number
   grows.
   NOTE: If the previous kernel does not present such behaviour, try to add some constant delay in the iexp() function.
   Design and implement a fair interleaving of the tasks, i.e. blinking and exponential, such that the blinking speed
   remains constant.
   Once your code is complete, compile it and boot the RPi using the newly created kernel, i.e., a2p2.img.

-------------

### 5. Submitting results
   For Assignment 2 Part 2, one student in the group must upload (click on the title of this section) the following
   files:
   ```c
   expstruct.c 
   expstruct.h
   piface.h
   piface.h
   a2p3.
   ```
   **DON'T submit compressed files, i.e., .zip or .rar files.**

   All students in the group are equally responsible for the submitted source code.
   The group ensures that the submitted code does not include cheating and plagiarism issues.
 
-------------

   **!Congratulations!!!!!**
- ![#f03c15](https://via.placeholder.com/15/f03c15/f03c15.png) `#f03c15`
</p>
</details>

-------------

# Assignment 3

 

-   ![Item](https://bb.hh.se/images/ci/sets/set12/document_on.svg)

    ### Assignment 3

    ### Objectives

    -   Straighten your skills in working with the Raspberry Pi, particularly concerning concurrent programming.
    -   To understand, use and modify the internals of a small multi-threading kernel called [tinythreads](http://www.sm.luth.se/csee/courses/d0003e/labs/lab2.html).
    -   Instead of manual interleaving, implement [cooperative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking) (aka non-preemptive multitasking) using a lightweight multi-threading kernel implemented with non-local gotos.

    ---

    ### Content

    -   Assignment 3 includes 3 parts.
        -   In Part 1, the goal is to understand how Tinythreads library works.
        -   In Part 2, the goal is to assess your understanding of how the modified Tinythreads library works.
        -   In Part 3, implement cooperative multitasking using TinyThreads.

    ---

    ### Grading and Deadline

    -   Assignment 3 will be graded during the Grading Sessions on **Friday, October 7th at 08:15 and 13:15**.
    -   The deadline for developed results is **Thursday, October 6th at 15:00**.

    ---

    ### Q&A

    -   Questions will be addressed during the supervision sessions.
    -   Questions or comments relevant to other students shall be posted on the Discussions forum.
    -   Please, don't post source code.

    ---

    ### Required equipment and software

    -   Lab kit
        -   PiFace Control and Display + breadboard circuit for the LED.
    -   Raspberry Pi OS (if you are compiling the code on it)
    -   For debugging, maybe a serial console software, such as PuTTY.
        -   PuTTY, is an SSH, Telnet, and serial communication client that works on Windows, macOS, and Linux.

    ---

    ### References

    -   [Valvers Bare Metal Programming in C](http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/)
    -   [C reference](https://en.cppreference.com/w/c) (Wagner recommends ;D)
    -   [Tiny Threads](http://www.sm.luth.se/csee/courses/d0003e/labs/lab2.html)

-   ![Item](https://bb.hh.se/images/ci/sets/set12/document_on.svg)

    ### Assignment 3 - Part 1

    Attached Files:

    -    [![File](https://learn.content.blackboardcdn.com/3900.48.0-rel.18+c7edfda/images/ci/ng/cal_year_event.gif) a3p1.zip](https://bb.hh.se/bbcswebdav/pid-433498-dt-content-rid-5709121_1/xid-5709121_1) (45.166 KB)

    ### Tinythreads

    [Tinythreads](http://www.sm.luth.se/csee/courses/smd/138/lab2.html) is a lightweight multi-threading kernel implemented using non-local gotos. In Assignment 3, the original Tinythreads library ([tinythreads.h](http://www.sm.luth.se/csee/courses/d0003e/labs/tinythreads.h) and [tinythreads.c](http://www.sm.luth.se/csee/courses/d0003e/labs/tinythreads.c)) was modified and ported to RPi 3 (ARMv8).

    The objective of Part 1 is to understand how Tinythreads library works, including added modifications for the DT8025 course.

    #### 1. Understanding Tinythreads

    Using the Tinythreads source code (lib/tinythreads.c and lib/tinythreads.h), the [lecture slides](http://www.sm.luth.se/csee/courses/d0003e/12/lectures/lecture4.pdf) from Fredrik Bengtssonslides, and the notes below, make sure you understand setjmp and longjmp and how the Tinythreads library works.

    **Obs**: do not underestimate the importance of this part of the assignment.

    **Technical notes on the implementation (By Fredrik Bengtsson @ LTU.SE )**

    -   _The thread implementation in tinythreads is of the kind to expect in a typical threading library; i.e., the threads share global memory and other resources but use private stacks._ _Execution using alternative stacks is achieved using a small platform-dependent trick in **spawn();** when the newly created thread has had its execution context initialized by **setjmp()** (return value 0), the stored stack-pointer is overwritten with a suitable address within a separate memory block.__The exact location within a **jmp_buf** where the stack-pointer is stored differs between platforms, hence the preprocessor macro **SETSTACK(buf,a)** has to be modified if tinythreads.c is to be moved to the RPi 3 (ARMv8). **Note**: The initial value must be set close to the highest address of the designated memory block, especially on architectures where the stack grows towards lower addresses._
        -   For Assignment 3, the SETSTACK(buf,a) macro has been modified to work with the RPi 3 (ARMv8).

    -   _The key to understanding this thread library is to come to peace with how the use of **setjmp()** and **longjmp()** works._ _You might therefore find it helpful to work through a sequence of **spawn()** and **yield()** calls presented in the [lecture slides](http://www.sm.luth.se/csee/courses/d0003e/12/lectures/lecture4.pdf), and notice how the underlying "thread of execution" jumps from context to context._

    -   _Finally, a note on memory management. The stack space for a thread is allocated as part of the control block for that thread, and a fixed amount of thread control blocks are defined in a global array, initially organized as a linked list of free blocks, from which memory can be allocated when a new thread is spawned. For simplicity, allocation and deallocation of thread memory are handled by the same operations that organize queues of threads in other parts of the implementation. However, it should be noted that this is a slight overkill – there is no underlying need to treat the pool of free thread blocks as a queue. The stack spaces and the thread block array are of fixed size, which can be a limiting factor in practice. In the current implementation, execution simply halts if dequeuing is attempted on an empty queue. In contrast, a shortage of stack space will manifest as random memory corruption caused by out-of-bounds memory writes._
        -   _In a production system, a more dynamic memory management scheme would be desirable, preferably coupled with an analysis method to statically predict the memory needs of a set of threads._

    #### 2. Download a3p1.zip and uncompress it

    #### 3. Adding C libraries

    -   Regarding results from Assignments 1 and 2, copy into a3p1/lib/ the following files:
        -   piface.*
        -   expstruct.*
            -   **NOTE**: Use the files from a2p2, i.e., the iexp() function without the LED blinking interleaving.
        -   led.*
            -   **NOTE**: add and implement a function called led_toggle() to toggle the state of the LED, i.e., switch the LED on or off depending on its previous state.

    #### 4. Generating a kernel using Tinythreads

    -   The a3p1.c file contains an example of a program executing two tasks concurrently.
        -   One task computes and displays the power of a number indefinitely, while the other computes and displays prime numbers indefinitely. 
        -   Each task is given to a different "thread" to execute; one is spawned while the other is the main thread.
    -   Compile the code and boot the RPi using the newly created kernel, i.e., a3p1.img.
        -   A successful kernel creation and installation shall enable you to visualize on the PiFace Display the outcome of 2 threads executing the power function, similarly to a3p1.expected.img.

-   ![Assignment](https://bb.hh.se/images/ci/sets/set12/assignment_on.svg)

    ### [Assignment 3 - Part 2 (click to submit results)](https://bb.hh.se/webapps/assignment/uploadAssignment?content_id=_433499_1&course_id=_14168_1&group_id=&mode=view)

    ### Testing your understanding of Tinythreads

    The objective of Part 2 is to challenge your understanding of how the modified Tinythreads library works.

    For that, consider the Tinythreads source code and the following code (excerpt of a3p1.c) to answer a few questions:  
    1  int main() {  
    2      piface_init();    
    3      spawn(computePower, 0);  
    4      computePrimes(1);  
    5  }

    **1. Create a file called _"Answers.txt" and_** **add the answers to the following questions**

    1.  What is the purpose of the function spawn?
    2.  What is the purpose of the function dispatch?
    3.  What is the purpose of the function yield?
    4.  After finishing the execution of line 3, describe the content of readyQ.
    5.  After finishing the execution of line 3, describe the content of freeQ.
    6.  Consider the code above and the a3p1.img kernel from Pat 1. Which task executes first? Why?
    7.  As they are, functions computePower and computePrimes execute indefinitely, i.e, never return. However, and considering the a3p1.img kernel, these functions are executed concurrently. How?
    8.  Again, computePower and computePrimes never return. However, consider a situation when these functions return. This implies that the tiny thread assigned to execute the task will terminate. Consequently, if you want or need to execute a task again, you might need to track which tiny threads terminated. One approach is to keep information about the terminated threads in a list called doneQ. Thus, where in lib/tinythreads.c, would add the tiny thread that terminated into doneQ?

    #### 2. Submitting results

    -   For Assignment 3 Part 2, one student in the group must upload (click on the title of this section) the following files:
        -   Answers.txt
    -   DON'T submit compressed files, i.e., .zip or .rar files.
    -   All students in the group are equally responsible for the submitted source code.
        -   The group ensures that the submitted code does not include cheating and plagiarism issues.

    ---

    ## Congratulations!!!!!
- 
____
-   ![Assignment](https://bb.hh.se/images/ci/sets/set12/assignment_on.svg)

    ### [Assignment 3 - Part 3 (click to submit results)](https://bb.hh.se/webapps/assignment/uploadAssignment?content_id=_433512_1&course_id=_14168_1&group_id=&mode=view)

    Attached Files:

    -    [![File](https://learn.content.blackboardcdn.com/3900.48.0-rel.18+c7edfda/images/ci/ng/cal_year_event.gif) a3p3.expected.img](https://bb.hh.se/bbcswebdav/pid-433512-dt-content-rid-5710529_1/xid-5710529_1) (19.949 KB)

    ### Cooperative multitasking using TinyThreads

    The objective of Part 3 is to implement cooperative multitasking using TinyThreads.

    In cooperative multitasking, multiple tasks are executed concurrently and voluntarily yield control to another task.

    #### 1. a3p3 folder/directory

    1.  Make a copy of the a3p1 folder/directory and rename it to a3p3.
    2.  In a3p3, rename a3p1.c to a3p3.c.
    3.  Edit Makefile and change MAINFILE = a3p3.
    4.  Edit a3p3.c and implement
        1.  void computeExponential(int seg)
            -   It will compute and display the result of the iexp function in a particular segment in the LED.
                -   If seg is odd, the function displays the fraction part of iexp, the integer part otherwise.
        2.  void toggle_led(int seg)
            -   It Will toggle the state of the LED.
    5.  Edit lib/piface.c and implement the following functions (already declared):
        1.  void print_at_seg(int seg, int num)
            -   The LCD can be divided into 4 segments. Each segment (top_left, top_right, bottom_left and bottom_right) can be used by a thread to present the output result of its running function. See the example illustrated below:
            -
            ![](https://bb.hh.se/bbcswebdav/pid-433512-dt-content-rid-5469028_1/xid-5469028_1)  
                 
            -   To position the cursor in the PiFace Display, you might find it useful to use void piface_set_cursor(uint8_t col, uint8_t row) in lib/piface. This function was inspired by the piface library created by Thomas Preston <thomas.preston@openlx.org.uk> .
    6.  Edit a3p3.c and replace the calls to PUTTOLDC("T%i: %i", seg, W) with print_at_seg(seg, W).
        -   For example, considering the computePower function, replace the instruction PUTTOLDC("T%i: %i", pos, n*n) with print_at_seg(pos, n*n);
    7.  To test, compile the code and boot the RPi using the newly created kernel, i.e., a3p3.img.
    8.  DON'T submit compressed files, i.e., .zip or .rar files.
    9.  All students in the group are equally responsible for the submitted source code.
        -   The group ensures that the submitted code does not include cheating and plagiarism issues.

    #### 3. Cooperative multitasking

    1.  Edit a3p3.c and change the main file to:  
        int main() {  
            led_init();  
            piface_init();  
            piface_clear();  
            piface_puts("DT8025 - A3P3");  
            RPI_WaitMicroSeconds(2000000);  
            piface_clear();  
            spawn(computePower, 0);  
            spawn(computePrimes, 1);  
            spawn(computeExponential, 2);  
            spawn(computeExponential, 3);  
            toggle_led(4);  
        }

    2.  Compile the code and boot the RPi using the newly created kernel, i.e., a3p3.img.
        -   A successful kernel creation and installation shall enable you to visualize on the PiFace Display the outcome of the cooperative multitasking, including the LED blocking periodically. It should be similar to a3p1.expected.img.
    3.  Now, edit a3p3.c and change the main file to:  
        int main() {  
            led_init();  
            piface_init();  
            piface_clear();  
            piface_puts("DT8025 - A3P3");  
            RPI_WaitMicroSeconds(2000000);  
            piface_clear();  
            spawn(computePower, 0);  
            spawn(computePower, 1);  
            spawn(computePrimes, 2);  
            spawn(computePrimes, 3);  
            spawn(computeExponential, 4);  
            spawn(computeExponential, 5);  
            toggle_led(6);  
        }
    4.  Compile the code and boot the RPi using the newly created kernel, i.e., a3p3.img.
        -   Does it work? Create a file called Answers.txt and the explanation for why this new kernel is not working as expected.

    #### 2. Submitting results

    -   For Assignment 3 Part 2, one student in the group must upload (click on the title of this section) the following files:
        -   Answers.txt
        -   a3p3.c
        -   piface.c
        -   led.c
    -   DON'T submit compressed files, i.e., .zip or .rar files.
    -   All students in the group are equally responsible for the submitted source code.
        -   The group ensures that the submitted code does not include cheating and plagiarism issues.

    ---

    ## Congratulations!!!!!
    
    $log_2{(23)}\cdot 10^{2}$
