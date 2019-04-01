#include "Server.h"
#include "Config.h"
#include <conio.h>
#include <iostream>

#pragma warning(disable:4996)
int main() {

	bool start = false;
	Server srv;
	while (true)
	{
		if (kbhit())
		{
			if (getch() == 13)
				start = true;
		}
		if (start)
		{
			if (Config::getConfig() == -1) return -1;
			if (srv.WinsockStartup() == -1) return -1;
			if (srv.ServerStartup() == -1) return -1;
			if (srv.ListenStartup() == -1) return -1;
			if (srv.Loop() == -1) return -1;
			srv.~Server();
			cout << "ÍË³ö³É¹¦£¡" << endl;
			start = false;
		}
	}
	return 0;
}
