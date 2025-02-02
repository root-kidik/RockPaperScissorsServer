#include <QCoreApplication>
#include <QtPlugin>

#include <infrastructure/Server.hpp>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    rps::infrastructure::Server server;
    if (!server.listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server could not start! Choose another port";
        return 1;
    }
    qDebug() << "Server started on port" << server.serverPort();

    return a.exec();
}
