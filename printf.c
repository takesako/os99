#include "stdio.h"

void printf(const char *fmt, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    while (*fmt) {
        if (*fmt != '%') { putchar(*fmt++); continue; }
        fmt++;
        char pad = (*fmt == '0') ? *fmt++ : ' ';
        int width = 0;
        if (*fmt == '*') { width = __builtin_va_arg(ap, int), fmt++; }
        else { while ('0' <= *fmt && *fmt <= '9') width = width * 10 + *fmt++ - '0'; }
        if (*fmt == 's') {
            char *s = __builtin_va_arg(ap, char *);
            int len = 0;
            while (s[len]) len++;
            while (len < width) putchar(pad), width--;
            while (*s) putchar(*s++);
        } else if (*fmt == 'c') {
            putchar(__builtin_va_arg(ap, int));
        } else if (*fmt == 'd' || *fmt == 'x' || *fmt == 'X') {
            unsigned x; char buf[16]; int i = 0, base = (*fmt == 'd') ? 10 : 16;
            char *digits = (*fmt == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";
            if (*fmt == 'd') {
                int n = __builtin_va_arg(ap, int);
                if (n < 0) putchar('-'), n = -n, width--;
                x = n;
            } else x = __builtin_va_arg(ap, unsigned);
            do buf[i++] = digits[x % base], x /= base; while (x);
            while (i < width) putchar(pad), width--;
            while (i--) putchar(buf[i]);
        } else {
            if (*fmt != '%') putchar('%');
            putchar(*fmt);
        }
        fmt++;
    }
    __builtin_va_end(ap);
}
