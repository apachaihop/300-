#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QObject>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStyledItemDelegate>
#include <QRegularExpression>
#include <QMessageBox>
#include <QTableWidget>
#include <QVariant>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//Закоголовок окна, где описываются основные переменные и слоты
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void onTableViewactivmycoll(const QModelIndex &current, const QModelIndex &previous);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_action_3_triggered();

    void on_action_4_triggered();

private:
    Ui::MainWindow *ui;
    Document xlsxW;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int m_row,m_column;
};
#endif // MAINWINDOW_H
