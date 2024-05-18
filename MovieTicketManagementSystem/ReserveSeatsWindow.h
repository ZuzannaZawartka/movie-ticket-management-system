#pragma once
#include <QGridLayout>

class ReserveSeatsWindow
{
public:
	ReserveSeatsWindow(QGridLayout* layout);
	~ReserveSeatsWindow();
private:
	void generateSeats();
	QGridLayout* layout;
	QString fileName;
};

