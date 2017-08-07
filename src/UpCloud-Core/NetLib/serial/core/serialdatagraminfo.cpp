#include "serialdatagraminfo.h"

SerialDataGramInfo::SerialDataGramInfo()
{
    clear();
}

void SerialDataGramInfo::clear()
{
    begin = 0;
    msgType = 0;
    timestamp = 0;
    dataLength = 0;
    message.clear();
    end = 0;
}

