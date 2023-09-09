# WindowNavigator

A basic command line application to navigate between windows quickly. (Windows)

## Description

Press `F2` to see a console window having the first 10 windows names matching your input.

Works like live/fuzzy search.

Uses the [Levenshtein Distance](https://en.wikipedia.org/wiki/Levenshtein_distance)

Case insensitive.

## Usage
Press `F2` and start typing in the console window.

The contents would look like below:
```
WhatsApp "ApplicationFrameHost.exe"
GitHub Desktop "GitHubDesktop.exe"
Windows Input Experience "TextInputHost.exe"
Adobe Acrobat Reader (64-bit) "Acrobat.exe"
pwsh "ConEmu64.exe"
Program Manager "explorer.exe"
WindowNavigator - Microsoft Visual Studio "devenv.exe"
README.md - WindowNavigator - Visual Studio Code "Code.exe"
spider2048/WindowNavigator: a faster way to switch windows - Google Chrome "chrome.exe"
D:\Coding\Cpp\WindowNavigator\x64\Debug\WindowNavigator.exe "VsDebugConsole.exe"
> whatsapp  --> your input
```

The order of the items change as you type.

There can be many windows, but the best 10 windows are printed onto the console.

Pressing `ENTER` will set the first window to foreground.

## Later

Yet to implement a window with hotkey support.

Currently uses `GetKeyState(...)` in a loop.