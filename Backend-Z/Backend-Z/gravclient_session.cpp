#include "gravclient_session.h"
#include "grav_ball.h"
#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QMap>
#include <QString>
#include <QList>
#include <QJsonDocument>   // Pour manipuler le document global
#include <QJsonObject>     // Pour les structures { "cle": "valeur" }
#include <QJsonArray>      // Si tu as des listes [ ... ]
#include <QJsonValue>      // Pour manipuler une donnée précise
#include <QJsonParseError> // TRES important pour savoir pourquoi ça crash



gravClient_Session::gravClient_Session(QWebSocket *pclient, QObject *parent)
{
    m_pclient=pclient;
    // connect message reçue
    connect(m_pclient, &QWebSocket::textMessageReceived, this, &gravClient_Session::onMessageReceived);


}

void gravClient_Session::onMessageReceived(const QString &message)
{
    // message contient ici le texte envoyé par le client
    qDebug() << "Message reçu du Squid Client :" << message;
    // début trantement JSON
    QString reponc="";
    QString statue="";
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        reponc = "Erreur : Le JSON est corrompu ou mal formé ou vide.";
    }else{
        QJsonObject root = doc.object();
        QString status = root["status"].toString();
        if (status=="create"){
            float X = root["x"].toDouble();
            float Y = root["y"].toDouble();
            float mass = root["mass"].toDouble();
            float coefficient_f = root["coefficient_f"].toDouble();

            //Lave 0.50
            //eau 0.60
            //plond 0.47
            //Plume 1


            qDebug() << "création de balle a X : "<< X <<" Y: "<< Y;
            qDebug() << ". la balle a comme mass" << mass << "et sont coefficient de frener est de " << coefficient_f ;
            grav_ball *ball = new grav_ball(X,Y,mass,coefficient_f);
            while (ball->get_Y()==0){
                float new_y = ball->calcule_grav();
                qDebug() << new_y ;

                QJsonObject jsonObj;
                jsonObj["id"] = 1;
                jsonObj["status"] = "falling";
                jsonObj["x"] = X;
                jsonObj["y"] = new_y;

                QJsonDocument doc(jsonObj);
                QString jsonString = doc.toJson(QJsonDocument::Compact);
                this->sendMessage(jsonString);

            }

        }
    }
}


void gravClient_Session::sendMessage(const QString &message)
{
    // On vérifie que le pointeur n'est pas nulptr == conextion fermer
    if (m_pclient && m_pclient->isValid()) {
        m_pclient->sendTextMessage(message);
    } else {
        qDebug() << "Erreur : Impossible d'envoyer le message, socket invalide ou déconnecté.";
    }
}
