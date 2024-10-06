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

function foreach_homework_and_task {
    for homework_dir in */ ; do
        if [[ ! $homework_dir =~ ^(homework_.+)/$ ]]; then
            continue
        fi

        homework=${BASH_REMATCH[1]}

        for task_dir in $homework_dir*/ ; do
            if [[ ! $task_dir =~ ^${homework}/(task_.+)/$ ]]; then
                continue
            fi

            task=${BASH_REMATCH[1]}

            $1 $homework $task $2 $3 $4
        done
    done
}

# $1: configuration
# $2: quietBuild
function buildAll {
    foreach_homework_and_task build $1 $2
}

# $1: configuration
# $2: quietBuild
# $3: quietTest
function testAll {
    foreach_homework_and_task test $1 $2 $3
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
