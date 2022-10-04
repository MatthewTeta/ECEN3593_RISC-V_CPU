#ifndef _CODASIP_H_
#define _CODASIP_H_

int siprintf(char*, const char*, ...);
int snprintf(char*, size_t, const char*, ...);

int vsprintf (char *, const char *, va_list);
int vsnprintf (char *, size_t, const char *, va_list);

void * memset ( void *, int, size_t);
int write(int, const void *, size_t);

#define sprintf(...) siprintf(__VA_ARGS__)
#define snprintf(...) sniprintf(__VA_ARGS__)

#define vsprintf(str, format, args) vsiprintf(str, format, args)
#define vsnprintf(str, n, format, args) vsniprintf(str, n, format, args)

#endif /* _CODASIP_H_ */
