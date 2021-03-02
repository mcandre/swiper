# swiper: high performance Cisco password cracker

# EXAMPLE<sup>1</sup>

```console
$ /usr/bin/time --verbose bin/bench-swiper
        Command being timed: "bin/bench-swiper"
        User time (seconds): 12.48
        System time (seconds): 0.00
        Percent of CPU this job got: 100%
        Elapsed (wall clock) time (h:mm:ss or m:ss): 0:12.48
        Average shared text size (kbytes): 0
        Average unshared data size (kbytes): 0
        Average stack size (kbytes): 0
        Average total size (kbytes): 0
        Maximum resident set size (kbytes): 3656
        Average resident set size (kbytes): 0
        Major (requiring I/O) page faults: 0
        Minor (reclaiming a frame) page faults: 142
        Voluntary context switches: 1
        Involuntary context switches: 3
        Swaps: 0
        File system inputs: 0
        File system outputs: 0
        Socket messages sent: 0
        Socket messages received: 0
        Signals delivered: 0
        Page size (bytes): 4096
        Exit status: 0
```

# DOCUMENTATION

https://mcandre.github.io/swiper/

# CONTRIBUTING

For more details on developing swiper itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

<sup>1</sup> upper bound observed with clang 10 on a Surface Pro 7 in WSL.
