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

#include<Sink.h>
#include<tcpMsg_m.h>
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

namespace mstcp2 {

Define_Module(Sink);

void Sink::initialize()
{
    lastArrival = simTime();
    iaTimeHistogram.setName("interarrival times");
    arrivalsVector.setName("arrivals");
    arrivalsVector.setInterpolationMode(cOutVector::NONE);

    msgSignal = registerSignal("arrive");
    ackNum  = 0;
    updateArr   = 0.1;
    updateMsg = new cMessage("update");

    emit(msgSignal, ackNum);
    scheduleAt(simTime() + updateArr, updateMsg);

}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t d = simTime() - lastArrival;
    simtime_t delay = 0.05;
//    EV << "Thoi gian toi gan nhat "<<d<< endl;

    const char * temp ;
    int i = getId();
    int j = msg->getSenderModuleId();
    temp = msg->getName();

    if(strcmp(temp,"Data")==0)    //neu la goi DataS thi reply 1 goi ACKs
    {
//        if (uniform(0,1) < 0)
//           {
//               EV << "\"Losing\" message.\n";
//               bubble("message lost");  // making animation more informative...
//               drop(msg);
//               cancelAndDelete(msg);
//           }
//        else
//        {
//            EV<<"Nhan dc du lieu : "<<temp<<endl;

            ackNum++;
            tcpMsg * rcMsg = check_and_cast<tcpMsg *>(msg);
            tcpMsg * replyMsg = new tcpMsg("ACKs");

            replyMsg->setSrc(i);
            replyMsg->setDest(j);
            replyMsg->setAck(ackNum);
            replyMsg->setSeq(rcMsg->getSeq());
            replyMsg->setTimestamp(msg->getTimestamp());    //copy lai timestamp luc gui goi di

            sendDelayed(replyMsg, delay ,"out", -1);

            drop(msg);
            cancelAndDelete(msg);
//        }

    }
    else
    {
        emit(msgSignal, ackNum);
        scheduleAt(simTime() + updateArr, updateMsg);
    }



    iaTimeHistogram.collect(d);
    arrivalsVector.record(1);
    lastArrival = simTime();
}

void Sink::finish()
{
    recordStatistic(&iaTimeHistogram);
}

}; // namespace
