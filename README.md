# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench
[100%] Built target bench-swiper

 Performance counter stats for '/home/andrew/go/src/github.com/mcandre/swiper/bin/bench-swiper':

    16,208,677,591      branches                                                      (26.60%)
           271,256      branch-misses             #    0.00% of all branches          (26.63%)
    63,897,918,244      cycles                                                        (33.30%)
   197,654,241,293      instructions              #    3.09  insn per cycle           (39.97%)
         2,054,067      cache-references                                              (40.00%)
           381,448      cache-misses              #   18.570 % of all cache refs      (40.03%)
    27,219,024,812      L1-dcache-loads                                               (40.05%)
           745,106      L1-dcache-load-misses     #    0.00% of all L1-dcache hits    (40.05%)
           147,773      LLC-loads                                                     (26.71%)
            24,652      LLC-load-misses           #   16.68% of all LL-cache hits     (26.69%)
   <not supported>      L1-icache-loads
         2,153,876      L1-icache-load-misses                                         (26.69%)
    27,191,872,880      dTLB-loads                                                    (26.67%)
             6,544      dTLB-load-misses          #    0.00% of all dTLB cache hits   (26.65%)
            41,271      iTLB-loads                                                    (26.62%)
            56,959      iTLB-load-misses          #  138.01% of all iTLB cache hits   (26.60%)

      15.825956703 seconds time elapsed

      15.812708000 seconds user
       0.007996000 seconds sys
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> Median report on a System76 Meerkat
