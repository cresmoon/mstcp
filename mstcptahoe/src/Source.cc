//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Source.h"
#include "omnetpp.h"


namespace mstcp2 {

Define_Module(Source);

Source::Source()
{
    timerMessage = nextMsg = msgCwnd = msgStat =  NULL;
}

Source::~Source()
{
    cancelAndDelete(timerMessage);
    cancelAndDelete(nextMsg);
    cancelAndDelete(msgCwnd);
    cancelAndDelete(msgStat);
}

void Source::initialize()
{
    //khoi tao RTT min
    upStat      =   0.1;
    updateSend  =   0;

    seqNum      =   1;
    cWin        =   1;
//    preCWND     =   cWin/1;

    EV<< "window cua S"<< getId() - 1 <<" la : "<< cWin << endl;
    cWinSignal = registerSignal("cwnd");
    sendSignal = registerSignal("seqnum");

    emit(cWinSignal, cWin);
    emit(sendSignal, updateSend);

    for(int i = 0; i < cWin; i++ )
    //khoi tao cac phan tu mang ackRcv
    {
        ackRcv[i]   =   -1;
    }

    timerMessage = new cMessage("timer");
    nextMsg =   new cMessage("Next");
    msgCwnd = new cMessage("upcwnd");
    msgStat = new cMessage("upstat");
//    int t = getId();
//    int t = intuniform(0,4);
//    t=t-1;
    scheduleAt(simTime() , timerMessage);

    scheduleAt(simTime() + upStat, msgStat);
}

void Source::handleMessage(cMessage *msg)
{
    const char * temp = msg->getName();

    if(msg->isSelfMessage() )
    //neu la source module thi tao msg moi gui di
    {
        if (strcmp(temp,"timeout")==0 )
        //neu la 1 msg timeout cua 1 ack nao do," va chua nhan dc ack"
        {
            tcpMsg * rcMsg = check_and_cast<tcpMsg *>(msg);
            int soSeq = rcMsg->getSeq();
            int coX = haveElement(soSeq,0);

           if( coX == 1 )
           {
               if(cWin>1)
               cWin = cWin/2;
               else
                   cWin = 1;
               seqNum = soSeq;
               EV<<"One Msg Timeout"<<endl;
               sendMessage(soSeq);
           }
           else
               EV<<"Clear timeout"<<endl;
           drop(msg);
           cancelAndDelete(msg);
        }
        else if(strcmp(temp,"upstat")==0)
        {
            emit(sendSignal, updateSend);
            emit(cWinSignal, cWin);
            scheduleAt(simTime() + upStat, msgStat);
            EV<<"cap nhat cwind: "<<cWin<<endl;
        }
        else    //gap timer msg cap nhat lai window
        {
            for(int i = 0; i < cWin; i++)
            if(ackRcv[i] == -1)                     //neu window con trong thi gui goi
            {
                    ackRcv[i]   =   seqNum;         // dua so seq cua goi vao mang theo doi ack
                    sendMessage(seqNum);
                    seqNum++;                       //Tang so seq number len 1
            }
            EV<<"So SeqNum: "<<seqNum<<" cWin la: "<<cWin<<endl;
        }
    }
    //if la ACK msg
    else
    {
            tcpMsg * rcMsg = check_and_cast<tcpMsg *>(msg);
            const char * name = getFullName();
            int t   =   rcMsg->getSeq();
            EV<<"Nhan dc ACK cua Msg thu' "<< t <<endl;

            int k =  haveElement(t, 1);
            if(k==1)
            {
                simtime_t delayT = simTime() - msg->getTimestamp();
                EV<< "Thoi gian RTT cua source "<< name <<" la: "<< delayT <<endl;
                avgRTT =    ((seqNum -1)/seqNum * avgRTT) + (1/seqNum)*delayT;
                EV<< "Thoi gian avgRTT moi :"<<avgRTT<<endl;

                cWin = cWin + 1;
                ackRcv[cWin -1] = -1;
                EV<<"cWin tang len: "<< cWin<<endl;
                bool b = nextMsg->isScheduled();
                EV<< "self msg: "<< t<<", context :" <<rcMsg->getContextPointer()<<endl;

                if(b == 0 )
                    scheduleAt(simTime() +0.001, nextMsg);
            }
            drop(msg);
            cancelAndDelete(msg);
    }
}

int Source::haveElement(int x, int y)
{
        for(int i = 0; i < cWin; i++)
        {
            if(ackRcv[i] == x)
            {   //set lai ack
                if(y==1) ackRcv[i]   =   -1;
                return 1;
            }
        }
        return 0;
}
/*

bool Source::emptyElement()
{
    for(int i = cWin-1; i < preCWND; i++)
        if(ackRcv[i] !=-1)
            return 0;
    return 1;
}
*/

void Source::sendMessage(int seqNumber)
{
    updateSend ++;
        tcpMsg * job = new tcpMsg("Data");

            job->setAck(0);
            job->setSeq(seqNumber);
            job->setTimestamp(simTime());

        sendDelayed(job, 0.001, "out");

        tcpMsg * ackTimeout = new tcpMsg("timeout");
        simtime_t   timeOut   = (avgRTT+3);
        ackTimeout->setSeq(seqNumber);
        scheduleAt(simTime() + timeOut, ackTimeout );
}

}; // namespace
