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
//��ȡtick
mxArray *GetTick(mxArray *inst, mxArray *start, mxArray *end);
//��ȡbar
mxArray *GetBar(mxArray *inst, mxArray *tp, mxArray *start, mxArray *end);
//���ü���
void SetCollection(mxArray *collection);
//��ȡ��Լ
mxArray *GetInstrument(mxArray *inst);
//д��bar
void WriteBar(mxArray *bar);
//д��tick
bool WriteTick(mxArray *file);
//��ʱ���ɾ��tick
void DeleteTick(mxArray *inst, mxArray *start, mxArray *end);
//��ѯָ��ʱ�����һ��tick
mxArray *GetLastTick(mxArray *inst, mxArray *end);