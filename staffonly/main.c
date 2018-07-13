//
//  main.c
//  staffonly
//
//  Created by 鈴木充 on 2018/07/13.
//  Copyright © 2018年 鈴木充. All rights reserved.
//
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define	VAR_NAME(var)	#var

void joinpath(char *path, const char *path1, const char *path2) {
	strcpy(path, path1);
	strcat(path, "/");
	strcat(path, path2);
	return;
}

void listfiles(char *path) {
	DIR *dir = opendir(path);
	for (struct dirent *dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if (dp->d_name[0] != '.') {
			char path2[256];
			joinpath(path2, path, dp->d_name);
			struct stat fi;
			stat(path2, &fi);
			if (!S_ISDIR(fi.st_mode)) {
				printf("%s\n", path2);
			}
		}
	}
	closedir(dir);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, %s=%d!\n", VAR_NAME(argc), argc);

	char path[256];
	if (argc == 1) {
		strcpy(path, ".");
	} else {
		strcpy(path, argv[1]);
	}
	listfiles(path);
	return 0;
}
