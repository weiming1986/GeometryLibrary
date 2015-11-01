#pragma once
#include "ITriMesh.h"
#include <vector>

namespace GPP
{
    class GPP_EXPORT ParameterizeMesh
    {
    public:
        ParameterizeMesh();
        ~ParameterizeMesh();

        static Int AnglePreservingParameterize(const ITriMesh* triMesh, std::vector<Real>* texCoords);
    };
}
