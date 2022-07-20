#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soapStub.h"
#include "MobileCodeWSSoap.nsmap"

void getMobileCodeInfo(char *mobileCode)
{
    struct soap *soap = NULL;//结构体
    const char  *endpoint = "http://ws.webxml.com.cn/WebServices/MobileCodeWS.asmx";
    struct _ns1__getMobileCodeInfo          req;
    struct _ns1__getMobileCodeInfoResponse  resp;

    soap = soap_new();                      //分配和初始化上下文

    soap_set_mode(soap, SOAP_C_UTFSTRING);  //支持多字节字符串

    memset(&req, 0x00, sizeof(req));//memset是一个初始化函数，作用是将某一块内存中的全部设置为指定的值。
    req.mobileCode = mobileCode;
    req.userID     = NULL;

    //调用成功时返回 SOAP_OK（零），失败时返回非零错误。
    if(SOAP_OK == soap_call___ns1__getMobileCodeInfo(soap, endpoint, NULL, &req, &resp)) 
    {
        if (NULL != resp.getMobileCodeInfoResult) 
        {
            printf("%s\n", resp.getMobileCodeInfoResult);
        }
    }

    soap_destroy(soap);     //删除反序列化的对象
    soap_end(soap);         //删除分配的数据
    soap_free(soap);        //释放soap结构上下文数据
}

int main(int argc, char **argv)
{
    system("chcp 65001");//采用utf8编码

    if (argc < 2) 
    {
        return 0;
    }

    getMobileCodeInfo(argv[1]);

    return 0;
}
