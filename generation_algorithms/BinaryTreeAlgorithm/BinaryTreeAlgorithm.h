#pragma once
#include"Header/Header_generation_algorithms.h"
#include"..\..\Field\Field.h"
class BinaryTreeAlgorithm
{
public:
	void generate(Field &f) {
		srand(time(0));
		int randValue = 0;
		vector<int> path;
		f.clearPreviousPath();
		f.SetNumberOfQuads(f.GetNumberOfQuads());
		for (int i = 0; i < f.GetNumberOfQuads(); i++)
		{
			f.Write(i,0, 0);
		}

		for (int y = 0; y < f.GetNumberOfQuads(); y+=2)
		{
			for (int x = 1; x < f.GetNumberOfQuads(); x+=2)
			{
				if (f.Read(x, y) != 1) path = ChekPosition(x, y, f);;
				//path = ChekPosition(x, y, f);
				if (path.size() != 0) {


					randValue = rand() % path.size();
					if (path[randValue] == 1) f.Write(x-1, y,0);
					if (path[randValue] == 2) f.Write(x, y-1, 0);
					if (path[randValue] == 3) f.Write(x+1, y, 0);
				}
			}
		}
	}

private:
	vector<int> ChekPosition(const int x, const int y, Field &f) {
		vector<int> validpath;
		//1 - left
		//2 - up
		//3 - right
		if (x - 1 >= 0) {
			if (f.Read(x - 1, y) > 0) validpath.push_back(1);
		}
		if (x + 1 < f.GetNumberOfQuads()) {
			if(f.Read(x + 1 ,y) > 0)  validpath.push_back(3);
		}
		if (y - 1 >= 0) {
			if(f.Read(x, y - 1) > 0) validpath.push_back(2);
		}
		return validpath;
	}
};

