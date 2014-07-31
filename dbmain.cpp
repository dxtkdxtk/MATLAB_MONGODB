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

//�����ܲ���
mongo::DBClientConnection *mCon;
std::string mongoServer;
std::string database;
std::string collection;

void CheckIsConnect()
{
    if(NULL == mCon)
        mexErrMsgTxt("���ӿռ�δ����!");
}

//mex���������
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    //Ϊ��֤�ٶȣ�δ���Ӱ�ȫ�ж�
    int choise = (int)mxGetScalar(prhs[0]);
    switch(choise)
    {
        
        case 1:
        {
            try
            {
                if(mCon != NULL)
                    mexWarnMsgTxt("���ݿ��Ѿ�����!");
                else
                {
                    mCon = new mongo::DBClientConnection();
                    CheckIsConnect();
                    mongoServer = mxArrayToString(prhs[1]);
                    database = mxArrayToString(prhs[2]);
                    mCon->connect(mongoServer);
                    mexPrintf("�������ݿ�ɹ�\n");
                    collection = "";
                }
            }
            catch (const mongo::DBException &e)
            {
                mexErrMsgTxt("���Ӵ���!");
            }
            break;
        }
        case 2:
        {
            CheckIsConnect();
            delete mCon;
            mCon = NULL;
            mexPrintf("�Ͽ����ݿ�ɹ�\n");
            break;
        }
        default:
            mexErrMsgTxt("û���ҵ���ز���");
            
    }
    
}