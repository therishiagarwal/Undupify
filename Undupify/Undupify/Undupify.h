// Undupify.h


#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Undupify.h"
#include <QListWidget>

class Undupify : public QMainWindow
{
    Q_OBJECT

public:
    Undupify(QWidget* parent = nullptr);
    ~Undupify();

private slots:
    void on_selectFileButton_clicked();
    void on_selectLocationButton_clicked();
    void on_scanButton_clicked();

private:
    Ui::UndupifyClass ui;
    QListWidget* resultListView;
    QListWidget* similarListView; // Added for similar files list
    QPushButton* scanButton;
    QString selectedFilePath;
    QString selectedDirectory;
    QStringList fileList; // Added this line to declare fileList


    double calculateSimilarity(const QString& str1, const QString& str2);
    QStringList similarFiles;
};
