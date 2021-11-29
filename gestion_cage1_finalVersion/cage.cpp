#include "cage.h"
#include <QDateTime>
#include<QSqlQuery>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QtDebug>
#include<QObject>
#include <QMessageBox>


Cage::Cage()
    {
        NUM=0;
        NBR=0;
        ESPECEC="";
       ETATC="";
     }
Cage::Cage(int NUM,int NBR,QString ETATC,QString ESPECEC)
{this->NUM=NUM;
this->NBR=NBR;
 this->ETATC=ETATC;
 this->ESPECEC=ESPECEC;

}

void Cage::setNUM(int n)
{NUM = n;}
void Cage::setNBR(int n)
{ NBR = n;}
void Cage::setETATC(QString n)
{ ETATC = n;}
void  Cage::setESPECEC(QString n)
{ESPECEC = n;}
int Cage ::get_NUM()
{return NUM;}
int  Cage::get_NBR()
{return NBR;}
QString Cage:: get_ETATC()
{return ETATC;}
QString Cage::get_ESPECEC()
{return ESPECEC;}

bool Cage::ajouter()
    {
        QSqlQuery query;
    QString res=QString ::number(NUM);
    query.prepare("INSERT INTO CAGE (NUM, NBR, ETATC, ESPECEC)"
                        "VALUES (:NUM, :NBR, :ETATC, :ESPECEC)");
     query.bindValue(":NUM", res);
    query.bindValue(":NBR", NBR);
     query.bindValue(":ETATC", ETATC);
    query.bindValue(":ESPECEC", ESPECEC);
    if((ETATC !="bon") && (ETATC !="mauvais") )
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("etat doit etre bon ou mauvais\n""click cancel to exit."),
                                 QMessageBox::Cancel);
        return false;}
else
return query.exec();
 }

 bool Cage ::supprimer(int NUM )
     {  QSqlQuery query;

         query.prepare("DELETE FROM CAGE where NUM=:NUM");
         query.bindValue(0,NUM);
         return query.exec();
     }
 QSqlQueryModel* Cage::afficher()
    {
      QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT* FROM CAGE");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("NBR"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETATC"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ESPECEC"));
return  model;
  }
bool Cage::modifier(int NUM,int NBR ,QString ETATC, QString ESPECEC )
 {
     QSqlQuery query;
     query.prepare("update CAGE SET NUM=:NUM,NBR=:NBR,ETATC=:ETATC,ESPECEC=:ESPECEC where NUM=:NUM");
     query.bindValue(":NUM", NUM);
     query.bindValue(":NBR",NBR);
     query.bindValue(":ETATC",ETATC);
     query.bindValue(":ESPECEC",ESPECEC);
     if((ETATC !="bon") && (ETATC !="mauvais") )
     {
         QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                  QObject::tr("etat doit etre bon ou mauvais\n""click cancel to exit."),
                                  QMessageBox::Cancel);
  return false;
     }
return query.exec();
 }
 QSqlQueryModel * Cage::tricroissant()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * FROM CAGE ORDER BY NBR ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NBR"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETATC"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("ESPECEC"));
 return model;
 }
 QSqlQueryModel * Cage::tridecroissant()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * FROM CAGE ORDER BY NUM ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NBR"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETATC"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("ESPECEC"));

     return model;
 }
 QSqlQueryModel * Cage::triespece()
 {QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("select * FROM CAGE ORDER BY ESPECEC ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NBR"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETATC"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("ESPECEC"));

     return model;
 }



 /*QSqlQueryModel * Cage::recherche(QString cls)
 {QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("select * FROM CAGE WHERE NUM LIKE '%"+cls+"%'");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NBR"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETATC"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("ESPECEC"));
 return model;
 }*/
 QSqlQueryModel * Cage::displayClause(QString cls)
 {
     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("SELECT * FROM CAGE " +cls);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NBR"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETATC"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("ESPECEC"));

     return model;
 }

 QSqlQueryModel*  Cage ::recherche2(QString NUM)
  {

     QSqlQuery qry;


      qry.prepare("SELECT* FROM CAGE where NUM=:NUM");
      qry.bindValue(":NUM",NUM);
      qry.exec();
      QSqlQueryModel *model= new QSqlQueryModel;
 model->setQuery(qry);


     return model;
 }
 QSqlQueryModel* Cage::wombo_combo(){

     QSqlQueryModel* model=new QSqlQueryModel();
     model->setQuery("select NUM from CAGE");
     return model;
 }

 /* QSqlQueryModel * Cage ::stat()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("select ETATC,(count(ETATC)*100/ (select count(*)from CAGE)) as pourcentage from CAGE group by ETATC");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ETATC"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("percentage"));
        return model;
 }*/
