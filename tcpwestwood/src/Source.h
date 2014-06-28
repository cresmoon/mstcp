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

#ifndef __MSTCP2_SOURCE_H
#define __MSTCP2_SOURCE_H

#include <omnetpp.h>
#include <tcpMsg_m.h>

namespace mstcp2 {

/**
 * Generates messages; see NED file for more info.
 */
class Source : public cSimpleModule
{
  private:
        cMessage    *   timerMessage;
        cMessage    *   nextMsg;
        cMessage    *   msgCwnd;
        cMessage    *   msgStat;

        simtime_t       minRTT;
        simtime_t       RTT;
        simtime_t       avgRTT;
        simtime_t       upRTT;
        simtime_t       upStat;


        simsignal_t     cWinSignal;
        simsignal_t     sendSignal;

        float           alpha;
        int             data;
        double          b;
        double          B;                      // bang thong
        int             seqNum;                 //so luong goi gui di
        double             cWin;                   //do rong cua window vi du = 5 goi
        int             updateSend;

        int         ackRcv[10000];               // mang kiem tra ack cua goi.
                                            // + khoi tao cac element bang -1
                                            // + gui goi nao thi gan seqNum vao element dau tien trong mang phan tu
                                            // + khi nhan ack cua seq thi gan element co gia tri seqNum do bang -1
                                            // + gui goi tiep theo thi tim 1 phan tu con bang -1 thi dc gui.

  public:
        Source();
        virtual ~Source();

  protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual int haveElement(int i,int j);
//        virtual bool emptyElement();
        virtual void sendMessage(int j);

};

}; // namespace

#endif
