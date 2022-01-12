#include "salarios.h"
#include "ui_salarios.h"

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

void Salarios::limpiar()
{
    ui->inHoras->setValue(0);
    ui->inNombre->clear();
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}

void Salarios::calcular()
{
    if(ui->inNombre->text()==""){
        ui->statusbar->showMessage("INGRESE UN NOMBRE VALIDO!",3500);

        QMessageBox::warning(this,"NOMBRE","EL NOMBRE NO ES VALIDO");
        return;
    }
    else if((ui->inMatutina->isChecked()==false&&ui->inNocturna->isChecked()==false&&ui->inVespertina->isChecked()==false)){
        ui->statusbar->showMessage("SE NECESITA SABER LA JORNADA DEL TRABAJADOR",3500);
        QMessageBox::warning(this,"JORNADA","ES NECESARIO ESCOGER LA JORNADA DEL TRABAJADOR");
        return;
    }
    else if(ui->inHoras->value()==0){
        ui->statusbar->showMessage("EL NUMERO DE HORAS NO PUEDE SER 0",3500);
        QMessageBox::warning(this,"HORAS","EL NUMERO DE HORAS NO PUEDE SER 0");
        return;
    }


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
        limpiar();
    }

}


void Salarios::on_cmdCalcular_clicked()
{
    calcular();

}


void Salarios::on_actionNuevo_triggered()
{
    ui->inHoras->setValue(8);
    ui->inNombre->clear();
    ui->outResultado->clear();
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}


void Salarios::on_actioncalcular_triggered()
{
    calcular();
}

void Salarios::guardar()
{
    //abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,"Guardar datos",QDir::home().absolutePath(),"Archivo de salarios (*.slr)");
    //crear un objeto QFile

    QFile archivo(nombreArchivo);
    //abrir para escritura
    if(archivo.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream salida(&archivo);
        salida<<ui->outResultado->toPlainText();
        ui->statusbar->showMessage("Datos almacenados en "+nombreArchivo,3500);
    }
    else{
        QMessageBox::warning(this,"Advertencia!","Los datos no pudieron ser guardados");
    }
    //cerrar el archivo
    archivo.close();
}


void Salarios::on_actionGuardar_triggered()
{
    guardar();
}

void Salarios::abrir()
{
    //abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getOpenFileName(this,"Abrir Archivos",QDir::home().absolutePath(),"Archivo de salarios (*.slr)");
    //crear un objeto QFile

    QFile archivo(nombreArchivo);
    //abrir para lectura
    if(archivo.open(QFile::ReadOnly)){
        QTextStream entrada(&archivo);
        //leer todo el contenido
       QString datos=entrada.readAll();
       //cargar a la pantalla
       ui->outResultado->clear();
       ui->outResultado->setPlainText(datos);
        ui->statusbar->showMessage("El archivo "+nombreArchivo+" no pudo ser leido!",3500);
    }
    else{
        QMessageBox::warning(this,"Advertencia!","Los datos no pudieron ser leidos");
    }
    //cerrar el archivo
    archivo.close();
}

void Salarios::on_actionAbrir_triggered()
{

    abrir();
}

