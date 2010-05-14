#ifndef _REALM_H
#define _REALM_H

#include "Common.h"
#include "Policies/Singleton.h"

class Logon
{
    public:
		Logon();
		~Logon();

		int RunR();

    private:
		bool StartDB();
};

#define sRealm Diamond::Singleton<Logon>::Instance()
#endif