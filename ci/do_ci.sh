#!/bin/bash

set -e

[ -z "${SRC_DIR}" ] && export SRC_DIR="`pwd`"
[ -z "${BUILD_DIR}" ] && export BUILD_DIR=$HOME/build
mkdir -p "${BUILD_DIR}"
[ -z "${PLUGIN_DIR}" ] && export PLUGIN_DIR=$HOME/plugin
mkdir -p "${PLUGIN_DIR}"

BAZEL_OPTIONS=""
BAZEL_TEST_OPTIONS="$BAZEL_OPTIONS --test_output=errors"

if [[ "$1" == "cmake.test" ]]; then
  cd "${BUILD_DIR}"
  rm -rf *
  cmake -DCMAKE_BUILD_TYPE=Debug  \
        -DCMAKE_CXX_FLAGS="-Werror" \
        "${SRC_DIR}"
  make
  make test
  exit 0
elif [[ "$1" == "cmake.build_example_plugin" ]]; then
  cd "${BUILD_DIR}"
  rm -rf *
  cat <<EOF > export.map
{
  global:
    OpenTelemetryMakeFactoryImpl;
  local: *;
};
EOF

  LINKER_FLAGS="\
    -static-libstdc++ \
    -static-libgcc \
    -Wl,--version-script=${PWD}/export.map \
  "
  cmake -DCMAKE_BUILD_TYPE=Debug  \
        -DCMAKE_CXX_FLAGS="-Werror" \
        -DCMAKE_EXE_LINKER_FLAGS="$LINKER_FLAGS" \
        -DCMAKE_SHARED_LINKER_FLAGS="$LINKER_FLAGS" \
        "${SRC_DIR}"
  make example_plugin
  cp examples/plugin/plugin/libexample_plugin.so ${PLUGIN_DIR}
  exit 0
elif [[ "$1" == "cmake.test_example_plugin" ]]; then
  cd "${BUILD_DIR}"
  rm -rf *
  cmake -DCMAKE_BUILD_TYPE=Debug  \
        -DCMAKE_CXX_FLAGS="-Werror" \
        "${SRC_DIR}"
  make load_plugin_example
  examples/plugin/load/load_plugin_example ${PLUGIN_DIR}/libexample_plugin.so /dev/null
  exit 0
elif [[ "$1" == "bazel.test" ]]; then
  bazel build $BAZEL_OPTIONS -- //...
  bazel test $BAZEL_TEST_OPTIONS //...
  exit 0
elif [[ "$1" == "bazel.asan" ]]; then
  bazel test --config=asan $BAZEL_TEST_OPTIONS //...
  exit 0
elif [[ "$1" == "format" ]]; then
  tools/format.sh
  CHANGED="$(git ls-files --modified)"
  if [[ ! -z "$CHANGED" ]]; then
    echo "The following files have changes:"
    echo "$CHANGED"
    exit 1
  fi
  exit 0
fi

echo "Invalid do_ci.sh target, see ci/README.md for valid targets."
exit 1
