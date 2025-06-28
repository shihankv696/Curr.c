$toolsPath = "$(Split-Path -Parent $MyInvocation.MyCommand.Definition)"
$exePath = Join-Path $toolsPath "currc.exe"

Write-Host "Installing Curr.c Framework..."
Install-ChocolateyShortcut -ShortcutFilePath "$env:ProgramData\Microsoft\Windows\Start Menu\Programs\Curr.c.lnk" -TargetPath $exePath
Write-Host "Curr.c Framework installed successfully."
if (Test-Path $exePath) {
    Write-Host "Curr.c executable found at $exePath"
} else {
    Write-Host "Curr.c executable not found at $exePath. Installation may have failed."
}