#ifndef CONSTANTS_H
#define CONSTANTS_H

// Instances with linear bin costs where W_k = C_k
static const int BIN_TYPES = 5;
static const int BIN_SIZE [] = { 60,
                                 80,
                                100,
                                120,
                                150};
static const int MAX_COST = BIN_SIZE[BIN_TYPES - 1];

#endif