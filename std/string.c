/**
 * @brief Learn from: https://github.com/ArthurWu6688/my_string.h.git
 */

#include "std/string.h"

// #define NULL ((void *)0)

// typedef unsigned int size_t;

size_t strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		;

	return sc - s;
}

void *memcpy(void *dest, const void *src, size_t count)
{
	char *tmp = dest;
	const char *s = src;

	while (count--)
		*tmp++ = *s++;
	return dest;
}


// char* strcpy(char* dest, const char* src) 
// {
// 	char* ptr = dest;
// 	while (*ptr++ = *src++);
// 	return dest;
// }

// char* strcat(char* dest, const char* src) 
// {
// 	char* ptr = dest;
// 	while (*ptr != '\0') {
// 		++ptr;

// 	} while (*ptr++ = *src++);
// 	return dest;
// }

// int strcmp(const char* str1, const char* str2) 
// {
// 	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
// 		++str1;
// 		++str2;
// 	}
	
// 	return *str1 - *str2;
// }

// char* strncpy(char* dest, char* src, int n) 
// {
// 	char* ptr = dest;
// 	while ((*ptr = *src) && (n--)) {
// 		++ptr;
// 		++src;
// 	}

// 	*ptr = '\0';
// 	return dest;
// }

// char* strncat(char* dest, char* src, int n) 
// {
// 	char* ptr = dest;
// 	while (*ptr != '\0') {
// 		++ptr;
// 	}
// 	while ((*ptr = *src) && (n--)) {
// 		++ptr;
// 		++src;
// 	}

// 	*ptr = '\0';
// 	return dest;
// }

// int strncmp(char* str1, char* str2, int n) 
// {

// 	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2 && n>1) {
// 		++str1;
// 		++str2;
// 		--n;
// 	}
// 	return *str1 - *str2;
// }

// const char* strchr(const char* src, char ch) 
// {
// 	const char* ptr = src;
// 	while (*ptr != '\0') {
// 		if (ch == *ptr) {
// 			return ptr;
// 		}
// 		++ptr;
// 	}
// 	return NULL;
// }

// const char* strstr(const char* str1, char* str2) 
// {
// 	while (*str1 != '\0') {
// 		const char* s1 = str1;
// 		char* s2 = str2;

// 		while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
// 			++s1;
// 			++s2;
// 		}
// 			if (*s2 == '\0')
// 				return str1;
// 			if (*s1 == '\0')
// 				break;
// 		++str1;
// 	}
// 	return NULL;
// }

// char* strtok(char* str, char* sep) 
// {
// 	static char* start;
// 	char* ptr = start;
// 	char* res = start;
// 	if (*start == '\0')
// 		return 0;
// 	while (*ptr != '\0') {
// 		for (int i = 0; sep[i] != '\0'; ++i) {
// 			if (*ptr == sep[i]) {
// 				if (ptr == start) {
// 					start = ptr + 1;
// 					res = start;
// 					break;
// 				}
// 				*ptr = '\0';
// 				start = ptr + 1;
// 				return res;
// 			}
// 		}
// 		++ptr;
// 	}
// 	start = ptr;
// 	return res;
// }

// void memset(void* base, unsigned char val, size_t len) 
// {
// 	while (len>0) {
// 		*((char*)base + len - 1) = val;
// 		len--;
// 	}
// 	return NULL;
// }

// void* memmove(void* dest, void* src, size_t len) 
// {
// 	if (dest > src && (char*)dest < (char*)src + len) {
// 		while (len-- > 0) {
// 			*((char*)dest + len) = *((char*)src + len);
// 		}
// 	}
// 	else {
// 		for (int i = 0; i < (int)len; ++i) {
// 			*((char*)dest + i) = *((char*)src + i);
// 		}
// 	}
// 	return dest;
// }