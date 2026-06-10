# Regular iterative build (default recipe)
build:
    cmake --build build

# Build and run the main executable
run: build
    ./build/railway-multigraphs

# Build and run tests
test: build
    ctest --test-dir build --output-on-failure --verbose

# Full clean rebuild
rebuild: clean && build
    cmake -B build -DCMAKE_BUILD_TYPE=Release

# Lint with Clang-Tidy
lint: build
    run-clang-tidy "$PWD/(src|tests)/" -p build -quiet -use-color -warnings-as-errors '*'

# Check formatting with Clang-Format
fmt-check:
    git ls-files '*.cpp' '*.hpp' | xargs clang-format --dry-run --Werror \
        && echo 'Formatting check passed'

# Remove build artifacts
clean:
    rm -rf build
