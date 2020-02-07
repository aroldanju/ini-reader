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

#include "ini.h"

#include <stdio.h>
#include <string.h>

const char *ini_get_value(const INI* ini, const char* section, const char* name)    {
    int i, j;

    for (i = 0; i < ini->sections; i++) {
        if (strcmp(ini->section[i].name, section) == 0) {
            for (j = 0; j < ini->section[i].configurations; j++) {
                if (strcmp(ini->section[i].configuration[j].key, name) == 0) {
                    return ini->section[i].configuration[j].value;
                }
            }
        }
    }

    return NULL;
}

int ini_save(const char* filename, INI* ini) {
    FILE *file;
    int i, j;

    file = fopen(filename, "w");
    if (!file) {
#ifdef __INI_DEBUG__
        printf("ini_save(): error creating INI file %s\n", filename);
#endif
        return 1;
    }

    for (i = 0; i < ini->sections; i++) {
        fwrite("[", 1, 1, file);
        fwrite(ini->section[i].name, strlen(ini->section[i].name), 1, file);
        fwrite("]\n", 2, 1, file);
        for (j = 0; j < ini->section[i].configurations; j++) {
            fwrite(ini->section[i].configuration[j].key, strlen(ini->section[i].configuration[j].key), 1, file);
            fwrite("=", 1, 1, file);
            fwrite(ini->section[i].configuration[j].value, strlen(ini->section[i].configuration[j].value), 1, file);
            fwrite("\n", 1, 1, file);
        }
        fwrite("\n", 1, 1, file);
    }

    fclose(file);

    return 0;
}

int ini_load(INI* ini, const char *filename) {
    FILE* file;
    char *tkn;
    char buffer[256];
    const int bufferLength = 256;

    file = fopen(filename, "r");
    if (!file) {
#ifdef __INI_DEBUG__
        printf("ini_load(): error loading INI file %s\n", filename);
#endif
        return 1;
    }

    struct _ini_section *section = NULL;

    while(fgets(buffer, bufferLength, file)) {
        if (buffer[0] != '#' && buffer[0] != ' ' && buffer[0] != '\n') {
            if (buffer[strlen(buffer) - 1] == '\n') {
                buffer[strlen(buffer) - 1] = '\0';
            }

            if (buffer[0] == '[') {
                buffer[strlen(buffer) - 1] = '\0';
                section = &ini->section[ini->sections];
                strncpy(ini->section[ini->sections].name, (buffer + 1), strlen(buffer));
                ini->sections++;
            }
            else {
                if (section) {
                    tkn = strtok(buffer, "=");
                    if (tkn) {
                        strcpy(section->configuration[section->configurations].key, tkn);
                        tkn = strtok(NULL, "=");
                        if (tkn) {
                            strcpy(section->configuration[section->configurations].value, tkn);
                            section->configurations++;
                        }
                    }
                }
#ifdef __INI_DEBUG__
                else {
                    printf("ini_load(): configuration '%s' without section.\n", buffer);
                }
#endif
            }
        }
    }

    fclose(file);

    return 0;
}
