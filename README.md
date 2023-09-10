# WindowNavigator

A basic command line application to navigate between windows quickly. (Windows)

## Description

Press `F7` to see a console window having the first 10 windows names matching your input.

Live/Fuzzy search.

Uses [Levenshtein Distance](https://en.wikipedia.org/wiki/Levenshtein_distance) between input string and the window names / app names.

Case insensitive.

## Usage
Press `F7` and start typing in the console window.

The contents would look like below:
```
1: PowerShell 7 ~ WindowsTerminal.exe
2: Release ~ explorer.exe
3: Program Manager ~ explorer.exe
4: D:\Coding\Cpp\WindowNavigator\README.md - Notepad++ ~ notepad++.exe
5: D:\Coding\Cpp\WindowNavigator\x64\Release\WindowNavigator.exe ~ WindowNavigator.exe
6: WindowNavigator - Microsoft Visual Studio ~ devenv.exe
7: ? README.md - WindowNavigator - Visual Studio Code ~ Code.exe
8: YouTube ù Mozilla Firefox ~ firefox.exe
> pwsh
```

The order of the items change as you type.

There can be many windows, but a few best windows are printed onto the console.

Pressing `ENTER` will set the first window to foreground.

## Later

Yet to implement a window with hotkey support.

Currently uses `GetKeyState(...)` in a loop -> So avoid using it later.

Sleep cooldown is 100ms.