#ifndef __INCLUDE_STRING_H__
#define __INCLUDE_STRING_H__

#define NULL ((void *)0)

typedef unsigned int size_t;

size_t strlen(const char* str);

// char*  strcpy(char* dest, const char* src);
// char*  strcat(char* dest, const char* src);
// int    strcmp(const char* str1, const char* str2);
// char*  strncpy(char* dest, char* src,int n);
// char*  strncat(char* dest, char* src, int n);
// int    strncmp(char* str1, char* str2, int n);
// char*  strtok(char* str, char* sep);

// void  memset(void* base, unsigned char val, size_t len);
void *memcpy(void *dest, const void *src, size_t count);
char *strcpy(char *dest, const char *src);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *s1, const char *s2, size_t n);
char* strncpy(char *dest, const char *src, size_t n);
char* strcat(char* dest, const char* src);
char *strtok(char *str, const char *delim);
int strchr(const char *s, char c);
// void* memmove(void* dest, void* src, size_t len);

// const char* strchr(const char* str, char ch);
// const char* strstr(const char* str1, char* str2);

#endif // !__INCLUDE_STRING_H__