#include <QCoreApplication>
#include "grave_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    grave_Server server(&a);
    server.start_SquidServer(1234);


    return a.exec();
}
