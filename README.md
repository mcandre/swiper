# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ cmake --build . --target bench

 Performance counter stats for 'bin/bench-swiper':

    18,827,871,861      cycles

    60,062,771,732      instructions              #    3.19  insn per cycle
           803,219      cache-references

            87,923      cache-misses              #   10.946 % of all cache refs

       4.644529082 seconds time elapsed

       4.628538000 seconds user
       0.008000000 seconds sys
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> clang 10 on a System76 Meerkat.
