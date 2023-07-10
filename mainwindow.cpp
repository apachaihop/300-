 #include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace QXlsx;

enum class Column
{
    Last_Name=0,
    First_Name,
    Surname,
    Date
}coll;

//Делегат для ограничения ввода для даты
class YouEditMaskDelegate1 : public QStyledItemDelegate
{
public:
     using QStyledItemDelegate::QStyledItemDelegate;
     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
     {
         auto * edit = QStyledItemDelegate::createEditor(parent,option,index);
         auto * lineEdit = dynamic_cast<QLineEdit*>(edit);
         if(lineEdit)
         {
             QRegularExpression ipRegex ("[2][0][0-2][0-9][-]([0][1-9]|[1][0-2])[-]([1-2][0-9]|[0][1-9]|[3][0-1])");

              QRegularExpressionValidator *ipValidator = new  QRegularExpressionValidator(ipRegex);
              lineEdit->setValidator(ipValidator);
         }
         return edit;
     }
};
//Конструктор окна, который подключит файл с данными, создаст таблицу,использует ранее созданные делегаты
//для нужных колонок и выведет данные
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./DBB.db");
    if(db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }
    query=new QSqlQuery(db);
    query->exec("CREATE TABLE Person (Фамилия varchar(25),Имя varchar(25), Отчество varchar(25),Дата DATE);");
    model=new QSqlTableModel(this,db);
    model->setTable("Person");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(3,new YouEditMaskDelegate1(this));

     QObject::connect(ui->tableView->selectionModel(), SIGNAL(currentColumnChanged(const QModelIndex, const QModelIndex)),
                      this, SLOT(onTableViewactivmycoll(const QModelIndex, const QModelIndex)));

}
//Деструктор разрушает окно
MainWindow::~MainWindow()
{
    delete ui;
}

//Слот добавления данных из табличной модели в файл
void MainWindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

//Слот удаления поля из табличной модели и файла
void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(m_row);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
   m_row=index.row();
   m_column=index.column();
}


//Слот сортировки файла и таблицы
void MainWindow::on_pushButton_3_clicked()
{
    model->sort(m_column,Qt::SortOrder::AscendingOrder);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString find;
    coll=Column(m_column);
    switch (coll) {
    case Column::Last_Name:
        find="Фамилия";
        break;
    case Column::First_Name:
        find="Имя";
        break;
    case Column::Surname:
        find="Отчество";
        break;
    case Column::Date:
        find="Дата";
        break;
    default:
        QMessageBox::warning(this, "Внимание","Нажмите на поле по которому \n желаете вести поиск.");
        break;
    }
    QString s;
    QString fun="'";
    s=ui->lineEdit->text();
    QSqlQuery *query;
    query=new QSqlQuery(db);
    query->exec("SELECT * FROM Person WHERE "+find+"="+fun+s+fun+";");
    QSqlQueryModel *model1;
    model1=new QSqlQueryModel(this);
    model1->setQuery(*query);
    ui->tableView_2->setModel(model1);
}

void MainWindow::onTableViewactivmycoll(const QModelIndex &current, const QModelIndex &previous)
{
    m_row=current.row();
    m_column=current.column();
}



void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    m_row=index.row();
    m_column=index.column();
}


void MainWindow::on_action_3_triggered()
{
    QSqlQuery *query;
    query=new QSqlQuery(db);
    query->exec("SELECT * FROM Person;");
    QSqlQueryModel *model1;
    model1=new QSqlQueryModel(this);
    model1->setQuery(*query);
    for(int i=0;i<model1->rowCount();i++)
    {
        for(int j=0;j<model1->columnCount();j++)
        {
            QVariant data;
            data=model1->data(model1->index(i,j));
            xlsxW.write(i+1, j+1, data);
        }

    }
    if(xlsxW.saveAs("Test.xlsx"))
    QMessageBox::information(this, "Информация","Файл сохранен.");
    else
    QMessageBox::warning(this, "Внимание","Файл не удалось сохранить.");
}


void MainWindow::on_action_4_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);

    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        ui->tableView->render(&painter);
    }
}

