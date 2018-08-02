//
//  ListFiles.h
//  staffonly
//
//  Created by 鈴木充 on 2018/07/18.
//  Copyright © 2018年 鈴木充. All rights reserved.
//

#ifndef ListFiles_h
#define ListFiles_h

extern int ListFiles(char *root, DEFINITION *definitions, char *path,
					 int (*found)(char *root, DEFINITION *definitions, char *path));

#endif /* ListFiles_h */
