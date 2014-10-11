#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
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
        QSettings item(QString("HKEY_CLASSES_ROOT\\CLSID\\%1").arg(list.at(i)),
                       QSettings::NativeFormat);
        auto chidlGroups = item.childGroups();
        if (chidlGroups.contains("Control") && chidlGroups.contains("ProgID")) {
            int index = table->rowCount();
            table->setRowCount(index+1);
            QTableWidgetItem *nameItem = new QTableWidgetItem(item.value(".").toString());
            nameItem->setToolTip(item.value(".").toString());
            item.beginGroup("ProgID");
            nameItem->setData(Qt::UserRole, item.value("."));
            item.endGroup();
            table->setItem(index, 0, nameItem);
        }
    }
}

void MainWindow::on_selectionChanged()
{
    auto selects = ui->tableWidget->selectedItems();
    QString comName = selects.at(0)->data(Qt::UserRole).toString();
    QAxObject ax;
    if (ax.setControl(comName)) {
        QString doc = ax.generateDocumentation();
        ui->textBrowser->setText(doc);
    } else {
        ui->textBrowser->setText("");
    }
}
