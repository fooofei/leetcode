

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef WIN32
#include <asprintf.h>
#endif

// using namespace std;

// 151 https://leetcode-cn.com/problems/reverse-words-in-a-string/

typedef struct {
    char* addr;
    int cap;
    char* first;
    char* last;
} string_t;

void StringTerm(string_t* s)
{
    if (s->addr) {
        free(s->addr);
    }
    s->addr = NULL;
    s->cap = 0;
    s->first = NULL;
    s->last = NULL;
}

void StringInit(string_t* s, int cap)
{
    StringTerm(s);
    s->addr = (char*)malloc(cap);
    s->cap = cap;
    s->first = s->addr;
    s->last = s->first;
    (*s->last) = '\0';
}

// If attach a stack buffer,
// cannot call `StringTerm` to free it later.
void StringAttach(string_t* s, char* addr, int cap)
{
    StringTerm(s);
    s->addr = addr;
    s->cap = cap;
    s->first = addr;
    s->last = s->first;
    (*s->last) = '\0';
}

int StringLen(string_t* s)
{
    return (int)(s->last - s->first);
}

int StringFirstOff(string_t* s)
{
    return (int)(s->first - s->addr);
}

int StringLastOff(string_t* s)
{
    return (int)(s->last - s->addr);
}

const char* StringCStr(string_t* s)
{
    return s->first;
}

void StringAppendStrN(string_t* s, const char* sub, size_t subLen)
{
    int oldLen = StringLen(s);
    int lastOff = StringLastOff(s);

    if (((int)subLen + 1) > (s->cap - lastOff)) {
        int newLen = oldLen + subLen + 1;
        char* newAddr = (char*)malloc(newLen * 2);
        // TODO securec
        memcpy(newAddr, StringCStr(s), oldLen);

        free(s->addr);
        s->addr = newAddr;
        s->cap = newLen * 2;
        s->first = s->addr;
        s->last = s->first + oldLen;
        *(s->last) = '\0';
    }

    // TODO securec
    if (subLen > 0) {
        memcpy(s->last, sub, subLen);
    }
    s->last += subLen;
    *(s->last) = '\0';
}

void StringAppendStr(string_t* s, const char* sub)
{
    StringAppendStrN(s, sub, strlen(sub));
}

void StringAppendChar(string_t* s, char c, int count)
{
    if (count == 1) {
        StringAppendStrN(s, &c, 1);
    } else {
        char* dummy = (char*)malloc(count + 1);
        for (int i = 0; i < count; i++) {
            dummy[i] = c;
        }
        StringAppendStrN(s, dummy, count);
        free(dummy);
    }
}

#ifdef WIN32
void StringFormat(string_t* s, const char* fmt, ...)
{
    va_list ap0;
    va_list ap1;

    va_start(ap0, fmt);
    va_copy(ap1, ap0);

    // TODO securec
    int size = (int)vsnprintf(NULL, 0, fmt, ap0);
    va_end(ap0);
    if (size <= 0) {
        va_end(ap1);
        // ignore the error
        return;
    }
    size += 1;

    char* buf = (char*)malloc(size);
    // TODO securec
    size = vsnprintf(buf, size, fmt, ap1);
    va_end(ap1);
    if (size <= 0) {
        free(buf);
        return;
    }
    StringAppendStrN(s, buf, size);
    free(buf);
}
#else
#define StringFormat(sobj, fmt, ...)      \
    do {                                  \
        char* __s = NULL;                 \
        asprintf(&__s, fmt, __VA_ARGS__); \
        StringAppendStr(sobj, __s);       \
        free(__s);                        \
    } while (0)
#endif

typedef struct {
    void** addr;
    int cap;
    int first;
    int last;
} vector_t;

void VectorTerm(vector_t* vec)
{
    if (vec->addr) {
        free(vec->addr);
    }
    vec->addr = NULL;
    vec->cap = 0;
    vec->first = 0;
    vec->last = 0;
}

void VectorInit(vector_t* vec, int cap)
{
    VectorTerm(vec);
    vec->addr = (void**)calloc(cap, sizeof(void*));
    vec->cap = cap;
    vec->first = 0;
    vec->last = vec->last;
    vec->addr[vec->last] = NULL;
}

int VectorLen(vector_t* vec)
{
    return (int)(vec->last - vec->first);
}

void* VectorAt(vector_t* vec, int at)
{
    if (at >= VectorLen(vec)) {
        return NULL;
    }
    return vec->addr[vec->first + at];
}

void* VectorFront(vector_t* vec)
{
    if (VectorLen(vec) <= 0) {
        return NULL;
    }
    return vec->addr[vec->first];
}

void* VectorBack(vector_t* vec)
{
    if (VectorLen(vec) <= 0) {
        return NULL;
    }
    return vec->addr[vec->last - 1];
}

void VectorPushBack(vector_t* vec, void* p)
{
    int oldLen = VectorLen(vec);

    if (vec->last >= vec->cap) {
        // 只扩充后面， 前面保持不变
        int newCap = vec->cap + 1;
        newCap *= 2;
        void** new_ = (void**)calloc(newCap, sizeof(void*));
        if (oldLen > 0) {
            memcpy(new_ + vec->first, vec->addr + vec->first,
                oldLen * sizeof(void*));
        }

        free(vec->addr);
        vec->addr = new_;
        vec->cap = newCap;
    }

    vec->addr[vec->last] = p;
    vec->last++;
}

void* VectorPopBack(vector_t* vec)
{
    if (VectorLen(vec) <= 0) {
        return NULL;
    }
    void* ret = VectorBack(vec);
    vec->addr[vec->last] = NULL;
    vec->last--;
    return ret;
}

void VectorPushFront(vector_t* vec, void* p)
{
    int oldLen = VectorLen(vec);

    // 100 是一个可容忍的容量
    if (vec->cap > 100 && oldLen == 0) {
        vec->first = vec->last = vec->cap / 2;
    }

    if (vec->first <= 0) {
        // 只扩充前面，后面不变
        int newCap = vec->cap + 1;
        newCap *= 2;
        void** new_ = (void**)calloc(newCap, sizeof(void*));
        if (oldLen > 0) {
            memcpy(new_ + vec->cap + 1 + vec->first,
                vec->addr + vec->first, oldLen * sizeof(void*));
        }
        free(vec->addr);

        vec->addr = new_;
        vec->first += vec->cap + 1;
        vec->last += vec->cap + 1;

        vec->cap = newCap;
    }

    vec->first--;
    vec->addr[vec->first] = p;
}

void* VectorPopFront(vector_t* vec)
{
    if (VectorLen(vec) <= 0) {
        return NULL;
    }
    void* ret = VectorFront(vec);
    vec->addr[vec->first] = NULL;
    vec->first++;
    return ret;
}

char* reverseWords(char* s)
{
    vector_t vec = { 0 };

    VectorInit(&vec, 10);
    string_t src = { 0 };
    StringInit(&src, 10);
    StringFormat(&src, "%s", s);
    StringFormat(&src, "%s", " ");

    const char* first = NULL;
    const char* p = StringCStr(&src);

    for (; *p; p++) {

        if (*p == ' ') {
            if (first != NULL) {
                string_t* newWord = (string_t*)calloc(1, sizeof(string_t));
                StringInit(newWord, 10);
                StringFormat(newWord, "%.*s", p - first, first);
                VectorPushFront(&vec, newWord);

                string_t* blank = (string_t*)calloc(1, sizeof(string_t));
                StringInit(blank, 10);
                StringFormat(blank, "%s", " ");
                VectorPushFront(&vec, blank);
            }
            first = NULL;
        } else {
            if (first == NULL) {
                first = p;
            }
        }
    }

    string_t dst = { 0 };
    StringInit(&dst, 10);

    if (VectorLen(&vec) > 0) {
        string_t* popStr = (string_t*)VectorPopFront(&vec);
        StringTerm(popStr);
        free(popStr);
    }

    for (; VectorLen(&vec) > 0;) {
        string_t* popStr = (string_t*)VectorPopFront(&vec);
        StringAppendStrN(&dst, StringCStr(popStr), StringLen(popStr));
        StringTerm(popStr);
        free(popStr);
    }

    VectorTerm(&vec);

    StringTerm(&src);
    return dst.addr;
}

void test2()
{
    char* s = reverseWords("  hello world!  ");
    printf("%s() %s\n", __func__, s);
}

void test1()
{
    char* s = reverseWords("the sky is blue");
    printf("%s() %s\n", __func__, s);
}

int main()
{
    test1();
    return 0;
}
