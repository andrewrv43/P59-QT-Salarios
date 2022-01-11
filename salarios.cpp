#include "salarios.h"
#include "ui_salarios.h"
#include <QMessageBox>

Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador=new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_cmdCalcular_clicked()
{

    if(ui->inNombre->text()==""){
    ui->statusbar->showMessage("INGRESE UN NOMBRE VALIDO!",3500);

    QMessageBox::warning(this,"NOMBRE","EL NOMBRE NO ES VALIDO");
    }
    else if((ui->inMatutina->isChecked()==false&&ui->inNocturna->isChecked()==false&&ui->inVespertina->isChecked()==false)){
       ui->statusbar->showMessage("SE NECESITA SABER LA JORNADA DEL TRABAJADOR",3500);
       QMessageBox::warning(this,"JORNADA","ES NECESARIO ESCOGER LA JORNADA DEL TRABAJADOR");
    }
    else{

    QString nombre=ui->inNombre->text();
    int horas=ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
            jornada=TipoJornada::Matutina;
}
            else if(ui->inNocturna->isChecked()){
                       jornada=TipoJornada::Nocturna;
           }
    if(ui->inVespertina->isChecked()){
               jornada=TipoJornada::Vespertina;
   }
    m_controlador->agregarObrero(nombre,horas,jornada);

    if(m_controlador->calcularSalario()){
        ui->outResultado->appendPlainText(m_controlador->obrero()->toString());
}

}
}


void Salarios::on_actionNuevo_triggered()
{
    ui->inHoras->setValue(8);
    ui->inNombre->clear();
    ui->outResultado->clear();
    ui->inMatutina->setChecked(true);
}

