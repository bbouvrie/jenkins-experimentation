#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>

#include "common/qtjson.h"
#include "clientrunner.h"
#include "AIBaseClass.h"

/************************************************\
*                                                *
*  PLEASE UPDATE THE BELOW CODE TO LOAD YOUR AI  *
*                                                *
\************************************************/
#include "GoofBot.h"

AIBaseClass* createAi()
{
    /* Create your AI object here */
    return new GoofBot();
}

/************************************************\
*                                                *
*     NO CHANGES REQUIRED BEYOND THIS POINT      *
*                                                *
\************************************************/

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Register meta types from 'qtjson.h'
    qRegisterMetaType<Json::Value>();

    // Set command line options to get required connection info
    QCommandLineParser parser;
    parser.setApplicationDescription("Bommberman AI");
    parser.addHelpOption();
    parser.addPositionalArgument("portnr", "Port number of the bomberman client or server.");
    parser.addPositionalArgument("token", "Identification token that will be passed back to the server for identificaton.");

    // Parse and validate command line options
    parser.process(app);
    const QStringList args = parser.positionalArguments();
    if (args.size() != 2)
    {
        fprintf(stderr, "You must supply all 2 command line options.\n\n");
        parser.showHelp(1);
    }
    bool ok = false;
    int portNr = args.at(0).toInt(&ok);
    const QString token = args.at(1);
    if (!ok)
    {
        fprintf(stderr, "Given port number is not a valid integer.\n\n");
        parser.showHelp(1);
    }

    // Create ClientRunner to interact with AI object
    ClientRunner* runner = new ClientRunner(portNr, token, createAi(), &app);

    // Hook up ClientRunner 'finished' signal to allow clean exit of program
    QObject::connect(runner, &ClientRunner::finished, &app, &QCoreApplication::quit);

    // Set up a trigger to start ClientRunner once the event loop starts
    QTimer::singleShot(0, runner, SLOT(run())); // Note: New style syntax (&ClientRunner::run) is only supported from Qt 5.4 up

    // Start the event loop
    return app.exec();
}
