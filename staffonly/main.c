//
//  main.c
//  staffonly
//
//  Created by 鈴木充 on 2018/07/13.
//  Copyright © 2018年 鈴木充. All rights reserved.
//
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslimits.h>
#include "language.h"
#include "definitions.h"
#include "ListFiles.h"

#define	STRINGIZE(var)	#var

static int _lint_StaffOnly(char *root, DEFINITION *definitions, char *path) {
	int errors = 0;
	LANGUAGE_DEFINE *language = FindLanguages(path);
	if (language != NULL) {
		FEATURE *features = definitionsFeatures(definitions, path);
		if (features != NULL) {
			FILE *fp = fp = fopen(path, "rt");
			if (fp != NULL) {
				size_t root_length = strlen(root);
				for (int number = 1; !feof(fp); number++) {
					static char line[LINE_MAX];
					fgets(line, sizeof(line), fp);
					char *include = language->hasInclude(line);
					if (include != NULL) {
						printf("%s %d: %s", &path[root_length + 1], number, line);
						errors++;
					}
				}
				fclose(fp);
			}
		}
	}
	return errors;
}

int main(int argc, const char * argv[]) {
	int exit = 0;
	bool help = false;
	char root[PATH_MAX];
	if (argc <= 1) {
		strcpy(root, ".");
	} else {
		for (int index = 1; index < argc; index++) {
			switch (argv[index][0]) {
				case '-':
					help = true;
					break;
				default:
					strcpy(root, argv[index]);
					break;
			}
		}
	}
	if (help) {
		printf("staffonly -- declaration lint\n");
		printf("usage: staffonly <directory>\n\n");
		printf("definition-file: <directory>/.staffonly\n");
		printf("  # Example\n");
		printf("  comm/urart\n");
		printf("    <dirent.h>\n");
		printf("    <sys/stat.h>\n");
		exit = 9;
	} else {
		DEFINITION *definitions = definitionsRead(root);
		int errors = ListFiles(root, definitions, root, _lint_StaffOnly);
		if (errors > 0) {
			printf("%d ERRORS.\n", errors);
			exit = 1;
		} else {
			printf("Success.\n");
			exit = 0;
		}
	}
	return exit;
}
