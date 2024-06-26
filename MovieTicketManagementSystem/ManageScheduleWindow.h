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
    explicit ManageScheduleWindow(QComboBox* titleEdit, QDateEdit* dateEdit, QTimeEdit* timeEdit,  QLineEdit* durationTime, QPushButton* addButton, QPushButton* removeButton, QPushButton* editButton, QTableWidget* scheduleTableWidget);
    ~ManageScheduleWindow();

private:
    QDateEdit* dateEdit;
    QTimeEdit* timeEdit;
    QComboBox* titleEdit;
    QLineEdit* durationTime;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* editButton;
    ScheduleDatabase scheduleDatabase;
    ScheduleTableWidget* scheduleTableWidget;
    MovieDatabase movieDatabase;
    Schedule getScheduleFromFields();
    bool checkInputFields();
    void updateFields();
    void updateDuration();
    void updateFields(const Schedule& schedule);
    int selectedScheduleId;

public slots:
    void refreshSchedules();

signals:
    void schedulesChanged();

private slots:
    void addNewSchedule();
    void removeCurrentSchedule();
    void editCurrentSchedule();
    void setLimitationsOnFields();
    void updateMinimumTime(const QDate& date);
    void onScheduleSelected(const QModelIndex& index); 
};