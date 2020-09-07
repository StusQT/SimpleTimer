#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include <windows.h>
#include <QGridLayout>
#include <QSpacerItem>

#include <QDebug>

static QFont montserrat_medium;
static QFont montserrat_semiBold;


QFont loadFont (QString fontName) {
    int id = QFontDatabase::addApplicationFont(fontName);
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    return QFont(font);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    montserrat_medium = loadFont(":/fonts/Montserrat-Medium.ttf");
    montserrat_semiBold = loadFont (":/fonts/Montserrat-SemiBold.ttf");

    ui->label_2->setFont(montserrat_medium);
    ui->timeEdit->setFont(montserrat_medium);
    ui->plainTextEdit->setFont(montserrat_medium);
    ui->pushButton->setFont(montserrat_semiBold);
}

MainWindow::~MainWindow()
{
    delete ui;    
}

void MainWindow::resizeEvent(QResizeEvent* e)
{
    int tempX, tempY;
    QSize size = e->size();

    tempX = static_cast<int>(size.width() * 0.1420217);
    ui->plainTextEdit->setGeometry(tempX,
                                   static_cast<int>(size.height() * 0.111821),
                                   static_cast<int>(size.width() * 0.7192982),
                                   static_cast<int>(size.height() * 0.4169329));


    tempY = static_cast<int>(size.height() * 0.5910543);
    ui->label_2->setGeometry(tempX, tempY,
                             static_cast<int>(size.width() * 0.3182957),
                             static_cast<int>(size.height() * 0.0814696));


    ui->timeEdit->setGeometry(static_cast<int>(size.width() * 0.7017543),
                              tempY,
                              static_cast<int>(size.width() * 0.1595655),
                              static_cast<int>(size.height() * 0.0974440));


    ui->pushButton->setGeometry(static_cast<int>(size.width() * 0.384294),
                                static_cast<int>(size.height() * 0.7667731),
                                static_cast<int>(size.width() * 0.2347535),
                                static_cast<int>(size.height() * 0.1293929));

}

void MainWindow::on_pushButton_clicked()
{

    QString text = ui->plainTextEdit->toPlainText();
    QTime time = ui->timeEdit->time();
    long timeMc = time.hour() * 3600000 + time.minute() * 60000 + time.second() * 1000;

    QMessageBox box;

    QSpacerItem* horizontalSpacer = new QSpacerItem(static_cast<int>(window()->size().width() * 0.2923976),
                                                    0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = dynamic_cast <QGridLayout*>(box.layout());
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    box.setWindowTitle(" ");
    box.setDefaultButton(QMessageBox::Ok);

    if (text.length() == 0) {
        box.setText("Невозможно создать напоминание без текста");
        box.exec();
        return;
    }

    box.setText("Напоминание успешно установлено! Приложение будет скрыто до получения напоминания.");
    box.exec();

    window()->hide();
    Sleep(static_cast<DWORD>(timeMc));

    box.setText(text);    
    box.exec();

    window()->show();
}
