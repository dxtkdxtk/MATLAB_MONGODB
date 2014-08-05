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
//     mexPrintf("数据长度%d, collection为%s\n", size, collection.c_str());
    mwSize dims[2] = {1, size};
    result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    cursor = mCon->query(string("MarketData.") + collection, qry);
    BSONObj p;
    int i = size - 1;
    while(cursor->more())
    {
        p = cursor->next();
        tm buf;
        //trun into peking time;
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
        mxSetField(result, i, "av1", mxCreateDoubleScalar(p["AskVolume1"].Int()));
        mxSetField(result, i, "bv1", mxCreateDoubleScalar(p["BidVolume1"].Int()));
        
        --i;
        if(i < -1)
        {
            mexWarnMsgTxt("GetTick程序越界!");
            break;
        }
    }
    
    return result;
}
void SetCollection(mxArray *coll)
{
    collection = mxArrayToString(coll);
    mexPrintf("collection已设置为%s\n", collection.c_str());
}