// Undupify.cpp

#include "Undupify.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QCryptographicHash>
#include "fileoperations.h"
#include "duplicatedetection.h"
#include "hashing.h"
#include "LoadingScreen.h" // Include the header for LoadingScreen

Undupify::Undupify(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);


    resultListView = new QListWidget(this);
    resultListView->setGeometry(430, 80, 360, 170);
    resultListView->addItem("Duplicate File Paths:");

    similarListView = new QListWidget(this);
    similarListView->setGeometry(430, 280, 360, 170);
    similarListView->addItem("Similar File Paths:");

    scanButton = new QPushButton("Scan", this);
    scanButton->setGeometry(170, 330, 131, 81);

    // Connect the clicked signal of the scanButton to the on_scanButton_clicked slot
    connect(scanButton, SIGNAL(clicked()), this, SLOT(on_scanButton_clicked()));


}

Undupify::~Undupify() {}

void Undupify::on_selectFileButton_clicked() {
    this->selectedFilePath = QFileDialog::getOpenFileName(this, tr("Select a File"), "", tr("All Files (*)"));
    if (!this->selectedFilePath.isEmpty()) {
        ui.selectedFileLineEdit->setText(this->selectedFilePath);
    }
}

void Undupify::on_selectLocationButton_clicked() {
    selectedDirectory = QFileDialog::getExistingDirectory(this, tr("Select a Directory"), "");
    if (!selectedDirectory.isEmpty()) {
        ui.selectedLocationLineEdit->setText(selectedDirectory);
    }
}

void Undupify::on_scanButton_clicked()
{
    // Show loading screen
    LoadingScreen loadingScreen(this);
    loadingScreen.show(); // Show the loading screen

    //similarListView->clear();
    resultListView->clear(); // Clear previous results
    similarListView->clear(); // Clear previous results
    similarFiles.clear(); // Clear the list of similar files from previous scans



    if (selectedFilePath.isEmpty() || selectedDirectory.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select both a file and a directory.");
        return;
    }

    // Calculate hash of the selected file
    QString selectedFileHash = Hashing::calculateFileHash(selectedFilePath);
    if (selectedFileHash.isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to calculate hash for the selected file.");
        return;
    }

    if (this->fileList.isEmpty()) {
        this->fileList = FileOperations::getAllFilesInDirectory(selectedDirectory);
    }

    // Create a map of hashes and corresponding file paths
    QMap<QString, QStringList> hashToFileMap;
    QString selectedFileData;

    QFile selectedFile(selectedFilePath);

    if (selectedFile.open(QIODevice::ReadOnly)) {
        selectedFileData = selectedFile.readAll();
    }

    

    int totalFiles = this->fileList.size();
    int filesProcessed = 0;

    for (const QString& filePath : this->fileList) {
        if (filePath != selectedFilePath) {
            QFile file(filePath);

            if (file.open(QIODevice::ReadOnly)) {
                QByteArray fileData = file.readAll();
                double similarity = calculateSimilarity(selectedFileData, fileData);
                if (similarity > 0.1) {
                    similarFiles.append(filePath + " (Similarity: " + QString::number(similarity * 100, 'f', 2) + "%)");
                }

                QString fileHash = QCryptographicHash::hash(fileData, QCryptographicHash::Md5).toHex();
                hashToFileMap[fileHash].append(filePath);
            }
        }

        filesProcessed++;

        int progress = (static_cast<double>(filesProcessed) / totalFiles) * 100;
        loadingScreen.setProgress(progress);

        // Force the application to process events to update the GUI
        QCoreApplication::processEvents();
    }

    QStringList duplicates = hashToFileMap[selectedFileHash];

    resultListView->clear();
    resultListView->addItem("Duplicate File Paths:");

    int serialNo = 1;
    for (const QString& filePath : duplicates) {
        if (filePath != selectedFilePath) { // Only add if it's not the selected file
            QString itemText = QString::number(serialNo) + ": " + filePath;
            QListWidgetItem* item = new QListWidgetItem(itemText);
            resultListView->addItem(item);
            serialNo++;
        }
    }

    int duplicateCount = resultListView->count() - 1; // Subtract 1 to exclude the header item
    ui.resultLabel->setText(tr("Number of Duplicate Files Found: %1").arg(duplicateCount));

    similarListView->clear();
    similarListView->addItem("Similar File Paths:");
    similarListView->addItems(similarFiles);

    // Ensure loading screen reaches 100% before hiding it
    loadingScreen.setProgress(100);
    loadingScreen.hide();
}

double Undupify::calculateSimilarity(const QString& str1, const QString& str2)
{
    QByteArray data1 = str1.toUtf8();
    QByteArray data2 = str2.toUtf8();

    QString encoded1 = data1.toPercentEncoding();
    QString encoded2 = data2.toPercentEncoding();

    int similarity = 0;

    for (int i = 0; i < qMin(encoded1.length(), encoded2.length()); ++i) {
        if (encoded1.at(i) == encoded2.at(i)) {
            ++similarity;
        }
    }

    return static_cast<double>(similarity) / qMax(encoded1.length(), encoded2.length());
}
