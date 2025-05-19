#include "black_box.h"

void set_time(void) {
    
    if(time_init_flag == 0) // Display 1st time when Function is called
    {
        time_init_flag = 1; // Set the Flag to High
        time_print_flag = 0; // Reset the time print flag
        clcd_print("HH:MM:SS", LINE1(4)); // Print the HH:MM:SS in the First Row on CLCD
        
        /* Get the Current Hour, Minute and Seconds from RTC */
        hour = ((time[0] - 48) * 10) + (time[1] - 48); 
        min = ((time[3] - 48) * 10) + (time[4] - 48);
        sec = ((time[6] - 48) * 10) + (time[7] - 48);
        
    }
    
    if(time_print_flag == 0) // Flag for Displaying the TIME on CLCD
    {
        time_print_flag = 1; 
        /* Print Hour */
        clcd_putch((hour / 10) + 48, LINE2(4));
        clcd_putch((hour % 10) + 48, LINE2(5));
        clcd_putch(':', LINE2(6));
        /* Print Minutes */
        clcd_putch((min / 10) + 48, LINE2(7));
        clcd_putch((min % 10) + 48, LINE2(8));
        clcd_putch(':', LINE2(9));
        /* Print Seconds */
        clcd_putch((sec / 10) + 48, LINE2(10));
        clcd_putch((sec % 10) + 48, LINE2(11));
    }
    
    key_press = read_switches(STATE_CHANGE); // Read the Switch Press
    
    
    if (key_press == 1) { // If switch 1 is Pressed
        if (field_select == 0) { // If field Selected is Hour
            if (++hour > 23) { // Increment the Hour till 23 and then again reset it
                hour = 0;
            }
        }
        if (field_select == 1) { // If Field Selected is Minutes
            if (++min > 59) { // Increment the Minutes Till 59 and then again reset it
                min = 0;
            }
        }
        if (field_select == 2) { // If Field Selected is Seconds
            if (++sec > 59) { // Increment the Seconds Till 59 and then again reset it
                sec = 0;
            }
        }
    }
    
    if(key_press == 2) // Switch Fields when Switch 2 is Pressed
    {
        if(++field_select > 2) // Increment field select till 2 and then again reset it
        {
            field_select = 0;
        }
    }
    
    if(key_press == 11) // If Switch 11 is Pressed
    {
        /* Write the Changed time to RTC and Return to Dashboard */
        write_ds1307(HOUR_ADDR, ((hour / 10) << 4) | (hour % 10));
        write_ds1307(MIN_ADDR, ((min / 10) << 4) | (min % 10));
        write_ds1307(SEC_ADDR, ((sec / 10) << 4) | (sec % 10));
        CLEAR_DISP_SCREEN;
        state = e_dashboard;
    }
    
    if(key_press == 12) // If Switch 12 is Pressed
    {
        /* Return to Dashboard without saving the changed Time*/
        CLEAR_DISP_SCREEN;
        state = e_dashboard;
    }
    /* Blinking a Black Block on the Selected Field using Non-Blocking Delay */
    
    if(field_select == 0)
    {
        delay1++;
        if(delay1 == 100)
        {
            clcd_putch(0xFF, LINE2(4)); // Putting Black Block on CLCD
            clcd_putch(0xFF, LINE2(5));
        }
        else if(delay1 == 200)
        {
            time_print_flag = 0;
            delay1 = 0;
        }
    }
    if(field_select == 1)
    {
        delay2++;
        if(delay2 == 100)
        {
            clcd_putch(0xFF, LINE2(7));
            clcd_putch(0xFF, LINE2(8));
        }
        else if(delay2 == 200)
        {
            time_print_flag = 0;
            delay2 = 0;
        }
    }
    if(field_select == 2)
    {
        delay3++;
        if(delay3 == 100)
        {
            clcd_putch(0xFF, LINE2(10));
            clcd_putch(0xFF, LINE2(11));
        }
        else if(delay3 == 200)
        {
            time_print_flag = 0;
            delay3 = 0;
        }
    }
}
