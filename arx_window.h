#ifndef ARX_WINDOW_H
#define ARX_WINDOW_H

#include <QDialog>

namespace Ui {
class ARX_window;
}

class ARX_window : public QDialog
{
    Q_OBJECT

public:
    explicit ARX_window(QWidget *parent = nullptr);
    ~ARX_window();

private:
    Ui::ARX_window *ui;
};

#endif // ARX_WINDOW_H
