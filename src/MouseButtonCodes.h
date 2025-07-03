#pragma once
///<TAKEN FROM SDL MOUSE CODES>///
#define Knight_BUTTON_LEFT     1
#define Knight_BUTTON_MIDDLE   2
#define Knight_BUTTON_RIGHT    3
#define Knight_BUTTON_X1       4
#define Knight_BUTTON_X2       5

#define Knight_BUTTON_MASK(X)  (1u << ((X)-1))
#define Knight_BUTTON_LMASK    Knight_BUTTON_MASK(Knight_BUTTON_LEFT)
#define Knight_BUTTON_MMASK    Knight_BUTTON_MASK(Knight_BUTTON_MIDDLE)
#define Knight_BUTTON_RMASK    Knight_BUTTON_MASK(Knight_BUTTON_RIGHT)
#define Knight_BUTTON_X1MASK   Knight_BUTTON_MASK(Knight_BUTTON_X1)
#define Knight_BUTTON_X2MASK   Knight_BUTTON_MASK(Knight_BUTTON_X2)
