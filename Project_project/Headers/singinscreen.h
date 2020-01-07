#ifndef SINGINSCREEN_H
#define SINGINSCREEN_H

#include <QDialog>

namespace Ui {
  class SingInScreen;
}

class SingInScreen : public QDialog
{
  Q_OBJECT

public:
  explicit SingInScreen(QWidget *parent = nullptr);
  ~SingInScreen();

private:
  Ui::SingInScreen *ui;
};

#endif // SINGINSCREEN_H
