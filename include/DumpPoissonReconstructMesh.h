#pragma once
#include "DumpInfo.h"

namespace GPP
{
    extern GPP_EXPORT DumpBase* CreateDumpPointCloudPoissonReconstructMesh(void);

    class IPointCloud;
    class ITriMesh;
    class GPP_EXPORT DumpPointCloudPoissonReconstructMesh : public DumpBase
    {
    public:
        DumpPointCloudPoissonReconstructMesh();
        ~DumpPointCloudPoissonReconstructMesh();

        virtual ApiName GetApiName(void);
        virtual void LoadDumpFile(const std::string& fileName);
        virtual ErrorCode Run(void);
        virtual TriMesh* GetTriMesh(Int id = 0);
        virtual PointCloud* GetPointCloud(Int id = 0);

        void DumpApiInfo(const IPointCloud* pointCloud);

    private:
        TriMesh* mpTriMesh;
        PointCloud* mpPointCloud;
    };
}
