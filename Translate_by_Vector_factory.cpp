#include "Translate_by_Vector_factory.h"
#include "Translate_by_Vector.h"

TranslateFactory::TranslateFactory()
{
	editSample = new QAction(QIcon(":/images/icon_Translate.png"),"Translate current model by matrix in several steps - GY", this);
	actionList << editSample;	
	foreach(QAction *editAction, actionList)
		editAction->setCheckable(true); 	
}
	
//gets a list of actions available from this plugin
QList<QAction *> TranslateFactory::actions() const
{
	return actionList;
}

//get the edit tool for the given action
MeshEditInterface* TranslateFactory::getMeshEditInterface(QAction *action)
{
	if(action == editSample)
	{
		return new TranslatePlugin();
	} else assert(0); //should never be asked for an action that isnt here
}

QString TranslateFactory::getEditToolDescription(QAction *)
{
	return TranslatePlugin::Info();
}

MESHLAB_PLUGIN_NAME_EXPORTER(CalculateDiffFactory)
