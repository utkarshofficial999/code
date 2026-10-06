<#
.SYNOPSIS
    Registers or unregisters Windows Scheduled Tasks for the LeetCode NeetCode 250 Auto-Solver.

.PARAMETER Action
    Install, Uninstall, List, or RunNow (default: Install)

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

switch ($Action.ToLower()) {
    "uninstall" {
        Write-Host "--- Removing LeetCode Scheduled Tasks ---" -ForegroundColor Cyan
        $Existing = Get-ScheduledTask -TaskName "LeetCode_AutoSolver_*" -ErrorAction SilentlyContinue
        if ($Existing) {
            foreach ($t in $Existing) {
                Unregister-ScheduledTask -TaskName $t.TaskName -Confirm:$false
                Write-Host "Removed task: $($t.TaskName)" -ForegroundColor Green
            }
        } else {
            Write-Host "No active LeetCode_AutoSolver tasks found." -ForegroundColor Yellow
        }
    }

    "list" {
        Write-Host "--- Active LeetCode Scheduled Tasks ---" -ForegroundColor Cyan
        $Tasks = Get-ScheduledTask -TaskName "LeetCode_AutoSolver_*" -ErrorAction SilentlyContinue
        if ($Tasks) {
            $Tasks | Select-Object TaskName, State | Format-Table -AutoSize
            foreach ($t in $Tasks) {
                $Info = Get-ScheduledTaskInfo -TaskName $t.TaskName
                Write-Host "[$($t.TaskName)] Next Run: $($Info.NextRunTime) | Last Run: $($Info.LastRunTime) (Result: $($Info.LastTaskResult))" -ForegroundColor Gray
            }
        } else {
            Write-Host "No registered LeetCode scheduled tasks." -ForegroundColor Yellow
        }
    }

    "runnow" {
        Write-Host "--- Triggering Immediate Test Run ---" -ForegroundColor Cyan
        $PyExe = Join-Path $ScriptDir ".venv\Scripts\python.exe"
        $RunnerPy = Join-Path $ScriptDir "run_scheduled_solve.py"
        & $PyExe $RunnerPy --slot "Manual_Trigger" --no-jitter
    }

    default {
        Write-Host "==========================================================" -ForegroundColor Magenta
        Write-Host "  Registering LeetCode NeetCode 250 Scheduled Tasks       " -ForegroundColor Magenta
        Write-Host "==========================================================" -ForegroundColor Magenta
        Write-Host "Working Directory : $ScriptDir" -ForegroundColor Gray
        Write-Host "Scheduled Slots   : $($TimeSlots -join ', ')" -ForegroundColor Yellow

        # Clean existing
        $Existing = Get-ScheduledTask -TaskName "LeetCode_AutoSolver_*" -ErrorAction SilentlyContinue
        if ($Existing) {
            foreach ($t in $Existing) {
                Unregister-ScheduledTask -TaskName $t.TaskName -Confirm:$false
            }
        }

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
                -ExecutionTimeLimit (New-TimeSpan -Hours 1)

            Register-ScheduledTask `
                -TaskName $TaskName `
                -Action $ActionObj `
                -Trigger $TriggerObj `
                -Settings $SettingsObj `
                -Force | Out-Null

            Write-Host "  [+] Registered: $TaskName -> Daily at $slot" -ForegroundColor Green
        }

        Write-Host "`nAll tasks registered successfully!" -ForegroundColor Green
        Write-Host "Execution runs silently in background. Results will be pushed to GitHub & Telegram." -ForegroundColor Cyan
    }
}
