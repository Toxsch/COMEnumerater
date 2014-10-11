#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QDebug>
#include <QAxObject>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    auto table = ui->tableWidget;
    connect(table, &QTableWidget::itemSelectionChanged, this, &MainWindow::on_selectionChanged);
    QSettings CLSID("HKEY_CLASSES_ROOT\\CLSID", QSettings::NativeFormat);
    QStringList list = CLSID.childGroups();
    for (int i = 0; i < list.size(); i++) {
        QString itemPath = QString("HKEY_CLASSES_ROOT\\CLSID\\%1").arg(list.at(i));
        QSettings item(itemPath, QSettings::NativeFormat);
        if (item.childGroups().contains("Control")) {
            int index = table->rowCount();
            table->setRowCount(index+1);
            QTableWidgetItem *nameItem = new QTableWidgetItem(item.value(".").toString());
            nameItem->setToolTip(item.value(".").toString());
            table->setItem(index, 0, nameItem);
        }
    }
}

void MainWindow::on_selectionChanged()
{
    auto selects = ui->tableWidget->selectedItems();
    QString comName = selects.at(0)->text();
    QAxObject ax(comName);
    QString doc = ax.generateDocumentation();
    ui->textBrowser->setText(doc);
}
