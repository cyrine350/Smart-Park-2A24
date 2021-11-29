/*#ifndef WIDGET_H
#define WIDGET_H
#include <QDialog>
#include"gestion_cage1.h"

namespace Ui {
class Widget;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    Ui::gestion_cage1 *ui;


   QCamera *mCamera;
   QCameraViewfinder *mCameraViewfinder;
   QCameraImageCapture *mCameraImageCapture;
   QVBoxLayout *mLayout;
   QMenu *mOptionsMenu;
   QAction *mAllumerAction;
   QAction *mEteindreAction;
    QAction *mCapturerAction;

};


#endif // WIDGET_H*/
