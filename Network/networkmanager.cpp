#include "networkmanager.h"

NetworkManager *NetworkManager::m_networkManager = nullptr;

NetworkManager *NetworkManager::getInstance()
{
    if(m_networkManager == nullptr){
        m_networkManager = new NetworkManager();
    }
    return m_networkManager;
}

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager();
}

// ************************************************************** HTTP POST METHOD ******************************************************************************************************//
void NetworkManager::postCredentials(QString username, QString password)
{
    QUrlQuery postData;
    postData.addQueryItem("username", username);
    postData.addQueryItem("password", password);

    QNetworkRequest request(QUrl(EFM_POST_CREDS));
    request.setRawHeader("User-Agent", "User Agent");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_networkReply = m_networkAccessManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    connect(m_networkReply, &QIODevice::readyRead, this, &NetworkManager::onReply);
}

// ************************************************************** HTTP GET METHOD ******************************************************************************************************//
void NetworkManager::getGameFiles()
{
    QUrlQuery postData;

    QNetworkRequest request(QUrl(EFM_POST_CREDS));
    request.setRawHeader("User-Agent", "User Agent");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_networkReply = m_networkAccessManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    connect(m_networkReply, &QIODevice::readyRead, this, &NetworkManager::downloadFile);
}



// ************************************************************** HTTP REPLY ******************************************************************************************************//
void NetworkManager::onReply()
{
    QString reply = m_networkReply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();
    QString type_value = jsonObject.value("type").toString();
    if(type_value == "success") emit loginQueryAnswer(jsonObject.value("token").toString());
    else emit loginQueryAnswer(NULL);
}

void NetworkManager::downloadFile()
{
    if(m_networkReply->error() == QNetworkReply::NoError){
            QFile other("Download.zip");
            other.open(QIODevice::WriteOnly);
            other.write(m_networkReply->readAll());
            other.flush();
            other.close();
        }
        m_networkReply->deleteLater();
}
// ************************************************************** HTTP ERROR ******************************************************************************************************//
void NetworkManager::slotError()
{
    Logger::getInstance()->addLog(Logger::LogLevel::ERROR,  m_networkReply->errorString());
}
