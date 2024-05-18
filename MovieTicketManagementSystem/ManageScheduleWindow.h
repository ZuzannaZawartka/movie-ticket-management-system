#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QTimeEdit>
#include "ScheduleDatabase.h"
#include "MovieDatabase.h"
#include "ScheduleTableWidget.h"

class ManageScheduleWindow : public QWidget
{
    Q_OBJECT;

public:
    explicit ManageScheduleWindow(QComboBox* titleEdit, QDateEdit* dateEdit, QTimeEdit* timeEdit,  QLineEdit* durationTime, QPushButton* addButton, QPushButton* removeButton, QTableWidget* scheduleTableWidget);
    ~ManageScheduleWindow();

private:
    QDateEdit* dateEdit;
    QTimeEdit* timeEdit;
    QComboBox* titleEdit;
    QLineEdit* durationTime;
    QPushButton* addButton;
    QPushButton* removeButton;
    ScheduleDatabase scheduleDatabase;
    ScheduleTableWidget* scheduleTableWidget;
    int selectedScheduleId;
    MovieDatabase movieDatabase;
    bool checkInputFields();
    void updateFields();
    void updateFields(const Schedule& schedule);
    Schedule getScheduleFromFields();

private slots:
    void addNewSchedule();
    void removeCurrentSchedule();
    void onScheduleSelected(const QModelIndex& index); 
};