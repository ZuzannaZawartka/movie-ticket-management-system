#pragma once

#include <QGridLayout>
#include <QObject>
#include <QString>

class ReserveSeatsWindow : public QObject
{
    Q_OBJECT // Makro wymagane dla sygna³ów i slotów

public:
    ReserveSeatsWindow(QGridLayout* layout);
    ~ReserveSeatsWindow();
    std::vector<QString> getReservedSeats() const;

private:
    void generateSeats();
    void onButtonClicked(int row, int col);

    QGridLayout* layout;
    QString fileName;
    std::vector<QString> reservedSeats;
};