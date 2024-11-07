# Repository with homework assignments from first semester

## Pre-build

Run

```sh
git submodule update --init
```

and create `config.env` in repository root; it should look like this:

```bash
HW_CMAKE="CMake path"
HW_CMAKE_COMPILER="C compiler path"
HW_CMAKE_GENERATOR="CMake generator"
HW_EXE_EXTENSION="executable files extension" # set to ".exe" on Windows and to "none" on Unix-like systems
```

You can also set those environment variables before running build script

## Commands

You can run either `build.sh` or `build.ps1`, they are functionally identical

Arguments in square brackets are optional

Arguments in parentheses must be specified only when running `build` / `run` / `buildTest` / `test` commands

```ps1
./build.ps1 {command} (homework_x) (task_y) [-c|--clear] [-r|--release] [-d|--debug] [-qb|--quiet-build]
./build.sh {command} (homework_x) (task_y) [-c|--clear] [-r|--release] [-d|--debug] [-qb|--quiet-build]
```

When running/testing tasks(s) working directory is set to `homework_x/task_y`

Running task or testing also builds it, so you don't have to run both `build`/`buildTest` and `run`/`test` commands

| Command     | Description                                               |
|-------------|-----------------------------------------------------------|
| `build`     | Build `task_y` in `homework_x`                            |
| `run`       | Build and run `task_y` in `homework_x`                    |
| `buildTest` | Build tests for `task_y` in `homework_x`                  |
| `test`      | Build and run tests for `task_y` in `homework_x`          |
| `buildAll`  | Build all tasks in all homework folders                   |
| `buildAll`  | Build and run tests for all tasks in all homework folders |

| Argument                 | Description                                     |
|--------------------------|-------------------------------------------------|
| `command`                | Command to run                                  |
| `homework`               | The homework folder                             |
| `task`                   | The task folder inside the homework folder      |
| `-c` or `--clear`        | Clear cache before running                      |
| `-r` or `--release`      | Use release configuration when building         |
| `-d` or `--debug`        | Use debug configuration when building (default) |
| `-qb` or `--quiet-build` | Disable output from CMake (even if build fails) |
| `-qt` or `--quiet-test`  | Disable output from tests (even if test fails)  |
