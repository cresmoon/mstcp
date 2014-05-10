//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include<string.h>
#include<AbstractFifo.h>

namespace mstcp2 {

void AbstractFifo::initialize()
{
    queue.setName("queue");

    qlenSignal = registerSignal("qlen");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingTime");
    emit(qlenSignal, queue.length());
    emit(busySignal, false);
}

void AbstractFifo::handleMessage(cMessage *msg)
{

//    EV << "Msg dau vao QUEUE la " << msg->getName() <<endl;

    const char * vao = new char[20];
    vao= msg->getName();

    cMessage* msgServiced;
    cMessage*  temp = new cMessage("QL");

    if (strcmp(vao,"endjob")==0)                      //neu la self msg bao ket thuc thoi gian 1 msg trong queue
    {
        if (!queue.empty())
        {
//                EV<<"Queue Not Null"<< endl;
                msgServiced = (cMessage *) queue.pop();     // pop trong queue ra dua vao msgServiced
                endService(msgServiced);        // gui msg co san trong msgServiced ra cong out

                emit(qlenSignal, queue.length());
                emit(queueingTimeSignal, simTime() - msgServiced->getTimestamp()); //lay ra thoi gian msg toi
                delete(msg);

//                const char * name = getFullName();
                temp->setKind(queue.length());          //gan Queue length cho bien Kind trong msg temp
//                EV<<"Thong tin queue: "<< name << ", length : " << temp->getKind() << endl;
                send(temp,"gate$o");          //gui ra cong out 2 cho MW timer , do 2 cong 0, va 1 cua2 module Source
        }
        else    //queue rong
        {
                EV<<"Queue Null\n";
                emit(busySignal, false);        // xuat ra tin hieu k busy
        }
    }
    else        //neu la msgServiced dua tu Source toi
    {
//        EV<< " Nhan duoc goi Data\n";
        msg->setTimestamp();                    //gan cho msg timestamp la thoi diem hien tai
        EV <<"T : " << msg->getTimestamp() << endl;
        queue.insert( msg );

        emit(qlenSignal, queue.length());

//        const char * name = getFullName();
        temp->setKind(queue.length());          //gan Queue length cho bien Kind trong msg temp
//        EV<<"Cap Nhat queue: "<< name << ", length : " << temp->getKind() << endl;

        send(temp,"gate$o");          //gui ra cong out 2 cho MW timer , do 2 cong 0, va 1 cua 2 module Source
    }
}
}; //namespace

