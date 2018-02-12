from https://www.youtube.com/watch?v=b381xvbp6pw&list=PLWy-YwxbAu8FDpD2saP1p6IFHgvbzODyc&index=8


#include "mbed.h"

Serial pc(PA_2, PA_3);	// Tx, Rx
Serial esp8266(PC_1, PC_0);	// Tx, Rx

DigitalOut red(LED_RED);
DigitalOut green(LED_GREEN);
DigitalOut blue(LED_BLUE);

int main() {
	red = 1;
	green = 1;
	blue = 1;
	
	pc.printf("Hello World!\n");
	
	while (true) {
		if (pc.readable()) {
			char command = pc.getc();
			
			switch (command) {
				case 'R':
					red = 0;
					break;
				case 'G':
					green = 0;
					break;
				case 'B':
					blue = 0;
					break;
				case 'r':
					red = 1;
					break;
				case 'g':
					green = 1;
					break;
				case 'b':
					blue = 1;
					break;
			}
		}
	}
}
