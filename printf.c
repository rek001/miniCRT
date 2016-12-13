#include "minicrt.h"

#define va_list char*
#define va_start(ap, arg) (ap = ( va_list)&arg + sizeof(arg))
#define va_arg(ap, t) (*(t*)((ap += sizeof(t)) - sizeof(t)))
#define va_end(ap) (ap=(va_list)0)

//变长参数原理:linux 32bit 参数从右到左入栈，所以最后一个固定参数紧挨着变长参数，在低地址方向。
//按照固定参数的格式指定，依次读取变长参数的内容即可。
//64bit机器因为寄存器比较多，会尽量通过寄存器传参。glibc的va_系列宏对此做了特殊处理
static int vprintf(FILE *stream, const char *format, va_list arglist) {
    int translating = 0;
    int ret = 0;
    const char* p = 0;
    for(p = format; *p != 0; ++p){
        switch(*p){
            case '%':
                if(!translating){
                    translating =1;
                }else{
                    if(fputc('%', stream) < 0){
                        return EOF;
                    }
                    ++ret;
                    translating = 0;
                }
                break;
            case 'd':
                if(translating){    //%d
                    char buf[16];
                    translating = 0;
                    itoa(va_arg(arglist, int), buf, 10);
                    if(fputs(buf, stream) < 0){
                        return EOF;
                    }
                    ret += strlen(buf);
                }else if(fputc('d', stream) < 0){
                    return EOF;
                }else{
                    ++ret;
                }
                break;
            case 's':
                if(translating){    //%s
                    const char *str = va_arg(arglist, const char*);
                    translating = 0;
                    if(fputs(str, stream) < 0){
                        return EOF;
                    }
                    ret += strlen(str);
                }else if(fputc('s', stream) < 0){
                    return EOF;
                }else{
                    ++ret;
                }
                break;
            default:
                if(translating){
                    translating = 0;
                }
                if(fputc(*p, stream) < 0){
                    return EOF;
                }else{
                    ++ret;
                }
                break;
        }
    }
    return ret;
}

int fputc(int c, FILE *stream) {
    if (fwrite(&c, 1, 1, stream) != 1) {
        return EOF;
    } else {
        return c;
    }
}

int fputs(const char *str, FILE *stream) {
    int len = strlen(str);
    if (fwrite(str, 1, len, stream) != len) {
        return EOF;
    } else {
        return len;
    }
}

int printf(const char *format, ...) {
    va_list(arglist);
    va_start(arglist, format);
    return vprintf(stdout, format, arglist);
}

int fprintf(FILE *stream, const char *format, ...) {
    va_list(arglist);
    va_start(arglist, format);
    return vprintf(stream, format, arglist);
}


