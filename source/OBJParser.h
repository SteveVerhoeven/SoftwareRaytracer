#pragma once
#include <string>
#include <vector>

#include "EMath.h"

class Camera;
struct BoundingBox;
struct Vertex;
class OBJParser final
{
	public:
		OBJParser() = default;
		~OBJParser() = default;

		OBJParser(const OBJParser&) = delete;
		OBJParser(OBJParser&&) noexcept = delete;
		OBJParser& operator=(const OBJParser&) = delete;
		OBJParser& operator=(OBJParser&&) noexcept = delete;

		void LoadModel(const std::string& givenName, const std::string& filePath, std::vector<Vertex>& vBuffer, std::vector<size_t>& iBuffer);
		
	private:
};