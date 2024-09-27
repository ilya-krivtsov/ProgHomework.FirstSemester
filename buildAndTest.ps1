$root = $PSScriptRoot

$buildDirectory = [System.IO.Path]::Combine($root, "build")

$cmake = 'undefinedCmake'
$compiler = 'undefinedCompiler'
$generator = 'undefinedGenerator'
$executableExtension = 'undefinedExecutableExtension'

foreach($line in Get-Content config.txt) 
{
    $key, $value = $line.Split('=')
    switch ($key)
    {
        'cmake' { $cmake = $value }        
        'compiler' { $compiler = $value }        
        'generator' { $generator = $value }        
        'executable_extension' { $executableExtension = $value }        
    }
}

if ($cmake -eq 'undefinedCmake')
{
    Write-Error "cmake not unspecified"
    exit 1
}

if ($compiler -eq 'undefinedCompiler')
{
    Write-Error "compiler not unspecified"
    exit 1
}

if ($generator -eq 'undefinedGenerator')
{
    Write-Error "generator not unspecified"
    exit 1
}

if ($executableExtension -eq 'undefinedExecutableExtension')
{
    Write-Host "warning: executable extension not specified - assuming there is no executable extension"
    $executableExtension = ''
}

function CMake-BuildInternal($source, $target, $configuration)
{
    Remove-Item -Recurse -Force -ErrorAction Ignore $buildDirectory
    Run-Command "$cmake" @("-DCMAKE_BUILD_TYPE:STRING=$configuration", "-DCMAKE_C_COMPILER:FILEPATH=$compiler",
        "-S$([System.IO.Path]::Combine($root, $source))", "-B$buildDirectory", "-G", "`"$generator`"")
    Run-Command "$cmake" @("--build", $buildDirectory, "--config", $configuration, "--target", "$target", "-j", "14")
}

function CMake-Build($homework, $task, $configuration)
{
    CMake-BuildInternal "$homework/$task" $task $configuration
}

function CMake-Run($homework, $task, $configuration)
{
    CMake-BuildInternal "$homework/$task" $task $configuration
    Run-Command ([System.IO.Path]::Combine($buildDirectory, "$task$executableExtension"))
}

function CMake-BuildTest($homework, $task, $configuration)
{
    CMake-BuildInternal "$homework/$task" "$($task)_test" $configuration
}

function CMake-Test($homework, $task, $configuration)
{
    CMake-BuildInternal "$homework/$task" "$($task)_test" $configuration
    Run-Command ([System.IO.Path]::Combine($buildDirectory, "$($task)_test$executableExtension"))
}

function Run-Command($command, $commandArgs)
{
    $opt = [System.Diagnostics.ProcessStartInfo]@{
        Arguments = $commandArgs
        WorkingDirectory = $pwd
        Filename = $command
    }
    $p = [System.Diagnostics.Process]::Start($opt)
    $p.WaitForExit()
    if ($p.ExitCode -ne 0) { exit 1 }
}

$isDotSourced = $MyInvocation.InvocationName -eq '.' -or $MyInvocation.Line -eq ''
if ($isDotSourced)
{
    exit
}

$configuration = 'Debug'
$command = 'undefined_command'
for ($i = 0; $i -lt $args.Count; $i++)
{
    $arg = $args[$i]
    switch -Regex ($arg)
    {
        'build|run|buildTest|test'
        {
            $command=$arg
            $i++

            if ($i -ge $args.Count)
            {
                Write-Error "no homework folder specified"
                exit 1
            }

            $homework = $args[$i]
            if (-not (Test-Path -Path "$homework" -PathType Container))
            {
                Write-Error "Homework folder '$homework' not found"
                exit 1
            }
            $i++

            if ($i -ge $args.Count)
            {
                Write-Error "no task folder specified"
                exit 1
            }

            $task = $args[$i]
            if (-not (Test-Path -Path "$homework/$task" -PathType Container))
            {
                Write-Error "task folder '$task' not found in homework folder '$homework'"
                exit 1
            }
        }
        '-r|--release' { $configuration='Release' }
        '-d|--debug' { $configuration='Debug' }
        '-c|--clear' { Remove-Item -Recurse -Force -ErrorAction Ignore ./build }
        'clear' { Remove-Item -Recurse -Force -ErrorAction Ignore ./build; exit 0 }
        default  { Write-Error "unknown argument: $arg"; exit 1 }
    }
}

if ($command -eq 'undefined_command' )
{
    Write-Error "command not specified"
    exit 1
}

switch ($command)
{
    build { Cmake-Build $homework $task $configuration }
    run { Cmake-Run $homework $task $configuration }
    buildTest { CMake-BuildTest $homework $task $configuration }
    test { CMake-Test $homework $task $configuration }
}
