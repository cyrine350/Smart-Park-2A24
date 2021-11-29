#include "gestion_cage1.h"
#include "ui_gestion_cage1.h"
#include "cage.h"
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include<QSqlQueryModel>
#include<QModelIndex>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QFileDialog>
#include "widget.h"
#include <QPainter>
#include <QSqlRecord>
#include <QDebug>
#include <QUrl>
#include<QDateTime>
#include "history.h"
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include<QPixmap>
#include <QPrintDialog>
#include <QPdfWriter>
#include <vector>
#include <QFile>
#include <QTextDocument>
#include <QDebug>
#include<QIntValidator>
#include <QPainter>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include<QFileDialog>
#include <string>


gestion_cage1::gestion_cage1(QWidget *parent):
    QDialog(parent),
    ui(new Ui::gestion_cage1)
{
    ui->setupUi(this);
     ui->lineEdit_Num_A->setValidator(new QIntValidator(1000, 9999, this));
     ui->lineEdit_Num->setValidator(new QIntValidator(1000, 9999, this));
        ui->lineEdit_nbr_A->setValidator(new QIntValidator(1000, 99999999, this));
              ui->lineEdit_nbr->setValidator(new QIntValidator(1000, 99999999, this));
         ui->lineEdit_especec_A->setMaxLength(9);
           ui->lineEdit_especec->setMaxLength(9);

         QRegularExpression rx1("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                                           QRegularExpression::CaseInsensitiveOption);
                                 ui->lineEdit_especec_A->setValidator(new QRegularExpressionValidator(rx1, this));
                                   ui->lineEdit_especec->setValidator(new QRegularExpressionValidator(rx1, this));
                                   Model_Completer=new QCompleter(this);
                                                                       Model_Completer->setModel(cag.wombo_combo());
                                                            ui->lineEdit_Num_2->setCompleter(Model_Completer);



  ui->tableView->setModel(cag.afficher());
  mCamera = new QCamera(this);
  mCameraViewfinder = new QCameraViewfinder(this);
  mCameraImageCapture = new QCameraImageCapture(mCamera, this);
  mLayout = new QVBoxLayout;
  //mLayout->addItem(mCameraViewfinder);
  mOptionsMenu =new QMenu("Options", this);
  mAllumerAction =new QAction ("Allumer",this);
  mEteindreAction =new QAction ("Etteindre", this);
  mCapturerAction= new QAction ("Capturer",this);

  ui->tableView->setModel(cag.afficher());

  mOptionsMenu->addActions({ mAllumerAction, mEteindreAction, mCapturerAction });
  ui->OptionsPushButton->setMenu(mOptionsMenu);
  mCamera->setViewfinder(mCameraViewfinder);
  mLayout->addWidget(mCameraViewfinder);
  mLayout->setMargin(0);
  ui->scrollArea->setLayout(mLayout);
  connect(mAllumerAction,&QAction::triggered,[&](){
       mCamera->start();
      });

  connect(mEteindreAction, &QAction::triggered,[&](){
      mCamera->stop();
      });
  connect(mCapturerAction, &QAction::triggered,[&](){
      auto filename = QFileDialog::getSaveFileName(this, "Capturer","/","Image (.jpg;.jpeg");
      if (filename.isEmpty()) {
                  return ;
              }
         mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
         QImageEncoderSettings imageEncoderSettings ;
                 imageEncoderSettings.setCodec("image/jpeg");
                 imageEncoderSettings.setResolution(1600, 1200);
                 mCameraImageCapture->setEncodingSettings(QImageEncoderSettings());
                 mCamera->setCaptureMode(QCamera ::CaptureStillImage);
                 mCamera->start() ;
                 mCamera->searchAndLock();
                 mCameraImageCapture->capture(filename);
                 mCamera->unlock();
      });
}

gestion_cage1::~gestion_cage1()
{
    delete ui;
}

void gestion_cage1::on_pushButton_valider_clicked()

{  int id=ui->lineEdit_Num_A->text().toInt();
    QString dateh=QDateTime::currentDateTime().toString("dd/MM/yyyy");
     QString heureh=QDateTime::currentDateTime().toString("hh::mm");

    int NUM=ui->lineEdit_Num_A->text().toInt();
    int NBR=ui->lineEdit_nbr_A->text().toInt();
   QString ETATC=ui->lineEdit_Etatc_A->text();
   QString ESPECEC=ui->lineEdit_especec_A->text();

   if (NUM==NULL)
            {QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NUM!!!!") ;
            QMessageBox::critical(0, qApp->tr("Ajout"),
              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
          ui->lineEdit_Num_A->clear();
          ui->lineEdit_nbr_A->clear();
          ui->lineEdit_Etatc_A->clear();
          ui->lineEdit_especec_A->clear();}

         else if (NBR==NULL)
          {

              QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NBR!!!!") ;
              QMessageBox::critical(0, qApp->tr("Ajout"),
qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
              ui->lineEdit_Num_A->clear();
             ui->lineEdit_nbr_A->clear();
              ui->lineEdit_Etatc_A->clear();
             ui->lineEdit_especec_A->clear();
}
       else if (ESPECEC==NULL)
        {
            QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP ESPECEC!!!!") ;
            QMessageBox::critical(0, qApp->tr("Ajout"),
        qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
            ui->lineEdit_Num_A->clear();
           ui->lineEdit_nbr_A->clear();
            ui->lineEdit_Etatc_A->clear();
           ui->lineEdit_especec_A->clear();
 }
else {
Cage c (NUM,NBR,ETATC,ESPECEC);
history h;
  h.addHISTORYAjout(id,"ajouter",dateh,heureh);
bool test=c.ajouter();
if (test)
{
 ui->tableView->setModel(cag.afficher());
   QMessageBox::information(nullptr,QObject::tr("ok"),
                          QObject::tr("ajout effectué\n"
                                      "click Cancel to exit,"),QMessageBox::Cancel);
  }
else QMessageBox::critical(nullptr,QObject::tr(" not ok"),
                              QObject::tr("ajout non effectué\n"
                                          "click Cancel to exit,"),QMessageBox::Cancel);}}
/*void gestion_cage1::on_pushButton_supprimer_clicked()
{
    if(ui->tableView->currentIndex().row()==-1)
    { QMessageBox::information(nullptr, QObject::tr("Suppression"),
              QObject::tr("Veuillez Choisir une cage du Tableau.\n"
                                                "Click Ok to exit."), QMessageBox::Ok);}
                                                else {
 Cage c1;
  c1.setNUM( ui->lineEdit_Num->text().toInt());
     bool test=c1.supprimer(c1.get_NUM());
    QMessageBox msgBox;
        if(test)
        {
 msgBox.setText("Suppression avec succes.");
 ui->tableView->setModel(cag.afficher());
        }
else
 msgBox.setText("Echec de suppression.");
        msgBox.exec();
}}*/

void gestion_cage1::on_pushButton_supprimer_clicked()
{

    int id=ui->lineEdit_Num->text().toInt();
       QString dateh=QDateTime::currentDateTime().toString("dd/MM/yyyy");
           QString heureh=QDateTime::currentDateTime().toString("hh:mm");

   if(ui->tableView->currentIndex().row()==-1)
     QMessageBox::information(nullptr, QObject::tr("Suppression"),
              QObject::tr("Veuillez Choisir une cage du Tableau.\n"
                                                "Click Ok to exit."), QMessageBox::Ok);
    else
       {   int NUM=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
 QString str = " Vous voulez vraiment supprimer \n la cage :";
           int ret = QMessageBox::question(this, tr("cage"),str,QMessageBox::Ok|QMessageBox::Cancel);

           switch (ret) {
           case QMessageBox::Ok:
               if (cag.supprimer(NUM)){
                   history h;
                  h.addHISTORYAjout(id,"supprimer",dateh,heureh);
  QMessageBox::information(0, qApp->tr("Suppression"),
              qApp->tr("cage suprimée"), QMessageBox::Ok);
  }
 else
       {
      QMessageBox::critical(0, qApp->tr("Suppression"),
                                         qApp->tr("cage non trouvé "), QMessageBox::Ok);
               }
      break;
           case QMessageBox::Cancel:
             break;
           default:
               // should never be reached
             break;
           }
}
   ui->tableView->setModel(cag.afficher());
}
void gestion_cage1::on_tableView_activated(const QModelIndex &index)
{
    ui->lineEdit_Num->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
     ui->lineEdit_nbr->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
      ui->lineEdit_Etatc->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
       ui->lineEdit_especec->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
}
void gestion_cage1::on_pushButton_modifier_clicked()
{
    int NUM=ui->lineEdit_Num->text().toInt();
        int NBR=ui->lineEdit_nbr->text().toInt();;
        QString ETATC=ui->lineEdit_Etatc->text();
        QString ESPECEC=ui->lineEdit_especec->text();
        if (NUM==NULL)
                 {

          QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NUM!!!!") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),
            qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
                   ui->lineEdit_Num->clear();
                    ui->lineEdit_nbr->clear();
                    ui->lineEdit_Etatc->clear();
                    ui->lineEdit_especec->clear();

                 }

              else if (NBR==NULL)
               {

                   QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NBR!!!!") ;
                   QMessageBox::critical(0, qApp->tr("Ajout"),

                                   qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                   ui->lineEdit_Num->clear();
                  ui->lineEdit_nbr->clear();
                   ui->lineEdit_Etatc->clear();
                  ui->lineEdit_especec->clear();

               }
            else if (ESPECEC==NULL)
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP ESPECEC!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                 ui->lineEdit_Num->clear();
                ui->lineEdit_nbr->clear();
                 ui->lineEdit_Etatc->clear();
                ui->lineEdit_especec->clear();
      }
     else {

        Cage c;
        bool test=c.modifier(NUM,NBR, ETATC,ESPECEC );

        if(test)
        {  ui->tableView->setModel(cag.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("modification effectue\n""click cancel to exit."),
                                     QMessageBox::Cancel);

        }

        else
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                     QObject::tr("modification non effectue\n""click cancel to exit."),
                                     QMessageBox::Cancel);

  }
}

void gestion_cage1::on_pushButton_recherche_clicked()
{
/*    QString cls = ui->lineEdit_Num_2->text();
    ui->tableView->setModel(cag.recherche(cls));*/
    QString NUM=ui->lineEdit_Num_2->text();

                        Model_Completer=new QCompleter(this);
                            Model_Completer->setModel(cag.wombo_combo());
                            ui->lineEdit_Num_2->setCompleter(Model_Completer);
                              QSqlQueryModel* Model_Complete=cag.recherche2(NUM);
                              if (Model_Complete != nullptr)
                                                     {
                                                         ui->tableView->setModel(Model_Complete);
}

}


void gestion_cage1::on_pushButtontri_clicked()
{
      ui->tableView->setModel(cag.tricroissant());
}

void gestion_cage1::on_pushButton_tri2_clicked()
{

    ui->tableView->setModel(cag.tridecroissant());
}
void gestion_cage1::on_pushButton_tri3_clicked()
{
     ui->tableView->setModel(cag.triespece());
}




void gestion_cage1::on_pushButton_clicked()
{
    QString link="https://afdpz.org/le-bien-etre-animal/";
       QDesktopServices::openUrl(QUrl (link)) ;
}

void gestion_cage1::on_pushButton_H_clicked()
{
     ui->tableView_2->setModel(H.afficherh());
}

void gestion_cage1::on_pushButton_2_clicked()
{

 history H;
  H.setid( ui->lineEditid->text().toInt());
     bool test;
             test=H.supprimer(H.get_id());
    QMessageBox msgBox;
        if(test)
        {
 msgBox.setText("Suppression avec succes.");
 ui->tableView_2->setModel(H.afficherh());
        }
else
 msgBox.setText("Echec de suppression.");
        msgBox.exec();

}

void gestion_cage1::on_pushButton_pdf_clicked()
{
    QString strStream;
                             QTextStream out(&strStream);

const int rowCount = ui->tableView_2->model()->rowCount();
 const int columnCount = ui->tableView_2->model()->columnCount();
 out <<  "<html>\n"
                             "<head>\n"
 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
  <<  QString("<title>%1</title>\n").arg("strTitle")
  <<  "</head>\n"
 "<body bgcolor=#ffffff link=#5000A0>\n"
 //     "<align='right'> " << datefich << "</align>"
 "<center> <H1>Liste des Visiteurs</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";
 // headers
 out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
 out<<"<cellspacing=10 cellpadding=3>";
 for (int column = 0; column < columnCount; column++)
  if (!ui->tableView_2->isColumnHidden(column))
   out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
   out << "</tr></thead>\n";
// data table
for (int row = 0; row < rowCount; row++) {
  out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
  for (int column = 0; column < columnCount; column++) {
 if (!ui->tableView_2->isColumnHidden(column)) {
   QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
 }
  }
      out << "</tr>\n";
  }
 out <<  "</table> </center>\n"
 "</body>\n"
 "</html>\n";
  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                      if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
  QPrinter printer (QPrinter::PrinterResolution);
   printer.setOutputFormat(QPrinter::PdfFormat);
 printer.setPaperSize(QPrinter::A4);
 printer.setOutputFileName(fileName);
 QTextDocument doc;
 doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
 doc.print(&printer);

}

void gestion_cage1::on_pushButton_staaaaat_clicked()
{

        QSqlQueryModel * model= new QSqlQueryModel();
                        model->setQuery("select * from CAGE where NBR < 5 ");
                        float nbr=model->rowCount();
                        model->setQuery("select * from CAGE where NBR  between 5 and 12 ");
                        float nbrr=model->rowCount();
                        model->setQuery("select * from CAGE where NBR>12 ");
                        float nbrrr=model->rowCount();
                        float total=nbr+nbrr+nbrrr;
                        QString a=QString("moins de 5  "+QString::number((nbr*100)/total,'f',2)+"%" );
                        QString b=QString("entre 5 et 12 "+QString::number((nbrr*100)/total,'f',2)+"%" );
                        QString c=QString("+12 "+QString::number((nbrrr*100)/total,'f',2)+"%" );
                        QPieSeries *series = new QPieSeries();
                        series->append(a,nbr);
                        series->append(b,nbrr);
                        series->append(c,nbrrr
                                       );
                if (nbr!=0)
                {QPieSlice *slice = series->slices().at(0);
                 slice->setLabelVisible();
                 slice->setPen(QPen());}
                if ( nbrr!=0)
                {
                         // Add label, explode and define brush for 2nd slice
                         QPieSlice *slice1 = series->slices().at(1);
                         //slice1->setExploded();
                         slice1->setLabelVisible();
                }
                if(nbrrr!=0)
                {
                         // Add labels to rest of slices
                         QPieSlice *slice2 = series->slices().at(2);
                         //slice1->setExploded();
                         slice2->setLabelVisible();
                }
                        // Create the chart widget
                        QChart *chart = new QChart();
                        // Add data to chart with title and hide legend
                        chart->addSeries(series);
                        chart->setTitle("Pourcentage Par nombre d'animaux :Nombre Des animaux "+ QString::number(total));
                        chart->legend()->hide();
                        // Used to display the chart
                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        chartView->resize(1000,500);
                        chartView->show();

}

void gestion_cage1::on_pushButton_image_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("choose"), "", tr("image (*.png *.jpg *.jpeg *.bmp *.gif)"));
        if(QString::compare(filename,QString())!=0)
        {
            QImage image;
            bool valid = image.load(filename);
            if(valid)
            {
                ui->placeimage->setPixmap(QPixmap::fromImage(image));
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                      QObject::tr("Image non effectuée.\n"
                                                  "Click Cancel to exit."),QMessageBox::Cancel);
            }
        }
}

void gestion_cage1::on_lineEdit_Num_2_textChanged(const QString &arg1)
{
    QString NUM=ui->lineEdit_Num_2->text();

                        Model_Completer=new QCompleter(this);
                            Model_Completer->setModel(cag.wombo_combo());
                            ui->lineEdit_Num_2->setCompleter(Model_Completer);
                              QSqlQueryModel* Model_Complete=cag.recherche2(NUM);
                              if (Model_Complete != nullptr)
                                                     {
                                                         ui->tableView->setModel(Model_Complete);
}}
