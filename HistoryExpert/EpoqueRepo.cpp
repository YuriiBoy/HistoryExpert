#include "framework.h"
#include "EpoqueRepo.h"

EpoqueRepo::EpoqueRepo(std::string fileName)
	: Repository(fileName)
{
}

void EpoqueRepo::loadData()
{
	int id;
	TCHAR name[100];
	char buff[100];
	epo.clear();
	std::ifstream fin;
	fin.open(fileName);
	while (!fin.eof())	{
		fin.getline(buff, 100);
		if (strlen(buff) > 0) {
			id = atoi(buff);
			fin.getline(buff, 100);
			mbstowcs_s(NULL, name, 100, buff, 100);

			Epoque epoq(id, name);
			epo.push_back(epoq);
		}
	}
	fin.close();
}

void EpoqueRepo::saveData()
{
	char buff[100];
	std::ofstream fout;
	fout.open(fileName);

	// 2
	for (auto& epoq : epo) {
		fout << epoq.getId() << std::endl;
		wcstombs_s(NULL, buff, epoq.getName(), 100);
		fout << buff << std::endl;
	}

	// 3
	fout.close();
}

std::vector<Epoque>& EpoqueRepo::getEpoque()
{
	return epo;
}
