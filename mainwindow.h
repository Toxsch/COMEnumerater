#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void initialize();
protected slots:
    void on_selectionChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
