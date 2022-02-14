#include "OcctQtFile.h"
#include "ui_OcctQtFile.h"
#include "iostream"

OcctQtFile::OcctQtFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OcctQtFile)
{
    ui->setupUi(this);
}

OcctQtFile::~OcctQtFile()
{
    delete ui;
}

void OcctQtFile::on_toolButton_open_document_pressed()
{
    QString filename;

    QFileDialog *fd = new QFileDialog();
    fd->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    fd->setOption(QFileDialog::DontUseNativeDialog, true);

    QPalette p=OcctQtFile().palette();
    fd->setPalette(p);
    fd->setNameFilter("Step-Files (*.step);;Dxf-Files (*.dxf);;Ngc-Files (*.ngc)");
    ui->gridLayout_filedialog->addWidget(fd);


    if (fd->exec()){
        filename = QString::fromUtf8(fd->selectedFiles()[0].toUtf8().constData());

    }
    ui->listWidget->addItem(filename);

    if(fd->Reject){
        std::cout<<"rejected"<<std::endl;
    }
    if(fd->Accept){
        std::cout<<"accepted"<<std::endl;
    }
    //! Avoid processing when the cancel button is pressed.
    if(filename.size()>0){
        QPair<QString,QString> data;
        data.first=filename;
        data.second=fd->selectedNameFilter();
        toolButton_open_document_pressed(data);
    }
    this->close();
}

void OcctQtFile::on_toolButton_close_document_pressed()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        toolButton_close_document_pressed(item->text());
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
    this->close();
}

void OcctQtFile::on_buttonBox_accepted()
{
    this->close();
}

void OcctQtFile::on_toolButton_save_document_pressed()
{
    QString filename;

    QFileDialog *fd = new QFileDialog();
    fd->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    QPalette p=OcctQtFile().palette();
    fd->setPalette(p);
    fd->setNameFilter("Dxf-Files (*.dxf)");
    ui->gridLayout_filedialog->addWidget(fd);

    if (fd->exec()){
        filename = QString::fromUtf8(fd->selectedFiles()[0].toUtf8().constData());


    }
    //! Avoid processing when the cancel button is pressed.
    if(filename.size()>0){
        QPair<QString,QString> data;
        data.first=filename;
        data.second=fd->selectedNameFilter();
        toolButton_save_document_pressed(data);
    }
    this->close();
}
