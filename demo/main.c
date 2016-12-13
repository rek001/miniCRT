#include "../minicrt.h"

int main() {
    const char *msg = "hello world.";
    char *buf = (char *) malloc(128);
    if (buf == NULL) {
        printf("malloc fail.\n");
        exit(-1);
    }

    int z = fread(buf, 1, 128, stdin);
    if (z < 0) {
        printf("fread error\n");
        exit(-1);
    }
    printf("%s", msg);
    printf("%s", buf);


    FILE *fp = fopen("./test.txt", "w+");
    if(fp == NULL){
        printf("fail open.\n");
        exit(-1);
    }
    z = fwrite(msg, strlen(msg), 1, fp);
    if(z != strlen(msg)){
        printf("write error.\n");
        exit(-1);
    }
    fclose(fp);

    fp = fopen("./test.txt", "r");
    if(fp == NULL){
        printf("read error.\n");
        exit(-1);
    }
    char *readbuf = (char*)malloc(64);
    if (readbuf == NULL) {
        printf("malloc fail.\n");
        exit(-1);
    }
    z = fread(readbuf, 64, 1, fp);
    if(z < 0){
        printf("read error.\n");
        exit(-1);
    }
    printf("read: %s\n", readbuf);
    fclose(fp);

    free(buf);
    free(readbuf);
    return 0;
}