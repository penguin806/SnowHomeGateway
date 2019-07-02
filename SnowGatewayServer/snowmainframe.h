#ifndef SNOWMAINFRAME_H
#define SNOWMAINFRAME_H

#include <QDialog>
#include "webinterface.h"
#include "commanddispatcher.h"

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
    WebInterface *webInterface;
    CommandDispatcher *commandDispatcher;
};

#endif // SNOWMAINFRAME_H
