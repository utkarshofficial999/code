' Silent runner for Telegram Bot Service
' Runs Python in background without showing any command prompt window

Set WshShell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")

scriptDir = fso.GetParentFolderName(WScript.ScriptFullName)
pythonExe = scriptDir & "\.venv\Scripts\python.exe"
botScript = scriptDir & "\telegram_bot.py"

cmdLine = """" & pythonExe & """ """ & botScript & """"
WshShell.Run cmdLine, 0, False
