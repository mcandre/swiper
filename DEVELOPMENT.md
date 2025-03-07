# BUILDTIME REQUIREMENTS

* [clang++](https://clang.llvm.org/) 14+ or [g++](https://gcc.gnu.org/) 12+
* [cmake](https://cmake.org/) 3.5+
* [git](https://git-scm.com/) 2.39+
* POSIX compatible [make](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/make.html)
* [Python](https://www.python.org/) 3.12.1+
* [rez](https://github.com/mcandre/rez) 0.0.16
* [Rust](https://www.rust-lang.org/en-US/) 1.68.2+
* [Snyk](https://snyk.io/)
* Provision additional dev tools with `make -f install.mk [-j 4]`

## Recommended

* [ASDF](https://asdf-vm.com/) 0.10 (run `asdf reshim` after provisioning)
* [direnv](https://direnv.net/) 2
* [c++filt](https://linux.die.net/man/1/c++filt) from binutils
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [cpufrequtils](https://linux.die.net/man/1/cpufreq-set) (Linux)
* [llvm](https://llvm.org/) (UNIX)
* macOS [open](https://ss64.com/mac/open.html) or equivalent alias
* [GNU](https://www.gnu.org/)/[BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution) make
* [perf](https://perf.wiki.kernel.org/index.php/Main_Page) (Linux)
* [powershell](https://docs.microsoft.com/en-us/powershell/)
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
