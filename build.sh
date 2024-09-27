#!/bin/bash

build_dir='build'

cmake='undefined_cmake'
compiler='undefined_compiler'
generator='undefined_generator'
executable_extension='undefined_executable_extension'

while IFS="=" read -r var value; do
    case $var in
        cmake) cmake=$value ;;
        compiler) compiler=$value ;;
        generator) generator=$value ;;
        executable_extension) executable_extension=$value ;;
    esac
done < config.txt
unset IFS

if [[ $cmake = 'undefined_command' ]]; then
    echo "cmake not specified"
    exit 1
fi

if [[ $compiler = 'undefined_compiler' ]]; then
    echo "compiler not specified"
    exit 1
fi

if [[ $generator = 'undefined_generator' ]]; then
    echo "generator not specified"
    exit 1
fi

if [[ $executable_extension = 'undefined_executable_extension' ]]; then
    echo "warning: executable extension not specified - assuming there is no executable extension"
    executable_extension=''
fi

# $1: target to build
# $2: configuration
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
        $cmake -DCMAKE_BUILD_TYPE:STRING=$2 -DCMAKE_C_COMPILER:FILEPATH=$compiler -S . -B "$build_dir" -G "$generator"
        if [[ $? -ne 0 ]]; then
            exit 1
        fi

        echo $2 > $configuration_cache_file
    fi

    $cmake --build "$build_dir" --config $2 --target $1 -j 14
    if [[ $? -ne 0 ]]; then
        exit 1
    fi
}

# $1: homework
# $2: task
# $3: target
function run_internal {
    return_to=$pwd
    cd $1/$2
    build/$1/$2/$3$executable_extension
    cd $return_to
}

# build, run, buildTest and test have these arguments:
# $1: homework
# $2: task
# $3: configuration

function build {
    build_internal ${1}_$2 $3
}

function run {
    build $1 $2 $3
    run_internal $1 $2 ${1}_$2
}

function buildTest {
    build $1 ${2}_test $3
}

function test {
    buildTest $1 $2 $3
    run_internal $1 $2 ${1}_${2}_test
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

            $1 $homework $task $2
        done
    done
}

# $1: configuration
function buildAll {
    foreach_homework_and_task build $1
}

# $1: configuration
function testAll {
    foreach_homework_and_task test $1
}

configuration='Debug'
command='undefined_command'
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
        build $homework $task $configuration
        ;;
    run)
        run $homework $task $configuration
        ;;
    buildTest)
        buildTest $homework $task $configuration
        ;;
    test)
        test $homework $task $configuration
        ;;

    buildAll)
        buildAll $configuration
        ;;
    testAll)
        testAll $configuration
        ;;
esac
