' Silent runner for Windows Task Scheduler
' Executes Python in background without showing a command prompt window

Set WshShell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")

scriptDir = fso.GetParentFolderName(WScript.ScriptFullName)
pythonExe = scriptDir & "\.venv\Scripts\python.exe"
runScript = scriptDir & "\run_scheduled_solve.py"

args = ""
For i = 0 To WScript.Arguments.Count - 1
    args = args & " " & WScript.Arguments(i)
Next

cmdLine = """" & pythonExe & """ """ & runScript & """" & args
WshShell.Run cmdLine, 0, False
