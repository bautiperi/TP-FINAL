/*
 * ships.h
 *
 *  Created on: Jan 4, 2024
 *      Author: bauti
 */

#ifndef SHIPS_H_
#define SHIPS_H_

#include "map.h"

int ships_create (int diff, int mapa[][COL]);
void ships_update (int mapa[][COL]);


#endif /* SHIPS_H_ */
