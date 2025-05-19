#ifndef BLACK_BOX_H
#define BLACK_BOX_H

#include <xc.h>

#include "clcd.h"
#include "matrix_keypad.h"
#include "uart.h"
#include "ds1307.h"
#include "i2c.h"
#include "External_EEPROM.h"

#define _XTAL_FREQ 20000000
#define CHANNEL 0x04
 
#define MAX_EVENTs 10 // Max Events we can Store
#define EVENT_SIZE 12 // Event Size, TIME EV and SP

/* Variable Declarations and Initialization */

char time[9] = "00:00:00";
    
char event[9][3]  = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C_"};

char menu[4][15] = {"View Log", "Clear Log", "Download Log", "SET TIME"};

char read_event[10][15];
    
unsigned int event_index = 0;

unsigned int menu_index = 0;

unsigned int view_log_index = 0;

unsigned int event_count = 0;
    
unsigned int adc_val;

unsigned char start_addr = 0x00;

unsigned char key_press = 0;

unsigned char clear_flag = 0;

unsigned char menu_init_flag = 0;

unsigned char time_init_flag = 0;

unsigned char time_print_flag = 0;

unsigned int hour = 0;

unsigned int min = 0;

unsigned int sec = 0;

unsigned field_select = 0;

unsigned char delay1 = 0;

unsigned char delay2 = 0;

unsigned char delay3 = 0;

/* RTC */
unsigned char clock_reg[3];

/* Enum for maintaining the app state */
typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log
} State_t;


State_t state; // App state

//Function declarations

//Dashboard function declaration
void view_dashboard(void);

void get_time(void);

void display_time(void);

//Storing events function declaration
void event_store(void);

// Writing events function declaration
void write_event(unsigned char EEPROM_addr);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(void);

//Set time function declaration
void set_time(void);

//Download log function _declaration
void download_log(void);

//Clear log function declaration
void clear_log(void);

// Function Declaration for init ADC
void init_ADC(); 

// Function Declaration for read ADC
int read_adc(char channel); 

#endif