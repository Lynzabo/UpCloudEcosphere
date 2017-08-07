#include "datagraminfo.h"

DataGramInfo::DataGramInfo()
{
    clear();
}

void DataGramInfo::clear()
{
    begin = 0;begin_ISREAD = false;
    msgType = 0;msgType_ISREAD = false;
    UUID = 0;UUID_ISREAD = false;
    requestID.clear();requestID_ISREAD = false;
    timestamp = 0;timestamp_ISREAD = false;
    dataLength = 0;dataLength_ISREAD = false;
    message.clear();message_ISREAD = false;
    end = 0;end_ISREAD = false;
}
int i = qRegisterMetaType<DataGramInfo>("DataGramInfo");
