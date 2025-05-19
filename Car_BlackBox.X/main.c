#include "black_box.h"

void init_config()
{
    init_matrix_keypad(); // Initialize matrix keypad
    init_clcd(); // Initialize CLCD
    init_ADC(); // Initialize ADC
    init_uart(); // Initialize UART
    /*  Initialize I2C */
    init_i2c(); 
	init_ds1307();
    // Initial state 
    state = e_dashboard; 
}

void main(void) 
{
    init_config(); // Load Config
    get_time(); // Load Time
    adc_val = (unsigned int) (read_adc(CHANNEL) / 10.33); // Load Speed
    event_store(); // Store 1st ON EVENT

    while(1)
    {
        get_time();
        switch (state)
        {
            case e_dashboard:
                // Display dashboard
                view_dashboard();
                break;
            
            case e_main_menu:
                // Display dashboard
                display_main_menu();
                break;
            
            case e_view_log:
                // Display Log
                view_log();
                break;
                 
            case e_download_log:
                //Download Log
                download_log();
                break;
                
            case e_clear_log:
                // Clear Log
                clear_log();
                break;
                
                      
            case e_set_time:
                // Set Time
                set_time();
                break;
                
        }
    }   
}

