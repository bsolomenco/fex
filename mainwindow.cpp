#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _menuBar(new ToolBarWidget(this)),
      _leftPanel(new FilePanel(this)),
      _centerBar(new CenterBar(this)),
      _rightPanel(new FilePanel(this)),
      _commandBar(new CommandBar(this)),
      _functionBar(new FunctionBar(this)),
      _activePanel(_leftPanel),
      _fileOpController(new FileOperationController(this, this)),
      _compareController(new CompareController(this, this)),
      _searchController(new SearchController(this, this))
{
    setupLayout();
    connectSignals();
    resize(1200, 700);
    setWindowTitle("Total Commander");
}

void MainWindow::setupLayout() {
    auto *central  = new QWidget(this);
    auto *mainLay  = new QVBoxLayout(central);
    mainLay->setContentsMargins(0, 0, 0, 0);
    mainLay->setSpacing(0);

    auto *panelArea = new QWidget(this);
    auto *panelLay  = new QHBoxLayout(panelArea);
    panelLay->setContentsMargins(0, 0, 0, 0);
    panelLay->setSpacing(0);
    panelLay->addWidget(_leftPanel,  1);
    panelLay->addWidget(_centerBar,  0);
    panelLay->addWidget(_rightPanel, 1);

    mainLay->addWidget(_menuBar);
    mainLay->addWidget(panelArea, 1);
    mainLay->addWidget(_commandBar);
    mainLay->addWidget(_functionBar);

    setCentralWidget(central);
}

void MainWindow::connectSignals() {
    // ── Panel activation & command bar sync ──────────────────────────────
    connect(_leftPanel,  &FilePanel::activated, this, &MainWindow::setActivePanel);
    connect(_rightPanel, &FilePanel::activated, this, &MainWindow::setActivePanel);

    connect(_leftPanel,  &FilePanel::pathChanged, this, [this](const QString &p) {
        if (_activePanel == _leftPanel) _commandBar->setPrompt(p);
    });
    connect(_rightPanel, &FilePanel::pathChanged, this, [this](const QString &p) {
        if (_activePanel == _rightPanel) _commandBar->setPrompt(p);
    });

    // ── CenterBar → controllers ──────────────────────────────────────────
    connect(_centerBar, &CenterBar::copyRequested, this, [this]() {
        _fileOpController->copy(_activePanel->selectedFiles(),
                                inactivePanel()->currentPath());
    });

    connect(_centerBar, &CenterBar::compareRequested, this, [this]() {
        _compareController->compare(_leftPanel->currentPath(),
                                    _rightPanel->currentPath());
    });

    connect(_centerBar, &CenterBar::searchRequested, this, [this]() {
        _searchController->openSearch(_activePanel->currentPath());
    });

    // ── Controller results → panels ──────────────────────────────────────
    connect(_fileOpController, &FileOperationController::copyCompleted,
            this, [this]() { inactivePanel()->refresh(); });

    connect(_searchController, &SearchController::navigateRequested,
            this, [this](const QString &dir) { _activePanel->navigateTo(dir); });
}

void MainWindow::setActivePanel(FilePanel *panel) {
    _activePanel = panel;
    _commandBar->setPrompt(panel->currentPath());
}

FilePanel *MainWindow::inactivePanel() const {
    return (_activePanel == _leftPanel) ? _rightPanel : _leftPanel;
}

MainWindow::~MainWindow() {}
