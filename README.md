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

## Commands

Commands can be executed in two ways: passed as an argument or
ran as function from dot sourced script (you have to dot source script only once):

```ps1
# argument
./buildAndTest {command} {task path}
./buildAndTest {command2} {task path}

# dot-sourced
. ./buildAndTest
Cmake-{command} {task path}
Cmake-{command2} {task path}
```

Running task or test also builds it, so you don't have to run both
`build`/`buildTest` and `run`/`test` commands

### Examples

```ps1
# build
./buildAndTest build "homework_x/task_y"

# run
./buildAndTest run "homework_x/task_y"

# build test
./buildAndTest buildTest "homework_x/task_y"

# run test
./buildAndTest test "homework_x/task_y"
```
