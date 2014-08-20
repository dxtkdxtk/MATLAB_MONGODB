/*****************************************************************************
 * File name: mxMongokTool.cpp
 * Description: operate mongodb
 * Author: jebin
 * Version: 0.1
 * Date: 2014/07/30
 * History: see git log
 *****************************************************************************/
#include "mxMongoTool.h"

extern mongo::DBClientConnection *mCon;
extern std::string mongoServer;
extern std::string database;
extern std::string collection;

mxArray *GetTick(mxArray *inst, mxArray *start, mxArray *end)
{
    mxArray *result;
    const char *field_names[] = {"tradingday", "time", "instrument", "o", "h", "l", "c", "v", "i", "a1", "b1", "av1", "bv1"};
    
    string instrument = mxArrayToString(inst);
    int st = mxGetScalar(start);
    int et = mxGetScalar(end);
    auto_ptr<DBClientCursor> cursor;
    BSONObjBuilder b;
    BSONObjBuilder timePeriod;
    
    b.append("InstrumentID", instrument);
    timePeriod.appendDate("$gte",( (st - 719529) * 24LL)* 60LL * 60LL * 1000LL);
    timePeriod.appendDate("$lte", ( (et - 719529 + 1) * 24LL) * 60LL * 60LL * 1000LL);
    b.append("UpdateTime", timePeriod.obj());
    BSONObj qry = b.obj();
    cursor = mCon->query(string("MarketData.") + collection, qry);
    int size = cursor->itcount();
    mwSize dims[2] = {1, size};
    result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    cursor = mCon->query(string("MarketData.") + collection, qry);
    BSONObj p;
    int i = 0;
    while(cursor->more())
    {
        if(i >= size)
        {
            mexWarnMsgTxt("��ѯ��Χ������д�뷶Χ��\n");
            break;
        }
        p = cursor->next();
        tm buf;
        //turn into peking time;
        Date_t pkTime = Date_t(p["UpdateTime"].Date().millis + 8 * 3600000LL);
        double time = pkTime.millis%1000 / 100 / 100000.0;
        pkTime.toTm(&buf);
        int day = (buf.tm_year + 1900) * 10000 + (buf.tm_mon + 1) * 100 + buf.tm_mday;
        time = time + buf.tm_hour + buf.tm_min / 100.0 + buf.tm_sec / 10000.0;
        
        mxSetField(result, i, "tradingday", mxCreateDoubleScalar(day));
        mxSetField(result, i, "time", mxCreateDoubleScalar(time));
        mxSetField(result, i, "instrument", mxCreateString(instrument.c_str()));
        mxSetField(result, i, "o", mxCreateDoubleScalar( p["OpenPrice"].Double() ));
        mxSetField(result, i, "h", mxCreateDoubleScalar(p["HighestPrice"].Double()));
        mxSetField(result, i, "l", mxCreateDoubleScalar(p["LowestPrice"].Double()));
        mxSetField(result, i, "c", mxCreateDoubleScalar(p["LastPrice"].Double()));
        mxSetField(result, i, "v", mxCreateDoubleScalar(p["Volume"].Int()));
        mxSetField(result, i, "i", mxCreateDoubleScalar(p["OpenInterest"].Double()));
        mxSetField(result, i, "a1", mxCreateDoubleScalar(p["AskPrice1"].Double()));
        mxSetField(result, i, "b1", mxCreateDoubleScalar(p["BidPrice1"].Double()));
        mxSetField(result, i, "av1", mxCreateDoubleScalar(p["AskVolume1"].Double()));
        mxSetField(result, i, "bv1", mxCreateDoubleScalar(p["BidVolume1"].Double()));
        
        ++i;
        
    }
    return result;
}

mxArray *GetBar(mxArray *inst, mxArray *tp, mxArray *start, mxArray *end)
{

    mxArray *result;
    const char *field_names[] = {"tradingday", "time", "instrument", "type", "o", "h", "l", "c", "v", "i"};
    
    string instrument = mxArrayToString(inst);
    int type = mxGetScalar(tp);
    int st = mxGetScalar(start);
    int et = mxGetScalar(end);
    auto_ptr<DBClientCursor> cursor;
    BSONObjBuilder b;
    BSONObjBuilder timePeriod;

    b.append("instrument", instrument);
    b.append("type", type);
    timePeriod.appendDate("$gte",( (st - 719529) * 24LL)* 60LL * 60LL * 1000LL + 3 * 3600000);
    timePeriod.appendDate("$lte", ( (et - 719529 + 1) * 24LL) * 60LL * 60LL * 1000LL + 3 * 3600000);
    b.append("time", timePeriod.done());
    BSONObj qry = b.done();

    cursor = mCon->query(string("MarketData.") + collection, qry);
    int size = cursor->itcount();
    mwSize dims[2] = {1, size};
    result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    cursor = mCon->query(string("MarketData.") + collection, qry);
    BSONObj p;

    int i = 0;
    
    while(cursor->more())
    {
        if(i >= size)
        {
            mexWarnMsgTxt("��ѯ��Χ������д�뷶Χ��\n");
            break;
        }
        p = cursor->next();
        tm buf;

        Date_t pkTime = Date_t(p["time"].Date().millis);
        double time = pkTime.millis%1000 / 100 / 100000.0;
        pkTime.toTm(&buf);
        int day = (buf.tm_year + 1900) * 10000 + (buf.tm_mon + 1) * 100 + buf.tm_mday;
        time = time + buf.tm_hour + buf.tm_min / 100.0 + buf.tm_sec / 10000.0;
        
        mxSetField(result, i, "tradingday", mxCreateDoubleScalar(day));
        mxSetField(result, i, "time", mxCreateDoubleScalar(time));
        mxSetField(result, i, "instrument", mxCreateString(instrument.c_str()));
        mxSetField(result, i, "type", mxCreateDoubleScalar(type));
        mxSetField(result, i, "o", mxCreateDoubleScalar( p["o"].Double() ));
        mxSetField(result, i, "h", mxCreateDoubleScalar(p["h"].Double()));
        mxSetField(result, i, "l", mxCreateDoubleScalar(p["l"].Double()));
        mxSetField(result, i, "c", mxCreateDoubleScalar(p["c"].Double()));
        mxSetField(result, i, "v", mxCreateDoubleScalar(p["v"].Double()));
        mxSetField(result, i, "i", mxCreateDoubleScalar(p["i"].Double()));
        ++i;
        
    }
    return result;
}

mxArray *GetInstrument(mxArray *inst)
{
    mxArray *result;
    const char *field_names[] = {"InstrumentID", "ExchangeID", "InstrumentName", 
                                                    "ProductID", "DeliveryYear", "DeliveryMonth", 
                                                    "PriceTick", "CreateDate", "OpenDate", "ExpireDate", 
                                                    "StartDelivDate", "EndDelivDate", "LongMarginRatio", "ShortMarginRatio"};
    string instrument = mxArrayToString(inst);
    auto_ptr<DBClientCursor> cursor;
    BSONObjBuilder b;
    int size = 0;
    if(instrument.size() > 2)
    {
        b.append("InstrumentID", instrument);
        cursor = mCon->query(string("MarketData.") + collection, b.done());
        size = 1;
    }
    else if(instrument.size() == 0)
    {
        size = mCon->count(string("MarketData.") + collection);
        cursor = mCon->query(string("MarketData.") + collection, BSONObj());
    }
    else
    {
        b.append("ProductID", instrument);
        BSONObj qry = b.done();
        cursor = mCon->query(string("MarketData.") + collection, qry);
        size = cursor->itcount();
        cursor = mCon->query(string("MarketData.") + collection, qry);
    }
    
    mwSize dims[2] = {1, size};
    result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    int i = 0;
    BSONObj p;
    while(cursor->more())
    {
        if(i >= size)
        {
            mexWarnMsgTxt("��ѯʱ���ݿ�����д���Լ��Ϣ");
            break;
        }
        p = cursor->next();
        mxSetField(result, i, "InstrumentID", mxCreateString(p["InstrumentID"].String().c_str()));
        mxSetField(result, i, "ExchangeID", mxCreateString(p["ExchangeID"].String().c_str()));
        mxSetField(result, i, "InstrumentName", mxCreateString(p["InstrumentName"].String().c_str()));
        mxSetField(result, i, "ProductID", mxCreateString(p["ProductID"].String().c_str()));
        mxSetField(result, i, "DeliveryYear", mxCreateDoubleScalar(p["DeliveryYear"].Int()));
        mxSetField(result, i, "DeliveryMonth", mxCreateDoubleScalar(p["DeliveryMonth"].Int()));
        mxSetField(result, i, "PriceTick", mxCreateDoubleScalar(p["PriceTick"].Double()));
        mxSetField(result, i, "CreateDate", mxCreateString(p["CreateDate"].String().c_str()));
        mxSetField(result, i, "OpenDate", mxCreateString(p["OpenDate"].String().c_str()));
        mxSetField(result, i, "ExpireDate", mxCreateString(p["ExpireDate"].String().c_str()));
        mxSetField(result, i, "StartDelivDate", mxCreateString(p["StartDelivDate"].String().c_str()));
        mxSetField(result, i, "EndDelivDate", mxCreateString(p["EndDelivDate"].String().c_str()));
        mxSetField(result, i, "LongMarginRatio", mxCreateDoubleScalar(p["LongMarginRatio"].Double()));
        mxSetField(result, i, "ShortMarginRatio", mxCreateDoubleScalar(p["ShortMarginRatio"].Double()));

        ++i;
    }
    return result;
}

void SetCollection(mxArray *coll)
{
    collection = mxArrayToString(coll);
}

void WriteBar(mxArray *bar)
{
    
    int len = mxGetNumberOfElements(bar);
    for(int i = 0; i < len; ++i)
    {
        BSONObjBuilder b;
        b.append("instrument", mxArrayToString(mxGetField(bar, i, "instrument")));
        b.appendDate("time", Date_t((long long)mxGetScalar(mxGetField(bar, i, "time")) ));
        b.append("type", (int)mxGetScalar(mxGetField(bar, i, "type")));
        b.append("o", mxGetScalar(mxGetField(bar, i, "o")));
        b.append("h", mxGetScalar(mxGetField(bar, i, "h")));
        b.append("l", mxGetScalar(mxGetField(bar, i, "l")));
        b.append("c", mxGetScalar(mxGetField(bar, i, "c")));
        b.append("v", mxGetScalar(mxGetField(bar, i, "v")));
        b.append("i", mxGetScalar(mxGetField(bar, i, "i")));
        mCon->insert(string("MarketData.") + collection, b.done());
    }
}

