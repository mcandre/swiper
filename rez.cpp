#include <cstdlib>

#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string_view>
#include <unordered_set>
#include <vector>

using std::literals::string_view_literals::operator""sv;

std::optional<std::string> GetEnvironmentVariable(const std::string &key) {
    char *transient{ nullptr };

#if defined(_WIN32)
    size_t len{ 0 };
    errno = 0;
    _dupenv_s(&transient, &len, key.c_str());

    if (errno != 0) {
        std::cerr << "error querying environment variable " << key << " errno: " << errno << std::endl;
        free(transient);
        return std::nullopt;
    }

    if (transient != nullptr) {
        const std::string s{ transient };
        free(transient);
        return std::optional(s);
    }

    free(transient);
#else
    transient = getenv(key.c_str());

    if (transient != nullptr) {
        const std::string s{ transient };
        return std::optional(s);
    }
#endif

    return std::nullopt;
}

static int cmake_init() {
    return system("cmake -B build .");
}

static int lint() {
    const int status{ cmake_init() };

    if (status) {
        return status;
    }

    return system("cmake --build build --target lint");
}

static int doc() {
    const int status{ cmake_init() };

    if (status) {
        return status;
    }

    return system("cmake --build build --target doc");
}

static int build() {
    const int status{ cmake_init() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build build --config Release");
}

static int snyk() {
#if defined(_WIN32)
    const std::string home_env_var_name{ "USERPROFILE" };
#else
    const std::string home_env_var_name{ "HOME" };
#endif

    const std::optional<std::string> home_opt{ GetEnvironmentVariable(home_env_var_name) };

    if (!home_opt.has_value()) {
        std::cerr << "error missing environment variable: ";
        std::cerr << home_env_var_name;
        return EXIT_FAILURE;
    }

    const std::filesystem::path home{ *home_opt };
    const std::filesystem::path conan_data_dir{ home / ".conan" / "data" };
    std::stringstream command;
    command << "snyk test --unmanaged --trust-policies"
            << " "
            << conan_data_dir;

    const int status{ system(command.str().c_str()) };

    if (status) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int audit() {
    return snyk();
}

static int test() {
    const int status{ build() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("ctest -C Release");
}

static int install() {
    const int status{ build() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build build --target install");
}

static int uninstall() {
    const int status{ cmake_init() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build build --target uninstall");
}

static int bench() {
    const int status{ install() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build build --target bench");
}

static int fuzz() {
    const int status{ install() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build build --target fuzz");
}

static int clean_doc() {
    std::filesystem::remove_all("html");
    std::filesystem::remove_all("latex");
    return EXIT_SUCCESS;
}

static int clean_bin() {
    std::filesystem::remove_all("bin");
    return EXIT_SUCCESS;
}

static int clean_cmake() {
    std::filesystem::remove_all("build");
    return EXIT_SUCCESS;
}

static int clean() {
    clean_doc();
    clean_bin();
    clean_cmake();
    return EXIT_SUCCESS;
}

int main(int argc, const char **argv) {
    const std::vector<std::string_view> args{ argv + 1, argv + argc };
    const std::function<int()> default_task{ bench };

    if (args.empty()) {
        if (default_task()) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    const std::map<std::string_view, std::function<int()>> tasks{
        { "clean"sv, clean },
        { "clean_doc"sv, clean_doc },
        { "clean_bin"sv, clean_bin },
        { "clean_cmake"sv, clean_cmake },
        { "cmake_init"sv, cmake_init },
        { "snyk"sv, snyk },
        { "audit"sv, audit },
        { "bench"sv, bench },
        { "build"sv, build },
        { "doc"sv, doc },
        { "fuzz"sv, fuzz },
        { "lint"sv, lint },
        { "test"sv, test },
        { "install"sv, install },
        { "uninstall"sv, uninstall }
    };

    if (args.front() == "-l") {
        for (const auto &[name, _] : tasks) {
            std::cout << name << std::endl;
        }

        return EXIT_SUCCESS;
    }

    for (const std::string_view &arg : args) {
        try {
            const std::function<int()> f{ tasks.at(arg) };

            if (f()) {
                return EXIT_FAILURE;
            }
        } catch (std::out_of_range &e) {
            std::cerr << "no such task: " << arg << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
