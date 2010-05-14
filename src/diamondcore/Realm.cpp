#include "Common.h"
#include "Realm.h"
#include "Master.h"
#include "Database/DatabaseEnv.h"
#include "RealmList.h"

#include "Config/ConfigEnv.h"
#include "Log.h"
#include "sockets/ListenSocket.h"
#include "Policies/SingletonImp.h"
#include "AuthSocket.h"
#include "SystemConfig.h"
#include "revision_nr.h"
#include "Util.h"
#include <openssl/opensslv.h>
#include <openssl/crypto.h>

//bool stopEvent = false;                                     ///< Setting it to true stops the server

//DatabaseType loginDatabase;                                 ///< Accessor to the realm server database

INSTANTIATE_SINGLETON_1( Logon );

Logon::Logon()
{
}

Logon::~Logon()
{
}

int Logon::RunR()
{
	///- Initialize the database connection
    if (!StartDB())
        return 1;

	///- Get the list of realms for the server
    sRealmList.Initialize(sConfig.GetIntDefault("RealmsStateUpdateDelay", 20));
    if (sRealmList.size() == 0)
    {
        sLog.outError("No valid realms specified.");
        return 1;
    }

    ///- Launch the listening network socket
    port_t rmport = sConfig.GetIntDefault("RealmServerPort", DEFAULT_REALMSERVER_PORT);
	std::string bind_ip = sConfig.GetStringDefault("BindIP", "0.0.0.0");

	SocketHandler h;
    ListenSocket<AuthSocket> authListenSocket(h);
    if (authListenSocket.Bind(bind_ip.c_str(), rmport))
    {
        sLog.outError("LogonServer can not bind to %s:%d", bind_ip.c_str(), rmport);
        return 1;
    }

    // cleanup query
    //set expired bans to inactive
    loginDatabase.Execute("UPDATE account_banned SET active = 0 WHERE unbandate <= UNIX_TIMESTAMP() AND unbandate <> bandate");
    loginDatabase.Execute("DELETE FROM ip_banned WHERE unbandate <= UNIX_TIMESTAMP() AND unbandate <> bandate");

    h.Add(&authListenSocket);


    // maximum counter for next ping
    uint32 numLoops = (sConfig.GetIntDefault("MaxPingTime", 30) * (MINUTE * 1000000 / 100000));
    uint32 loopCounter = 0;

    return 0;
}

/// Initialize connection to the database
/*bool StartDB()
{
    std::string dbstring = sConfig.GetStringDefault("LoginDatabaseInfo", "");
    if (dbstring.empty())
    {
        sLog.outError("Database not specified");
        return false;
    }

    sLog.outString("Database: %s", dbstring.c_str() );
    if (!loginDatabase.Initialize(dbstring.c_str()))
    {
        sLog.outError("Cannot connect to database");
        return false;
	}

    return true;
}*/
bool Logon::StartDB()
{
	std::string dbstring = sConfig.GetStringDefault("LoginDatabaseInfo", "");
    if (dbstring.empty())
    {
        sLog.outError("Database not specified");
        return false;
    }

    sLog.outString("Database: %s", dbstring.c_str() );
    if (!loginDatabase.Initialize(dbstring.c_str()))
    {
        sLog.outError("Cannot connect to database");
        return false;
	}

    return true;
}

