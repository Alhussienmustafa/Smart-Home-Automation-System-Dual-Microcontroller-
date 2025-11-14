#include "interface.h"

void Master_Init(void) {
	LCD_Init();
	DIO_voidSetPinDir(PORTB_ID, PIN4_ID, PIN_OUTPUT); // SS Output
	DIO_voidSetPinValue(PORTB_ID, PIN4_ID, PIN_HIGH); // Idle = HIGH
	SPI_masterInit(CLOCK_32, SPI_MODE3);

	UART_t uart_cfg = {
			.baudRate = 9600,
			.ASYNC_DSM = True,
			.mode = DISABLED,
			.select = ONE_BIT
	};
	UART_init(&uart_cfg);
}

// always toggle SS inside this function
void Master_SendCommand(u8 cmd) {
	DIO_voidSetPinValue(PORTB_ID, PIN4_ID, PIN_LOW);  // Select Slave
	SPI_sendReceiveByte(cmd);
	DIO_voidSetPinValue(PORTB_ID, PIN4_ID, PIN_HIGH); // Deselect Slave
}


// LED Menu
void vManual_LEDMenu(void) {
	LCD_ClearScreen();
	LCD_DisplayStringRowColumn(0,0,"0:LED1ON 1:OFF");
	LCD_DisplayStringRowColumn(1,0,"2:LED2ON 3:OFF");

	u8 cmd = KEYPAD_getPressedKey();
	_delay_ms(300);

	if(cmd == '0' || cmd == '1' || cmd == '2' || cmd == '3') {
		Master_SendCommand(cmd);
		LCD_ClearScreen();
		switch(cmd) {
		case '0':
			LCD_DisplayStringRowColumn(0, 0, "LED 1 ON");
			break;
		case '1':
			LCD_DisplayStringRowColumn(0, 0, "LED 1 OFF");
			break;
		case '2':
			LCD_DisplayStringRowColumn(0, 0, "LED 2 ON");
			break;
		case '3':
			LCD_DisplayStringRowColumn(0, 0, "LED 2 OFF");
			break;
		default: break;
		}
		_delay_ms(500);
	}
}


// Fan Menu
void vManual_FanMenu(void) {
	LCD_ClearScreen();
	LCD_DisplayStringRowColumn(0,0,"4:OFF 5:L1 6:L2");
	LCD_DisplayStringRowColumn(1,0,"7:L3  8:SD 9:TS");

	u8 cmd = KEYPAD_getPressedKey();
	_delay_ms(300);

	if(cmd >= '4' && cmd <= '9') {
		Master_SendCommand(cmd);
		LCD_ClearScreen();
		switch(cmd) {
		case '4':
			LCD_DisplayStringRowColumn(0, 0, "Level 0 ON");
			break;
		case '5':
			LCD_DisplayStringRowColumn(0, 0, "Level 1 ON");
			break;
		case '6':
			LCD_DisplayStringRowColumn(0, 0, "Level 2 ON");
			break;
		case '7':
			LCD_DisplayStringRowColumn(0, 0, "Level 3 ON");
			break;
		case '8':
			LCD_DisplayStringRowColumn(0, 0, "Wel3aaa!!");
			break;
		case '9':
			LCD_DisplayStringRowColumn(0, 0, "TEMPRATURE MODE");
			break;
		default: break;
		}
		_delay_ms(500);
	}
}


// Manual System
void vManual_System(void) {
	while(1) {
		LCD_ClearScreen();
		LCD_DisplayStringRowColumn(0,0,"1: LED Menu");
		LCD_DisplayStringRowColumn(1,0,"2: Fan Menu");

		u8 choice = KEYPAD_getPressedKey();
		_delay_ms(300);

		if(choice == '1') {
			vManual_LEDMenu();
		} else if(choice == '2') {
			vManual_FanMenu();
		} else {
			LCD_ClearScreen();
			LCD_DisplayString("Invalid");
			_delay_ms(500);
		}
	}
}

// Bluetooth Mode
void vBluetooth_Mode(void) {
	u8 data;
	while(1) {
		LCD_ClearScreen();
		LCD_DisplayStringRowColumn(0, 0, "BluetoothModeOn");
		UART_receiveByte(&data);   // Receive from phone
		Master_SendCommand(data);
		LCD_ClearScreen();
		switch(data) {
		case '0':
			LCD_DisplayStringRowColumn(0, 0, "LED 1 ON");
			break;
		case '1':
			LCD_DisplayStringRowColumn(0, 0, "LED 1 OFF");
			break;
		case '2':
			LCD_DisplayStringRowColumn(0, 0, "LED 2 ON");
			break;
		case '3':
			LCD_DisplayStringRowColumn(0, 0, "LED 2 OFF");
			break;
		case '4':
			LCD_DisplayStringRowColumn(0, 0, "Level 0 ON");
			break;
		case '5':
			LCD_DisplayStringRowColumn(0, 0, "Level 1 ON");
			break;
		case '6':
			LCD_DisplayStringRowColumn(0, 0, "Level 2 ON");
			break;
		case '7':
			LCD_DisplayStringRowColumn(0, 0, "Level 3 ON");
			break;
		case '8':
			LCD_DisplayStringRowColumn(0, 0, "Wel3aaa!!");
			break;
		case '9':
			LCD_DisplayStringRowColumn(0, 0, "TEMPRATURE MODE");
			break;
		default: break;
		}
		_delay_ms(500);
	}
}

void Password_init(void) {
	u8 def[PASS_LEN] = {'1','2','3','4'};
	for (u8 i = 0; i < PASS_LEN; i++) {
		EEPROM_writeByte(PASS_ADDR + i, def[i]);
	}
}

static void Password_enter(u8 *buf) {
	LCD_ClearScreen();
	LCD_DisplayString("Enter Pass:");
	for (u8 i = 0; i < PASS_LEN; i++) {
		u8 key;
		do {
			key = KEYPAD_getPressedKey();
		} while (!(key >= '0' && key <= '9'));

		buf[i] = key;
		LCD_DisplayChar('*');
		_delay_ms(450);
	}
}

u8 Password_check(void) {
	u8 saved, entered[PASS_LEN];
	u8 tries = 0;

	while (tries < MAX_TRIES) {
		Password_enter(entered);

		u8 ok = 1;
		for (u8 i = 0; i < PASS_LEN; i++) {
			EEPROM_readByte(PASS_ADDR + i, &saved);
			if (entered[i] != saved) {
				ok = 0;
			}
		}

		if (ok) {
			LCD_ClearScreen();
			LCD_DisplayString("Correct Password");
			_delay_ms(1000);
			return 1;
		} else {
			LCD_ClearScreen();
			LCD_DisplayString("Wrong!");
			_delay_ms(1000);
			tries++;
		}
	}

	LCD_ClearScreen();
	LCD_DisplayString("System Locked!");
	while (1);
	return 0;
}


