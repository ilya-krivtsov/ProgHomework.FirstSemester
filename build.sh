#!/bin/bash

build_dir='build'

if [[ -f config.env ]]; then
    source config.env
fi

cmake=$HW_CMAKE
compiler=$HW_CMAKE_COMPILER
generator=$HW_CMAKE_GENERATOR
executable_extension=$HW_EXE_EXTENSION

if [[ -z $cmake ]]; then
    echo "cmake not specified"
    exit 1
fi

if [[ -z $compiler ]]; then
    echo "compiler not specified"
    exit 1
fi

if [[ -z $generator ]]; then
    echo "generator not specified"
    exit 1
fi

if [[ -z $executable_extension ]]; then
    echo "warning: executable extension not specified - assuming there is no executable extension"
    executable_extension='none'
fi

if [[ $executable_extension = 'none' ]]; then
    executable_extension=''
fi

# $1: quiet
# $@: command and args
function run_command {
    quiet=$1
    shift
    if $quiet; then
        "$@" 2>&1 > /dev/null
    else
        "$@"
    fi

    if [[ $? -ne 0 ]]; then
        exit 1
    fi
}

# $1: target to build
# $2: configuration
# $3: quiet
function build_internal {
    configure=false
    configuration_cache_file="$build_dir/__last_configuration"
    last_configuration='none'
    if [[ ! -d $build_dir ]]; then
        mkdir "$build_dir"
    else
        if [[ -f $configuration_cache_file ]]; then
            last_configuration=$(<$configuration_cache_file)
        fi
    fi

    if [[ $2 != $last_configuration ]]; then
        run_command $3 "$cmake" "-DCMAKE_BUILD_TYPE:STRING=$2" "-DCMAKE_C_COMPILER:FILEPATH=$compiler" "-S" "." "-B" "$build_dir" "-G" "$generator"
        if [[ $? -ne 0 ]]; then
            exit 1
        fi

        echo $2 > $configuration_cache_file
    fi

    run_command $3 "$cmake" "--build" "$build_dir" "--config" "$2" "--target" "$1" "-j" "14"
    if [[ $? -ne 0 ]]; then
        exit 1
    fi
}

# $1: homework
# $2: task
# $3: target
# $4: quiet
function run_internal {
    return_to=$PWD
    cd $1/$2
    run_command $4 "../../build/$1/$2/$3$executable_extension"
    cd $return_to
}

# build, run, buildTest and test have these arguments:
# $1: homework
# $2: task
# $3: configuration
# $4: quietBuild

function build {
    build_internal ${1}_$2 $3 $4
}

function run {
    build $1 $2 $3 $4
    run_internal $1 $2 ${1}_$2 $4
}

function buildTest {
    build $1 ${2}_test $3 $4
}

# $5: quietTest
function test {
    buildTest $1 $2 $3 $4
    run_internal $1 $2 ${1}_${2}_test $5
}

# $1 - $4 parameters
# $5 if running test
function foreach_homework_and_task {
    root_file='./CMakeLists.txt'
    while IFS='' read -r root_line; do
        if [[ ! $root_line =~ ^add_subdirectory\((.*)\)$ ]]; then
            continue
        fi

        homework=${BASH_REMATCH[1]}
        hw_file="./$homework/CMakeLists.txt"

        if [[ ! -f "$hw_file" ]]; then
            echo "homework file '$hw_file' not found"
            exit 1
        fi

        while IFS='' read -r hw_line; do
            if [[ ! $hw_line =~ ^add_subdirectory\((.*)\)$ ]]; then
                continue
            fi

            task=${BASH_REMATCH[1]}
            task_file="./$homework/$task/CMakeLists.txt"

            if [[ ! -f "$task_file" ]]; then
                echo "task file '$task_file' not found"
                exit 1
            fi

            while IFS='' read -r task_line; do
                if [[ ! $task_line =~ ^add_executable\((.*)[[:space:]].*\)$ ]]; then
                    continue
                fi

                target=${BASH_REMATCH[1]}

                target_is_test=false

                if [[ $target =~ _test ]]; then target_is_test=true; fi

                if [[ $5 = $target_is_test ]]; then
                    $1 $homework $task $2 $3 $4
                fi
            done < $task_file
        done < $hw_file
    done < $root_file
}

# $1: configuration
# $2: quietBuild
function buildAll {
    foreach_homework_and_task build $1 $2 '' false
}

# $1: configuration
# $2: quietBuild
# $3: quietTest
function testAll {
    foreach_homework_and_task test $1 $2 $3 true
}

configuration='Debug'
command='undefined_command'
quietBuild=false
quietTest=false
while [[ "$#" -gt 0 ]]; do
    case $1 in
        build | run | buildTest | test)
            command="$1"
            shift

            if [[ $# -eq 0 ]]; then
                echo "no homework folder specified"
                exit 1
            fi

            homework="$1"
            if [[ ! -d "$homework" ]]; then
                echo "homework folder '$homework' not found"
                exit 1
            fi
            shift

            if [[ $# -eq 0 ]]; then
                echo "no task folder specified"
                exit 1
            fi

            task="$1"
            if [[ ! -d "$homework/$task" ]]; then
                echo "task folder '$task' not found in homework folder '$homework'"
                exit 1
            fi
            ;;
        buildAll | testAll) command="$1" ;;
        -r|--release) configuration='Release' ;;
        -d|--debug) configuration='Debug' ;;
        -qb|--quiet-build) quietBuild=true ;;
        -qt|--quiet-test) quietTest=true ;;
        -c|--clear) rm -rf "$build_dir"; ;;
        clear) rm -rf "$build_dir"; exit 0 ;;
        *) echo "unknown argument: $1"; exit 1 ;;
    esac
    shift
done

if [[ $command == 'undefined_command' ]]; then
    echo "command not specified"
    exit 1
fi

case $command in
    build)
        build $homework $task $configuration $quietBuild
        ;;
    run)
        run $homework $task $configuration $quietBuild
        ;;
    buildTest)
        buildTest $homework $task $configuration $quietBuild
        ;;
    test)
        test $homework $task $configuration $quietBuild $quietTest
        ;;

    buildAll)
        buildAll $configuration $quietBuild
        ;;
    testAll)
        testAll $configuration $quietBuild $quietTest
        ;;
esac
