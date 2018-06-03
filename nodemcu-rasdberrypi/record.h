#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>


typedef struct _note
{
    // 시작 시간으로부터 찍힌 노트의 시간 (milli초 단위)
    long long int msec;
    // 연주한 악기의 종류
    int drum;
    // 악기 친 세기
    int power;
} note;

bool makefile(char*, char *);
bool fexists(const char*);
