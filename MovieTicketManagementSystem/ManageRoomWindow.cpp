#include "ManageRoomWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QRegularExpression>

ManageRoomWindow::ManageRoomWindow(QPlainTextEdit* plainTextEdit, QPushButton* acceptButton): plainTextEdit(plainTextEdit), acceptButton(acceptButton)
{
    fileName = "numbers.txt";

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(saveToFile()));

    loadDataFromFile();
    
}


ManageRoomWindow::~ManageRoomWindow()
{
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
    QString fileContent = in.readAll(); // Odczyt ca³ej zawartoœci pliku

    plainTextEdit->setPlainText(fileContent); // Ustawienie zawartoœci pliku w plainTextEdit
 
    file.close();
}

void ManageRoomWindow::saveToFile()
{
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
    }

}


bool ManageRoomWindow::validateFile()
{
    QString text = plainTextEdit->toPlainText();

    // Split the text into lines
    QStringList lines = text.split('\n', Qt::SkipEmptyParts);

    int expectedNumberCount = -1;
    foreach(const QString & line, lines) {
        // Check if the line contains spaces
        if (!line.contains(' ')) {
            QMessageBox::critical(nullptr, "Error", "Each line must contain numbers separated by spaces.");
            return false;
        }

        // Check if the line contains only 0, 1, 2, or spaces
        QRegularExpression validCharsPattern("^[0-2 ]+$");
        if (!validCharsPattern.match(line).hasMatch()) {
            QMessageBox::critical(nullptr, "Error", "Lines can only contain the digits 0, 1, 2, and spaces.");
            return false;
        }

        // Check if the number of digits in each line is the same
        QStringList numbers = line.split(' ', Qt::SkipEmptyParts);
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
/*
void ManageRoomWindow::loadGridFromFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);
    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList numbers = line.split(' ', Qt::SkipEmptyParts);

        for (int col = 0; col < numbers.size(); ++col) {
            QString number = numbers[col];

            QLabel* label = new QLabel(number);
            label->setAlignment(Qt::AlignCenter);
            label->setFrameStyle(QFrame::Box | QFrame::Plain);

            if (number == "0") {
                label->setStyleSheet("background-color: red;");
            }
            else if (number == "1") {
                label->setStyleSheet("background-color: green;");
            }
            else if (number == "2") {
                label->setStyleSheet("background-color: blue;");
            }

            layout->addWidget(label, row, col);
        }

        ++row;
    }
}
*/