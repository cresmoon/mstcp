//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


#include<Fifo.h>
#include <omnetpp.h>

namespace mstcp2 {

Define_Module(Fifo);

simtime_t Fifo::startService(cMessage *msg)
{
//    EV << "Starting service of " << msg->getName() << endl;

    return par("serviceTime");
}

void Fifo::endService(cMessage *msg)
{
    simtime_t delayT = 1;
//    EV << "Completed service of " << msg->getName() << endl;
    sendDelayed(msg, delayT ,"out", -1);
}

}; //namespace

