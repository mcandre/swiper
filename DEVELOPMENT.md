# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler with C++17 support (e.g. clang 7+, g++ 9+, MSVC 19+)
* [cmake](https://cmake.org/) 3.4+
* [conan](https://conan.io/) 1.35+

## Recommended

* [c++filt](https://linux.die.net/man/1/c++filt) from binutils
* [clang](https://clang.llvm.org/) (UNIX) or [MSVC](https://gist.github.com/mcandre/5ceb67ad44f6b974d33bcddedcb16e89) (Windows)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (UNIX)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) (UNIX)
* [cpufrequtils](https://linux.die.net/man/1/cpufreq-set) (Linux)
* [karp](https://github.com/mcandre/karp) (`go get github.com/mcandre/karp/...`)
* [llvm](https://llvm.org/) (UNIX)
* [perf](https://perf.wiki.kernel.org/index.php/Main_Page) (Linux)
* [powershell](https://docs.microsoft.com/en-us/powershell/)
* [pyenv](https://github.com/pyenv/pyenv)
* [time](https://linux.die.net/man/1/time)

macOS users may need additional patches:

* [Grow](https://github.com/mcandre/dotfiles/blob/master/.profile.d/xcode.sh) Xcode PATH

# INSTALL DEPENDENCIES

## macOS

```console
$ conan install -s compiler.cppstd=17 -s compiler=apple-clang -s compiler.version=<version> --build missing .
```

## UNIX (clang)

```console
$ conan install -s compiler.cppstd=17 -s compiler=clang -s compiler.version=<version> --build missing .
```

## UNIX (gcc)

```console
$ conan install -s compiler.cppstd=17 -s compiler=gcc -s compiler.version=<version> --build missing .
```

## Windows

```console
$ conan install -s compiler.cppstd=17 -s compiler=msvc -s compiler.version=<version> -s compiler.runtime=dynamic --build missing .
```

# INITIALIZE CMAKE

```console
$ cmake .
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
