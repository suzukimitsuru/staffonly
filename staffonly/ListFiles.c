//
//  ListFiles.c
//  staffonly
//
//  Created by 鈴木充 on 2018/07/18.
//  Copyright © 2018年 鈴木充. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <stdbool.h>
#include "definitions.h"
#include "ListFiles.h"

int ListFiles(char *root, DEFINITION *definitions, char *path,
			  int (*found)(char *root, DEFINITION *definitions, char *path)) {
	int errors = 0;
	DIR *dir = opendir(path);
	for (struct dirent *dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if (dp->d_name[0] != '.') {
			char child[PATH_MAX];
			strcpy(child, path);
			strcat(child, "/");
			strcat(child, dp->d_name);
			struct stat fi;
			stat(child, &fi);
			if (!S_ISDIR(fi.st_mode)) {
				errors += found(root, definitions, child);
			} else {
				errors += ListFiles(root, definitions, child, found);
			}
		}
	}
	closedir(dir);
	return errors;
}
