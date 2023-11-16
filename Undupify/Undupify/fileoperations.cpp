// fileoperations.cpp

#include "fileoperations.h"
#include <QDir>
#include <QStringList>

QStringList FileOperations::getAllFilesInDirectory(const QString& directoryPath) {
    QDir directory(directoryPath);
    QStringList fileList;

    if (directory.exists()) {
        QStringList filters;
        filters << "*.*";

        directory.setNameFilters(filters);
        fileList = directory.entryList(QDir::Files | QDir::NoDotAndDotDot);
        for (int i = 0; i < fileList.size(); ++i) {
            fileList[i] = directoryPath + "/" + fileList[i];
        }
    }

    return fileList;
}
