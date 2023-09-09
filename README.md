# WindowNavigator

A basic command line application to navigate between windows quickly.

## Usage

Press `F2` to see a console window with the first 10 windows matched.
Works like live/fuzzy search (uses the (Levenshtein Distance)[https://en.wikipedia.org/wiki/Levenshtein_distance])

Yet to implement a window with hotkey support.

Currently uses `GetKeyState(...)` in a loop.