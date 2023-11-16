// LoadingScreen.cpp

#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(300, 100);
    progressBar = new QProgressBar(this);
    progressBar->setGeometry(100, 50, 200, 30);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
}

LoadingScreen::~LoadingScreen()
{
    delete progressBar;
}

void LoadingScreen::setProgress(int value)
{
    progressBar->setValue(value);
}
