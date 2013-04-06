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
#include "DBField.hpp"
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

    DBCommand cmd(&connection, "SELECT guid, nick_name, gender FROM Users;");
    bool result = cmd.query();
    if (result == true)
    {
        while (cmd.fetchNext())
        {
            cout << cmd["guid"].fieldIndex() << ", " << cmd["guid"].fieldName() << endl;
            cout << cmd["nick_name"].fieldIndex() << ", " << cmd["nick_name"].fieldName() << endl;
            cout << cmd["gender"].fieldIndex() << ", " << cmd["gender"].fieldName() << endl;
        }
    }

    NetService net;
    net.start(port);

    return 0;
}

#ifdef WIN32
//#include "../../ThirdLibs/VisualLeakDetector/include/vld.h"
#endif
