// Message Receiver in C++ using POSIX Message Queue
// g++ --std=c++0x -lrt posixMQ_Recvr_CPP.cpp
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <boost/noncopyable.hpp>
extern "C"
{
#include <mqueue.h>
#include <sys/syscall.h>
}

using namespace std;


namespace
{
    const char MQ_NAME[] = "/MQ_Posix";
    const long MQ_MESSAGE_MAX_LENGTH = 64; // In bytes
    const long MQ_MAX_NUM_OF_MESSAGES = 10;
};


class MQ_Recvr : private boost::noncopyable
{
  public:
    MQ_Recvr();
    ~MQ_Recvr();
    void subscribeNotifications();
    void closeMsgQ();

  private:
    static void recvMsgAndSubscribeWrapper(/* union */sigval sv);
    void recvMsgAndSubscribe();
    void processMessage(const char* buffer);

    mqd_t m_mqDesc;
};


MQ_Recvr::MQ_Recvr() : m_mqDesc(-1)
{
    /* Form the queue attributes */
    mq_attr attr;
    attr.mq_flags = 0; /* i.e mq_send will be block if message queue is full */
    attr.mq_maxmsg = MQ_MAX_NUM_OF_MESSAGES;
    attr.mq_msgsize = MQ_MESSAGE_MAX_LENGTH;
    attr.mq_curmsgs = 0; /* mq_curmsgs is dont care */

    /* Create message queue */
    m_mqDesc = ::mq_open(MQ_NAME, O_RDONLY | O_CREAT | O_NONBLOCK,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, &attr);

    if (m_mqDesc == -1)
    {
        printf("Failed to open message queue %d\n", errno);
        throw std::runtime_error("Failed to open message queue");
    }
    else
    {
        printf("Message Queue name : %s; descriptor : %d\n", MQ_NAME, m_mqDesc);
    }
}


MQ_Recvr::~MQ_Recvr()
{
    closeMsgQ();
}


void MQ_Recvr::subscribeNotifications()
{
    // Empty the Message Queue prior to subscribing for notification
    int bytesRecvd = 0;
    while (bytesRecvd != -1)
    {
        char buffer[MQ_MESSAGE_MAX_LENGTH];
        // const timespec ts = {0, 100000000}; // 100 milliseconds
        // bytesRecvd = ::mq_timedreceive(m_mqDesc, buffer, MQ_MESSAGE_MAX_LENGTH, NULL, &ts);
        bytesRecvd = ::mq_receive(m_mqDesc, buffer, MQ_MESSAGE_MAX_LENGTH, NULL);
        if (bytesRecvd != -1)
        {
            printf("Received %d bytes from MQ %d\n", bytesRecvd, m_mqDesc);
        }
    }

    // Subscribe for notifications
    sigevent sev;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = &MQ_Recvr::recvMsgAndSubscribeWrapper;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = (void*)this;
    if ( ::mq_notify(m_mqDesc, &sev) == -1 )
    {
        throw std::runtime_error("Failed to subscribe for notification");
    }

    // To Block
    char c;
    cin >> c;
}


void MQ_Recvr::recvMsgAndSubscribeWrapper(/*union*/ sigval sv)
{
    // This gets executed in a different thread every time it gets called
    ((MQ_Recvr *)sv.sival_ptr)->recvMsgAndSubscribe();
}


void MQ_Recvr::recvMsgAndSubscribe()
{
    printf("Thread Id : %d\n", syscall(SYS_gettid) );
    int bytesRecvd = 0;
    while (bytesRecvd != -1)
    {
        char buffer[MQ_MESSAGE_MAX_LENGTH];
        // const timespec ts = {0, 100000000}; // 100 milliseconds
        // bytesRecvd = ::mq_timedreceive(m_mqDesc, buffer, MQ_MESSAGE_MAX_LENGTH, NULL, &ts);
        bytesRecvd = ::mq_receive(m_mqDesc, buffer, MQ_MESSAGE_MAX_LENGTH, NULL);
        if (bytesRecvd != -1)
        {
            printf("Received %d bytes from MQ %d\n", bytesRecvd, m_mqDesc);
            processMessage(buffer);
        }
    }

    // Subscribe for notifications
    sigevent sev;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = &MQ_Recvr::recvMsgAndSubscribeWrapper;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = (void*)this;
    if ( ::mq_notify(m_mqDesc, &sev) == -1 )
    {
        throw std::runtime_error("Failed to subscribe for notification");
    }
}


void MQ_Recvr::processMessage(const char* buffer)
{
    printf("Message : [%s]\n", buffer);
}


void MQ_Recvr::closeMsgQ()
{
    if ( ::mq_close(m_mqDesc) )
        printf("Message Queue close [desc : %d] failed\n", m_mqDesc);
    else
        printf("Message Queue [desc : %d] closed\n", m_mqDesc);

    if ( ::mq_unlink(MQ_NAME) )
        printf("Message Queue [desc : %d] unlink failed\n", m_mqDesc);
    else
        printf("Message Queue [desc : %d] unlinked\n", m_mqDesc);
}


int main()
{
    printf("Main Thread Id : %u\n",  syscall(SYS_gettid) );
    MQ_Recvr mqRecvr;
    mqRecvr.subscribeNotifications();
    return 0;
}

