// fileoperations.h

#pragma once

#include <QStringList>

class FileOperations {
public:
    static QStringList getAllFilesInDirectory(const QString& directoryPath);
};
