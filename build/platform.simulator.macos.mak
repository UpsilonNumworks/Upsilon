TOOLCHAIN = apple
EXE = bin

APPLE_PLATFORM = macos
APPLE_PLATFORM_MIN_VERSION = 10.10
EPSILON_TELEMETRY ?= 0

# Build universal binary for both x86_64 and ARM64 by default
# Can be overridden with ARCHS=arm64 or ARCHS=x86_64 for single architecture builds
ARCHS ?= x86_64 arm64

ifdef ARCH
BUILD_DIR := $(BUILD_DIR)/$(ARCH)
else
HANDY_TARGETS_EXTENSIONS = app
endif
