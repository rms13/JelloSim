#include "tetrahedrons.h"

#define oneSixth 0.166666666667

Tetrahedrons::Tetrahedrons()
{
    // TODO
}

void Tetrahedrons::computeRestDeformation( uint tetraIndex, std::shared_ptr<Particles> vertices )
{
    Eigen::Matrix<uint, 4, 1> vertexIndices = particleIndices[tetraIndex];
    Eigen::Matrix<T, 3, 3> restDef;

    for(uint i=0; i<3; i++)
    {
        //x1-x4  x2-x4  x3-x4
        //y1-y4  y2-y4  y3-y4
        //z1-z4  z2-z4  z3-z4
        restDef(i,0) = vertices->pos[vertexIndices[0]][i] - vertices->pos[vertexIndices[3]][i];
        restDef(i,1) = vertices->pos[vertexIndices[1]][i] - vertices->pos[vertexIndices[3]][i];
        restDef(i,2) = vertices->pos[vertexIndices[2]][i] - vertices->pos[vertexIndices[3]][i];
    }

    restDeformation[tetraIndex] = restDef;
}

void Tetrahedrons::computeInvRestDeformation( uint tetraIndex )
{
    restInverseDeformation[tetraIndex] = restDeformation[tetraIndex].inverse();
}

void Tetrahedrons::computeUndeformedVolume( uint tetraIndex )
{
    undeformedVolume[tetraIndex] = oneSixth * std::abs( restDeformation[tetraIndex].determinant() );
}

void Tetrahedrons::computeNewDeformation( Eigen::Matrix<T, 3, 3> newDef, uint tetraIndex, std::shared_ptr<Particles> vertices )
{
    Eigen::Matrix<uint, 4, 1> vertexIndices = particleIndices[tetraIndex];

    for(uint i=0; i<3; i++)
    {
        //x1-x4  x2-x4  x3-x4
        //y1-y4  y2-y4  y3-y4
        //z1-z4  z2-z4  z3-z4
        newDef(i,0) = vertices->pos[vertexIndices[0]][i] - vertices->pos[vertexIndices[3]][i];
        newDef(i,1) = vertices->pos[vertexIndices[1]][i] - vertices->pos[vertexIndices[3]][i];
        newDef(i,2) = vertices->pos[vertexIndices[2]][i] - vertices->pos[vertexIndices[3]][i];
    }
}

/*
 *  .node FILE FORMAT:
 *      http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html
 *
 *  First line:
 *              <# of tetrahedra> <nodes per tet. (4 or 10)> <region attribute (0 or 1)>
 *
 *  Remaining lines list # of tetrahedra:
 *              <tetrahedron #> <node> <node> ... <node> [attribute]
 *
 */

// helper function
void Tetrahedrons::tetgen_readLine(std::ifstream &fin, int nodesPerTet)
{
    float f;
    fin >> f; // first one is id..

    for(int i = 0; i < nodesPerTet; ++i)
    {
        fin >> particleIndices[f](i, 0);
    }
}

void Tetrahedrons::tetgen_readEleFile(const std::string &inputFileName)
{
    // TODO
    std::ifstream fin(inputFileName);

    if(fin.is_open())
    {
        int nodesPerTet;
        int region;

        fin >> numTetra >> nodesPerTet >> region;

        particleIndices.resize(numTetra);

        for(int i = 0; i < numTetra; ++i)
        {
            tetgen_readLine(fin, nodesPerTet);
        }

        fin.close();
    }
}