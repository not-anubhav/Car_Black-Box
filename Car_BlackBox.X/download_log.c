#include "black_box.h"

void download_log() {
    
    if(clear_flag == 0) // If Clear Log Flag is Not Set
    {
        clcd_print("Downloading...", LINE1(2));
    
        puts("TIME     EV SP\n\r"); // Print TIME EV and SP First on Terminal
        puts("\n\r"); // Move to next Line
        for(unsigned int i = 0; i < event_count; i++) // Print Stored Events One By One 
        {
            puts(read_event[i]);
            puts("\n\r"); // Print Each Event on next line 
        }
        
        puts("\n\r");
        
        __delay_ms(1000);
    
        CLEAR_DISP_SCREEN;
        menu_init_flag = 0; // Reset the menu init flag
        state = e_main_menu; // Return to Main Menu
    }
    else // If Clear Log Flag is SET
    {
        clcd_print("NO DATA !", LINE1(2)); // Print NO DATA if Cleared Log is Set on CLCD
        puts("NO DATA !\n\r"); // Print NO DATA if Cleared Log is Set on Terminal
        puts("\n\r"); // Move to New Line
        __delay_ms(1000);
    
        CLEAR_DISP_SCREEN;
        menu_init_flag = 0; // Reset the menu init flag
        state = e_main_menu; // Return to Main Menu
    }
}
