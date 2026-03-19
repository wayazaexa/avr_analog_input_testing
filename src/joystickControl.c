#include <stdio.h>
#include "joystickControl.h"

void print_horz_vert(uint16_t horz, uint16_t vert, bool *hasChanged) {
	static uint16_t oldhorz = 0;
	static uint16_t oldvert = 0;

	if (horz != oldhorz) {
		printf("Horz: %u\n", horz);
		oldhorz = horz;
		*hasChanged = true;
	}
	if (vert != oldvert) {
		printf("Vert: %u\n", vert);
		oldvert = vert;
		*hasChanged = true;
	}
}

bool handleInput(uint16_t horz, uint16_t vert, bool *hasChanged, int8_t *num) {
	bool shouldPrint = false;
	if (*hasChanged) {
		if (horz < 300) { // RIGHT
			shouldPrint = true;

			if (++(*num) == 7) {
				*num = 1;
			}
		}
		else if (horz > 700) { // LEFT
			shouldPrint = true;

			if (--(*num) == 0) {
				*num = 6;
			}
		}

		if (vert > 700) { // UP
			shouldPrint = true;
			*num += 2;

			if (*num > 6) {
				*num -= 6;
			}
		}
		else if (vert < 300) { // DOWN
			shouldPrint = true;
			*num -= 2;

			if (*num < 1) {
				*num += 6;
			}
		}
		*hasChanged = false;
	}
	return shouldPrint;
}
