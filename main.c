#include "header.h"
#include <dirent.h>
#include "parser.c"

int main() {
//    DIR *d;
//    char s[MAXCHAR];
//    char file_path[MAXCHAR];
//    struct dirent *dir;
//    d = opendir("tests/positive");
//    if (d) {
//        while ((dir = readdir(d)) != NULL) {
//            if(dir->d_type == DT_REG) {
//                printf("%s\n", dir->d_name);
//                strcpy(file_path, "tests/positive/");
//                strcpy(s, dir->d_name);
//                parse(strcat(file_path, s ));
//            }
//        }
//        closedir(d);
//    }
    parse("tests/negative/.html");
    // note - change to below line when submitting
//    parse("file.html");
}


