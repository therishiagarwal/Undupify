// hashing.h

#pragma once
#include <QString>

class Hashing
{
public:
    static QString calculateFileHash(const QString& filePath);
};
