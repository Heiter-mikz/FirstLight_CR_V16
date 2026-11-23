param(
    [string]$NdkRoot = "",
    [string]$Output = "",
    [string]$TargetVersion = ""
)

$ErrorActionPreference = "Stop"
. (Join-Path (Split-Path -Parent $PSScriptRoot) "local_config.ps1")
if (-not $PSBoundParameters.ContainsKey("NdkRoot")) { $NdkRoot = Get-LocalSetting "CR_NDK_ROOT" }

if (-not $PSBoundParameters.ContainsKey("TargetVersion")) {
    if ($env:CR_PROBE_TARGET_VERSION) {
        $TargetVersion = $env:CR_PROBE_TARGET_VERSION
    } else {
        $TargetVersion = "15"
    }
}
if ($TargetVersion -notin @("15", "16")) {
    throw "TargetVersion must be 15 or 16, got: $TargetVersion"
}

if (-not $PSBoundParameters.ContainsKey("Output")) {
    if ($env:CR_PROBE) {
        $Output = $env:CR_PROBE
    } elseif ($TargetVersion -eq "16") {
        $Output = Join-Path $PSScriptRoot "out\libcrprobe_v16.so"
    } else {
        $Output = Join-Path $PSScriptRoot "out\libcrprobe.so"
    }
}

$compiler = Join-Path $NdkRoot "toolchains\llvm\prebuilt\windows-x86_64\bin\aarch64-linux-android24-clang++.cmd"
$source = Join-Path $PSScriptRoot "cr_replay_probe.cpp"
$touchSource = Join-Path $PSScriptRoot "native_touch_interceptor.cpp"
$assemblySource = Join-Path $PSScriptRoot "native_call_arm64.S"
$remainingAssemblySource = Join-Path $PSScriptRoot "remaining_runtime_arm64.S"
$outputPath = [IO.Path]::GetFullPath($Output)
$outputDirectory = Split-Path -Parent $outputPath

if (-not (Test-Path -LiteralPath $compiler)) {
    throw "Missing NDK compiler: $compiler"
}
New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null

& $compiler `
    -std=c++17 `
    -O2 `
    -fPIC `
    -fvisibility=hidden `
    -Wall `
    -Wextra `
    "-DCR_PROBE_TARGET_VERSION=$TargetVersion" `
    -shared `
    "-Wl,-z,max-page-size=16384" `
    -o $outputPath `
    $source `
    $touchSource `
    $assemblySource `
    $remainingAssemblySource `
    -llog `
    -ldl `
    -lz

if ($LASTEXITCODE -ne 0) {
    throw "AArch64 probe compilation for V$TargetVersion failed with exit code $LASTEXITCODE"
}

Get-Item -LiteralPath $outputPath | Select-Object FullName, Length, LastWriteTime
