# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench
Scanning dependencies of target bench-swiper
[ 33%] Building CXX object CMakeFiles/bench-swiper.dir/src/cmd/bench-swiper/main.cpp.o
[ 66%] Linking CXX executable bin/bench-swiper
[100%] Built target bench-swiper

 Performance counter stats for '/home/andrew/go/src/github.com/mcandre/swiper/bin/bench-swiper':

    17,180,995,987      branches                                                      (26.63%)
        94,423,905      branch-misses             #    0.55% of all branches          (26.65%)
    72,408,800,748      cycles                                                        (33.33%)
   217,603,444,989      instructions              #    3.01  insn per cycle           (40.02%)
         4,262,965      cache-references                                              (40.04%)
           509,961      cache-misses              #   11.963 % of all cache refs      (40.07%)
    30,265,397,497      L1-dcache-loads                                               (40.06%)
         1,500,327      L1-dcache-load-misses     #    0.00% of all L1-dcache hits    (40.04%)
           274,589      LLC-loads                                                     (26.65%)
            29,007      LLC-load-misses           #   10.56% of all LL-cache hits     (26.62%)
   <not supported>      L1-icache-loads
         3,982,462      L1-icache-load-misses                                         (26.63%)
    30,233,681,024      dTLB-loads                                                    (26.66%)
             4,932      dTLB-load-misses          #    0.00% of all dTLB cache hits   (26.66%)
            84,476      iTLB-loads                                                    (26.66%)
           329,528      iTLB-load-misses          #  390.08% of all iTLB cache hits   (26.63%)

      17.925828072 seconds time elapsed

      17.887710000 seconds user
       0.020008000 seconds sys


[100%] Built target bench
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> clang 10 on a System76 Meerkat.
