#ifndef CAGE_H
#define CAGE_H
#include <QString>
#include<QSqlQueryModel>
class Cage
{
public:
    Cage();
    Cage(int,int,QString,QString);

    void setNUM(int n);
    void setNBR(int n);
    void setESPECEC(QString n);
    void setETATC(QString n);

   int get_NUM();
    int get_NBR();
    QString get_ESPECEC();
    QString get_ETATC();
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    bool modifier(int NUM,int NBR ,QString ETATC, QString ESPECEC );
     QSqlQueryModel* tricroissant();
      QSqlQueryModel *tridecroissant();
       QSqlQueryModel * triespece();
     QSqlQueryModel *displayClause(QString cls);
     QSqlQueryModel* recherche(QString cls);
     // QSqlQueryModel* stat();
     QSqlQueryModel*  recherche2(QString NUM);
     QSqlQueryModel* wombo_combo();


       void addToHistory(QString action, QString type, QString id);
        bool addHISTORYAjout(int id,QString activity,QString dateh);
private:
     int NUM, NBR;
     QString ETATC,ESPECEC;

};


#endif // CAGE_H
