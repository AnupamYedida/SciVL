/*-------------test_pong.h----------------------------------------------------//
*
* Purpose: Work with the test function to make a pong game
*
*-----------------------------------------------------------------------------*/

#ifndef TEST_PONG_H
#define TEST_PONG_H

#include "../include/GL_setup.h"

void play_pong(Param &par);
void move_pendulum(Param &par);

// Function to update fft arrays
void update_fft(Param &par);
void draw_fft(Param &par);

#endif
