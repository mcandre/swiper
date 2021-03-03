# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench
 Performance counter stats for '/home/andrew/go/src/github.com/mcandre/swiper/bin/bench-swiper':

    14,051,678,020      branches                                                      (26.76%)
         1,463,613      branch-misses             #    0.01% of all branches          (26.72%)
    45,910,267,392      cycles                                                        (33.38%)
   144,001,430,340      instructions              #    3.14  insn per cycle           (40.03%)
         3,444,882      cache-references                                              (40.03%)
           387,437      cache-misses              #   11.247 % of all cache refs      (39.99%)
    26,003,662,473      L1-dcache-loads                                               (39.98%)
         1,010,140      L1-dcache-load-misses     #    0.00% of all L1-dcache hits    (39.95%)
           184,860      LLC-loads                                                     (26.61%)
            16,435      LLC-load-misses           #    8.89% of all LL-cache hits     (26.61%)
   <not supported>      L1-icache-loads
         4,099,645      L1-icache-load-misses                                         (26.61%)
    26,066,513,350      dTLB-loads                                                    (26.61%)
             8,389      dTLB-load-misses          #    0.00% of all dTLB cache hits   (26.68%)
            48,676      iTLB-loads                                                    (26.71%)
           796,784      iTLB-load-misses          # 1636.91% of all iTLB cache hits   (26.75%)

      11.245572632 seconds time elapsed

      11.217501000 seconds user
       0.007998000 seconds sys
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> System76 Meerkat
