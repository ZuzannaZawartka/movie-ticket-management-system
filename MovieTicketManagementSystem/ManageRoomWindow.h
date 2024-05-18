#pragma once
#include <QWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QString>

class ManageRoomWindow : public QWidget
{
    Q_OBJECT

public:
    ManageRoomWindow(QPlainTextEdit* plainTextEdit, QPushButton* acceptButton);
    ~ManageRoomWindow();

private:
    QPlainTextEdit* plainTextEdit;
    QPushButton* acceptButton;
    QString fileName = "numbers.txt";

    bool validateFile();
    void loadDataFromFile();

private slots:
    void saveToFile();
};
