/*
 *  Created by Adrienne Slaughter
 *  CS 5007 Summer 2019
 *  Northeastern University, Seattle
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#include "FileCrawler.h"
#include "DocIdMap.h"
#include "LinkedList.h"


void CrawlFilesToMap(const char *dir, DocIdMap map) {
  struct stat s;
  struct dirent **name_list;
  int n;
  char str_tmp[256];
  n = scandir(dir, &name_list, 0, alphasort);
  
  if (n < 0) {
    perror("not found\n");
  } else {
    for (int i = 0; i < n; i++) {
      if (dir[strlen(dir)-1] == '/') {
        snprintf(str_tmp, sizeof(str_tmp), "%s%s", dir, name_list[i]->d_name);
      } else {
        snprintf(str_tmp, sizeof(str_tmp), "%s/%s", dir, name_list[i]->d_name);
      }
      if ((stat(str_tmp, &s) == 0)) {
	if(S_ISDIR(s.st_mode)) {
	  if ((strcmp(name_list[i]->d_name, ".") != 0) && (strcmp(name_list[i]->d_name, "..") != 0)) {
            CrawlFilesToMap(str_tmp, map);
	  }
	} else if (S_ISREG(s.st_mode)) {
	  char* file_name = (char*)malloc(sizeof(char) * 256);
	  snprintf(file_name, 256, "%s", str_tmp);
          PutFileInMap(file_name, map);
	}
      }
      free(name_list[i]);
    }
    free(name_list);
  }
}
