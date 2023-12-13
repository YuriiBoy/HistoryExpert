#pragma once
#include "Model.h"
class TimeEpoque :    public Model
{
	int epoqueId;
public:
	TimeEpoque();
	TimeEpoque(int id, TCHAR name[100], int epoqueId);
	int getEpoqueId();
};

