#pragma once
#include "Repository.h"
#include "Epoque.h"

class EpoqueRepo :    public Repository
{
	std::vector<Epoque> epo;
public:
	EpoqueRepo(std::string fileName);
	void loadData() override;
	void saveData() override;
	std::vector<Epoque>& getEpoque();
};

