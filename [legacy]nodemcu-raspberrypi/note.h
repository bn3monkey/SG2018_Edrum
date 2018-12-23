#ifndef __NOTE__
#define __NOTE__

typedef struct _note
{
    // 연주한 악기의 종류
    int drum;
    // 악기의 세기
    int power;
    // 시작 시간으로부터 찍힌 노트의 시간 (milli초 단위)
    long long int msec;
    
} note;

#endif