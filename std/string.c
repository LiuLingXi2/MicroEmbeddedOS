
#include <std/string.h>

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

char *strcpy(char *dest, const char *src)
{
    char *d = dest;
    const char *s = src;

    while (*s != '\0') {
        *d = *s;
        d++;
        s++;
    }

    *d = '\0';

    return dest;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
        str1++;
        str2++;
    }

    return (unsigned char)*str1 - (unsigned char)*str2;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    
    while (i < n && s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
        i++;
    }
    
    if (i < n) {
        return (unsigned char)s1[i] - (unsigned char)s2[i];
    }
    
    return 0;
}

char* strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    
    return dest;
}

char* strcat(char* dest, const char* src)
{
    while (*dest != '\0') {
        dest++;
    }

    while (*src != '\0') {
        *dest = *src; 
        dest++;
        src++;
    }

    *dest = '\0';

    return dest;
}

// char *strtok(char *str, const char *delim) {
//     static char *s = NULL;  // 静态变量，记录当前字符串的位置
//     char *start;

//     // 如果 str 不是 NULL，说明是第一次调用或重新开始分割，更新静态变量 s
//     if (str != NULL) {
//         s = str;
//     }

//     // 如果 s 是 NULL，表示没有更多的字符可以分割
//     if (s == NULL) {
//         return NULL;
//     }

//     // 跳过前面的分隔符
//     while (*s != '\0' && strchr(delim, *s)) {
//         s++;  // 跳过分隔符
//     }

//     // 如果已经到达字符串末尾
//     if (*s == '\0') {
//         s = NULL;
//         return NULL;
//     }

//     // 记录当前子字符串的起始位置
//     start = s;

//     // 寻找下一个分隔符，找到则替换为 '\0'，标记子字符串结束
//     while (*s != '\0' && !strchr(delim, *s)) {
//         s++;  // 移动指针，直到遇到分隔符或字符串末尾
//     }

//     // 如果遇到分隔符，将其替换为 '\0'
//     if (*s != '\0') {
//         *s = '\0';
//         s++;  // 跳过分隔符
//     }

//     return start;  // 返回当前子字符串
// }

// // 查找字符是否在字符串中
// int strchr(const char *s, char c) {
//     while (*s != '\0') {
//         if (*s == c) {
//             return 1;  // 找到分隔符
//         }
//         s++;
//     }
//     return 0;  // 没有找到分隔符
// }

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

// char* strtok(char* str, const char* sep) 
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