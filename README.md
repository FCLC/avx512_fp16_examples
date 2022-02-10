# avx512_fp16_examples
Hosting simple examples of AVX512fp16 example code and providing background on it's usage


## General information on AVX-512 FP16 and it's availability.
Because AVX512FP16 is an *extension* to the AVX512 ISA, it must either:

A) Have explicit hardware support built in.

B) Be emulated in software by promoting the type to another suitable alternative such as fp32 with specific rounding/conformance code.

As of the time of posting there are no systems in the market that have official AVX 512 FP16 support available. 

As of this posting (Feb 10 2022) the only in market support is the AVX512 P(erformance)-core workaround for Intel 12th generation K series AlderLake CPU's*. 

These P-cores, based on the Golden Cove architecture, support AVX512FP16*. 

To use the instruction in C or C++ a very recent compiler must be used. My own testing shows that GCC-12, Clang-14 and ICX 2022.0 are all capable of utilizing the instruction.

If you'd like to use an officially supported platform, the option is to wait for Intel Xeon Sapphire Rapids, which are based on only Golden Cove cores and will have the full AVX512 ISA enabled. 


A snippet of code that will compile to utilize the FMA instructions from the AVX512FP16 ISA extension is inside this repository in addition to a simple example showing the messy compiler state as of early 2022.  

## Note on using Alder Lake
*NB: This capability can only be enabled once Gracemont E-cores are disabled, on specific vendors motherboards with specific BIOS/Microcode revisions. This is not Sanctioned or supported by Intel


The reason for this is mainly to do with different ISA's between the Gracemont and Golden Cove core's and Process pinning (but that is beyond the scope of this readme. Reach out on twitter if you'd like to know more) 

## Code example using fp16_FMA_avx512.c 

Use `gcc-12 fp16_FMA_avx512.c -O3 -march=sapphirerapids -mavx512fp16 -o avx512example.bin `
To generate an executable if your platform supports the instruction

Use `gcc-12 fp16_FMA_avx512.c -O3 -march=sapphirerapids -mavx512fp16 -o avx512example.S -S`
To generate an assembly file that shows the usage of the instructions themselves.





## For Simple example:

run 
```
gcc-12 fp16simple.c -mavx512fp16 -o avx512pf16simple_O0.S -O0 -S && gcc-12 fp16simple.c -mavx512fp16 -o avx512pf16simple_O3.S -O3 -S && diff avx512pf16simple_O3.S avx512pf16simple_O0.S -y | less
```
You're looking for how when optimizing because of the extra cost of casting the fp16 back to a float32 (due to printf not having native support for fp16) the compiler realizes it's cheaper to just never use FP16, and promote the floats to fp32, then use the classic  `addq` instruction. 

That's in contrast to how when no optimization are requested, the compiler uses the simplest instruction available: `vaddsh` a dedicated instruction from the AVX512FP16 ISA extension to x86_64 that takes a given amount of fp16 values and adds them together. 
