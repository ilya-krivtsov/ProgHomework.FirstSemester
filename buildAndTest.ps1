$root = $PSScriptRoot

$buildDirectory = [System.IO.Path]::Combine($root, "build")

$config = Get-Content buildConfig.json | ConvertFrom-Json

$cCompiler = $config.c_compiler
$generator = $config.generator
$cmake = $config.cmake
$executableExtension = $config.executableExtension

function CMake-Build($path, $target)
{
    Remove-Item -Force ([System.IO.Path]::Combine($buildDirectory, "CMakeCache.txt"))
    Remove-Item -Recurse -Force ([System.IO.Path]::Combine($buildDirectory, "CMakeFiles"))
    Run-Command "$cmake" @("-DCMAKE_BUILD_TYPE:STRING=Debug",
        "-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE", "-DCMAKE_C_COMPILER:FILEPATH=$cCompiler",
        "-S$([System.IO.Path]::Combine($root, $path))", "-B$buildDirectory", "-G", "`"$generator`"")
    Run-Command "$cmake" @("--build", $buildDirectory, "--config", "Debug", "--target", "$target", "-j", "14")
}

function CMake-Run($path, $target)
{
    CMake-Build $path $target
    Run-Command ([System.IO.Path]::Combine($buildDirectory, "$target$executableExtension"))
}

function CMake-BuildTest($path, $target)
{
    CMake-Build $path "$($target)_test"
}

function CMake-Test($path, $target)
{
    CMake-Run $path "$($target)_test"
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
    if ($p.ExitCode -ne 0) { exit $p.ExitCode }
}

if ($args.Count -ne 2)
{
    Write-Error "Expected command (build / run / test / buildTest) and path to task"
    exit 1
}

$allowedCommands = 'build', 'run', 'test', 'buildTest'
$command = $args[0]
if (-not $allowedCommands.Contains($command))
{
    Write-Error "Command name (build / run / test / buildTest) expected"
    exit 1
}

$path = $args[1]

if (-not [System.IO.Directory]::Exists([System.IO.Path]::Combine($root, $path)))
{
    Write-Error "Path '$path' do not exist"
    exit 1
}

$target = [System.IO.Path]::GetFilename($path)
Switch ($command)
{
    'build' { CMake-Build -path $path -target $target }
    'run' { CMake-Run -path $path -target $target }
    'test' { CMake-Test -path $path -target $target }
    'buildTest' { CMake-BuildTest -path $path -target $target }
}

