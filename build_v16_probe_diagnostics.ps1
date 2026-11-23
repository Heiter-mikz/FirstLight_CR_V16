param(
    [string]$InputApk = "",
    [string]$OutputApk = "",
    [int]$EngineCount = 1
)

# Builds a diagnostic-only APK for V16 entrypoint discovery.
# It does not claim offline battle readiness and the embedded V16 profile
# deliberately installs no native hooks.

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "native_runner/local_config.ps1")
if (-not $InputApk) { $InputApk = "D:\AE下载\Nulls_Royale_16.635.1.apk" }
if (-not $OutputApk) { $OutputApk = Join-Path $PSScriptRoot "build/cr-probe-v16-diagnostics.apk" }

$python = Get-LocalSetting "CR_PYTHON" "python"
$java = Get-LocalSetting "CR_JAVA"
$buildTools = Get-LocalSetting "CR_BUILD_TOOLS"
$keytool = Get-LocalSetting "CR_KEYTOOL"
$ndk = Get-LocalSetting "CR_NDK_ROOT"
foreach ($required in @($InputApk, $java, $buildTools, $keytool, $ndk)) {
    if (-not $required -or -not (Test-Path -LiteralPath $required)) {
        throw "Missing diagnostic build input/tool: '$required'. Configure .env."
    }
}
$InputApk = (Resolve-Path -LiteralPath $InputApk).Path
$OutputApk = [IO.Path]::GetFullPath($OutputApk)
if ($InputApk -eq $OutputApk) { throw "OutputApk must not overwrite the original V16 APK." }

$verifier = Join-Path $PSScriptRoot "native_runner/probe/verify_v16_probe_apk.py"
$probeBuilder = Join-Path $PSScriptRoot "native_runner/probe/build_probe.ps1"
$probe = Join-Path $PSScriptRoot "native_runner/probe/out/libcrprobe_v16.so"
$work = Join-Path $PSScriptRoot ("build/v16-diagnostics-" + [Guid]::NewGuid().ToString("N"))
$decoded = Join-Path $work "decoded"
New-Item -ItemType Directory -Force -Path $work | Out-Null

Write-Host "[1/5] Verify original V16 APK and embedded libg identity"
& $python $verifier input --apk $InputApk
if ($LASTEXITCODE -ne 0) { throw "V16 input verification failed." }

Write-Host "[2/5] Build the V16 diagnostics-only native probe"
& $probeBuilder -NdkRoot $ndk -TargetVersion 16 -Output $probe
if ($LASTEXITCODE -ne 0) { throw "V16 probe build failed." }

Write-Host "[3/5] Decode the original V16 APK"
$apktoolVersion = "2.12.1"
$apktool = Join-Path $PSScriptRoot "native_runner/probe/out/tools/apktool_$apktoolVersion.jar"
New-Item -ItemType Directory -Force -Path (Split-Path $apktool) | Out-Null
if (-not (Test-Path -LiteralPath $apktool)) {
    Invoke-WebRequest -Uri "https://github.com/iBotPeaches/Apktool/releases/download/v$apktoolVersion/apktool_$apktoolVersion.jar" -OutFile $apktool
}
$apktoolHash = (Get-FileHash -LiteralPath $apktool -Algorithm SHA256).Hash.ToLowerInvariant()
if ($apktoolHash -ne "66cf4524a4a45a7f56567d08b2c9b6ec237bcdd78cee69fd4a59c8a0243aeafa") {
    throw "Apktool SHA-256 mismatch."
}
$apktoolReported = (& $java -jar $apktool --version 2>&1 | Out-String).Trim()
if ($LASTEXITCODE -ne 0 -or $apktoolReported -ne $apktoolVersion) {
    throw "Expected Apktool $apktoolVersion, got '$apktoolReported'."
}
& $java -jar $apktool decode $InputApk --output $decoded
if ($LASTEXITCODE -ne 0) { throw "V16 APK decode failed." }

Write-Host "[4/5] Inject the diagnostics probe and sign the APK"
& (Join-Path $PSScriptRoot "native_runner/build_engine_cluster_apk.ps1") `
    -DecodedApk $decoded -Probe $probe -OutputApk $OutputApk -EngineCount $EngineCount `
    -Java $java -Keytool $keytool -BuildTools $buildTools -Python $python
if ($LASTEXITCODE -ne 0) { throw "V16 diagnostics APK packaging failed." }

Write-Host "[5/5] Verify engine and probe payloads"
& $python $verifier output --apk $OutputApk --probe $probe
if ($LASTEXITCODE -ne 0) { throw "V16 diagnostics APK verification failed." }

Write-Host "V16 diagnostics APK built: $OutputApk"
Write-Host "Mode: identity-attested candidate logging only; no native hook is installed."
