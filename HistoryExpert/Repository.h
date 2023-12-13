#pragma once

class Repository
{
protected:
	std::string fileName;
public:
	Repository(std::string fileName);
	virtual void loadData() = 0;
	virtual void saveData() = 0;
};

