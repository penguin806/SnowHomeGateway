#ifndef SNOWMAINFRAME_H
#define SNOWMAINFRAME_H

#include <QDialog>

namespace Ui {
class SnowMainFrame;
}

class SnowMainFrame : public QDialog
{
    Q_OBJECT

public:
    explicit SnowMainFrame(QWidget *parent = nullptr);
    ~SnowMainFrame();

private:
    Ui::SnowMainFrame *ui;
};

#endif // SNOWMAINFRAME_H
