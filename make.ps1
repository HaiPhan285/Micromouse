param (
    [Parameter(Mandatory=$true)]
    [ValidatePattern('^[A-Za-z0-9._-]+$')]
    [string]$t,
    [Parameter(Mandatory=$false)][string]$a,
    [switch]$c=$false,
    [switch]$r=$false
)

$ErrorActionPreference = "Stop"
$buildDirectory = Join-Path "build" $t

$mode = "Debug"

if ($r) {
    $mode = "Release"
}

if ($c -and (Test-Path -LiteralPath $buildDirectory)) {
    Write-Host "Removing $buildDirectory"
    Remove-Item -LiteralPath $buildDirectory -Recurse -Force
}

cmake --preset $t "-DTARGET_APP=$a" "-DCMAKE_BUILD_TYPE=$mode"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build $buildDirectory
exit $LASTEXITCODE
