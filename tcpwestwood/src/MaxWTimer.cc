#include "MaxWTimer.h"


namespace mstcp2 {

Define_Module(MaxWTimer);


MaxWTimer::MaxWTimer()
{
    Self = NULL;
}

MaxWTimer::~MaxWTimer()
{

    cancelAndDelete(Self);
}

void MaxWTimer::initialize()
{

    g = 0;

    for(int i=0; i<4; i++)
        qLen[i] = 0;

    Self = new cMessage ("MW");
    gateIn = 0;

    EV<<"Khoi tao ~ QL 1: "<< qLen[0] << ", QL 2: "<< qLen[1] <<", QL 3: "<< qLen[2] << ", QL 4: "<< qLen[3] << endl;
    scheduleAt(simTime() + 0.1, Self );
}

void MaxWTimer::handleMessage(cMessage *msg)
{

    if(msg->isSelfMessage())
    {

        if ((qLen[0] != 0) || (qLen[1] != 0) || (qLen[2] != 0) || (qLen[3] != 0))
        {
            EV<<"QL 1: "<< qLen[0] << ", QL 2: "<< qLen[1] <<", QL 3: "<< qLen[2] << ", QL 4: "<< qLen[3] << endl;

            if(qLen[0]==qLen[1] && qLen[1]==qLen[2] && qLen[2]==qLen[3])
            {    g = intuniform(0,3);
                    EV<<"chon queue: "<<g<<endl;
            }
            else
                g = maxQueue();                             //TIM CONG RA CO QUEUE LON NHAT

//            EV<<"Cong ra cua msg : "<< g<< endl;
            cMessage *endmsg = new cMessage("endjob");
            sendDelayed(endmsg, 0.0, "gate$o", g);
        }

        simtime_t timer = par("serviceClock");
        scheduleAt(simTime() + timer, Self);
    }
    else                                              //neu la msg gui QLength toi
    {
        gateC = msg->getArrivalGate();

        int index = gateC->getIndex();
//        EV<< "Index cua gate In: " << index <<endl; //kiem tra gate in
//        EV<< "Message queue length"<<msg->getKind() <<endl;

        if (index == 0)
            {    qLen[0]    = msg->getKind();              // lay thong tin queue length tu Queue
//                 EV << "update ql 1: " <<qLen[0] <<endl;
            }
        else if (index == 1)
            {
                qLen[1]    = msg->getKind();
//                EV << "update ql 2: " << qLen[1] <<endl;
            }
        else if (index == 2)
            {
                qLen[2]    = msg->getKind();
//                EV << "update ql 3: " <<qLen[2] <<endl;
            }
        else if (index == 3)
            {
                qLen[3]    = msg->getKind();
//                EV << "update ql 4: " <<qLen[3] <<endl;
            }

        drop(msg);
        cancelAndDelete(msg);
    }
}

int MaxWTimer::maxQueue()
{
    int maxIndex = intuniform(0,3);

    EV<<"lay queue : "<<maxIndex<<endl;
    for (int i=0; i<4; i++)
        if( qLen[maxIndex] < qLen[i])
            maxIndex = i;

    return maxIndex;
}

}; // namespace
