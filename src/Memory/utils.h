#ifndef UTILS_H
#define UTILS_H

typedef unsigned long size_o;

typedef enum
{
    MY_FALSE = 0,
    MY_TRUE = 1
} dbool;

#define NULL ((void *)0)

#define MY_MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#define MY_MAX(a,b) (( (a) > (b) ) ? (a) : (b))

#endif
