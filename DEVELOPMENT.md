# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler
* [cmake](https://cmake.org/) 3.4+

## Recommended

* [clang](https://clang.llvm.org/) (macOS users will want to [update](https://gist.github.com/mcandre/6ad2edee00c693b057743aafba20f1df) llvm)
* [perf](https://perf.wiki.kernel.org/index.php/Main_Page)
* [time](https://linux.die.net/man/1/time)
* [c++filt](https://linux.die.net/man/1/c++filt) from binutils
* [powershell](https://docs.microsoft.com/en-us/powershell/)
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

## SPOT CHECK

```console
# CTEST_OUTPUT_ON_FAILURE=1 ctest -C Release
```

## FULL

```console
# cmake --build . --target fuzz
```

# BENCHMARK

```console
$ cmake --build . --target bench
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
