#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "ccpp_dds_dcps.h"
#include "CheckStatus.h"
#include "ccpp_chatbox.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QDebug>
#include <QtGui>

using namespace std;
using namespace DDS;
using namespace chatbox;

class CB_Publisher : public QObject
{
    Q_OBJECT

public:
    CB_Publisher(QPushButton *s, QLineEdit *t, QPushButton *btn_1,
                 QPushButton *btn_2, QPushButton *btn_3, QPushButton *btn_4,
                 QTextEdit *d,QTextEdit *d2, QTextEdit *d3, QTextEdit *d4);
    ~CB_Publisher();

private:
    QPushButton                         *msend;
    QLineEdit                           *mtype;
    QPushButton                         *mbtn1;
    QPushButton                         *mbtn2;
    QPushButton                         *mbtn3;
    QPushButton                         *mbtn4;
    QTextEdit                           *mdisp;
    QTextEdit                           *mdisp2;
    QTextEdit                           *mdisp3;
    QTextEdit                           *mdisp4;


    /* Generic DDS entities */
    DomainParticipantFactory_var        dpf;
    DomainParticipant_var               participant;
    Topic_var                           messageTopic;
    Publisher_var                       chatboxPublisher;
    DataWriter_var                      parentWriter;

    /* QosPolicy holders */
    TopicQos                            history_topic_qos;
    PublisherQos                        pub_qos;

    /* DDS Identifiers */
    DomainId_t                          domain = DOMAIN_ID_DEFAULT;
    InstanceHandle_t                    userHandle;
    ReturnCode_t                        status;

    /* Type-specific DDS entities */
    messageTypeSupport_var              messageTS;
    messageSeq_var                      msgSeq;
    messageDataWriter_var               talker;

    /* Sample definitions */
    message                             *msg;

    /* Others */
    const char                          *partitionName = "ChatRoom";
    char                                *messageTypeName;
    char                                buf[256];

public slots:
    DataWriter_ptr getWriter();
    void publishmsg();
    void display1();
    void display2();
    void display3();
    void display4();
};

#endif // PUBLISHER_H
