
#include "program.h"
#define F_PCU 8000000ul

int main(void) {
	Slave_Init();

	while(1) {
		u8 cmd = SPI_sendReceiveByte(0xFF);

		if(cmd >= '0' && cmd <= '3') {
			vManual_LEDMenu(cmd);
		}
		else if(cmd >= '4' && cmd <= '9') {
			vManual_FanMenu(cmd);
		}
		else {
			Buzz_Action();
		}
	}
	return 0;
}
