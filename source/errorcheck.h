#ifndef ERRORCHECK_H
#define ERRORCHECK_H
#include <QObject>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QTextStream>


class ErrorCheck: public QObject
{
    Q_OBJECT
public:
    explicit ErrorCheck(QObject *parent=nullptr);
    void errorcheck(QString *list);
    bool check_for_comment(QString *string);
    bool check_for_cmp_instruction(QStringList &list);
    QString check_for_cmp(QStringList *word,QStringList *Toword,int *j);
    int check_for_jstatments(QStringList *word,QStringList *Toword,int *j);
    int check_for_otheroperands(QStringList *word,QStringList *Toword,int *j);
    int check_for_dci(QStringList *word,QStringList *Toword,int *j);
    int check_for_label(QStringList *word,QStringList *Toword,int *j);
    bool check_for_dci_instruction(QStringList &string);
    bool check_for_jstatments_instructions(QStringList &string);
    bool check_for_otheroperands_instructions(QStringList &string);
    bool check_for_add_and_move_instruction(QStringList &string);
    QString check_for_add_and_move(QStringList *word,QStringList *Toword,int *j);
    /*
    NEW STUFF GOOD STUFF
    */
/////////////////////////////////////////////////////////////////////////
    bool check_for_dca_instruction(QStringList &list);
    int check_for_dca(QStringList *word,QStringList *Toword,int *j);
    bool check_for_rdi_instruction(QStringList &list);
    bool check_for_prt_instruction(QStringList &string);
    int check_for_prt(QStringList *word,QStringList *Toword,int *j);
    int check_for_rdi(QStringList *word,QStringList *Toword,int *j);

//////////////////////////////////////////////////////////////////////////

signals:
    void send_print_errors(QString message);

private:

    QStringList word;
    QStringList Toword;

    QStringList instructions={"rdi","cmp","#"};
    QStringList j_instructions={"jmr","jmp","jeq","jls"};
    QStringList cmp_operand={"cmp"};
    QStringList prt_instruction={"prt"};
    QStringList add_and_remove_instructions={"mov","add"};

};
#endif // ERRORCHECK_H
