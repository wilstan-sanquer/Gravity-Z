#ifndef GRAVE_SERVER_H
#define GRAVE_SERVER_H

#include <QObject>
#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QMap>
#include <QString>
#include <QList>
#include "gravclient_session.h"

class grave_Server : public QObject
{
    Q_OBJECT
public:
    explicit grave_Server(QObject *parent = nullptr);
    void start_SquidServer (int porte);
private:

    QWebSocketServer *m_pserver;
    gravClient_Session *m_pnewclient;
    int porte;
    QList<gravClient_Session*> User;

private slots:
    void New_Connection();
signals:
};

#endif // GRAVE_SERVER_H
