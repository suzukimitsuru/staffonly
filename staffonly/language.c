//
//  language.c
//  staffonly
//
//  Created by 鈴木充 on 2018/07/17.
//  Copyright © 2018年 鈴木充. All rights reserved.
//
#include <string.h>
#include "language.h"

extern char *CLang_hasInclude(char line[]);

static LANGUAGE_DEFINE _languages[] = {
	{".c",		CLang_hasInclude},
	{".cpp",	CLang_hasInclude},
	{"",		NULL},
};

LANGUAGE_DEFINE *FindLanguages(char filename[]) {
	LANGUAGE_DEFINE *result = NULL;
	char *extention = strrchr(filename, '.');
	if (extention != NULL) {
		for (int index = 0; _languages[index].extention[0] != '\0'; index++) {
			if (strcasecmp(_languages[index].extention, extention) == 0) {
				result = &_languages[index];
				break;
			}
		}
	}
	return result;
}
