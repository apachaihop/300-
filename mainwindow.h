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
#include <QThread>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>

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
class ReceiverThread : public QThread
{
    Q_OBJECT

public:
    explicit ReceiverThread(QObject *parent = nullptr);
    ~ReceiverThread();

    void startReceiver(const QString &portName, int waitTimeout);

signals:
    void request(const QString &s);

private:
    void run() override;

    QString m_portName;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    bool m_quit = false;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showRequest(const QString &s);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void onTableViewactivmycoll(const QModelIndex &current, const QModelIndex &previous);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_pushButton_5_clicked();

private:
    int m_transactionCount = 0;
    Ui::MainWindow *ui;
    Document xlsxW;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int m_row,m_column;
    ReceiverThread m_thread;
};
#endif // MAINWINDOW_H
