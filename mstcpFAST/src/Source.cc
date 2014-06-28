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
    minRTT      =   1;
    RTT         =   minRTT;

    avgRTT      =   1;
    alpha       =   10;
    gama        =   0.9;

    //thoi gian update RTT cua FAST
    upRTT       =   0.6;
    upStat      =   0.1;
    updateSend  =   0;

    seqNum      =   1;
    cWin        =   1;
    preCWND     =   cWin/1;

    EV<< "window cua S"<< getId() - 1 <<" la : "<< cWin << endl;
    cWinSignal = registerSignal("cwnd");
    sendSignal = registerSignal("seqnum");

    emit(cWinSignal, cWin);
    emit(sendSignal, updateSend);

    for(int i = 0; i < preCWND; i++ )
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
    scheduleAt(simTime() + upRTT, msgCwnd);
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
               EV<<"One Msg Timeout"<<endl;
               sendMessage(soSeq);
           }
           else
               EV<<"Clear timeout"<<endl;
           drop(msg);
           cancelAndDelete(msg);
        }
        else if (strcmp(temp,"upcwnd")==0)
        {
            double x= SIMTIME_DBL(minRTT)/SIMTIME_DBL(RTT);
            cWin = (gama*x + alpha) + (1-gama)*cWin ;

            emit(cWinSignal, cWin);

            if(cWin < 1) cWin = 1;

            if(cWin >= preCWND+1)
            {
                int t = (cWin-preCWND)/1;
                for(int i = preCWND; i < preCWND +t; i++)
                  ackRcv[i]= -1;
            }
            EV<< "MinRTT la : " <<minRTT<< ", RTT hien tai la :"<<RTT<<", CWND moi la: " << cWin<<endl;
            bool b = msgCwnd->isScheduled();

            if(b == 0 )
            scheduleAt(simTime() + upRTT, msgCwnd);
        }
        else if(strcmp(temp,"upstat")==0)
        {
            emit(sendSignal, updateSend);
            scheduleAt(simTime() + upStat, msgStat);
        }

        else    //gap timer msg cap nhat lai window
        {
            bool empty = emptyElement();
            if(empty == 1)  // k con phan tu nao chua nhan ack tu cWin toi preCWND
                preCWND = cWin/1;

            int w;

            if (preCWND > cWin)
                w   =   cWin/1;
            else
                w   =   preCWND;

            for(int i = 0; i < w; i++)
            if(ackRcv[i] == -1)                     //neu window con trong thi gui goi
            {
                    ackRcv[i]   =   seqNum;         // dua so seq cua goi vao mang theo doi ack
                    sendMessage(seqNum);
                    seqNum++;                       //Tang so seq number len 1

            }

            for(int j=0; j<preCWND; j++)
                EV<<" AckRcv["<<j<<"] : "<< ackRcv[j];
            EV<<endl;
        }
    }
    //if la ACK msg
    else
    {
            tcpMsg * rcMsg = check_and_cast<tcpMsg *>(msg);
            const char * name = getFullName();
            int t   =   rcMsg->getSeq();
            EV<<"Nhan dc ACK cua Msg thu' "<< t <<endl;

             haveElement(t, 1);

//            if(k==1)
//                emit(ackSignal, 1);

            double delayT = SIMTIME_DBL(simTime() - rcMsg->getTimestamp());
            EV<< "Thoi gian RTT cua source "<< name <<" la: "<< delayT <<endl;
            EV<< "avgRTT (cur): " << avgRTT << endl;

            //cap nhat min RTT//cap nhat average RTT
            if(t<2)
            {
                minRTT = delayT;
                avgRTT = delayT;
            }
            else
            {
                if (minRTT > delayT)    minRTT = delayT;
//                double real1 = (double) 255/256;
//                double real2 = (double) 1/256;
//                avgRTT = real1 * avgRTT + real2 * delayT;
            }

            EV<<"avgRTT :"<<avgRTT<<endl;
            RTT = delayT;

            EV<< "window cua S"<< getId() -1 <<" la : "<< cWin << endl;

            bool b = nextMsg->isScheduled();
            EV<< "self msg: "<< t<<", context :" <<rcMsg->getContextPointer()<<endl;

            if(b == 0 )
            scheduleAt(simTime() +0.01, nextMsg);

            drop(msg);
            cancelAndDelete(msg);
    }
}

int Source::haveElement(int x, int y)
{
        for(int i = 0; i < preCWND; i++)
        {
            if(ackRcv[i] == x)
            {   //set lai ack
                if(y==1) ackRcv[i]   =   -1;
                return 1;
            }
        }
        return 0;
}

bool Source::emptyElement()
{
    for(int i = cWin-1; i < preCWND; i++)
        if(ackRcv[i] !=-1)
            return 0;
    return 1;
}

void Source::sendMessage(int seqNumber)
{
    updateSend ++;
        tcpMsg * job = new tcpMsg("Data");

            job->setAck(0);
            job->setSeq(seqNumber);
            job->setTimestamp(simTime());

        sendDelayed(job, 0.01, "out");


        tcpMsg * ackTimeout = new tcpMsg("timeout");
        simtime_t   timeOut   = (avgRTT+3);
        ackTimeout->setSeq(seqNumber);
        scheduleAt(simTime() + timeOut, ackTimeout );
}

}; // namespace
