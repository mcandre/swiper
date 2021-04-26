# swiper: a high performance password cracker

# EXAMPLE

```console
$ bench-swiper "00091C080F5E"
2021-04-26T18:28:54-05:00
Running bench-swiper
Run on (8 X 1497.6 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 512 KiB (x4)
  L3 Unified 8192 KiB (x1)
Load Average: 0.30, 0.20, 0.11
------------------------------------------------------------------------
Benchmark                              Time             CPU   Iterations
------------------------------------------------------------------------
Decrypt/iterations:1073741824       4.24 ns         4.24 ns   1073741824
```

Don't be surprised if you get segfaults; Validation is left as an exercise for wrappers.

# TECH TALK SLIDES

[The Road to Gigacracking](https://app.box.com/s/w5n4h9gxhgdzo85e5zvlv1w0e71y2ti3)

# ABOUT

swiper is a library for regenerating passwords from Cisco type 7 encrypted configurations.

# WARNING

Expect API/ABI breakages as we continue to tune the project. Recommended to pin dependency at VCS commit ID.

# DOCUMENTATION

https://mcandre.github.io/swiper/

# LICENSE

FreeBSD

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

# DISCLAIMER

Intended for educational purposes only.
