//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


#ifndef __ABSTRACTFIFO_H
#define __ABSTRACTFIFO_H

#include <omnetpp.h>
#include <tcpMsg_m.h>

namespace mstcp2 {

/**
 * Abstract base class for single-server queues. Subclasses should
 * define startService() and endService(), and may override other
 * virtual functions.
 */
class AbstractFifo : public cSimpleModule
{
  protected:

    int     dropThresh;
    cMessage *msgServiced;
    cQueue queue;
    cMessage *updateQL;


    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;

  public:

    AbstractFifo();
    virtual ~AbstractFifo();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    // hook functions to (re)define behaviour
    virtual void arrival(cMessage *msg) {}
    virtual simtime_t startService(cMessage *msg) = 0;
    virtual void endService(cMessage *msg) = 0;
};

}; //namespace

#endif
