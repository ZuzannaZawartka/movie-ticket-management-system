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

    QPushButton* getButton() const;
    int row() const;
    int col() const;
    bool chooseSeat(); // returns true if seat was taken
    QChar type() const; // 0,1,2
    QString getSeatNumber() const; // A1, B2, C3, etc.

signals:
    void clicked(int row, int col);

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