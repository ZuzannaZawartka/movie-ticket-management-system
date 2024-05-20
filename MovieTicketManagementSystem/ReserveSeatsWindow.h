#pragma once

#include <QGridLayout>
#include <QObject>
#include <QString>
#include <QPushButton>

class ReserveSeatsWindow : public QObject
{
    Q_OBJECT 

public:
    ReserveSeatsWindow(QGridLayout* layout,QPushButton* acceptButton);
    ~ReserveSeatsWindow();
    std::vector<QString> getReservedSeats() const;
    bool isSeatReserved();

private:
    void generateSeats();
    void onButtonClicked(int row, int col);

    QPushButton* acceptButton;
    QGridLayout* layout;
    QString fileName;
    std::vector<QString> reservedSeats;
private slots:
    void onAcceptButtonClicked();
};