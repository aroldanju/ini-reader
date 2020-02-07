/*
 *  INI reader - Simple INI file reader
 *  Copyright (C) 2019 A. Roldán
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 	arldn.dev -at- gmail.com
 */

#ifndef __ini_h
#define __ini_h

#define INI_MAX_CONFIGURATIONS	32
#define INI_MAX_SECTIONS	    8

struct _ini_configuration {
    char key[16];
    char value[256];
};

struct _ini_section {
    char name[16];
    unsigned int                configurations;
    struct _ini_configuration   configuration[INI_MAX_CONFIGURATIONS];
};

typedef struct _ini {
    unsigned int        sections;
    struct _ini_section section[INI_MAX_SECTIONS];
} INI;

const char *ini_get_value(const INI* ini, const char* section, const char* name);

int ini_save(const char* filename, INI* ini) ;

int ini_load(INI* ini, const char *filename);

#endif  /* __ini_h */