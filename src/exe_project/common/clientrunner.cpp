#include "clientrunner.h"

#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>

#include "AIBaseClass.h"
#include "JsonClientMsg.h"
#include "util.h"

ClientRunner::ClientRunner(int portNr, const QString token, AIBaseClass* ai, QObject *parent)
    : QObject(parent)
    , m_PortNr(portNr)
    , m_Token(token)
    , m_Ai(ai)
    , m_ClientSocket(new QTcpSocket(this))
    , m_ExpectedDataSize(0)
{
    // Ensure token ends with newline character.
    if (!m_Token.endsWith('\n'))
    {
        m_Token.append('\n');
    }

    // Set up signals for handling of important socket events
    connect(m_ClientSocket, &QAbstractSocket::connected, this, &ClientRunner::socketConnected);
    connect(m_ClientSocket, &QAbstractSocket::disconnected, this, &ClientRunner::socketDisconnected);
    connect(m_ClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(m_ClientSocket, &QIODevice::readyRead, this, &ClientRunner::readyRead);

    // Set up command handling
    connect(this, &ClientRunner::messageReceived, this, &ClientRunner::executeCommand);
}

ClientRunner::~ClientRunner()
{
    delete m_Ai;
}

void ClientRunner::run()
{
    // Connect to server and send identification string
    m_ClientSocket->connectToHost(QHostAddress(QHostAddress::LocalHost), m_PortNr);
}

void ClientRunner::socketConnected()
{
    qDebug() << "Socket connected, sending identification string.";
    QByteArray tokenData = m_Token.toLocal8Bit();
    m_ClientSocket->write(tokenData);
}

void ClientRunner::socketDisconnected()
{
    qDebug() << "Socket disconneced. Exiting.";
    emit finished();
}

void ClientRunner::socketError(QAbstractSocket::SocketError error)
{
    if (error != QAbstractSocket::RemoteHostClosedError)
    {
        // Abort on socket error
        qCritical() << "Socket error encountered:"<< m_ClientSocket->errorString();
        QCoreApplication::exit(1);
    }
}

void ClientRunner::readyRead()
{
    while(m_ClientSocket->bytesAvailable() > 0)
    {
        receiveData();
    }
}

void ClientRunner::executeCommand(Json::Value message)
{
    std::string command = JsonRequestMessage::getCommand(message);
    qDebug() << "Received request:" << command.c_str();

    if (command == JRequestClientActionMessage::getTypeName())
    {
        // RequestClientAction
        JRequestClientActionMessage request(message);
        JGameState jgsc = request.getGameState();
        GameStateContainer gsc;
        gsc.cycle = jgsc.getCycle();
        gsc.width = jgsc.getMap().getWidth();
        gsc.height = jgsc.getMap().getHeight();;
        gsc.players = jgsc.getMap().getPlayers();
        gsc.entities = jgsc.getMap().getEntities();
        gsc.tiles = jgsc.getMap().getTiles();

        ActionType action = m_Ai->GetAction(gsc);
        std::string actionStr = Util::ActionToStr(action);

        JRequestClientActionReply reply(actionStr);

        sendReply(reply);
    }
    else if (command == JRequestClientIconMessage::getTypeName())
    {
        // RequestClientIcon
        JRequestClientIconReply reply(m_Ai->GetIcon());
        sendReply(reply);
    }
    else if (command == JRequestClientNameMessage::getTypeName())
    {
        // RequestClientName
        JRequestClientNameReply reply(m_Ai->GetName());
        sendReply(reply);

    }
    else if (command == JSetPlayerNameMessage::getTypeName())
    {
        // SetPlayerName
        JSetPlayerNameMessage request(message);
        m_Ai->SetPlayerName(request.getPlayerName());

        sendReply(JSetPlayerNameReply());
    }
    else
    {
        qWarning() << "Received unrecognized command '" << command.c_str() << "'. Command will be ignored.";
    }
}

void ClientRunner::receiveData()
{
    if (m_ExpectedDataSize == 0)
    {
        // New block of data, try to read size header. If line cannot be read yet 'readyRead' will be triggered again later.
        if (m_ClientSocket->canReadLine())
        {
            bool ok = false;
            QString sizeHeader = QString::fromLocal8Bit(m_ClientSocket->readLine());
            m_ExpectedDataSize = sizeHeader.toInt(&ok);

            if (!ok && !sizeHeader.isEmpty())
            {
                qWarning() << "Failed to read message size header. Ignoring next message.";
            }
        }
    }

    if (m_ExpectedDataSize > 0)
    {
        // Read up to iExpectedDataSize bytes.
        Q_ASSERT(m_CurrentData.size() < m_ExpectedDataSize);
        m_CurrentData.append(m_ClientSocket->read(m_ExpectedDataSize - m_CurrentData.size()));

        if (m_CurrentData.size() >= m_ExpectedDataSize)
        {
            // Parse message as JSON value
            Json::Value root;
            Json::Reader reader;
            bool parsed = reader.parse(m_CurrentData.constData(), m_CurrentData.constData() + m_CurrentData.size(), root, false);
            if (parsed)
            {
                emit messageReceived(root);
            }
            else
            {
                qWarning() << "Failed to parse incomming data as a valid JSON value. Ignoring message.";
            }

            // Reset for next message
            m_CurrentData.clear();
            m_ExpectedDataSize = 0;
        }
    }
}

void ClientRunner::sendReply(const JsonReplyMessage& reply)
{
    // Create message
    QByteArray replyMsg(reply.toJson().toStyledString().c_str());
    QString replySize = QString::number(replyMsg.size()) + "\n";

    // Send header
    m_ClientSocket->write(replySize.toLocal8Bit());

    // Send reply
    m_ClientSocket->write(replyMsg);

    qDebug() << "Sent reply message.";
}
