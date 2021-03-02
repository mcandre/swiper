# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ sudo perf stat -e 'cycles,instructions,cache-references,cache-misses' bench-swiper

 Performance counter stats for 'bench-swiper':

    65,851,151,756      cycles                    #    4.069 GHz

   208,256,784,578      instructions              #    3.16  insn per cycle
         2,619,217      cache-references          #    0.162 M/sec

           155,465      cache-misses              #    5.936 % of all cache refs

      16.219274669 seconds time elapsed

      16.169212000 seconds user
       0.016009000 seconds sys
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> clang 10 on a System76 Meerkat.
