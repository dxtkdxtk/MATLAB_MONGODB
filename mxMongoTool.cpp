/*****************************************************************************
 * File name: dbmain
 * Description: connect ctpdb
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
    
    return result;
}
void SetCollection(mxArray *coll)
{
    collection = mxArrayToString(coll);
}