#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

float seed = 1;
srand((time(0)));
int count = 31;
_Float16 factor = seed;


//primaries
_Float16 a=1.436;
_Float16 b=0.83546;



//arrays to be used for FMA
_Float16 alpha[32];
_Float16 delta[32];
_Float16 omega[32];

while (count>=0)
{
//fill the arrays with differing values
alpha[count]=(_Float16) (a*factor);
delta[count]=(_Float16) (b*factor);
omega[count]=(_Float16) (factor+(a*b));

factor = factor+b;

count--;
}

//count = 31;
printf("Print the FMA of 3  _Float16's that are cast as Float\n");


while (count < 32){

omega[count]=(omega[count]*alpha[count])+delta[count];

count++;
}
printf("\n"); //clear last line

while (count>=0)
{
printf("%i %f \n", count, (float) omega[count]);
count--;
}



// 32 entry variable to be used: 512/16 = 32
//c d e f g h i j k l m n o p q r s t u v w x y z aa ab ac ad ae af ag ah
//printf("Print the sum of 2 _Float16's that are cast as Float\n%f\n", (float) a);

}
