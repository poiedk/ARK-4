/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

#ifndef REBOOT_H
#define REBOOT_H

#include "main.h"
#include <rebootconfig.h>

extern u8* rebootbuffer;
extern u32 size_rebootbuffer;

// Sony Reboot Buffer Loader
extern int (* _LoadReboot)(void *, unsigned int, void *, unsigned int);

void buildRebootBufferConfig(int rebootBufferSize);
int LoadReboot(void * arg1, unsigned int arg2, void * arg3, unsigned int arg4);


#endif
