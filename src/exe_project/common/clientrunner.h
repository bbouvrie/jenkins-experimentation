#ifndef CLIENTRUNNER_H
#define CLIENTRUNNER_H

#include <QObject>
#include <QQueue>
#include <QString>
#include <QTcpSocket>

#include "qtjson.h"

class AIBaseClass;
class JsonReplyMessage;

class ClientRunner : public QObject
{
    Q_OBJECT
public:
    explicit ClientRunner(int portNr, const QString token, AIBaseClass* ai, QObject *parent = nullptr);
    ~ClientRunner();

signals:
    void finished();
    void messageReceived(Json::Value message);

public slots:
    void run();

    void socketConnected();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError /* error */);
    void readyRead();

    void executeCommand(Json::Value message);

private:
    void receiveData();
    void sendReply(const JsonReplyMessage& reply);

    int m_PortNr;
    QString m_Token;
    AIBaseClass* m_Ai;

    QTcpSocket* m_ClientSocket;
    int m_ExpectedDataSize;
    QByteArray m_CurrentData;
};

#endif // CLIENTRUNNER_H
