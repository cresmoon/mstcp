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
    timerMessage = NULL;
}

Source::~Source()
{
    cancelAndDelete(timerMessage);
}

void Source::initialize()
{
    cWinSignal = registerSignal("cwnd");
    emit(cWinSignal, cWin);
    EV<< "window cua S"<< getId() -1 <<" la : "<< cWin << endl;

    //khoi tao RTT min
    minRTT  =   65535;
    avgRTT  =   0.1;

    seqNum      =   0;
    cWin        =   1;
    cWinMax     = 20000;

    for(int i = 0; i< cWin; i++ )
    //khoi tao cac phan tu mang ackRcv
    {
        ackRcv[i]   =   -1;
    }

    timerMessage = new cMessage("timer");
//    int t = getId();
    int t = uniform(1,4);
    scheduleAt(simTime() +t, timerMessage);
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
            int t = rcMsg->getSeq();
            // neu co phan tu do thi gui lai nen k gan -1
            int x = haveElement(t,0);

           if( x == 1 )
           {
//               EV<<"Msg nhan dc la :"<< temp <<endl;
               if(cWin>1)
               cWin = cWin/2;
               EV<< "window cua S"<< getId() -1 <<" la : "<< cWin << endl;
               emit(cWinSignal, cWin);
               sendMessage(t);
           }
//           drop(msg);
           cancelAndDelete(msg);
        }
        else
        {
            //EV<<"Msg nhan dc la :"<< temp <<endl;
            for(int i = 0; i<cWin; i++)
                if(ackRcv[i] == -1)                     //neu window con trong thi gui goi
                {
                        ackRcv[i]   =   seqNum;         // dua so seq cua goi vao mang theo doi ack
                        sendMessage(seqNum);
                        seqNum++;                       //Tang so seq number len 1
                }
            if(strcmp(temp,"Next")==0)
                cancelAndDelete(msg);
            else
                drop(msg);
        }
    }
    //if la ACK msg
    else //if (strcmp(temp,"ACKs")==0)
    {
            tcpMsg * rcMsg = check_and_cast<tcpMsg *>(msg);
            const char * name = getFullName();

            int t   =   rcMsg->getSeq();
            EV<<"Nhan dc ACK cua Msg thu' "<< t <<endl;

            int k   =   haveElement(t, 1);

            if(k==1)
            {
                simtime_t delayT = simTime() - msg->getTimestamp();
                EV<< "Thoi gian RTT cua source "<< name <<" la: "<< delayT <<endl;

//                //cap nhat min RTT
//                if (minRTT > delayT)    minRTT = delayT;
                //cap nhat average RTT
                avgRTT =    ((seqNum -1)/seqNum * avgRTT) + (1/seqNum)*delayT;

                cWin = cWin + 1;
                ackRcv[cWin] = -1;

                emit(cWinSignal, cWin);
                EV<< "window cua S"<< getId() -1 <<" la : "<< cWin << endl;

                simtime_t   nextT   =   (1+avgRTT)/cWin;
                EV<<"Time nextT :"<<nextT<<endl;
                cMessage * nextMsg = new cMessage("Next");
                scheduleAt(simTime() + nextT , nextMsg );
            }
            cancelAndDelete(msg);
    }
}

int Source::haveElement(int x, int y)
{
        for(int i = 0; i < cWin; i++)
        {
            if(ackRcv[i] == x)
            {   //set lai ack neu cho y = 1
                if(y==1)
                    ackRcv[i]   =   -1;
                return 1;
            }
        }
        return 0;
}

void Source::sendMessage(int seqNumber)
{
        tcpMsg * job = new tcpMsg("Data");

            job->setAck(0);
            job->setSeq(seqNumber);
            job->setTimestamp(simTime());

        send(job,"out");

        tcpMsg * ackTimeout = new tcpMsg("timeout");
        simtime_t   timeOut   = (avgRTT+6)/cWin ;
        EV<<"Thoi gian timeout cua goi "<<seqNumber<<" la: "<< timeOut<<endl;
            ackTimeout->setSeq(seqNumber);
            scheduleAt(simTime() + timeOut, ackTimeout );
}

}; // namespace
