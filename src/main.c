#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "analogRead.h"
#include "uart.h"
#include "max72xx.h"

#define VERT_PIN 0
#define HORZ_PIN 1

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (a & (1U << b))

void clear(void);
void draw(int num);
void print_horz_vert(uint16_t horz, uint16_t vert, bool *hasChanged);
bool handleInput(uint16_t horz, uint16_t vert, bool *hasChanged, int8_t *num);

void clear(void) {
	for(int col = 3; col < 6; col++) {
		max7219b_clr(col, 3);
		max7219b_clr(col, 4);
		max7219b_clr(col, 5);
	}
}

void draw(int num) {
	if(num == 1) {
		max7219b_set(4, 4);
	}
	else if(num == 2) {
		max7219b_set(3, 3);
		max7219b_set(5, 5);
	}
	else if(num == 3) {
		max7219b_set(3, 3);
		max7219b_set(4, 4);
		max7219b_set(5, 5);
	}
	else if(num == 4) {
		max7219b_set(3, 3);
		max7219b_set(3, 5);
		max7219b_set(5, 3);
		max7219b_set(5, 5);
	}
	else if(num == 5) {
		max7219b_set(3, 3);
		max7219b_set(3, 5);
		max7219b_set(4, 4);
		max7219b_set(5, 3);
		max7219b_set(5, 5);
	}
	else if(num == 6) {
		max7219b_set(3, 3);
		max7219b_set(3, 4);
		max7219b_set(3, 5);
		max7219b_set(5, 3);
		max7219b_set(5, 4);
		max7219b_set(5, 5);
	}
	max7219b_out();
}

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

int main(void) {
	BIT_CLEAR(DDRC, VERT_PIN);
	BIT_CLEAR(DDRC, HORZ_PIN);

	init_serial();
	max7219_init();

	int8_t num = 1;
	bool hasChanged = false;
	bool shouldPrint;
	draw(num);

	while (1) {

		// Läs joystick
		uint16_t horz = analogRead(HORZ_PIN);
		uint16_t vert = analogRead(VERT_PIN);

		// Printa horz och vert, men bara om de ändrats
		print_horz_vert(horz, vert, &hasChanged);

		// Kontrollera om vi läst en signal som innebär modifiering av num.
		// LEFT: -1, RIGHT: +1, UP: +2, DOWN: -2
		shouldPrint = handleInput(horz, vert, &hasChanged, &num);

		if (shouldPrint) {
			shouldPrint = false;
			clear();
			printf("num: %d\n", num);
			draw(num);
		}
	}
	return 0;
}