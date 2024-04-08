# Crypto Test

A native app for various crypto calculations using Botan as the back-end.

## Hacking

- Versioning: [SemVer](https://semver.org)
- Commit comments: [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
- Branching model: [GitFlow](https://nvie.com/posts/a-successful-git-branching-model/)

## Build

### Pre-Requisites

- CMake 2.32+
- Conan 2

### Installing Dependencies

Since Conan is used for managing dependencies, following actions need to be carried out first.

#### Conan Profiles

Prepare necessary profiles for Debug and Release configurations. Examples for MSVC are below:

**msvc-dbg**
```
[settings]
arch=x86_64
build_type=Debug
compiler=msvc
compiler.cppstd=20
compiler.runtime=dynamic
compiler.version=193
os=Windows
```

**msvc-rel**
```
[settings]
arch=x86_64
build_type=Release
compiler=msvc
compiler.cppstd=20
compiler.runtime=dynamic
compiler.version=193
os=Windows
```

Then invoke the following command:

```bash
conan install . --profile <PROFILE> --build=missing --deployer=conan_bindeps
```

> *TIP*
>
> If needed, the default `build` folder can be customized by setting the `BUILDDIR` environment variable before invocing `conan install`

### Command-Line Build

```bash
cmake --preset conan-default
cmake --build --preset conan-debug
```

### VSCode Integration

CMake tools support this kind of build / run / debug activities naturally.
