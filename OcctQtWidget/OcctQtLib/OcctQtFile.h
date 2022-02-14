#ifndef OCCTQTFILE_H
#define OCCTQTFILE_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class OcctQtFile;
}

class OcctQtFile : public QWidget
{
    Q_OBJECT

public:
    explicit OcctQtFile(QWidget *parent = nullptr);
    ~OcctQtFile();

signals:
    void toolButton_open_document_pressed(QPair<QString,QString> data);
    void toolButton_save_document_pressed(QPair<QString,QString> data);
    void toolButton_close_document_pressed(QString str);

private slots:
    void on_toolButton_open_document_pressed();
    void on_toolButton_close_document_pressed();
    void on_buttonBox_accepted();

    void on_toolButton_save_document_pressed();

private:
    Ui::OcctQtFile *ui;
};

#endif // OCCTQTFILE_H
