#include "triangles.h"

Triangles::Triangles() : numTriangles(0)
{}

void Triangles::addTriangle(int i, int j, int k)
{
	Eigen::Matrix<uint, 3, 1> tri = {uint(i),uint(j),uint(k)};
	triFaceList.push_back(tri);
	numTriangles++;
}

void Triangles::tetgen_readLine(std::ifstream &fin)
{
    float f;
    fin >> f; // first one is id.. //next 3 are the actual indices of the vertices // last one is the boundary marker

    int j, k, l;
    fin >> j >> k >> l;
    addTriangle(j - 1, k - 1, l - 1);

    fin >> f;
}

void Triangles::tetgen_readFace(const std::string &inputFileName)
{
    std::ifstream fin(inputFileName);

    if(fin.is_open())
    {
        int numFaces;
        int boundaryMarker;

        fin >> numFaces >> boundaryMarker;

        for(int i = 0; i < numFaces; ++i)
        {
            tetgen_readLine(fin);
        }

        fin.close();
    }
}
