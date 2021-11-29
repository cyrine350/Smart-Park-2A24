#include "history.h"
#include <QDateTime>
#include<QSqlQuery>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QtDebug>
#include<QObject>
#include <QMessageBox>


history::history()
{
         id=0;
        activity="xx";
        dateh="xx";
          heureh="xx";

}


history::history(int id,QString activity,QString dateh,QString heureh)
{this->id=id;
this-> activity=activity;
 this-> dateh= dateh;

     this-> heureh= heureh;


}

void history::setid(int n)
{ id = n;}
void history::setactivity(int n)
{ activity = n;}
void history::setdateh(QString n)
{ dateh= n;}
void history::setheureh(QString n)
{ heureh= n;}
int history ::get_id()
{return id;}


bool history ::addHISTORYAjout(int id,QString activity,QString dateh,QString heureh)
{
    QSqlQuery query;
QString res=QString ::number(id);
query.prepare("INSERT INTO HISTORY (ID, ACTIVITY, DATEH,HEUREH) "
                    "VALUES (:ID, :ACTIVITY, :DATEH,:HEUREH)");
 query.bindValue(":ID", res);
query.bindValue(":ACTIVITY", activity);
 query.bindValue(":DATEH", dateh);
 query.bindValue(":HEUREH", heureh);

 return query.exec();
}

QSqlQueryModel* history::afficherh()
   {
     QSqlQueryModel* model=new QSqlQueryModel();
      model->setQuery("SELECT* FROM HISTORY");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("ACTIVITY"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEH"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("HEUREH"));

return  model;
 }
QSqlQueryModel * history::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM HISTORY " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ACTIVITY"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEH"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEUREH"));


    return model;
}
bool history ::supprimer(int id )
    {  QSqlQuery query;

        query.prepare("DELETE FROM HISTORY where id=:id");
        query.bindValue(0,id);
        return query.exec();
    }












