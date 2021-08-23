/*
 * =====================================================================================
 *
 *       Filename:  vargs.h
 *
 *    Description:  可变形参表相关的宏定义
 *
 *        Version:  1.0
 *        Created:  2013年11月06日 12时12分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_VARGS_H_
#define INCLUDE_VARGS_H_

typedef __builtin_va_list va_list;

#define va_start(ap, last)         (__builtin_va_start(ap, last))
#define va_arg(ap, type)           (__builtin_va_arg(ap, type))
#define va_end(ap) 

// 


// int AveInt(int v,...)
// {
//    int ReturnValue=0;
//    int i=v;
 
//    va_list ap ;
//    va_start(ap,v);
 
//    while(i>0)
//    {
//        ReturnValue+=va_arg(ap,int) ;
//        i--;
//    ｝
//    va_end(ap); 
//    return ReturnValue/=v;
// }
// #define  va_list              char *

// #define  va_start(p, last)   (p = (va_list)&first + sizeof(last))
// #define  va_arg(p, type)      (*(type*)((p += sizeof(type) ) - sizeof(type)))
// #define  va_end(p)            (p = (va_list)NULL)

#endif 	// INCLUDE_VARGS_H_
