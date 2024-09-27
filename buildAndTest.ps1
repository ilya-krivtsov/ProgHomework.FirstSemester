$root = $PSScriptRoot

$buildDirectory = [System.IO.Path]::Combine($root, "build")

$cmake = 'undefinedCmake'
$compiler = 'undefinedCompiler'
$generator = 'undefinedGenerator'
$executableExtension = 'undefinedExecutableExtension'

foreach ($line in Get-Content config.txt)
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

function Run-Command($command, $commandArgs, $workingDirectory)
{
    $opt = [System.Diagnostics.ProcessStartInfo]@{
        Arguments = $commandArgs
        WorkingDirectory = $workingDirectory
        Filename = $command
    }
    $p = [System.Diagnostics.Process]::Start($opt)
    $p.WaitForExit()
    if ($p.ExitCode -ne 0) { exit 1 }
}

function CMake-BuildInternal($target, $configuration)
{
    $configurationCacheFile = "$buildDirectory/__last_configuration"
    $lastConfiguration = 'none'

    if (-not (Test-Path -Path $buildDirectory -PathType Container))
    {
        New-Item -ItemType Directory $buildDirectory | Out-Null
    }
    elseif (Test-Path -Path $configurationCacheFile -PathType Leaf)
    {
        $lastConfiguration = Get-Content $configurationCacheFile
    }

    if ($configuration -ne $lastConfiguration)
    {
        Run-Command "$cmake" @("-DCMAKE_BUILD_TYPE:STRING=$configuration", "-DCMAKE_C_COMPILER:FILEPATH=$compiler",
            "-S", $root, "-B", $buildDirectory, "-G", "`"$generator`"")

        $configuration | Out-File $configurationCacheFile
    }

    Run-Command "$cmake" @("--build", $buildDirectory, "--config", $configuration, "--target", $target, "-j", "14")
}

function CMake-RunInternal($homework, $task, $target)
{
    Run-Command "$buildDirectory/$homework/$task/$target$executableExtension" @() "$root/$homework/$task"
}

function CMake-Build($homework, $task, $configuration)
{
    CMake-BuildInternal "$($homework)_$task" $configuration
}

function CMake-Run($homework, $task, $configuration)
{
    CMake-Build $homework $task $configuration
    CMake-RunInternal $homework $task "$($homework)_$task"
}

function CMake-BuildTest($homework, $task, $configuration)
{
    CMake-BuildInternal "$($homework)_$($task)_test" $configuration
}

function CMake-Test($homework, $task, $configuration)
{
    CMake-BuildTest $homework $task $configuration
    CMake-RunInternal $homework $task "$($homework)_$($task)_test"
}

function DoForeach-HomeworkAndTask($toRun, $configuration)
{
    foreach ($homework in Get-ChildItem -Filter "homework_*")
    {
        foreach ($task in Get-ChildItem $homework -Filter "task_*")
        {
            & $toRun $homework.Name $task.Name $configuration
        }
    }
}

function CMake-BuildAll($configuration)
{
    DoForeach-HomeworkAndTask CMake-Build $configuration
}

function CMake-TestAll($configuration)
{
    DoForeach-HomeworkAndTask CMake-Test $configuration
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
        { ($_ -eq 'build') -or ($_ -eq 'run') -or ($_ -eq 'buildTest') -or ($_ -eq 'test') }
        {
            $command = $arg
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
        { ($_ -eq 'buildAll') -or ($_ -eq 'testAll') } { $command = $arg }
        { ($_ -eq '-r') -or ($_ -eq '--release') } { $configuration = 'Release' }
        { ($_ -eq '-d') -or ($_ -eq '--debug') } { $configuration = 'Debug' }
        { ($_ -eq '-c') -or ($_ -eq '--clear') } { Remove-Item -Recurse -Force -ErrorAction Ignore ./build }
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
    buildAll { CMake-BuildAll $configuration }
    testAll { CMake-TestAll $configuration }
}
