#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

#include "Logger/logger.h"

#define EFM_POST_CREDS "http://lortetcesar.fr/api/connect"
#define EFM_POST_CREDS "http://lortetcesar.fr/api/connect"


class NetworkManager : public QObject
{
    Q_OBJECT

public:
    static NetworkManager *getInstance();
    void onReply();
    void downloadFile();
    void slotError();    
    void getGameFiles();

public slots:
    void postCredentials(QString username, QString password);

private:
    explicit NetworkManager(QObject *parent = nullptr);
    static NetworkManager *m_networkManager;
    QNetworkReply *m_networkReply;
    QNetworkAccessManager *m_networkAccessManager;

signals:
    void loginQueryAnswer(QString token);

};

#endif // NETWORKMANAGER_H
