/*****************************************************************************
 * File name: mxTool.h
 * Description: provide a set of operations to operate mongodb 
 * Author: jebin
 * Version: 0.1
 * Date: 2014/07/30
 * History: see git log
 *****************************************************************************/
#include "mex.h"
#include "matrix.h"
#include "mongo/client/dbclient.h"
#include "ThostFtdcUserApiStruct.h"

#include <iostream>
#include <string>
#include <set>
#include <utility>
#include <Windows.h>
using namespace std;
using namespace mongo;
using namespace bson;

time_t GetEpochTime(struct tm &t, string UpdateTime, int milisecond);
//获取tick
mxArray *GetTick(mxArray *inst, mxArray *start, mxArray *end);
//获取bar
mxArray *GetBar(mxArray *inst, mxArray *tp, mxArray *start, mxArray *end);
//设置集合
void SetCollection(mxArray *collection);
//获取合约
mxArray *GetInstrument(mxArray *inst);
//写入bar
void WriteBar(mxArray *bar);
//写入tick
bool WriteTick(mxArray *file);
//按时间段删除tick
void DeleteTick(mxArray *inst, mxArray *start, mxArray *end);
//查询指定时间最后一根tick
mxArray *GetLastTick(mxArray *inst, mxArray *end);