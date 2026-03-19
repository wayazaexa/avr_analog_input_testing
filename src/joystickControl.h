#ifndef JOYSTICK_CONTROL_H_
#define JOYSTICK_CONTROL_H_

#include <stdbool.h>
#include <stdint.h>

void print_horz_vert(uint16_t horz, uint16_t vert, bool *hasChanged);
bool handleInput(uint16_t horz, uint16_t vert, bool *hasChanged, int8_t *num);

#endif
