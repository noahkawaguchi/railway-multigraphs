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

# Remove build artifacts
clean:
    rm -rf build
