# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench
[100%] Built target bench-swiper

 Performance counter stats for '/home/andrew/go/src/github.com/mcandre/swiper/bin/bench-swiper':

    21,038,274,965      branches                                                      (26.64%)
         3,112,534      branch-misses             #    0.01% of all branches          (26.63%)
    92,350,458,733      cycles                                                        (33.30%)
   299,906,358,474      instructions              #    3.25  insn per cycle           (39.98%)
         7,234,623      cache-references                                              (39.97%)
           557,706      cache-misses              #    7.709 % of all cache refs      (39.98%)
    45,157,429,230      L1-dcache-loads                                               (40.02%)
         2,266,031      L1-dcache-load-misses     #    0.01% of all L1-dcache hits    (40.04%)
           418,719      LLC-loads                                                     (26.68%)
            26,788      LLC-load-misses           #    6.40% of all LL-cache hits     (26.68%)
   <not supported>      L1-icache-loads
         9,447,006      L1-icache-load-misses                                         (26.67%)
    45,169,191,341      dTLB-loads                                                    (26.66%)
             9,377      dTLB-load-misses          #    0.00% of all dTLB cache hits   (26.68%)
           206,710      iTLB-loads                                                    (26.68%)
         1,474,790      iTLB-load-misses          #  713.46% of all iTLB cache hits   (26.66%)

      22.787798904 seconds time elapsed

      22.644404000 seconds user
       0.083986000 seconds sys


[100%] Built target bench
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> clang 10 on a System76 Meerkat.
