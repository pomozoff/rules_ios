# iOS Rules for [Bazel](https://bazel.build)

![master](https://github.com/bazel-ios/rules_ios/workflows/CI-master/badge.svg)

`rules_ios` is [community developed Bazel rules](https://bazel-ios.github.io/)
that enable you to do iOS development with Bazel end to end.

It seamlessly Bazel builds iOS applications originally written under Xcode with
minimal-to-no code changes. It often re-uses ideas and code from `rules_swift`
and `rules_apple` and it isn't tied to untested or unused features. It generates
Xcode projects that _just work_ and makes using Apple Silicon with Bazel a
breeze.

_Learn more at [bazel-ios.github.io](https://bazel-ios.github.io/)_

## Reference documentation

[Click here](https://github.com/bazel-ios/rules_ios/tree/master/docs)
for the documentation.

## Getting started

### WORKSPACE setup

Add the following lines to your `WORKSPACE` file.
See the [latest release](https://github.com/bazel-ios/rules_ios/releases/latest) for an up-to-date snippet!

```python
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# See https://github.com/bazel-ios/rules_ios/releases/latest
http_archive(
    name = "build_bazel_rules_ios",
    sha256 = "bcff62919ea0be2b0f1e75dc6174029596d468bce09a442fe8523c5f0130ceb0",
    url = "https://github.com/bazelbuild/rules_ios/releases/download/1.0.0/rules_ios.1.0.0.tar.gz",
)

load(
    "@build_bazel_rules_ios//rules:repositories.bzl",
    "rules_ios_dependencies"
)

rules_ios_dependencies()

load(
    "@build_bazel_rules_apple//apple:repositories.bzl",
    "apple_rules_dependencies",
)

apple_rules_dependencies()

load(
    "@build_bazel_rules_swift//swift:repositories.bzl",
    "swift_rules_dependencies",
)

swift_rules_dependencies()

load(
    "@build_bazel_apple_support//lib:repositories.bzl",
    "apple_support_dependencies",
)

apple_support_dependencies()

load(
    "@com_google_protobuf//:protobuf_deps.bzl",
    "protobuf_deps",
)

protobuf_deps()
```

rules_ios pulls a vetted sha of `rules_apple` and `rules_swift` - you can find the versions in [`repositories.bzl`](https://github.com/bazel-ios/rules_ios/tree/master/rules/repositories.bzl).

### iOS applications

rules_ios supports all the primitives like apps, extensions, app clips, and widgets

For example, create an iOS app like so:

```python
load("@build_bazel_rules_ios//rules:app.bzl", "ios_application")

ios_application(
    name = "iOS-App",
    srcs = glob(["*.swift"]),
    bundle_id = "com.example.ios-app",
    minimum_os_version = "12.0",
    visibility = ["//visibility:public"],
)
```

### Xcode project generation

There are currently at least three options to generate Xcode projects that build with Bazel.

`rules_ios` has its own project generator that is considered stable and ready to be used in production. Here's a minimal example of how to load it in your `BUILD` file:

```python
load("@build_bazel_rules_ios//rules:xcodeproj.bzl", "xcodeproj")

xcodeproj(
    name = "MyXcode",
    bazel_path = "bazelisk",
    deps = [ ":iOS-App"]
)
```

Checkout [legacy_xcodeproj.bzl](https://github.com/bazel-ios/rules_ios/blob/master/rules/legacy_xcodeproj.bzl) for available attributes.

Alternatively the `bazel-ios` org has forks of both [XCHammer](https://github.com/bazel-ios/xchammer) and [Tulsi](https://github.com/bazel-ios/tulsi) with some changes to make it work with `rules_ios` and optionally enable the "build with Xcode" use case. This is currently considered "alpha" software and not recommended to be used in production. If you want to test it out when loading `rules_ios` per [WORKSPACE setup](#workspace-setup) instructions load `rules_ios` dependencies like so

```python
rules_ios_dependencies(load_xchammer_dependencies = True)
```

and additionally declare the `xchammer_xcodeproj` macro this way

```python
load("@build_bazel_rules_ios//rules:xchammer_xcodeproj.bzl", "xchammer_xcodeproj")

xchammer_xcodeproj(
    name = "MyXcode",
    bazel_path = "bazelisk",
    generate_xcode_schemes = False # if True enables "build with Xcode"
    targets = [ ":iOS-App"]
)
```

Checkout [xchammer_xcodeproj.bzl](https://github.com/bazel-ios/rules_ios/blob/master/rules/xchammer_xcodeproj.bzl) for available attributes.

Last, [rules_xcodeproj](https://github.com/MobileNativeFoundation/rules_xcodeproj) is another great alternative and we're working with them to better integrate it with `rules_ios`. Checkout [examples/rules_ios](https://github.com/MobileNativeFoundation/rules_xcodeproj/tree/main/examples/rules_ios) for examples of how to use it with `rules_ios`.

### Frameworks

Static frameworks with Xcode semantics - easily port existing apps to Bazel

```python
# Builds a static framework
apple_framework(
    name = "Static",
    srcs = glob(["static/*.swift"]),
    bundle_id = "com.example.b",
    data = ["Static.txt"],
    infoplists = ["Info.plist"],
    platforms = {"ios": "12.0"},
    deps = ["//tests/ios/frameworks/dynamic/c"],
)
```

### Dynamic iOS frameworks

rules_ios builds frameworks as static or dynamic - just flip
`link_dynamic`

```python
apple_framework(
    name = "Dynamic",
    srcs = glob(["dynamic/*.swift"]),
    bundle_id = "com.example.a",
    infoplists = ["Info.plist"],
    link_dynamic = True,
    platforms = {"ios": "12.0"},
    deps = [":Static"],
)
```

### Testing - UI / Unit

Easily test iOS applications with Bazel - ui and unit testing rules

```python
load("//rules:test.bzl", "ios_unit_test")

ios_unit_test(
    name = "Unhosted",
    srcs = ["some.swift"],
    minimum_os_version = "11.0",
    deps = [":Dynamic"]
)
```

### Apple Silicon ready

- Automatically run legacy deps on Apple Silicon - it _just works_ by running [arm64-to-sim](https://github.com/bogo/arm64-to-sim) and more.
- Testing mechanisms to easily test in ephemeral VMs

## Examples

See the [tests](https://github.com/bazel-ios/rules_ios/tree/master/tests)
directory for tested use cases.

## Special notes about debugging xcode projects

Debugging does not work in sandbox mode, due to issue [#108](https://github.com/bazel-ios/rules_ios/issues/108). The workaround for now is to disable sandboxing in the .bazelrc file.

Bazel version required by current rules is [here](https://github.com/bazel-ios/rules_ios/blob/master/.bazelversion)

**Xcode 13** and above supported, to find the last `SHA` with support for older versions see the list of git tags.

## Xcode 14.3 support on Bazel 5

If you're using Bazel 5 and want to update to Xcode 14.3 there's an incompatibility issue related to [this commit](https://github.com/bazelbuild/bazel//commit/43dadb275b3f9690242bf2d94a0757c721d231a9) in Bazel 6. In order to fix that you can use our fork of `apple_support` which will override the toolchain and fix the Xcode locator compilation invocation. Just add this to your `.bazelrc`:

```python
build --apple_crosstool_top=@local_config_apple_cc//:toolchain
build --crosstool_top=@local_config_apple_cc//:toolchain
build --host_crosstool_top=@local_config_apple_cc//:toolchain
common --repo_env=BAZEL_DO_NOT_DETECT_CPP_TOOLCHAIN=1
```

Additionally if your Xcode is not installed under `/Appplications` add this:

```python
common --repo_env=BAZEL_ALLOW_NON_APPLICATIONS_XCODE=1
```

Finally, when loading `rules_ios` dependecies in your `WORKSPACE` file pass this flag:

```python
rules_ios_dependencies(override_toolchain = True)
```