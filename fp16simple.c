#include <stdio.h>

/*
Simple example of FP16 arithmetic with it's declaration

NB: This uses Clang/GCC convention FP16 declarations due to near universal platform support.

Any compiler that has yet to formally adopt ISO/IEC TS 18661-3:2015 (“Floating-point extensions for C”) will not support the type.

Known working x86_64 compilers as of Feb 08 2022 are:

Clang/LLVM-14+
GCC-12+
Intel ICX Version 2022.0.0


Known working archetectures:

Intel Alder-Lake*
Intel Sapphire Rapids


*under certain conditions
*/



int main(){

_Float16 a=16.436;

_Float16 b=4889.23546;

a = a+b;

printf("\nPrint the sum of 2 _Float16's that are cast as Float %f\n", (float) a); 
printf("With casting, GCC, ICX and Clang all perform as expected\n\n");


printf("Print the sum of 2 _Float16's that are not cast as Float %f\n",a); 
printf("Without casting GCC, Clang and ICX return 0.0000, but Clang and ICX return a warning\n" );




}
