#pragma once

class Model
{
protected:
	int id;
	TCHAR name[100];
public:
	Model();
	Model(int id, TCHAR name[100]);
	int getId();
	TCHAR* getName();
};

