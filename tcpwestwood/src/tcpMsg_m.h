//
// Generated file, do not edit! Created by opp_msgc 4.4 from tcpMsg.msg.
//

#ifndef _MSTCP2_TCPMSG_M_H_
#define _MSTCP2_TCPMSG_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif


namespace mstcp2 {

/**
 * Class generated from <tt>tcpMsg.msg</tt> by opp_msgc.
 * <pre>
 * message tcpMsg {
 *         
 *     int src;
 *     int dest;
 *     
 *     int Ack;
 *     int Seq;
 *     
 * }
 * </pre>
 */
class tcpMsg : public ::cMessage
{
  protected:
    int src_var;
    int dest_var;
    int Ack_var;
    int Seq_var;

  private:
    void copy(const tcpMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const tcpMsg&);

  public:
    tcpMsg(const char *name=NULL, int kind=0);
    tcpMsg(const tcpMsg& other);
    virtual ~tcpMsg();
    tcpMsg& operator=(const tcpMsg& other);
    virtual tcpMsg *dup() const {return new tcpMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getSrc() const;
    virtual void setSrc(int src);
    virtual int getDest() const;
    virtual void setDest(int dest);
    virtual int getAck() const;
    virtual void setAck(int Ack);
    virtual int getSeq() const;
    virtual void setSeq(int Seq);
};

inline void doPacking(cCommBuffer *b, tcpMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, tcpMsg& obj) {obj.parsimUnpack(b);}

}; // end namespace mstcp2

#endif // _MSTCP2_TCPMSG_M_H_
