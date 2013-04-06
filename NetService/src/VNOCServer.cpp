//============================================================================
// Name        : epoll_server.cpp
// Author      : AngryPowman
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Common.h"
#include <iostream>
#include "NetService.h"
#include "Config.hpp"
#include <string>
#include "SQLUserStorage.h"
#include "UserManage.hpp"
#include "DBConnection.h"
#include "DBCommand.h"
#include <ezlogger_headers.hpp>

using namespace std;
using namespace VNOC::Message;

int main(int argc, char* argv[])
{
    Config::getInstance()->Initialize("vnoc.conf");
    cout<<"port:"<<Config::getInstance()->getValue("port")<<endl;
    //sUserStorage us;
    //CUserManage::GetInstance()->initial(&us);
	uint16 port = Config::getInstance()->getValue("port");

    //db test
    DBConnection connection("F:\\VNOC\\NetService\\Database\\VNOC.db");
    connection.open();
    if (connection.isAlive())
    {
        cout << "Start DB OK." << endl;
    }

    DBCommand cmd(&connection, "SELECT nick_name, gender FROM Users WHERE guid = ?;");
    cmd << 20000;
    cmd.query();

    NetService net;
    net.start(port);

    return 0;
}

#ifdef WIN32
//#include "../../ThirdLibs/VisualLeakDetector/include/vld.h"
#endif
