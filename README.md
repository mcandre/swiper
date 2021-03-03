# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench
[100%] Built target bench-swiper

 Performance counter stats for '/home/andrew/go/src/github.com/mcandre/swiper/bin/bench-swiper':

    88,125,158,735      cycles                                                        (38.44%)
   296,294,792,393      instructions              #    3.36  insn per cycle           (46.15%)
         4,889,337      cache-references                                              (46.17%)
           463,043      cache-misses              #    9.470 % of all cache refs      (46.20%)
    45,045,731,691      L1-dcache-loads                                               (46.18%)
         1,818,491      L1-dcache-load-misses     #    0.00% of all L1-dcache hits    (46.17%)
           275,101      LLC-loads                                                     (30.81%)
            27,321      LLC-load-misses           #    9.93% of all LL-cache hits     (30.79%)
   <not supported>      L1-icache-loads
         6,486,480      L1-icache-load-misses                                         (30.76%)
    45,110,939,794      dTLB-loads                                                    (30.75%)
             5,604      dTLB-load-misses          #    0.00% of all dTLB cache hits   (30.69%)
           119,156      iTLB-loads                                                    (30.73%)
           922,974      iTLB-load-misses          #  774.59% of all iTLB cache hits   (30.75%)

      21.655134632 seconds time elapsed

      21.580937000 seconds user
       0.035988000 seconds sys


[100%] Built target bench
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> clang 10 on a System76 Meerkat.
