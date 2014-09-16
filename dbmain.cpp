/*****************************************************************************
 * File name: dbmain
 * Description: connect mongodb main entry
 * Author: jebin
 * Version: 0.1
 * Date: 2014/07/30
 * History: see git log
 *****************************************************************************/
#include "mex.h"
#include "matrix.h"
#include "mxMongoTool.h"

#include <iostream>
#include <string>
#include <set>
#include <utility>

using namespace std;
using namespace mongo;
using namespace bson;

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
    //Ϊ��֤�ٶȣ�δ��Ӱ�ȫ�ж�
    int choise = (int)mxGetScalar(prhs[0]);
    switch(choise)
    {
        //�������ݿ�
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
                delete mCon;
                mCon = NULL;
                mexErrMsgTxt("���Ӵ���!");
            }
            break;
        }
        
        //�Ͽ����ݿ�
        case 2:
        {
            CheckIsConnect();
            delete mCon;
            mCon = NULL;
            mexPrintf("�Ͽ����ݿ�ɹ�\n");
            break;
        }
        
        //����collection
        case 3:
        {
            CheckIsConnect();
            SetCollection(prhs[1]);
            break;
        }
        
        //��ȡtick����
        case 4:
        {
            CheckIsConnect();
            plhs[0] = GetTick(prhs[1], prhs[2], prhs[3]);
            break;
        }
        
        case 5:
        {
            CheckIsConnect();
            plhs[0] = GetInstrument(prhs[1]);
            break;
        }
        case 6:
        {
            CheckIsConnect();
            WriteBar(prhs[1]);
            break;
        }
        case 7: 
        {
            CheckIsConnect();
            plhs[0] = GetBar(prhs[1], prhs[2], prhs[3], prhs[4]);
            break;
        }
        case 8: 
        {
            CheckIsConnect();
            bool ok = WriteTick(prhs[1]);
            if(ok)
            {
                mexPrintf("д��tick�ɹ�\n");
            }
            else
            {
                mexPrintf("д��tickʧ��\n");
            }
            break;
        }
        default:
            mexErrMsgTxt("û���ҵ���ز���");
            
    }
    
}
