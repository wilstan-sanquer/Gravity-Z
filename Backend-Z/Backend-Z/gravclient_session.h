#ifndef GRAVCLIENT_SESSION_H
#define GRAVCLIENT_SESSION_H
#include <QObject>
#include <QWebSocket>
#include <QMap>
#include <QString>
#include <QList>
#include <QObject>

class gravClient_Session : public QObject
{
    Q_OBJECT
public:
    explicit gravClient_Session(QWebSocket *pclient, QObject *parent = nullptr);
    void sendMessage(const QString &message);

private:
    QWebSocket *m_pclient;

signals:

private slots:
void  onMessageReceived(const QString &message)   ;
};

#endif // GRAVCLIENT_SESSION_H
