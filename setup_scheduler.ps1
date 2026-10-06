<#
.SYNOPSIS
    Registers or unregisters Windows Scheduled Tasks for the LeetCode NeetCode 250 Auto-Solver and 24/7 Telegram Bot.

.PARAMETER Action
    Install, Uninstall, List, RunNow, StartBot, or StopBot (default: Install)

.PARAMETER Times
    Comma-separated 24-hr times to schedule (default: read from .env or '09:00,15:45,16:15')
#>

param (
    [string]$Action = "Install",
    [string]$Times = ""
)

$ErrorActionPreference = "Stop"
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# 1. Resolve Times
if (-not $Times) {
    $EnvFile = Join-Path $ScriptDir ".env"
    if (Test-Path $EnvFile) {
        $Match = Select-String -Path $EnvFile -Pattern "^SCHEDULE_TIMES=(.*)" | Select-Object -First 1
        if ($Match) {
            $Times = $Match.Matches.Groups[1].Value.Trim()
        }
    }
}

if (-not $Times) {
    $Times = "09:00,15:45,16:15"
}

$TimeSlots = $Times.Split(',') | ForEach-Object { $_.Trim() } | Where-Object { $_ -ne "" }
$VbsPath = Join-Path $ScriptDir "run_silent.vbs"
$PythonWExe = Join-Path $ScriptDir ".venv\Scripts\pythonw.exe"

switch ($Action.ToLower()) {
    "uninstall" {
        Write-Host "--- Removing LeetCode Scheduled Tasks & Telegram Bot ---" -ForegroundColor Cyan
        $Existing = Get-ScheduledTask -TaskName "LeetCode_*" -ErrorAction SilentlyContinue
        if ($Existing) {
            foreach ($t in $Existing) {
                Stop-ScheduledTask -TaskName $t.TaskName -ErrorAction SilentlyContinue
                Unregister-ScheduledTask -TaskName $t.TaskName -Confirm:$false
                Write-Host "Removed task: $($t.TaskName)" -ForegroundColor Green
            }
        } else {
            Write-Host "No active LeetCode tasks found." -ForegroundColor Yellow
        }
        # Stop any lingering pythonw processes for the bot
        Get-Process pythonw -ErrorAction SilentlyContinue | Where-Object { $_.Path -like "*leetcode agent*" } | Stop-Process -Force -ErrorAction SilentlyContinue
    }

    "list" {
        Write-Host "--- Active LeetCode Scheduled Tasks & Bot ---" -ForegroundColor Cyan
        $Tasks = Get-ScheduledTask -TaskName "LeetCode_*" -ErrorAction SilentlyContinue
        if ($Tasks) {
            $Tasks | Select-Object TaskName, State | Format-Table -AutoSize
            foreach ($t in $Tasks) {
                $Info = Get-ScheduledTaskInfo -TaskName $t.TaskName
                Write-Host "[$($t.TaskName)] Next Run: $($Info.NextRunTime) | Last Run: $($Info.LastRunTime) (Result: $($Info.LastTaskResult))" -ForegroundColor Gray
            }
        } else {
            Write-Host "No registered LeetCode tasks." -ForegroundColor Yellow
        }
    }

    "runnow" {
        Write-Host "--- Triggering Immediate Test Solve ---" -ForegroundColor Cyan
        $PyExe = Join-Path $ScriptDir ".venv\Scripts\python.exe"
        $RunnerPy = Join-Path $ScriptDir "run_scheduled_solve.py"
        & $PyExe $RunnerPy --slot "Manual_Trigger" --no-jitter
    }

    "startbot" {
        Write-Host "--- Starting 24/7 Telegram Bot Task ---" -ForegroundColor Cyan
        Start-ScheduledTask -TaskName "LeetCode_Telegram_Bot" -ErrorAction SilentlyContinue
        Write-Host "Telegram Bot service started." -ForegroundColor Green
    }

    "stopbot" {
        Write-Host "--- Stopping Telegram Bot ---" -ForegroundColor Cyan
        Stop-ScheduledTask -TaskName "LeetCode_Telegram_Bot" -ErrorAction SilentlyContinue
        Get-Process pythonw -ErrorAction SilentlyContinue | Where-Object { $_.Path -like "*leetcode agent*" } | Stop-Process -Force -ErrorAction SilentlyContinue
        Write-Host "Telegram Bot stopped." -ForegroundColor Yellow
    }

    default {
        Write-Host "==========================================================" -ForegroundColor Magenta
        Write-Host "  Registering LeetCode Auto-Solver & 24/7 Telegram Bot    " -ForegroundColor Magenta
        Write-Host "==========================================================" -ForegroundColor Magenta
        Write-Host "Working Directory : $ScriptDir" -ForegroundColor Gray
        Write-Host "Scheduled Slots   : $($TimeSlots -join ', ')" -ForegroundColor Yellow

        # 1. Clean existing AutoSolver tasks
        $Existing = Get-ScheduledTask -TaskName "LeetCode_AutoSolver_*" -ErrorAction SilentlyContinue
        if ($Existing) {
            foreach ($t in $Existing) {
                Unregister-ScheduledTask -TaskName $t.TaskName -Confirm:$false
            }
        }

        # 2. Register slot tasks
        foreach ($slot in $TimeSlots) {
            $SafeName = $slot.Replace(":", "")
            $TaskName = "LeetCode_AutoSolver_$SafeName"

            $ActionObj = New-ScheduledTaskAction `
                -Execute "wscript.exe" `
                -Argument "`"$VbsPath`" --slot $slot" `
                -WorkingDirectory $ScriptDir

            $TriggerObj = New-ScheduledTaskTrigger -Daily -At $slot

            $SettingsObj = New-ScheduledTaskSettingsSet `
                -AllowStartIfOnBatteries `
                -DontStopIfGoingOnBatteries `
                -StartWhenAvailable `
                -WakeToRun `
                -ExecutionTimeLimit (New-TimeSpan -Hours 1)

            Register-ScheduledTask `
                -TaskName $TaskName `
                -Action $ActionObj `
                -Trigger $TriggerObj `
                -Settings $SettingsObj `
                -Force | Out-Null

            Write-Host "  [+] Registered: $TaskName -> Daily at $slot" -ForegroundColor Green
        }

        # 3. Register 24/7 Telegram Bot Task
        $BotTaskName = "LeetCode_Telegram_Bot"
        $BotScript = Join-Path $ScriptDir "telegram_bot.py"
        $BotAction = New-ScheduledTaskAction `
            -Execute $PythonWExe `
            -Argument "`"$BotScript`"" `
            -WorkingDirectory $ScriptDir

        $BotTrigger = New-ScheduledTaskTrigger -AtLogOn -User "$env:USERDOMAIN\$env:USERNAME"
        $BotPrincipal = New-ScheduledTaskPrincipal -UserId "$env:USERDOMAIN\$env:USERNAME" -LogonType Interactive

        $BotSettings = New-ScheduledTaskSettingsSet `
            -AllowStartIfOnBatteries `
            -DontStopIfGoingOnBatteries `
            -RestartCount 10 `
            -RestartInterval (New-TimeSpan -Minutes 1) `
            -ExecutionTimeLimit ([TimeSpan]::Zero)

        Register-ScheduledTask `
            -TaskName $BotTaskName `
            -Action $BotAction `
            -Trigger $BotTrigger `
            -Principal $BotPrincipal `
            -Settings $BotSettings `
            -Force | Out-Null

        Write-Host "  [+] Registered: $BotTaskName -> 24/7 Persistent Background Service" -ForegroundColor Green

        # 4. Start Telegram Bot Task right now
        Stop-ScheduledTask -TaskName $BotTaskName -ErrorAction SilentlyContinue
        Start-Sleep -Milliseconds 500
        Start-ScheduledTask -TaskName $BotTaskName

        Write-Host "`nAll tasks & 24/7 Telegram Bot registered and started!" -ForegroundColor Green
        Write-Host "Control anytime from your phone via Telegram: https://t.me/leetcdebot" -ForegroundColor Cyan
    }
}
