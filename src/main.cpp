#include "./widgets/DrawingsBDWidget.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    
    DrawingsBDWidget w;
    w.show();

    return a.exec();
}
