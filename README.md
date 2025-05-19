# Car_Black-Box

 Description : 
 * Black Boxes are typically used in any transportation system (ex: Airplanes) that are used for analysis post-crash 
 * and understand the root cause of accidents. Continuous monitoring and logging of events (ex: over-speeding) is critical for 
 * effective usage of black box. 
 * The goal of this project is to implement core functionalities of a care black-box in a PIC based micro-controller supported 
 * by rich peripherals. Events will be logged in EEPROM in this project. 
 * This project can be further extended to any vehicle.
 * 
 * Dashboard : When the system is Booted, it would act like a dashboard which would show the current time, 
    latest occurred event and speed of vehicle.
 
 * Main Menu : The main menu should contain 4 option View Log, Clear Log, Download Log, Set Time
    The UP(key 1) / DOWN(key 2) keys are used to Scroll and Navigate, Key 11 is used to Enter the Menu
    and key 12 is used to come out of Main Menu.
 
 * Maximum 10 Event's can Be LOGGED, and Each Event Size is 12 ( 8 Bytes TIME Data, 2 Bytes EVENT Data, 2 Bytes SPEED Data).
 * 
 * View Log : Can Display Logged Event's, Use Key 1 and Key 2 For scrolling up and Down and Key 12 for returning to main menu
   the Present Menu Should be indicated by "*". 
 * 
 * Clear Log : Clearing the Stored Logs by Resetting Event Count and Address of EEPROM
 * 
 * Download Log : Display all the Stored Log's on tera-term terminal
 * 
 * SET TIME : Used to Set the HOUR, MINUTE and SECOND By changing and Writing New changed TIME to DS1307, 
   The Selected Fields are Indicated Using the Blinking Black Block on CLCD.
