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
* [rez](https://github.com/mcandre/rez) 0.0.9
* [snyk](https://www.npmjs.com/package/snyk) 1.893.0 (`npm install -g snyk@1.893.0`)
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

# SECURITY AUDIT

```console
$ rez audit
```

# LINT

```console
$ rez lint
```

# COMPILE

```console
$ rez [build]
```

# TEST

## SPOT CHECK

```console
$ rez test
```

## FULL

```console
$ rez fuzz
```

# BENCHMARK

```console
$ rez bench
```

# DOCUMENT

```console
# rez doc
$ karp html/index.html
```

# CLEAN

```console
$ rez clean
```
