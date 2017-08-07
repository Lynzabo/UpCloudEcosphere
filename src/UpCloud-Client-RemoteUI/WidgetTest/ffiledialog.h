#ifndef FILEDIALOG_H
#define FILEDIALOG_H
#include <QtCore>
#include <QFileDialog>

class FFileDialog : public QFileDialog
{
public:
    FFileDialog();

    void initWindow();

private slots:
};

#endif // FILEDIALOG_H
