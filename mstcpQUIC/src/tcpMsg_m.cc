//
// Generated file, do not edit! Created by opp_msgc 4.4 from tcpMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "tcpMsg_m.h"

USING_NAMESPACE

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}



namespace mstcp2 {

Register_Class(tcpMsg);

tcpMsg::tcpMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->src_var = 0;
    this->dest_var = 0;
    this->Ack_var = 0;
    this->Seq_var = 0;
}

tcpMsg::tcpMsg(const tcpMsg& other) : ::cMessage(other)
{
    copy(other);
}

tcpMsg::~tcpMsg()
{
}

tcpMsg& tcpMsg::operator=(const tcpMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void tcpMsg::copy(const tcpMsg& other)
{
    this->src_var = other.src_var;
    this->dest_var = other.dest_var;
    this->Ack_var = other.Ack_var;
    this->Seq_var = other.Seq_var;
}

void tcpMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->dest_var);
    doPacking(b,this->Ack_var);
    doPacking(b,this->Seq_var);
}

void tcpMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dest_var);
    doUnpacking(b,this->Ack_var);
    doUnpacking(b,this->Seq_var);
}

int tcpMsg::getSrc() const
{
    return src_var;
}

void tcpMsg::setSrc(int src)
{
    this->src_var = src;
}

int tcpMsg::getDest() const
{
    return dest_var;
}

void tcpMsg::setDest(int dest)
{
    this->dest_var = dest;
}

int tcpMsg::getAck() const
{
    return Ack_var;
}

void tcpMsg::setAck(int Ack)
{
    this->Ack_var = Ack;
}

int tcpMsg::getSeq() const
{
    return Seq_var;
}

void tcpMsg::setSeq(int Seq)
{
    this->Seq_var = Seq;
}

class tcpMsgDescriptor : public cClassDescriptor
{
  public:
    tcpMsgDescriptor();
    virtual ~tcpMsgDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(tcpMsgDescriptor);

tcpMsgDescriptor::tcpMsgDescriptor() : cClassDescriptor("mstcp2::tcpMsg", "cMessage")
{
}

tcpMsgDescriptor::~tcpMsgDescriptor()
{
}

bool tcpMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<tcpMsg *>(obj)!=NULL;
}

const char *tcpMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int tcpMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int tcpMsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *tcpMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "src",
        "dest",
        "Ack",
        "Seq",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int tcpMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest")==0) return base+1;
    if (fieldName[0]=='A' && strcmp(fieldName, "Ack")==0) return base+2;
    if (fieldName[0]=='S' && strcmp(fieldName, "Seq")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *tcpMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *tcpMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int tcpMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    tcpMsg *pp = (tcpMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string tcpMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    tcpMsg *pp = (tcpMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrc());
        case 1: return long2string(pp->getDest());
        case 2: return long2string(pp->getAck());
        case 3: return long2string(pp->getSeq());
        default: return "";
    }
}

bool tcpMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    tcpMsg *pp = (tcpMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrc(string2long(value)); return true;
        case 1: pp->setDest(string2long(value)); return true;
        case 2: pp->setAck(string2long(value)); return true;
        case 3: pp->setSeq(string2long(value)); return true;
        default: return false;
    }
}

const char *tcpMsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *tcpMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    tcpMsg *pp = (tcpMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

}; // end namespace mstcp2

