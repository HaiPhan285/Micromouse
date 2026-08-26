#!/usr/bin/env bash

set -euo pipefail

find app common tests -type f \( -name '*.h' -o -name '*.c' -o -name '*.cc' \) -print0 \
  | xargs -0 --no-run-if-empty clang-format --dry-run --Werror
