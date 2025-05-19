#include "black_box.h"

void view_log()
{
    clcd_print("TIME", LINE1(2));
    clcd_print("EV", LINE1(9));
    clcd_print("SP", LINE1(12));
    
    key_press = read_switches(STATE_CHANGE); // Read the Switch Press
    
    if (key_press == 1) { // Switch 1 for Scroll Up Log's
        if (view_log_index > 0) {
            CLEAR_DISP_SCREEN;
            view_log_index--; 
        }
    }
    
    if (key_press == 2) { // Switch 2 for Scroll Down Log's
        if (view_log_index < (event_count - 1))
        {
            CLEAR_DISP_SCREEN;
            if(view_log_index > (MAX_EVENTs - 1)) // Index Should Not Exceed Maximum recorded Event's
            {
                view_log_index = (MAX_EVENTs - 1); // Keeping it inbound
            }
            else
            {
                view_log_index++; 
            }
        }
    }
    
    if (key_press == 12) { // Return to Main Menu from View Log's if Switch 12 is Pressed
        CLEAR_DISP_SCREEN;
        menu_init_flag = 0;
        state = e_main_menu;
    }

    clcd_putch(view_log_index + 48, LINE1(0)); // Print the Log Index
    clcd_print(read_event[view_log_index], LINE2(0)); // Print the Stored Log's
}

/* Function For Reading Store Event from External EEPROM */

void event_reader(void) 
{
    for(unsigned int i = 0; i < event_count; i++)
    {
        unsigned int read_start_addr = start_addr + (i * EVENT_SIZE); // Calculate event start address
        unsigned int addr = read_start_addr;
        
        for(int j = 0; j < 15; j++)
        {
            if(j == 8 || j == 11)
            {
                read_event[i][j] = ' ';
            }
            else if(j == 14)
            {
                read_event[i][j] = '\0';
            }
            else
            {  
                read_event[i][j] = read_external_eeprom(addr++);
            }
        }
    }
}
