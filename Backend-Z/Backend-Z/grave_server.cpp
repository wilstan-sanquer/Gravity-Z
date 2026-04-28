#include "grave_server.h"
#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QMap>
#include <QString>
#include <QList>

grave_Server::grave_Server(QObject *parent)
    : QObject{parent}
{}

void grave_Server::start_SquidServer(int porte)
{
    m_pserver = new QWebSocketServer(QStringLiteral("Gravi-Z"),QWebSocketServer::NonSecureMode);

    // C'est ici qu'on connecte le serveur à ton slot New_Connection
    connect(m_pserver, &QWebSocketServer::newConnection,this, &grave_Server::New_Connection);


    if (m_pserver->listen(QHostAddress::Any, porte)) {
        qDebug() << "Serveur lancé sur le port" << porte;
    }else{
        qDebug() << "Erreur: Le port" << porte << "est probablement en cours d'utilisation par un autre processus.";
    }
}

void grave_Server::New_Connection()
{
    QWebSocket *pSocket = m_pserver->nextPendingConnection();

    if (pSocket){
        qDebug() << "nouvaux GRAVE Client";
        m_pnewclient = new gravClient_Session(pSocket);


        User.append(m_pnewclient);
        qDebug() << "Le nouvaux est connecter";
    }
}
