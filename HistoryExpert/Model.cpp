#include "framework.h"
#include "Model.h"

Model::Model() : id(0)
{
	lstrcpy(this->name, L"");
}

Model::Model(int id, TCHAR name[100]) : id(id)
{
	lstrcpy(this->name, name);
}

int Model::getId()
{
	return id;
}

TCHAR* Model::getName()
{
	return name;
}
