#ifndef INFPROGRESS_H
#define INFPROGRESS_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QCloseEvent>

class InfProgress : public QDialog
{
    Q_OBJECT
public:
    InfProgress(QString text, QWidget *parent = 0);
    void setText(QString text);
    void closeEvent(QCloseEvent *event);

public slots:
    void changeColor();

private:
    QLabel *label;
    QProgressBar *progress;
    int timeID;
    QString text;
};

#endif // INFPROGRESS_H
