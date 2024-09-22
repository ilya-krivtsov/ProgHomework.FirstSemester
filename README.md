# Repository with homework assignments from first semester

## Pre-build

Run

```sh
git submodule update --init
```

and create `buildConfig.json` in repository root; it should look like this:

```jsonc
{
    "c_compiler": "C compiler path",
    "cxx_compiler": "C++ compiler path",
    "generator": "CMake generator",
    "cmake": "CMake path",
    "executableExtension": "executable files extension" // set to ".exe" on Windows and to "" on Unix-like systems
}
```

## Build

```ps1
buildAndTest.ps1 build "homework_x/task_y"
```

or

```ps1
. ./buildAndTest.ps1
CMake-Build "homework_x/task_y"
```

## Running tests

```ps1
buildAndTest.ps1 test "homework_x/task_y"
```

or

```ps1
. ./buildAndTest.ps1
CMake-Test "homework_x/task_y"
```
