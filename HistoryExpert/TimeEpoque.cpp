#include "framework.h"
#include "TimeEpoque.h"

TimeEpoque::TimeEpoque() : Model(), epoqueId(0)
{}

TimeEpoque::TimeEpoque(int id, TCHAR name[100], int epoqueId)
	: Model(id, name), epoqueId(epoqueId)
{}

int TimeEpoque::getEpoqueId()
{
	return id;
}
