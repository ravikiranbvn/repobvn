#include "publisher.h"

CB_Publisher::CB_Publisher(QPushButton *s, QLineEdit *t, QPushButton *btn_1,
                           QPushButton *btn_2, QPushButton *btn_3, QPushButton *btn_4, QTextEdit *d,
                           QTextEdit *d2, QTextEdit *d3, QTextEdit *d4)
{
    msend = s;
    mtype = t;
    mbtn1 = btn_1;
    mbtn2 = btn_2;
    mbtn3 = btn_3;
    mbtn4 = btn_4;
    mdisp = d;
    mdisp2 = d2;
    mdisp3 = d3;
    mdisp4 = d4;

    /* Create a DomainParticipantFactory and a DomainParticipant (using Default QoS settings). */
    dpf = DomainParticipantFactory::get_instance ();
    checkHandle(dpf.in(), "DDS::DomainParticipantFactory::get_instance");
    participant = dpf->create_participant(domain, PARTICIPANT_QOS_DEFAULT, NULL, STATUS_MASK_NONE);
    checkHandle(participant.in(), "DDS::DomainParticipantFactory_Sender::create_participant");

    /* Register the required datatype for message. */
    messageTS = new messageTypeSupport();
    checkHandle(messageTS.in(), "new messageTypeSupport");
    messageTypeName = messageTS->get_type_name();
    status = messageTS->register_type(participant.in(), messageTypeName);
    checkStatus(status, "chatbox::messageTypeSupport::register_type");

    /* Set the HistoryQosPolicy to History, with a depth of 20 to keep track */
    status = participant->get_default_topic_qos(history_topic_qos);
    checkStatus(status, "DDS::DomainParticipant::get_default_topic_qos");
    history_topic_qos.history.kind = DDS::KEEP_LAST_HISTORY_QOS;
    // history_topic_qos.resource_limits = DDS::VOLATILE_DURABILITY_QOS;
    history_topic_qos.history.depth = 20;

    /* Make the tailored QoS the new default. */
    status = participant->set_default_topic_qos(history_topic_qos);
    checkStatus(status, "DDS::DomainParticipant::set_default_topic_qos");

    /* Use the changed QoS policy when defining the message topic */
    messageTopic = participant->create_topic("chatbox_message", messageTypeName, history_topic_qos, NULL, STATUS_MASK_NONE);
    checkHandle(messageTopic.in(), "DDS::DomainParticipant::create_topic (message)");

    /* Adapt the default PublisherQos to write into the "ChatRoom" Partition. */
    status = participant->get_default_publisher_qos (pub_qos);
    checkStatus(status, "DDS::DomainParticipant::get_default_publisher_qos");
    pub_qos.partition.name.length(1);
    pub_qos.partition.name[0] = partitionName;

    /* Create a Publisher for the chatbox application. */
    chatboxPublisher = participant->create_publisher(pub_qos, NULL, STATUS_MASK_NONE);
    checkHandle(chatboxPublisher.in(), "DDS::DomainParticipant::create_publisher");

    /* Create a DataWriter for the messageTopic (using the appropriate QoS). */
    parentWriter = chatboxPublisher->create_datawriter(messageTopic.in(), DATAWRITER_QOS_USE_TOPIC_QOS, NULL,
                                                       STATUS_MASK_NONE);
    checkHandle(parentWriter.in(), "DDS::Publisher::create_datawriter (message)");

    // Publish Events
    DataWriter_var parentWriter = getWriter();
    talker = messageDataWriter::_narrow(parentWriter.in());
    msg = new message();

    connect(msend, SIGNAL(clicked(bool)), this, SLOT(publishmsg()));

    connect(mbtn1, SIGNAL(clicked(bool)), this, SLOT(display1()));
    connect(mbtn2, SIGNAL(clicked(bool)), this, SLOT(display2()));
    connect(mbtn3, SIGNAL(clicked(bool)), this, SLOT(display3()));
    connect(mbtn4, SIGNAL(clicked(bool)), this, SLOT(display4()));

}

CB_Publisher::~CB_Publisher()
{
    /* Release the data-samples. */
    delete msg; // msg allocated on heap: explicit de-allocation required!!

    /* Remove the DataWriters */
    status = chatboxPublisher->delete_datawriter( talker.in() );
    checkStatus(status, "DDS::Publisher::delete_datawriter (parentwriter)");

    /* Remove the Publisher. */
    status = participant->delete_publisher( chatboxPublisher.in() );
    checkStatus(status, "DDS::DomainParticipant::delete_publisher");

    /* Remove the Topics. */
    status = participant->delete_topic( messageTopic.in() );
    checkStatus(status, "DDS::DomainParticipant::delete_topic (messageTopic)");

    /* Remove the type-names. */
    CORBA::string_free(messageTypeName);

    /* Remove the DomainParticipant. */
    status = dpf->delete_participant( participant.in() );
    checkStatus(status, "DDS::DomainParticipantFactory::delete_participant");
}

DataWriter_ptr CB_Publisher::getWriter()
{
    return DataWriter::_duplicate(parentWriter.in());
}

void CB_Publisher::publishmsg()
{
    static unsigned long count[4] = {0};

    msg->msg = mtype->text().toUtf8().constData();
    msg->uid = password;


    if(disp == 1)
    {
        msg->uname = "Akhil";
        msg->msgid = ++count[0];
        mdisp->setTextColor(Qt::green);
        mdisp->append(mtype->text() + "    " + QTime::currentTime().toString());

    }
    if(disp == 2)
    {
        msg->uname = "Chaitu";
        msg->msgid = ++count[1];
        mdisp2->setTextColor(Qt::green);
        mdisp2->append(mtype->text() + "    " + QTime::currentTime().toString());
    }
    if(disp == 3)
    {
        msg->uname = "Alekya";
        msg->msgid = ++count[2];
        mdisp3->setTextColor(Qt::green);
        mdisp3->append(mtype->text() + "    " + QTime::currentTime().toString());
    }
    if(disp == 4)
    {
        msg->uname = "Ravi";
        msg->msgid = ++count[3];
        mdisp4->setTextColor(Qt::green);
        mdisp4->append(mtype->text() + "    " + QTime::currentTime().toString());
    }

    mtype->setText("");

    checkHandle(msg, "new chatbox::message");

    /* Register a message for this user (pre-allocating resources for it!!) */
    userHandle = talker->register_instance(*msg);

    /* Write a message using the pre-generated instance handle. */
    status = talker->write(*msg, userHandle);
    checkStatus(status, "messageDataWriter::write");

}


void CB_Publisher::display1()
{
    mdisp2->hide();
    mdisp3->hide();
    mdisp4->hide();
    mdisp->show();

    disp = 1;

}

void CB_Publisher::display2()
{
    mdisp2->show();
    mdisp3->hide();
    mdisp4->hide();
    mdisp->hide();

    disp = 2;
}

void CB_Publisher::display3()
{
    mdisp2->hide();
    mdisp3->show();
    mdisp4->hide();
    mdisp->hide();

    disp = 3;
}

void CB_Publisher::display4()
{
    mdisp2->hide();
    mdisp3->hide();
    mdisp4->show();
    mdisp->hide();

    disp = 4;
}
