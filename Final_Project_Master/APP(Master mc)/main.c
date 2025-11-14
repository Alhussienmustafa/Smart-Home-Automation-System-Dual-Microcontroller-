#include "interface.h"
#define F_PCU 8000000ul

int main(void)
{
	// Initialize all peripherals
	Master_Init();
	Password_init();
	if (!Password_check())
		return 0;

	while(1)
	{
		LCD_ClearScreen();
		LCD_DisplayStringRowColumn(0,0,"1: Manual Mode");
		LCD_DisplayStringRowColumn(1,0,"2: Bluetooth");

		u8 choice = KEYPAD_getPressedKey();
		_delay_ms(300);

		if(choice == '1') {
			vManual_System();   // Manual Menu (LED / Fan)
		}
		else if(choice == '2') {
			vBluetooth_Mode();  // Forward commands from UART (Bluetooth) to Slave
		}
		else {
			LCD_ClearScreen();
			LCD_DisplayString("Invalid Choice");
			_delay_ms(500);
		}
	}

	return 0;
}

