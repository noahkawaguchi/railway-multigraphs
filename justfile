####################################################################################################
# Config
####################################################################################################

preset := '--preset conan-release'
bin-dir := 'build/Release'
bin := 'railway-multigraphs'

####################################################################################################
# Build lifecycle
####################################################################################################

# Build the project (default recipe)
build:
    if ! test -d build; then \
        conan install . --build=missing --profile:all=profiles/detect; \
        cmake {{ preset }}; \
    fi

    cmake --build {{ preset }}

# Build and run the main executable
run: build
    ./{{ bin-dir }}/{{ bin }}

# Full clean rebuild
rebuild: clean build

# Remove build artifacts
clean:
    rm -rf build

####################################################################################################
# Testing and quality
####################################################################################################

# Run tests, lints, format checking, and spell checking to match CI
all-checks: (test '--progress') lint fmt-check spell-check

# Build and run tests
test *ARGS: build
    ctest {{ preset }} --output-on-failure {{ ARGS }}

# Build and lint with Clang-Tidy
lint: build
    clang-tidy -p {{ bin-dir }} --quiet --use-color --warnings-as-errors='*' \
        $(jq -r '.[].file' {{ bin-dir }}/compile_commands.json | sort -u)

# Check formatting with Clang-Format
fmt-check:
    git ls-files -z '*.cpp' '*.hpp' | xargs -0 clang-format --dry-run --Werror \
        && echo 'Formatting check passed'

# Check spelling with Codebook
spell-check:
    git ls-files -z | xargs -0 codebook-lsp lint
