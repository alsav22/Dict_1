#ifndef G_VARIABLES_H
#define G_VARIABLES_H
#include <QtGui>
#include <QtCore>

//"stardict-ER-LingvoUniversal-2.4.2"
//"stardict-lingvo-ER-Biology-2.4.2"
//"stardict-lingvo-ER-Computer-2.4.2"
//"stardict-lingvo-ER-Informal-2.4.2"
//"stardict-lingvo-ER-Medical-2.4.2"
//"stardict-lingvo-ER-Polytechnical-2.4.2"


class GlobalVariables
{
public:
	const QString dirDict; // папка словаря
	const QString tr; // направление перевода
	QStringList dicts; // имена словарей (папок)      
	
	static GlobalVariables& getGlobalVariables() 
	{
		static GlobalVariables GlobalVar;
		return GlobalVar;
	}

private:
	GlobalVariables() : tr("ER")
	{ 
		dicts << "stardict-ER-LingvoUniversal-2.4.2" << "stardict-lingvo-ER-Informal-2.4.2"
			  << "stardict-lingvo-ER-Computer-2.4.2" << "stardict-lingvo-ER-Polytechnical-2.4.2"
			  << "stardict-lingvo-ER-Biology-2.4.2"  << "stardict-lingvo-ER-Medical-2.4.2";
			
	}

	GlobalVariables(const GlobalVariables& );
	GlobalVariables& operator=(const GlobalVariables& );
};
#endif