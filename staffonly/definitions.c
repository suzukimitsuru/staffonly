//
//  definition.c
//  staffonly
//
//  Created by 鈴木充 on 2018/07/19.
//  Copyright © 2018年 鈴木充. All rights reserved.
//
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslimits.h>
#include <alloca.h>
#include "definitions.h"

DEFINITION *definitionsRead(char *root) {
	DEFINITION *definitions = NULL;
	char filename[PATH_MAX];
	strcpy(filename, root);
	strcat(filename, "/.staffonly");
	FILE *fp = fp = fopen(filename, "rt");
	if (fp != NULL) {
		DEFINITION *definition = alloca(sizeof(DEFINITION));
		FEATURE *feature = alloca(sizeof(FEATURE));
		if (definition && feature) {
			memset(definition, 0, sizeof(DEFINITION));
			memset(feature, 0, sizeof(FEATURE));
			
			for (int number = 1; !feof(fp); number++) {
				static char line[LINE_MAX];
				memset(line, '\0', sizeof(line));
				fgets(line, sizeof(line), fp);
				
				char *comment = strchr(line, '#');
				if (comment) comment[0] = '\0';
				for (int index = (int)strlen(line) - 1; (index >= 0) && (line[index] <= '\x20'); index--) {
					line[index] = '\0';
				}
				
				int length = (int)strlen(line);
				if (length > 0) {
					if (line[0] <= '\x20') {
						char *include = NULL;
						for (int index = 0; index < length; index++) {
							if (line[index] > '\x20') {
								include = &line[index];
								break;
							}
						}
						if (include) {
							if (feature->name[0] != '\0') {
								feature->next = alloca(sizeof(FEATURE));
								if (feature->next) {
									memset(feature->next, 0, sizeof(FEATURE));
								} else {
									break;
								}
								feature = feature->next;
							}
							strcpy(feature->name, include);
							if (definition->features == NULL) {
								definition->features = feature;
							}
						}
					} else {
						if (definition->directory[0] != '\0') {
							definition->next = alloca(sizeof(DEFINITION));
							if (definition->next) {
								memset(definition->next, 0, sizeof(DEFINITION));
							} else {
								break;
							}
							definition = definition->next;
						}
						strcpy(definition->directory, root);
						if (strcmp(line, ".") != 0) {
							strcat(definition->directory, "/");
							strcat(definition->directory, line);
						}
						if (definitions == NULL) {
							definitions = definition;
						}
					}
				}
			}
		}
		fclose(fp);
	}
	return definitions;
}

FEATURE *definitionsFeatures(DEFINITION *definitions, char *path) {
	FEATURE *features = NULL;
	DEFINITION *definition = definitions;
	while (definition != NULL) {
		if (strcmp(definition->directory, path) == 0) {
			features = definition->features;
			break;
		} else {
			definition = definition->next;
		}
	}
	return features;
}

bool definitionsIsError(FEATURE *features, char *include) {
	bool is_error = false;
	for (FEATURE *feature = features; feature != NULL; feature = feature->next) {
		if (strcmp(feature->name, include) == 0) {
			is_error = true;
		}
	}
	return is_error;
}
