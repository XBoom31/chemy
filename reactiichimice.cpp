#include "reactiichimice.h"
#include "ui_reactiichimice.h"
#include "vars.h"


#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>



//merge doar pentru molecule simple
//nu merge daca are numere in element, cel putin nu bine
float masa(QString elem){
    float ret = 0;
    for(int i = 0; i<120; i++){
        auto sym = vars.tabel[i].sym.c_str();
        if(elem.contains(sym))
            ret += vars.tabel[i].atomic_mass;
    }
    return ret;
}

const QString cifre[] = {"0", "1", "2", "3", "4"
                         "5", "6", "7", "8", "9"};

reactiichimice::reactiichimice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reactiichimice)
{
    ui->setupUi(this);
    x = y = 10;
    w = h = 400;
    nr = 35;

    atomz[0]= QImage(":/home/impl38/dev/chimie/atom.png");
    atomz[1]= QImage(":/home/impl38/dev/chimie/atom2.png");


    //citim lista de reactii
    QFile freac(":/home/impl38/dev/chimie/reactii");
    freac.open(QFile::ReadOnly);
    QTextStream str(&freac);
    QString line;
    while (str.readLineInto(&line)) {
        reactii.push_back(line.toStdString());
    }

}

void reactiichimice::createatom(QPainter& painter, int type){
    int px = rand() % w;
    int py = rand() % h;
    const int sz = 30;
    QRect pos(px - sz/2, py-sz/2, sz, sz);
    painter.drawImage(pos, atomz[type]);

}

void reactiichimice::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRect(0,0,w,h);
    srand(time(0));
    float per = 0.5f;
    for(int i = 0; i < nr * per; i++){
        createatom(painter, 0);
    }
    for(int i = 0; i < nr * (1-per); i++){
        createatom(painter, 1);
    }
}

reactiichimice::~reactiichimice()
{
    delete ui;
}


// Function to calculate GCD
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate b1, b2 and b3
int balance(int x, int y, int p, int q)
{
    // Variable declaration
    int b1, b2, b3;

    if (p % x == 0 && q % y == 0) {
        b1 = p / x;
        b2 = q / y;
        b3 = 1;
    }

    else {
        p = p * y;
        q = q * x;
        b3 = x * y;

        // temp variable to store gcd
        int temp = gcd(p, gcd(q, b3));

        // Computing GCD
        b1 = p / temp;
        b2 = q / temp;
        b3 = b3 / temp;
    }

    //b1g encoding
    return b1 * 100 + b2 * 10 + b3;


}

//este caracterul o cifra?
bool cifra(QChar c){
    for(auto x : cifre)
        if(x == c)
            return true;
    return false;
}

//desparte elementul in atom si in numarul de atomi in 2 variabile
QString desparte(QString E1, int &x){
    int e1c = 0;
    for (auto n : cifre){
        if(E1.contains(n)) e1c++;
    }
    QString A = E1;
    //vedem daca are paranteze
    bool paranteze = false;
    for(QChar c:A)
        if(c=="("){
            paranteze = true;
            break;
        }

    //pentru element simplu, fara smecherii
    if(e1c == 1){
        if(!paranteze){
            for(auto n : cifre)
                A.replace(n, "");
            x=E1.at(E1.size()-1).toLatin1() - 48; // -48 == char to int
        }
        else{
            QString nr;
            //punem ce e in fata parantezei in nr
            for(int i = 0; i<A.size(); i++){
                if(cifra(A.at(i)))
                    nr+=A.at(i);
                if(A.at(i)=="(")
                    break;
            }
            //stergem numarul din a
            A.replace(nr,"");
            //s-ar putea sa fie doua numere la fel in a si atunci l-ar lua naspa
            x = atoi(nr.toStdString().c_str());
        }
    }
    else if(!e1c) //daca nu are nimic in fata
        x = 1;    //vom spune ca e doar un singur element
    else{   //broken

        //daca are paranteze luam numarul din fata si
        //il stergem din A
        if(paranteze){
            QString nr;
            //punem ce e in fata parantezei in nr
            for(int i = 0; i<A.size(); i++){
                if(cifra(A.at(i)))
                    nr+=A.at(i);
                if(A.at(i)=="(")
                    break;
            }
            //stergem numarul din a
            A.replace(nr,"");
            //s-ar putea sa fie doua numere la fel in a si atunci l-ar lua naspa
            x = atoi(nr.toStdString().c_str());
        }
    }
    //stergem parantezele
    A.replace("(", "");
    A.replace(")", "");

    //stergem primul numar, nu ar trebui sa facem asta, dar deocamdata
    //doar atat putem face pana rezolva cineva functia de mai sus
    //for(auto n : cifre)
      //  if(A.at(0) == n)
        //    A.remove(0, 1);

    return A;
}

#define S(x) x.toStdString().c_str()

QString reactiichimice::process(QString str){
    if(str=="")
        return "No data";
    int a;
    QString E1 = str.split("+")[0];
    QString E2 = str.split("+")[1];
    //gasim primul element   A si x din E1
    QString A = desparte(E1, a);
    //gasim B si y din E2
    QString B = desparte(E2, a);

    for(auto buf:reactii)
        if(buf != ""){
            QString s = buf.c_str();
            s = s.split("->")[0];
            if(s.contains(A, Qt::CaseInsensitive) && s.contains(B,Qt::CaseInsensitive))
                return buf.c_str();
        }

    return "No data";
}

QString reactiichimice::balance(QString str){
    int x, y, p, q;
    //gasim ce e in stanga de sageata
    QString left = str.split("->")[0];
    //gasim ce e in dreapta de sageata
    QString right = str.split("->")[1];
    //despartim elementele din stanga
    QString E1 = left.split("+")[0];
    QString E2 = left.split("+")[1];
    //gasim primul element   A si x din E1
    QString A = desparte(E1, x);
    //gasim B si y din E2
    QString B = desparte(E2, y);
    //gasim C din dreapta
	
	int plusuri = 0;

    auto right2 = (const char*)right.toStdString().c_str();

   // for(qsizetype i=0; i < right.size()-1; i++)
    //    if(right.at(i) == "+")
    //		plusuri++;
	
    std::cout << S(A) << x << S(B) << y << std::endl <<  p << std::endl;
    return A;

}

void reactiichimice::on_balancebtn_clicked()
{
    ui->balanceoutput->setPlainText(process(ui->balanceinput->toPlainText()));
}


void reactiichimice::on_balt_clicked()
{
    srand(time(0));
    int rid = rand() % reactii.size();
    QString reactie = reactii.at(rid).c_str();
    if(reactie == "") return;

    QString e1,e2,e3;
    //gasim ce e in stanga de sageata
    QString left = reactie.split("->")[0];
    //gasim ce e in dreapta de sageata
    QString right = reactie.split("->")[1];
    //despartim elementele din stanga
    QString E1 = left.split("+")[0];
    QString E2 = left.split("+")[1];

    e1 = desparte(E1, c1);
    e2 = desparte(E2, c2);
    e3 = desparte(right, c3);

    ui->elem1->setText(e1);
    ui->elem2->setText(e2);
    ui->elem3->setText(e3);
}


void reactiichimice::on_bverifica_clicked()
{
    QIcon corect = QIcon(":/home/impl38/dev/chimie/check.png");
    QIcon gresit = QIcon(":/home/impl38/dev/chimie/x.png");
    if(ui->cof1->value() == c1 &&
       ui->cof2->value() == c2 &&
       ui->cof3->value() == c3)
        ui->bverifica->setIcon(corect);
    else
        ui->bverifica->setIcon(gresit);
}

f
