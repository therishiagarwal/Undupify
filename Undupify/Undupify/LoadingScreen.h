// LoadingScreen.h

#pragma once

#include <QWidget>
#include <QProgressBar>

class LoadingScreen : public QWidget
{
    Q_OBJECT

public:
    LoadingScreen(QWidget* parent = nullptr);
    ~LoadingScreen();

    void setProgress(int value);

private:
    QProgressBar* progressBar;
};
