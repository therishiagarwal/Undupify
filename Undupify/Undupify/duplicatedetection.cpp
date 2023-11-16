// duplicatedetection.cpp

#include "duplicatedetection.h"
#include "hashing.h"
#include <QDebug> // Added for debug statements

QMap<QString, QStringList> DuplicateDetection::detectDuplicates(const QStringList& fileList) {
    QMap<QString, QStringList> duplicateMap;

    for (const QString& filePath : fileList) {
        QString fileHash = Hashing::calculateFileHash(filePath);
        if (!fileHash.isEmpty()) {
            if (duplicateMap.contains(fileHash)) {
                duplicateMap[fileHash].append(filePath);
            }
            else {
                duplicateMap[fileHash] = QStringList{ filePath };
            }
        }
    }

    // Remove non-duplicates from the map
    QMap<QString, QStringList>::iterator it = duplicateMap.begin();
    while (it != duplicateMap.end()) {
        if (it.value().size() < 2) {
            it = duplicateMap.erase(it++);
        }
        else {
            ++it;
        }
    }

    qDebug() << "Duplicate Map Content:" << duplicateMap; // Debug statement

    return duplicateMap;
}