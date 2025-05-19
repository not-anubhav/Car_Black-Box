#include "black_box.h"

void display_main_menu(void) {
    
    if(menu_init_flag == 0) // Displaying the Main menu one time when Initialized
    {
        menu_init_flag = 1; // Make the Flag as 1
        CLEAR_DISP_SCREEN; 
        /* Printing View Log and Clear Log on CLCD when Displayed*/
        clcd_print(menu[menu_index], LINE1(2));
        clcd_print(menu[menu_index + 1], LINE2(2));
        clcd_putch('*', (0x80 + 0)); // Printing Indicator next to Main Menu Options
    }
    
    key_press = read_switches(STATE_CHANGE); // Read Switches
    
    if (key_press == 1 && menu_index > 0) { // Scroll Up Main Menu when Switch 1 is pressed
        CLEAR_DISP_SCREEN;
        menu_index--; // Decrement Menu Index
        clcd_print(menu[menu_index], LINE1(2));
        clcd_print(menu[menu_index + 1], LINE2(2));
        clcd_putch('*', (0x80 + 0));
    }
    
    if (key_press == 2 && menu_index < 3) { // Scroll Down Main Menu when Switch 1 is pressed
        CLEAR_DISP_SCREEN;
        menu_index++; // Increment Menu Index
        clcd_print(menu[menu_index - 1], LINE1(2));
        clcd_print(menu[menu_index], LINE2(2));
        clcd_putch('*', (0xC0 + 0));
    }
    
    if (key_press == 11) { // Press Switch 11 to Enter into a Menu from Main Menu
        CLEAR_DISP_SCREEN;
        switch (menu_index) {
            case 0: // View Log Index
                if(clear_flag == 0) // If log is Not Cleared
                {
                    view_log_index = 0;
                    state = e_view_log;
                }
                else // If Log is Cleared
                {
                    clcd_print("NO DATA !", LINE1(2));
        
                    __delay_ms(1000);
    
                    CLEAR_DISP_SCREEN;
                    menu_init_flag = 0;
                    state = e_main_menu;
                }
                break;
            case 1: // Clear Log Index
                state = e_clear_log;
                break;
            case 2: // Download Log Index
                state = e_download_log;
                break;
            case 3: // SET TIME Index
                /* Reseting Flag and Values For SET TIME Function */
                
                time_init_flag = 0;
                field_select = 0;
                hour = 0;
                min = 0;
                sec = 0;
                delay1 = 0;
                delay2 = 0;
                delay3 = 0;
                state = e_set_time;
                break;
        }
    }
    
    if (key_press == 12) { // Return to Dashboard from Main Menu when SWitch 12 is Pressed
        CLEAR_DISP_SCREEN;
        clear_flag = 0;
        state = e_dashboard;
    }
}
