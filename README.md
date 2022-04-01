# swiper: high performance password cracker

# EXAMPLE

```console
$ bench-swiper "00091C080F5E"

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                4.85 |      206,326,418.08 |    0.5% |      0.98 | `crack`
```

Don't be surprised if you get segfaults; Validation is left as an exercise for wrappers.

# TECH TALK SLIDES

[The Road to Gigacracking](https://app.box.com/s/w5n4h9gxhgdzo85e5zvlv1w0e71y2ti3)

# ABOUT

swiper is a library for regenerating passwords from Cisco type 7 encrypted configurations.

# WARNING

Expect API/ABI breakages as we continue to tune the project. Recommended to pin dependency at VCS commit ID.

Performance metrics are questionable on Raspberry Pi; ns/op appears to be weirdly too stable. Perhaps a rebase onto Debian Bullseye could refine the metrics.

# DOCUMENTATION

https://mcandre.github.io/swiper/

# LICENSE

FreeBSD

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

# DISCLAIMER

Intended for educational purposes only.

# DEPRECATED

See [shifty](https://github.com/mcandre/shifty), an FPGA implementation.
