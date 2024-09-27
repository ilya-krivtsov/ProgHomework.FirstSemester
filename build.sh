#!/bin/bash

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
    executable_extension=
fi

function buildInternal {
    $cmake -DCMAKE_BUILD_TYPE:STRING=$3 -DCMAKE_C_COMPILER:FILEPATH=$compiler -S$1 -B./build -G "$generator"
    if [[ $? -ne 0 ]]; then
        exit 1
    fi
    
    $cmake --build ./build --config $3 --target $2 -j 14
    if [[ $? -ne 0 ]]; then
        exit 1
    fi
}

function build {
    buildInternal "$1/$2" $2 $3
}

function run {
    buildInternal "$1/$2" $2 $3
    ./build/$2$executable_extension
}

function buildTest {
    buildInternal "$1/$2" "$(echo $2)_test" $3
}

function test {
    buildInternal "$1/$2" "$(echo $2)_test" $3
    ./build/$(echo $2)_test$executable_extension
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
        -r|--release) configuration='Release' ;;
        -d|--debug) configuration='Debug' ;;
        -c|--clear) rm -rf ./build; ;;
        clear) rm -rf ./build; exit 0 ;;
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
esac
