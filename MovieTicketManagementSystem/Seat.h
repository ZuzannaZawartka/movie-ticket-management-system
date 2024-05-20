#pragma once
#include <QObject>
#include <QWidget>
#include <QPushButton>

class Seat : public QObject
{
    Q_OBJECT
public:
    Seat(int row, int col,QChar type, QWidget* parent = nullptr);
    ~Seat();

    QPushButton* getButton() const;
    int row() const;
    int col() const;
    QChar type() const;
    bool takeSeat();
    QString getSeatNumber() const;

signals:
    void clicked(int row, int col);

private:
    int seatRow;
    int seatCol;
    QChar seatType;
    bool isSelected = false;
    QString seatNumber;
    QPushButton* button;

    void updateColor();

private slots:
    void onButtonClicked();
};