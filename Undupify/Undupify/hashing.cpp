// hashing.cpp

#include "hashing.h"
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>

QString Hashing::calculateFileHash(const QString& filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray fileData = file.readAll();
        QByteArray hash = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
        return hash.toHex();
    }
    else {
        qDebug() << "Failed to open file: " << filePath;
        return QString();
    }
}
