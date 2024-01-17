# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler with C++17 support (e.g. clang 7+, g++ 9+, MSVC 19+)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [cmake](https://cmake.org/) 3.5+
* GNU or BSD [findutils](https://en.wikipedia.org/wiki/Find_(Unix))
* POSIX compatible [make](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html)
* [Node.js](https://nodejs.org/en) 20.10.0+
* [Python](https://www.python.org/) 3.12.1+
* [Rust](https://www.rust-lang.org/en-US/) 1.68.2+
* POSIX compatible [sh](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html)
* Provision additional dev tools with `make -f install.mk`

## Recommended

* [ASDF](https://asdf-vm.com/) 0.10 (run `asdf reshim` after provisioning)
* [direnv](https://direnv.net/) 2
* [c++filt](https://linux.die.net/man/1/c++filt) from binutils
* [clang](https://clang.llvm.org/) (UNIX) or [MSVC](https://gist.github.com/mcandre/5ceb67ad44f6b974d33bcddedcb16e89) (Windows)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (UNIX)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) (UNIX)
* [cpufrequtils](https://linux.die.net/man/1/cpufreq-set) (Linux)
* [llvm](https://llvm.org/) (UNIX)
* macOS [open](https://ss64.com/mac/open.html) or equivalent alias
* [perf](https://perf.wiki.kernel.org/index.php/Main_Page) (Linux)
* [powershell](https://docs.microsoft.com/en-us/powershell/)
* [rez](https://github.com/mcandre/rez) 0.0.15
* [time](https://linux.die.net/man/1/time)

# INSTALL DEPENDENCIES

## macOS

```console
$ conan install -s compiler.cppstd=17 -s compiler=apple-clang -s compiler.version=<version> --build missing . --install-folder build
```

## UNIX (clang)

```console
$ conan install -s compiler.cppstd=17 -s compiler=clang -s compiler.version=<version> --build missing . --install-folder build
```

## UNIX (gcc)

```console
$ conan install -s compiler.cppstd=17 -s compiler=gcc -s compiler.version=<version> --build missing . --install-folder build
```

## Windows

```console
$ conan install -s compiler.cppstd=17 -s compiler=msvc -s compiler.version=<version> -s compiler.runtime=dynamic --build missing . --install-folder build
```

# AUDIT

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
$ open html/index.html
```

# CLEAN

```console
$ rez clean
```
