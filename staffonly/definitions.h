//
//  definitions.h
//  staffonly
//
//  Created by 鈴木充 on 2018/07/19.
//  Copyright © 2018年 鈴木充. All rights reserved.
//

#ifndef definitions_h
#define definitions_h

typedef struct S_FEATURE {
	char name[FILENAME_MAX];
	struct S_FEATURE *next;
} FEATURE;

typedef struct S_DEFINITION {
	char directory[PATH_MAX];
	FEATURE *features;
	struct S_DEFINITION *next;
} DEFINITION;

extern DEFINITION *definitionsRead(char *root);
extern FEATURE *definitionsFeatures(DEFINITION *definitions, char *path);
extern bool definitionsIsError(FEATURE *features, char *include);

#endif /* definitions_h */
