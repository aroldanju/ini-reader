#include "ini.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
	INI ini;

	// Read
	if (ini_load(&ini, "FILE.INI") != 0) {
		printf("Error reading FILE.INI\n");
		return 1;
	}

	printf("SECTION.Key1 = %s\n", ini_get_value(&ini, "SECTION", "Key1"));

	// Save
	ini_save("OUT.INI", &ini);

	return 0;
}