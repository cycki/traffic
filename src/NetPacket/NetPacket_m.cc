//
// Generated file, do not edit! Created by opp_msgc 4.4 from NetPacket/NetPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "NetPacket_m.h"

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




Register_Class(NetPacket);

NetPacket::NetPacket(const char *name, int kind) : ::cPacket(name,kind)
{
    this->src_var = -1;
    this->dst_var = -1;
    this->sessionId_var = -1;
    this->packetId_var = -1;
    this->priority_var = 0;
    this->startTime_var = 0;
    this->endTime_var = 0;
}

NetPacket::NetPacket(const NetPacket& other) : ::cPacket(other)
{
    copy(other);
}

NetPacket::~NetPacket()
{
}

NetPacket& NetPacket::operator=(const NetPacket& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void NetPacket::copy(const NetPacket& other)
{
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
    this->sessionId_var = other.sessionId_var;
    this->packetId_var = other.packetId_var;
    this->priority_var = other.priority_var;
    this->startTime_var = other.startTime_var;
    this->endTime_var = other.endTime_var;
}

void NetPacket::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
    doPacking(b,this->sessionId_var);
    doPacking(b,this->packetId_var);
    doPacking(b,this->priority_var);
    doPacking(b,this->startTime_var);
    doPacking(b,this->endTime_var);
}

void NetPacket::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
    doUnpacking(b,this->sessionId_var);
    doUnpacking(b,this->packetId_var);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->startTime_var);
    doUnpacking(b,this->endTime_var);
}

int NetPacket::getSrc() const
{
    return src_var;
}

void NetPacket::setSrc(int src)
{
    this->src_var = src;
}

int NetPacket::getDst() const
{
    return dst_var;
}

void NetPacket::setDst(int dst)
{
    this->dst_var = dst;
}

int NetPacket::getSessionId() const
{
    return sessionId_var;
}

void NetPacket::setSessionId(int sessionId)
{
    this->sessionId_var = sessionId;
}

int NetPacket::getPacketId() const
{
    return packetId_var;
}

void NetPacket::setPacketId(int packetId)
{
    this->packetId_var = packetId;
}

int NetPacket::getPriority() const
{
    return priority_var;
}

void NetPacket::setPriority(int priority)
{
    this->priority_var = priority;
}

double NetPacket::getStartTime() const
{
    return startTime_var;
}

void NetPacket::setStartTime(double startTime)
{
    this->startTime_var = startTime;
}

double NetPacket::getEndTime() const
{
    return endTime_var;
}

void NetPacket::setEndTime(double endTime)
{
    this->endTime_var = endTime;
}

class NetPacketDescriptor : public cClassDescriptor
{
  public:
    NetPacketDescriptor();
    virtual ~NetPacketDescriptor();

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

Register_ClassDescriptor(NetPacketDescriptor);

NetPacketDescriptor::NetPacketDescriptor() : cClassDescriptor("NetPacket", "cPacket")
{
}

NetPacketDescriptor::~NetPacketDescriptor()
{
}

bool NetPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NetPacket *>(obj)!=NULL;
}

const char *NetPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NetPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int NetPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *NetPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "src",
        "dst",
        "sessionId",
        "packetId",
        "priority",
        "startTime",
        "endTime",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int NetPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sessionId")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetId")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "startTime")==0) return base+5;
    if (fieldName[0]=='e' && strcmp(fieldName, "endTime")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NetPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "double",
        "double",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *NetPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NetPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NetPacket *pp = (NetPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NetPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NetPacket *pp = (NetPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrc());
        case 1: return long2string(pp->getDst());
        case 2: return long2string(pp->getSessionId());
        case 3: return long2string(pp->getPacketId());
        case 4: return long2string(pp->getPriority());
        case 5: return double2string(pp->getStartTime());
        case 6: return double2string(pp->getEndTime());
        default: return "";
    }
}

bool NetPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NetPacket *pp = (NetPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrc(string2long(value)); return true;
        case 1: pp->setDst(string2long(value)); return true;
        case 2: pp->setSessionId(string2long(value)); return true;
        case 3: pp->setPacketId(string2long(value)); return true;
        case 4: pp->setPriority(string2long(value)); return true;
        case 5: pp->setStartTime(string2double(value)); return true;
        case 6: pp->setEndTime(string2double(value)); return true;
        default: return false;
    }
}

const char *NetPacketDescriptor::getFieldStructName(void *object, int field) const
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
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<7) ? fieldStructNames[field] : NULL;
}

void *NetPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NetPacket *pp = (NetPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


