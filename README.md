# TotalCommander

A dual-pane file manager built with Qt6 and C++17, inspired by the classic Total Commander.

## Features

- **Dual file panels** — navigate two directories simultaneously
- **Copy** — copy selected files/directories from the active panel to the other, with conflict detection and progress dialog
- **Compare** — color-coded side-by-side comparison of two directory listings
- **Search** — recursive file search with glob (`*.cpp`) or substring patterns
- **Menu bar** — eight dropdown menus (Files, Mark, Commands, Net, Show, Configuration, Start, Help)
- **Drive bar** — one-click navigation to any mounted volume
- **Command bar** — path prompt that tracks the active panel
- **Function bar** — F1–F10 shortcut buttons
- **Live theme reload** — edit `style.qss` and changes appear instantly without restarting

## Requirements

| Tool | Version |
|------|---------|
| Qt | 6.x (tested on 6.11.0) |
| CMake | ≥ 3.28 |
| GCC / Clang | C++17 support required |

## Build

```bash
git clone <repo-url>
cd TotalCommander

cmake -B build -DCMAKE_PREFIX_PATH="/path/to/Qt/6.x/gcc_64"
cmake --build build -j$(nproc)

./build/TotalCommander
```

> If Qt is installed to the default system path, the `-DCMAKE_PREFIX_PATH` flag can be omitted.

## Project structure

```
TotalCommander/
├── main.cpp                        Entry point, stylesheet loader with live-reload
├── mainwindow.h/.cpp               Root window — layout and signal wiring only
├── style.qss                       Catppuccin dark theme (edit for live changes)
├── resources.qrc                   Embeds style.qss as a fallback Qt resource
│
├── ui/                             Presentation layer — no business logic
│   ├── ToolBarWidget               Menu bar with 8 dropdown menus
│   ├── ToolTextButton              Flat QPushButton with logical ButtonType enum
│   ├── FilePanel                   Drive bar + path label + QTableView/QFileSystemModel
│   ├── CenterBar                   Copy / Compare / Search buttons
│   ├── CommandBar                  Path prompt and command input
│   ├── FunctionBar                 F1–F10 shortcut buttons
│   ├── CompareDialog               Color-coded comparison results table
│   └── SearchDialog                Live-populating search results dialog
│
├── services/                       Pure logic — no Qt widgets, independently testable
│   ├── FileOperations              Recursive file/directory copy
│   ├── DirectoryComparator         Compares two directories by name, size, and mtime
│   └── FileSearcher                Recursive search with glob and substring matching
│
└── controller/                     Orchestration layer
    ├── FileOperationController     Confirmation → conflict check → progress → copy
    ├── CompareController           Run comparator → open CompareDialog
    └── SearchController            Create FileSearcher + SearchDialog, relay navigation
```

## Architecture

The project follows a strict three-layer architecture:

```
UI layer  →  Controller layer  →  Service layer
(widgets)    (orchestration)       (pure logic)
```

- **UI** emits signals and displays data — it never touches the filesystem directly.
- **Controllers** receive UI signals, call services, and open result dialogs.
- **Services** contain all algorithms — no `QWidget` dependencies, fully testable.

This separation satisfies all five SOLID principles. In particular:

- `SearchDialog` receives a `FileSearcher*` by injection (DIP) — swapping the search algorithm requires no changes to the dialog.
- `CompareDialog` receives a pre-computed `QList<CompareEntry>` — it has no knowledge of how the comparison was performed.
- `MainWindow` is ~60 lines of pure layout and signal wiring.

## Live theme editing

The stylesheet is loaded from `SOURCE_DIR/style.qss` on disk at startup. A `QFileSystemWatcher` re-applies it on every save, so you can tweak colours in `style.qss` and see results immediately. The embedded Qt resource (`:/style.qss`) is only used as a fallback when the source file is not present (e.g. in a distributed build).

## Keyboard shortcuts (menu reference)

| Key | Action |
|-----|--------|
| F1 | Help |
| F3 | View file |
| F4 | Edit file |
| F5 | Copy |
| F6 | Rename / Move |
| F7 | Make directory |
| F8 | Delete |
| F10 | Quit |
| Alt+F7 | Find files |
| Alt+F5 | Pack files |
| Ctrl+F1 | Brief view |
| Ctrl+F2 | Full view |
| Ctrl+F3–F6 | Sort by Name / Extension / Size / Date |
