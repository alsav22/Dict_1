#ifndef G_VARIABLES_H
#define G_VARIABLES_H
#include <QtGui>
#include <QtCore>

class GlobalVariables
{
public:
	const QString FILE_NAME;   // ��� �����, � ������� ������� ���� � ����� �� ��������� �������
	      QString PATH_SOUND;  // ���� � ����� �� ��������� �������
	const QString FILTER;
	
	static GlobalVariables& getGlobalVariables() 
	{
		static GlobalVariables GlobalVar;
		return GlobalVar;
	}

private:
	GlobalVariables() : FILE_NAME("Path_Sound.txt"),
		                PATH_SOUND("")
	{ 
		
			
	}

	GlobalVariables(const GlobalVariables& );
	GlobalVariables& operator=(const GlobalVariables& );
};
#endif