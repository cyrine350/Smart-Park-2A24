#ifndef HISTORY_H
#define HISTORY_H
#include <QString>
#include<QSqlQueryModel>


class history
{
public:
    history();
   history(int,QString,QString,QString);
   void setid(int n);
   void setactivity(int n);
   void setdateh(QString n);
   void setheureh(QString n);



  int get_id();

   QString getactivity();
   QString get_dateh();
     QString get_heureh();
   bool addHISTORYAjout(int id,QString activity,QString dateh,QString heureh);

   QSqlQueryModel* afficherHistorique();
   QSqlQueryModel* afficherh();
   QSqlQueryModel *displayClause(QString cls);
   bool supprimer(int id );


private:
   int id ;
    QString activity,dateh,heureh;


};

#endif // HISTORY_H
