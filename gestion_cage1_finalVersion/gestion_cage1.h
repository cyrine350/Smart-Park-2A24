#ifndef GESTION_CAGE1_H
#define GESTION_CAGE1_H
#include"cage.h"
#include<QSqlError>
#include<QTabWidget>
#include <QDialog>
#include <QWidget>
#include <history.h>
#include <QCompleter>


namespace Ui {
class gestion_cage1;
}
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;

class gestion_cage1 : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_cage1(QWidget *parent = nullptr);
    ~gestion_cage1();
private slots:
 void on_pushButton_valider_clicked();
   void on_pushButton_supprimer_clicked();


   void on_pushButton_modifier_clicked();

   void on_tableView_activated(const QModelIndex &index);


   void on_pushButtontri_clicked();

   void on_pushButton_tri2_clicked();

  void on_pushButton_recherche_clicked();

   void on_pushButton_tri3_clicked();

   void on_pushButton_clicked();

   void on_pushButton_H_clicked();

   void on_pushButton_2_clicked();

   void on_pushButton_pdf_clicked();

   void on_pushButton_staaaaat_clicked();

   void on_pushButton_image_clicked();

   void on_lineEdit_Num_2_textChanged(const QString &arg1);

private:
    Ui::gestion_cage1 *ui;
     Cage cag ;
     QCamera *mCamera;
     QCameraViewfinder *mCameraViewfinder;
     QCameraImageCapture *mCameraImageCapture;
     QVBoxLayout *mLayout;
     QMenu *mOptionsMenu;
     QAction *mAllumerAction;
     QAction *mEteindreAction;
      QAction *mCapturerAction;
      QCompleter* Model_Completer;
     history H;
};

#endif // GESTION_CAGE1_H
