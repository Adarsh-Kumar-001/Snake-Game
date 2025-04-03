#ifndef SCORES_H
#define SCORES_H

#define MAX_LINE_LENGTH 50
#define MAX_USERS 100

#include <stdint.h>

void updatehighscore(const char* user,uint16_t curr_score);

#endif