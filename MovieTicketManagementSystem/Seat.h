#pragma once
#include <QObject>
#include <QWidget>
#include <QPushButton>

class Seat : public QObject
{
    Q_OBJECT

public:
    Seat(int row, int col, QChar type);
    ~Seat();
    int row() const;
    int col() const;
    bool chooseSeat(); 
    bool isSelectedSeat() const;
    void resetSeat();
    void setEnabled(bool variable);
    void setSeat(bool variable);
    QChar type() const; // 0,1,2
    QPushButton* getButton() const;
    QString getSeatNumber() const; // A1, B2, C3, etc.

signals:
    void clicked(QString seatNumber);

private:
    int seatRow;
    int seatCol;
    bool isSelected = false;
    QChar seatType;
    QString seatNumber;
    QPushButton* button;
    void updateColor();

private slots:
    void onButtonClicked();
};