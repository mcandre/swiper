# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench
[100%] Built target bench-swiper

 Performance counter stats for '/home/andrew/go/src/github.com/mcandre/swiper/bin/bench-swiper':

    14,142,417,288      branches                                                      (26.59%)
        71,441,270      branch-misses             #    0.51% of all branches          (26.59%)
    52,333,797,037      cycles                                                        (33.26%)
   157,486,302,942      instructions              #    3.01  insn per cycle           (39.93%)
         2,990,700      cache-references                                              (39.95%)
           361,908      cache-misses              #   12.101 % of all cache refs      (39.98%)
    21,111,865,364      L1-dcache-loads                                               (40.01%)
           934,200      L1-dcache-load-misses     #    0.00% of all L1-dcache hits    (40.04%)
           204,086      LLC-loads                                                     (26.70%)
            22,762      LLC-load-misses           #   11.15% of all LL-cache hits     (26.73%)
   <not supported>      L1-icache-loads
         2,979,717      L1-icache-load-misses                                         (26.73%)
    21,101,510,209      dTLB-loads                                                    (26.70%)
             1,685      dTLB-load-misses          #    0.00% of all dTLB cache hits   (26.70%)
            47,394      iTLB-loads                                                    (26.65%)
           169,742      iTLB-load-misses          #  358.15% of all iTLB cache hits   (26.62%)

      12.958468696 seconds time elapsed

      12.940001000 seconds user
       0.012007000 seconds sys


[100%] Built target bench
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> clang 10 on a System76 Meerkat.
