# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench
Scanning dependencies of target bench-swiper
[ 33%] Building CXX object CMakeFiles/bench-swiper.dir/src/cmd/bench-swiper/main.cpp.o
[ 66%] Building CXX object CMakeFiles/bench-swiper.dir/src/swiper.cpp.o
[100%] Linking CXX executable bin/bench-swiper
[100%] Built target bench-swiper

 Performance counter stats for '/home/andrew/go/src/github.com/mcandre/swiper/bin/bench-swiper':

    14,087,594,659      branches                                                      (26.47%)
           124,694      branch-misses             #    0.00% of all branches          (26.55%)
    21,312,457,647      cycles                                                        (33.23%)
    65,843,279,773      instructions              #    3.09  insn per cycle           (39.92%)
           870,135      cache-references                                              (40.00%)
           182,955      cache-misses              #   21.026 % of all cache refs      (40.07%)
    13,931,568,041      L1-dcache-loads                                               (40.13%)
           227,029      L1-dcache-load-misses     #    0.00% of all L1-dcache hits    (40.13%)
            34,210      LLC-loads                                                     (26.76%)
             7,333      LLC-load-misses           #   21.44% of all LL-cache hits     (26.75%)
   <not supported>      L1-icache-loads
           665,974      L1-icache-load-misses                                         (26.75%)
    14,047,049,130      dTLB-loads                                                    (26.71%)
             2,245      dTLB-load-misses          #    0.00% of all dTLB cache hits   (26.63%)
            14,596      iTLB-loads                                                    (26.56%)
            19,812      iTLB-load-misses          #  135.74% of all iTLB cache hits   (26.49%)

       5.322955041 seconds time elapsed

       5.321860000 seconds user
       0.000000000 seconds sys
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> System76 Meerkat
