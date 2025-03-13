#include <QtWidgets/QApplication>
#include "movie_service.h"
#include "all_tests.h"
#include <QtWidgets/qmessagebox.h>
#include "app_gui.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Tests testApp{};

    try {
        MovieRepoFromFile repo{ "data.txt" };
        Validator val;
        MovieService srv{ repo, val };
        AppGUI gui{ srv };
        gui.show();
        return a.exec();
     }
    catch (Exception& err)
    {
        QMessageBox* mess = new QMessageBox;
        mess->setParent(nullptr);
        mess->setWindowTitle("Eroare");
        mess->setText(QString::fromStdString(err.Message));
        mess->show();
    }
    
}