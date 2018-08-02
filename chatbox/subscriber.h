#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

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
#include <QTimer>

using namespace std;
using namespace DDS;
using namespace chatbox;

extern unsigned long msgid[4];
extern string messg[4];

class CB_Listener : public DataReaderListener
{

public:
    messageSeq                          L_msgList;
    GuardCondition_var                  escape;
    bool                                closed ;
    messageDataReader_var               chatboxAdmin;

    CB_Listener()
    {
        escape = new GuardCondition();
        closed = false;
    }

    /* Callback method implementation. */
    void on_data_available(DDS::DataReader_ptr parentReader)
      THROW_ORB_EXCEPTIONS;

    void on_requested_deadline_missed(DDS::DataReader_ptr reader,
      const DDS::RequestedDeadlineMissedStatus &status)THROW_ORB_EXCEPTIONS;

    void on_requested_incompatible_qos(DDS::DataReader_ptr reader,
      const DDS::RequestedIncompatibleQosStatus &status)THROW_ORB_EXCEPTIONS;

    void on_sample_rejected(DDS::DataReader_ptr reader, const DDS
      ::SampleRejectedStatus &status)THROW_ORB_EXCEPTIONS;

    void on_liveliness_changed(DDS::DataReader_ptr reader, const DDS
      ::LivelinessChangedStatus &status)THROW_ORB_EXCEPTIONS;

    void on_subscription_matched(DDS::DataReader_ptr reader, const
      DDS::SubscriptionMatchedStatus &status)THROW_ORB_EXCEPTIONS;

    void on_sample_lost(DDS::DataReader_ptr reader, const DDS
      ::SampleLostStatus &status)THROW_ORB_EXCEPTIONS;
};


class CB_Subscriber : public QObject
{
    Q_OBJECT

public:
    CB_Subscriber(QTextEdit *d,QTextEdit *d2, QTextEdit *d3, QTextEdit *d4);
    virtual ~CB_Subscriber();
    Duration_t timeout = { 0, 200000000 };
    int count = 0;

private:
    QTextEdit                           *mdisp;
    QTextEdit                           *mdisp2;
    QTextEdit                           *mdisp3;
    QTextEdit                           *mdisp4;
    QTimer                               timer;

    /* Generic DDS entities */
    DomainParticipantFactory_var        dpf;
    DomainParticipant_var               participant;
    Topic_var                           messageTopic;
    Subscriber_var                      chatboxSubscriber;
    DataReader_var                      parentReader;

    /* Type-specific DDS entities */
    messageTypeSupport_var              messageTS;
    messageSeq_var                      msgSeq;

    /* QosPolicy holders */
    TopicQos                            history_topic_qos;
    SubscriberQos                       sub_qos;

    /* DDS Identifiers */
    DomainId_t                          domain = DOMAIN_ID_DEFAULT;
    InstanceHandle_t                    userHandle;
    ReturnCode_t                        status;

    /* Sample definitions */
    message                             *msg;

    /* Others */
    const char                          *partitionName = "ChatRoom";
    char                                *messageTypeName = NULL;
    char                                buf[256];

public slots:
    DataReader_ptr getReader();
    void update();
};

#endif // SUBSCRIBER_H
