#include "black_box.h"

void clear_log(void)
{ 
    if(clear_flag == 0) // If Log is Not previously Cleared
    {
        clear_flag = 1; // Set the Clear Flag
        
        clcd_print("Clearing...", LINE1(2)); // Print on CLCD
     
        event_count = 0; // Reset Event Count

        start_addr = 0x00; // Reset Starting Address
    
        __delay_ms(1000); 
    
        CLEAR_DISP_SCREEN; // Clearing Screen
        menu_init_flag = 0; // Reset Main Menu Initialization Flag
        state = e_main_menu; // Change state to Main Menu to return to Main Menu
    }
    else // If clear Lo Flag is 1
    {
        clcd_print("NO DATA !", LINE1(2)); // Display NO DATA on CLCD
        
        __delay_ms(1000);
    
        CLEAR_DISP_SCREEN; // Clearing Screen
        menu_init_flag = 0; // Reset Main Menu Initialization Flag
        state = e_main_menu; // Change state to Main Menu to return to Main Menu
    }
}
