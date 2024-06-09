#include "ManageRoomWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QRegularExpression>

ManageRoomWindow::ManageRoomWindow(QPlainTextEdit* plainTextEdit, QPushButton* acceptButton): plainTextEdit(plainTextEdit), acceptButton(acceptButton) {
    fileName = "numbers.txt";
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
    loadDataFromFile();
}

ManageRoomWindow::~ManageRoomWindow() {
    delete plainTextEdit;
    delete acceptButton;
}

void ManageRoomWindow::loadDataFromFile() {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll(); 
    plainTextEdit->setPlainText(fileContent);
    file.close();
}

void ManageRoomWindow::saveToFile() {
    if (validateFile()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Cannot open file for writing.");
            return;
        }

        QTextStream out(&file);
        out << plainTextEdit->toPlainText();
        file.close();

        QMessageBox::information(nullptr, "Success", "File saved successfully.");
        emit fileSaved();
    }
}

//Only 0, 1, 2, and spaces at the end are allowed,  Validate the file content
bool ManageRoomWindow::validateFile() {
    QString text = plainTextEdit->toPlainText();

    // Split the text into lines
    QStringList lines = text.split('\n', Qt::SkipEmptyParts);

    int expectedNumberCount = -1;
    foreach(const QString & line, lines) {
        // Check if the line contains only 0, 1, 2, or spaces at the end
        QRegularExpression validCharsPattern("^[0-2]* *$");
        if (!validCharsPattern.match(line).hasMatch()) {
            QMessageBox::critical(nullptr, "Error", "Lines can only contain the digits 0, 1, 2, and optional trailing spaces.");
            return false;
        }

        // Check if the line contains spaces between numbers
        QRegularExpression spacesBetweenNumbersPattern("^[0-2]+ *$");
        if (!spacesBetweenNumbersPattern.match(line).hasMatch()) {
            QMessageBox::critical(nullptr, "Error", "Numbers must be contiguous without spaces between them, except optional trailing spaces.");
            return false;
        }

        // Remove any trailing spaces and count the digits
        QString trimmedLine = line.trimmed();

        // Split the line into individual digits
        QStringList numbers = trimmedLine.split("", Qt::SkipEmptyParts);

        if (expectedNumberCount == -1) {
            expectedNumberCount = numbers.size();
        }
        else if (numbers.size() != expectedNumberCount) {
            QMessageBox::critical(nullptr, "Error", "Invalid number of digits in some lines.");
            return false;
        }
    }
    return true;
}
