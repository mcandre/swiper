# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler
* [cmake](https://cmake.org/) 3.4+

## Recommended

* [perf](https://perf.wiki.kernel.org/index.php/Main_Page)
* [time](https://linux.die.net/man/1/time)
* [karp](https://github.com/mcandre/karp) (`go get github.com/mcandre/karp/...`)

# LINT

```console
# cmake --build . --target lint
```

# COMPILE

```console
# cmake --build . --config Release
```

# TEST

```console
# cmake --build . --target fuzz
```

# BENCHMARK

```console
$ cmake --build . --target perf
```

# DOCUMENT

```console
# cmake --build . --target doc
$ karp html/index.html
```

# CLEAN

```console
# ./clean-cmake.sh
```
