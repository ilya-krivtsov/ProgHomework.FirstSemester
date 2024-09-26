#!/bin/bash

cmake='undefined_cmake'
compiler='undefined_compiler'
generator='undefined_generator'
executable_extension='undefined_executable_extension'

while IFS="=" read -r var value; do
    case $var in
        cmake)
            cmake=$value
            ;;
        compiler)
            compiler=$value
            ;;
        generator)
            generator=$value
            ;;
        executable_extension)
            executable_extension=$value
            ;;
    esac
done < config.txt
unset IFS

function buildInternal {
    $cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=$compiler -S$1 -B./build -G "$generator"
    $cmake --build ./build --config Debug --target $2 -j 14
}

function build {
    buildInternal $1 $(basename -- "$1")
}

function run {
    buildInternal $1 $(basename -- "$1")
    ./build/$(basename -- "$1")$executable_extension
}

function buildTest {
    target=$(basename -- "$1")_test
    buildInternal $1 $target
}

function test {
    target=$(basename -- "$1")_test
    buildInternal $1 $target
    ./build/$target$executable_extension
}

case $1 in
    build)
        build $2
        ;;
    run)
        run $2
        ;;
    buildTest)
        buildTest $2
        ;;
    test)
        test $2
        ;;
    clear)
        rm -rf ./build
        ;;
esac
