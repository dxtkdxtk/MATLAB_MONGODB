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

#include <iostream>
#include <string>
#include <set>
#include <utility>
using namespace std;
using namespace mongo;
using namespace bson;

mxArray *GetTick(mxArray *inst, mxArray *start, mxArray *end);
void SetCollection(mxArray *collection);