#ifndef FILEDIALOG_H
#define FILEDIALOG_H
#include <QtCore>
#include <QFileDialog>

class FileDialog : public QFileDialog
{
public:
    FileDialog();

    void initWindow();

private slots:
};

#endif // FILEDIALOG_H
