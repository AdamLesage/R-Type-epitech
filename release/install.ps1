if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
    Write-Host "Installing Chocolatey..."
    Set-ExecutionPolicy Bypass -Scope Process -Force; `
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; `
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
}

Import-Module $env:ChocolateyInstall\helpers\chocolateyProfile.psm1

choco install git -y
refreshenv

choco install visualstudio2022community --package-parameters "--add Microsoft.VisualStudio.Workload.NativeDesktop --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.CMake.Project" -y
choco install windows-sdk-10.1 -y

choco install visualstudio2022buildtools -y

choco install cmake -y

git clone https://github.com/microsoft/vcpkg.git "C:\Program Files\vcpkg"
& "C:\Program Files\vcpkg\bootstrap-vcpkg.bat"

refreshenv

$vcpkgPath = "C:\Program Files\vcpkg"
$env:PATH += ";$vcpkgPath"
vcpkg install sfml boost-asio libconfig

New-Item -Path "$PSScriptRoot\build" -ItemType Directory -Force
Set-Location "$PSScriptRoot\build"
cmake -DCMAKE_TOOLCHAIN_FILE="$env:ProgramFiles\vcpkg\scripts\buildsystems\vcpkg.cmake" "$PSScriptRoot\R-Type-epitech\release"
cmake --build . --config Release

$binDir = "$PSScriptRoot\R-Type-epitech\release\bin\Release"
$destinationDir = "$PSScriptRoot"

$clientExe = "$binDir\r-type_client.exe"
$serverExe = "$binDir\r-type_server.exe"

if (Test-Path $clientExe) {
    Move-Item -Path $clientExe -Destination "$destinationDir"
} else {
    Write-Host "Client executable not found!"
}

if (Test-Path $serverExe) {
    Move-Item -Path $serverExe -Destination "$destinationDir"
} else {
    Write-Host "Server executable not found!"
}

$libDir = "$destinationDir\lib"
New-Item -Path $libDir -ItemType Directory -Force

$engines = @{
    "RenderingEngine.dll" = "libRenderingEngine.dll";
    "PhysicEngine.dll" = "libPhysicEngine.dll";
    "NetworkEngine.dll" = "libNetworkEngine.dll";
    "GameEngine.dll" = "libGameEngine.dll";
    "AudioEngine.dll" = "libAudioEngine.dll"
}

foreach ($engine in $engines.Keys) {
    $dllPath = "$binDir\$engine"
    if (Test-Path $dllPath) {
        Move-Item -Path $dllPath -Destination "$libDir\$($engines[$engine])"
    } else {
        Write-Host "$engine not found!"
    }
}

$dlls = Get-ChildItem -Path $binDir -Filter "*.dll" | Where-Object { $_.Name -notin $engines.Keys }
foreach ($dll in $dlls) {
    Move-Item -Path $dll.FullName -Destination $destinationDir
}

$assetsSrc = "$PSScriptRoot\R-Type-epitech\assets"
$assetsDst = "$PSScriptRoot\assets"

if (Test-Path $assetsSrc) {
    Copy-Item -Path $assetsSrc -Destination $assetsDst -Recurse
} else {
    Write-Host "Assets directory not found!"
}

if (Test-Path "$PSScriptRoot\R-Type-epitech\lib") {
    Copy-Item -Path "$PSScriptRoot\R-Type-epitech\lib\*" -Destination "$PSScriptRoot\lib" -Recurse
} else {
    Write-Host "Lib directory not found!"
}
