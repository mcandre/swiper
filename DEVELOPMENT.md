# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler with C++17 support
* [cmake](https://cmake.org/) 3.4+
* [conan](https://conan.io/) 1.35+

## Recommended

* [clang](https://clang.llvm.org/) or [clang-cl.exe](https://gist.github.com/mcandre/5ceb67ad44f6b974d33bcddedcb16e89)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [llvm](https://llvm.org/)
* [perf](https://perf.wiki.kernel.org/index.php/Main_Page) (Linux)
* [cpufrequtils](https://linux.die.net/man/1/cpufreq-set) (Linux)
* [time](https://linux.die.net/man/1/time)
* [c++filt](https://linux.die.net/man/1/c++filt) from binutils
* [powershell](https://docs.microsoft.com/en-us/powershell/)
* [karp](https://github.com/mcandre/karp) (`go get github.com/mcandre/karp/...`)

macOS users may need additional patches:

* [Grow](https://github.com/mcandre/dotfiles/blob/master/.profile.d/xcode.sh) Xcode PATH

# INSTALL DEPENDENCIES

```console
$ conan install -s compiler.cppstd=17 [-s compiler={clang,apple-clang} -s compiler.version={10,12.0}] --build missing .
```

# INITIALIZE CMAKE

```console
$ cmake [-T ClangCL] .
```

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
# ./clean.sh
```
