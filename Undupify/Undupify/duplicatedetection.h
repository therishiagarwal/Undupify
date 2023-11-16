// duplicatedetection.h

#pragma once

#include <QStringList>
#include <QMap>

class DuplicateDetection {
public:
    static QMap<QString, QStringList> detectDuplicates(const QStringList& fileList);
};
