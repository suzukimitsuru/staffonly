//
//  CLang.c
//  staffonly
//
//  Created by 鈴木充 on 2018/07/17.
//  Copyright © 2018年 鈴木充. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <sys/syslimits.h>

char *CLang_hasInclude(char line[]) {
	static char headerfile[PATH_MAX];
	char *result = NULL;
	
	char *sharp = strchr(line, '#');
	if (sharp != NULL) {
		
		char *include = strstr(line, "include");
		if (include != NULL) {
			
			const char brackets[][2] = {{'<', '>'},{'\"', '\"'},};
			for (int bracket = 0; bracket < (sizeof(brackets) / sizeof(brackets[0])); bracket++) {
				
				char *open = strchr(include, brackets[bracket][0]);
				if (open) {
					char *close = strchr(open + 1, brackets[bracket][1]);
					if (close) {
						
						char *source = open;
						int length = (int)((close + 1) - source);
						for (int index = 0; index < length; index++) {
							headerfile[index] = source[index];
						}
						headerfile[length] = '\0';
						
						result = headerfile;
						break;
					}
				}
			}
		}
	}
	return result;
}
