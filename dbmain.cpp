/*****************************************************************************
 * File name: dbmain
 * Description: connect ctpdb
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

//连接总参数
mongo::DBClientConnection *mCon;
std::string mongoServer;
std::string database;
std::string collection;

void CheckIsConnect()
{
    if(NULL == mCon)
        mexErrMsgTxt("连接空间未开辟!");
}

//mex主函数入口
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    //为保证速度，未添加安全判断
    int choise = (int)mxGetScalar(prhs[0]);
    switch(choise)
    {
        
        case 1:
        {
            try
            {
                if(mCon != NULL)
                    mexWarnMsgTxt("数据库已经分配!");
                else
                {
                    mCon = new mongo::DBClientConnection();
                    CheckIsConnect();
                    mongoServer = mxArrayToString(prhs[1]);
                    database = mxArrayToString(prhs[2]);
                    mCon->connect(mongoServer);
                    mexPrintf("连接数据库成功\n");
                    collection = "";
                }
            }
            catch (const mongo::DBException &e)
            {
                mexErrMsgTxt("连接错误!");
            }
            break;
        }
        case 2:
        {
            CheckIsConnect();
            delete mCon;
            mCon = NULL;
            mexPrintf("断开数据库成功\n");
            break;
        }
        default:
            mexErrMsgTxt("没有找到相关操作");
            
    }
    
}
