#include <iostream>
using namespace std;

#include <Yap/YapInterface.h>

void qgis_halt (int exit, void* stuff)
{
	cout << exit;
	cout << stuff;
	cout << "exiting \n";
}

extern "C" void
init_predicates (void)
{
	cout << "init\n";

	YAP_HaltRegisterHook(qgis_halt,NULL);
}
