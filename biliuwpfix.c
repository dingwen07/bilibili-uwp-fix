#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    // bilibili UWP fix
    // biliuwpfix <path>

    char *usage_msg = "Usage: biliuwpfix <path>";

    if (argc < 2) {
        printf("%s\n", usage_msg);
        return 1;
    }

    char *path = argv[1];
    
    // open file
    FILE *fp = fopen(path, "r+");
    if (fp == NULL) {
        printf("Error: cannot open file %s\n", path);
        return 1;
    }

    // read first 3 bytes
    char buf[3];
    fread(buf, 1, 3, fp);

    // check if they are ff ff ff
    // if not, exit
    if (buf[0] != -1 || buf[1] != -1 || buf[2] != -1) {
        printf("Error: file %s is not a valid BiliBili UWP video file\n", path);
        return 1;
    }

    // remove temp file if it exists
    remove("temp");
    FILE *fp2 = fopen("temp", "w");
    if (fp2 == NULL) {
        printf("Error: cannot create temp file\n");
        return 1;
    }
    // save binary file without first 3 bytes
    char c;
    while (!feof(fp)) {
        c = fgetc(fp);
        if (ferror(fp)) {
            printf("Error: failed reading file %s\n", path);
            return 1;
        }
        fputc(c, fp2);
    }

    // close file
    fclose(fp);

    // rename temp file to original file
    remove(path);
    rename("temp", path);
    
    return 0;
}
