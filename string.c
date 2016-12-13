#include "minicrt.h"

int strcmp(const char *src, const char *dst) {
    int ret = 0;
    unsigned char *p1 = (unsigned char *) src;
    unsigned char *p2 = (unsigned char *) dst;
    while (!(ret = *p1 - *p2) && *p2) {
        ++p1;
        ++p2;
    }
    if (ret < 0) {
        ret = -1;
    } else if (ret > 0) {
        ret = 1;
    }
    return ret;
}

char *itoa(int n, char *str, int radix) {
    char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = str;
    char *head = str;
    if (!p || radix < 2 || radix > 36) {
        return p;
    }
    if (n == 0) {
        *p++ = '0';
        *p = 0;
        return p;
    }
    if (radix == 10 && n < 0) {
        *p++ = '-';
        n = -n;
    }
    while (n) {
        *p++ = digit[n % radix];
        n = n / radix;
    }
    *p = 0;
    for (--p; head < p; ++head, --p) {
        char tmp = *head;
        *head = *p;
        *p = tmp;
    }
    return str;
}

char *strcpy(char *dst, const char *src) {
    char *ret = dst;
    while(*src){
        *dst++ = *src++;
    }
    *dst = 0;
    return  ret;
}

unsigned strlen(const char *str) {
    int cnt = 0;
    if(!str){
        return 0;
    }
    for(; *str != 0; str ++){
        cnt ++;
    }
    return cnt;
}