#include "black_box.h"

void view_dashboard(void) {
    /* Print TIME EV and SP string on first row*/
    clcd_print("TIME", LINE1(2));
    clcd_print("EV", LINE1(9));
    clcd_print("SP", LINE1(12));
    /* Print TIME EV and SP values on 2nd Row */
    display_time(); // Call display time function for displaying time
    clcd_print(event[event_index], LINE2(9)); // Display Event

    key_press = read_switches(STATE_CHANGE); // Read Switch Press
    
    if (key_press == 11) { // If Switch 11 is pressed, Change state to Main Menu
        menu_index = 0;
        menu_init_flag = 0;
        event_reader(); // Read Store Events From External EEPROM
        state = e_main_menu;
    }
    else
    {
        if (key_press == 1) 
        {
            if (event_index == 8) // If Event Index Becomes 8, and Key 1 is Pressed 
            {
                event_index = 1; // Make Event Index as 1
                event_store(); // Store the new Event
            } 
            else
            {
                if (++event_index > 7) // Increment Event Index If Switch 1 is Pressed 
                {
                    event_index = 7; // Keep Index as 7, If it becomes greater than 7
                }
                event_store(); // Store the new Event
            }
        }

        if (key_press == 2) // Decrement Event Index If Switch 2 is Pressed
        {
            if (event_index == 8) // If Event Index Becomes 8, and Key 1 is Pressed
            {
                event_index = 1; // Make Event Index as 1
                event_store(); // Store the new Event
            }
            else if (event_index > 0)
            {
                if (--event_index < 1) // Decrement Event Index If Switch 2 is Pressed
                {
                    event_index = 1; // Keep Index as 1, If it becomes less than 1
                }
                event_store(); // Store new Event
            }
        }

        if (key_press == 3) { // Collision Event If switch 3 is pressed
            if(event_index != 8)
            {
                event_index = 8;
                event_store();
            }
        }
        
        clcd_print(event[event_index], LINE2(9)); // Display the Event on CLCD

        adc_val = (unsigned int) (read_adc(CHANNEL) / 10.33); // Calculate the Speed

        /* Display the Speed on CLCD */
        
        clcd_putch(((adc_val / 10) + 48), LINE2(12)); 

        clcd_putch(((adc_val % 10) + 48), LINE2(13));
    }
}

/* Write the EVENT on External EEPROM */

void write_event(unsigned char EEPROM_addr)
{
    for (unsigned char i = 0; i < 8; i++) // Write 8 Bytes of TIME
    {
        write_external_eeprom(EEPROM_addr++, time[i]);
    }

    for (unsigned char j = 0; j < 2; j++) // Write 2 Bytes of EVENT 
    {
        write_external_eeprom(EEPROM_addr++, event[event_index][j]);
    }
    /* Write 2 Bytes of SPEED */
    write_external_eeprom(EEPROM_addr++, ((adc_val / 10) + 48));
    write_external_eeprom(EEPROM_addr++, ((adc_val % 10) + 48));
}

void event_store(void)
{
    unsigned char EEPROM_addr;
    if(event_count > MAX_EVENTs - 1) // If Event Count exceeds 10
    {
        /* Shift Events */
        event_count = MAX_EVENTs;
        for(unsigned char i = 1; i < MAX_EVENTs; i++)
        {
            unsigned char copy_from = start_addr + (i * EVENT_SIZE);
            unsigned char copy_to = start_addr + ((i - 1) * EVENT_SIZE);
            
            for(unsigned char j = 0; j < EVENT_SIZE; j++)
            {
                unsigned char data = read_external_eeprom(copy_from++);
                write_external_eeprom(copy_to++, data);
            }
        }
        /* Calculate EEPROM address from where Event should be stored */
        EEPROM_addr = start_addr + ((MAX_EVENTs - 1) * EVENT_SIZE); // Copy new event to last position address
    }
    else // If Event Count is Less than 10
    {
        /* Calculate EEPROM address from where Event should be stored */
        EEPROM_addr = start_addr + (event_count * EVENT_SIZE);
        event_count++; // Increment Event Count
    }
    
    write_event(EEPROM_addr); // Call write event function to write the events on External EEPROM
}