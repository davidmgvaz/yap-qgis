#include <iostream>
using namespace std;

// QGIS
#include <qgis.h>
#include <qgsvectorlayer.h>
#include <qgsproviderregistry.h>

// QT
#include <QString>

// YAP
#include <Yap/YapInterface.h>

int qgis_QgsVectorLayer_open(void)
{
	QString path = YAP_AtomName(YAP_AtomOfTerm(YAP_ARG1));
	QString basename = YAP_AtomName(YAP_AtomOfTerm(YAP_ARG2));
	QString provider = YAP_AtomName(YAP_AtomOfTerm(YAP_ARG3));
	YAP_Term out;

	QgsVectorLayer *layer =
		  new QgsVectorLayer(path, basename, provider);

	if (layer->isValid())
	{
		cerr << "Layer Type: " << layer->geometryType() << endl;
		cerr << "Feature Count: " << layer->featureCount() << endl;
		return TRUE;
	}
	else
	{
		delete layer;
		return FALSE;
	}
}

void qgis_halt (int exit, void* stuff)
{
	cout << exit;
	cout << stuff;
	cout << "exiting \n";
}

extern "C" void
qgis_init (void)
{
	cout << "init\n";

	QString myPluginsDir        = "/usr/lib/qgis/plugins";
	QgsProviderRegistry::instance(myPluginsDir);

	YAP_UserCPredicate ("qgis_vector_open", qgis_QgsVectorLayer_open, 3);

	YAP_HaltRegisterHook(qgis_halt,NULL);
}
