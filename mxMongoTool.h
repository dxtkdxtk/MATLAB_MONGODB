/*****************************************************************************
 * File name: mxTool.h
 * Description: 提供所有数据库操作
 * Author: jebin
 * Version: 0.1
 * Date: 2014/07/30
 * History: see git log
 *****************************************************************************/
#include "mex.h"
#include "matrix.h"
#include "mongo/client/dbclient.h"

#include <iostream>
#include <string>
#include <set>
#include <utility>
using namespace mongo;

mxArray *GetTick(mxArray *inst, mxArray *start, mxArray *end);
mxArray *SetCollection(mxArray *collection);