# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler
* [cmake](https://cmake.org/) 3.4+
* [time](https://linux.die.net/man/1/time)

## Recommended

* [perf](https://perf.wiki.kernel.org/index.php/Main_Page)
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
$ cmake --build . --target bench
```

# INSPECT

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
