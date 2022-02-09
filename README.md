# avx512_fp16_examples
hosting simple examples of fp16 code 


## For Simple example:

run 
```
gcc-12 fp16simple.c -mavx512fp16 -o avx512pf16simple_O0.S -O0 -S && gcc-12 fp16simple.c -mavx512fp16 -o avx512pf16simple_O3.S -O3 -S && diff avx512pf16simple_O3.S avx512pf16simple_O0.S -y | less
```
from there you're looking for how, when optimizing, because of the extra cost of casting the fp16 back to a float32 (due to printf not having native support for fp16) the compiler realizes it's cheaper to just never use FP16, and promote the floats to fp32, then use the classic  `addq`. 

That's in contrast to how when no optimization are requested, the compiler uses the simplest instruction available: `vaddsh` a dedicated instruction from the AVX512FP16 ISA extension to x86_64 that takes a given amount of fp16 values and adds them together. 
