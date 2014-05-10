/*
 * RRTime.h
 *
 *  Created on: Feb 7, 2014
 *      Author: Hunt1
 */

#ifndef __MAXWTIMER_H
#define __MAXWTIMER_H

#include <omnetpp.h>
#include <cmodule.h>

namespace mstcp2 {

/**
 * Message sink; see NED file for more info.
 */
class MaxWTimer : public cSimpleModule
{
  private:

    cMessage * Self;
    int qLen[4];

    int g;
    int gateIn ;
    cGate * gateC;


  public:
    MaxWTimer();
    virtual ~MaxWTimer();


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual int maxQueue();
    //virtual void finish();
};

}; // namespace


#endif /* MAXWTIMER_H */
