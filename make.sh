#!/usr/bin/env bash

set -euo pipefail

# Function to display usage
usage() {
  echo "Usage: $0 -t <target_name> [-a <app_name>] [-r] [-c]"
  exit 1
}

# Initialize variables
TARGET=""
APP=""
MODE="Debug"
CLEAN=0

# Parse command-line arguments
while getopts ":t:a:rc" opt; do
  case ${opt} in
    ( t )
      TARGET="$OPTARG"
      ;;
    ( a )
      APP="$OPTARG"
      ;;
    (r)
      MODE="Release"
      ;;
    (c)
      CLEAN=1
      ;;
    (\?)
      echo "Invalid option: -$OPTARG" 1>&2
      usage
      ;;
    (:)
      echo "Option -$OPTARG requires an argument." 1>&2
      usage
      ;;
  esac
done

# Check if the target name is provided
if [[ -z "$TARGET" || ! "$TARGET" =~ ^[A-Za-z0-9._-]+$ ]]; then
  usage
fi

if ((CLEAN)); then
  echo "Removing build/$TARGET"
  rm -rf -- "build/$TARGET"
fi

cmake --preset "$TARGET" -DTARGET_APP="$APP" -DCMAKE_BUILD_TYPE="$MODE"
cmake --build "build/$TARGET"
