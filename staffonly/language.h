//
//  language.h
//  staffonly
//
//  Created by 鈴木充 on 2018/07/17.
//  Copyright © 2018年 鈴木充. All rights reserved.
//

#ifndef language_h
#define language_h

typedef struct {
	char *extention;
	char *(*hasInclude)(char line[]);
} LANGUAGE_DEFINE;
extern LANGUAGE_DEFINE *FindLanguages(char filename[]);

#endif /* language_h */
