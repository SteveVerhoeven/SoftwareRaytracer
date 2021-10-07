#include "OBJParser.h"

#include <string>
#include <fstream>
#include <iostream>
#include "EMath.h"
#include <vector>
#include <sstream>

#include "structs.h"

void OBJParser::LoadModel(const std::string& givenName, const std::string& filePath, std::vector<Vertex>& vBuffer, std::vector<size_t>& iBuffer)
{
	std::vector<Elite::FPoint3> points;
	std::vector<Elite::FVector3> normals;
	std::vector<Elite::FVector2> UVs;

	std::string name = givenName;

	std::ifstream in(filePath, std::ios::in);
	if (!in)
	{
		std::cout << ("Model \"" + filePath + "\" does not exist");
		return;
	}

	std::string line;
	while (getline(in, line))
	{
		if (line.substr(0, 1) == "#" || line.substr(0, 1) == "")
			continue;

		if (line.substr(0, 2) == "v ")
		{
			std::istringstream s{ line.substr(2) };
			Elite::FPoint3 v{};
			s >> v.x >> v.y >> v.z;
			points.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream s(line.substr(1));
			unsigned short v1, v2, v3;
			s >> v1 >> v2 >> v3;

			Vertex vert0{};
			vert0.position = Elite::FPoint3{ points[--v1] };
			Vertex vert1{};
			vert1.position = Elite::FPoint3{ points[--v2] };
			Vertex vert2{};
			vert2.position = Elite::FPoint3{ points[--v3] };

			bool found0{ false };
			bool found1{ false };
			bool found2{ false };
			int foundIndex0{};
			int foundIndex1{};
			int foundIndex2{};
			for (size_t i{}; i < vBuffer.size(); i++)
			{
				if (!found0 && vBuffer[i].position == vert0.position)
				{
					found0 = true;
					foundIndex0 = (int)i;

					vert0 = vBuffer[i];
				}
				if (!found1 && vBuffer[i].position == vert1.position)
				{
					found1 = true;
					foundIndex1 = (int)i;

					vert1 = vBuffer[i];
				}
				if (!found2 && vBuffer[i].position == vert2.position)
				{
					found2 = true;
					foundIndex2 = (int)i;

					vert2 = vBuffer[i];
				}
			}

			if (!found0)
			{
				vBuffer.push_back(vert0);
				iBuffer.push_back(vBuffer.size() - 1);
			}
			else
			{
				iBuffer.push_back(foundIndex0);
			}
			if (!found1)
			{
				vBuffer.push_back(vert1);
				iBuffer.push_back(vBuffer.size() - 1);
			}
			else
			{
				iBuffer.push_back(foundIndex1);
			}
			if (!found2)
			{
				vBuffer.push_back(vert2);
				iBuffer.push_back(vBuffer.size() - 1);
			}
			else
			{
				iBuffer.push_back(foundIndex2);
			}
		}
	}
}