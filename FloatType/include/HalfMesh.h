#pragma once
#include "Vector3.h"
#include <vector>
#include <map>

namespace GPP
{
    class Edge3D;
    class GPP_EXPORT Vertex3D
    {
    public:
        Vertex3D();
        Vertex3D(const Vector3& coord);
        Vertex3D(const Vector3& coord, const Vector3& normal);

        Vector3 GetCoord() const;
        void    SetCoord(const Vector3& coord);
        Vector3 GetNormal() const;
        void    SetNormal(const Vector3& normal);
        Edge3D* GetEdge();
        const Edge3D* GetEdge() const;
        void    SetEdge(Edge3D* edge);
        Int     GetId() const;
        void    SetId(Int id);
        Int     GetEdgeMapId(void) const;
        void    SetEdgeMapId(Int id);
        Int     GetDegree(void) const;

        ~Vertex3D();

    private:
        Int     mId;    // mId is the index of mVertexList in HalfMesh
        Int     mEdgeMapId;    // mEdgeMapId is used in construct edge map in HalfMesh, this value will not be changed
        Edge3D* mpEdge;
        Vector3 mCoord;
        Vector3 mNormal;  
    };

    class Face3D;
    class GPP_EXPORT Edge3D
    {
    public:
        Edge3D();

        Vertex3D* GetVertex();
        const Vertex3D* GetVertex() const;
        void      SetVertex(Vertex3D* vertex);
        Edge3D*   GetPair();
        const Edge3D* GetPair() const;
        void      SetPair(Edge3D* edge);
        Edge3D*   GetNext();
        const Edge3D* GetNext() const;
        void      SetNext(Edge3D* edge);
        Edge3D*   GetPre();
        const Edge3D* GetPre() const;
        void      SetPre(Edge3D* edge);
        Face3D*   GetFace();
        const Face3D* GetFace() const;
        void      SetFace(Face3D* face);
        Int       GetId() const;
        void      SetId(Int id);

        ~Edge3D();

    private:
        Int       mId;    // mId is the index of mEdgeList in HalfMesh
        Vertex3D* mpVertex;
        Edge3D*   mpPair;
        Edge3D*   mpNext;
        Edge3D*   mpPre;
        Face3D*   mpFace;
    };

    class GPP_EXPORT Face3D
    {
    public:
        Face3D();

        Edge3D* GetEdge();
        const Edge3D* GetEdge() const;
        void    SetEdge(Edge3D* edge);
        Vector3 GetNormal() const;
        void    SetNormal(const Vector3& normal);
        Int     GetId() const;
        void    SetId(Int id);

        ~Face3D();

    private:
        Int     mId;    // mId is the index of mFaceList in HalfMesh
        Edge3D* mpEdge;
        Vector3 mNormal;
    };

    class GPP_EXPORT HalfMesh
    {
    public:
        HalfMesh();
        
        Int GetVertexCount() const;
        Int GetEdgeCount() const;
        Int GetFaceCount() const;

        Vertex3D* GetVertex(Int vid);
        const Vertex3D* GetVertex(Int vid) const;
        void SetVertex(Int vid, Vertex3D* vertex); // be carefull memory leak, we just simple set mVertexList.at(vid) = vertex
        Edge3D* GetEdge(Int eid);
        const Edge3D* GetEdge(Int eid) const;
        Face3D* GetFace(Int fid);
        const Face3D* GetFace(Int fid) const;
        
        void ReserveVertex(Int vertexCount);
        void ReserveEdge(Int edgeCount);
        void ReserveFace(Int faceCount);
        Vertex3D* InsertVertex(const Vector3& coord);
        Vertex3D* InsertVertex(const Vector3& coord, const Vector3& normal);
        Face3D*   InsertFace(const std::vector<Vertex3D* >& vertexList);

        // Unify bounding box size as bboxSize, make the center of bounding box to origin point (0, 0, 0)
        void UnifyCoords(Real bboxSize);

        // 1. Compute Face Normal
        // 2. If onlyFaceNormal == false, compute vertex normal
        void UpdateNormal(bool onlyFaceNormal = false);
        
        // 1. Remove edges which have no face 
        // 2. SetBoundaryVertexEdge
        // 3. Remove dummy vertex
        void ValidateTopology();
        
        // Set boundary vertex's out edge (GetEdge) to be boundary half edge
        void SetBoundaryVertexEdge();
        
        // Erase NULL element from element list, and update element ids
        void UpdateVertexIndex();
        void UpdateEdgeIndex();
        void UpdateFaceIndex();
        
        // If you don't change topology later, you can clear edge map to free memory
        void ClearEdgeMap(void);
        
        // They are used in Simply Mesh, it is better not to use it, if you indeed want to use it, please contact the author Li Guo
        // mEdgeList.at(edgeId) and its pair edge will be deleted, the related vertices, edges, faces will be updated
        // mVertexList, mEdgeList, mFaceList will not erase the deleted elements, just set them to NULL
        // If you want to erase the NULL elements, UpdateVertexIndex, UpdateEdgeIndex, UpdateFaceIndex can be used to do this
        ErrorCode ContractInnerEdge(Int edgeId, bool updateEdgeMap);
        ErrorCode ContractBoundaryEdge(Int edgeId, bool updateEdgeMap);

        ~HalfMesh();

    private:
        // InsertEdge is used in InsertFace
        Edge3D* InsertEdge(Vertex3D* vertexStart, Vertex3D* vertexEnd);
        
        void RemoveEdgeFromEdgeMap(Edge3D* edge);

    private:
        std::vector<Vertex3D* > mVertexList;
        std::vector<Edge3D* >   mEdgeList;
        std::vector<Face3D* >   mFaceList;
        std::vector<std::map<Int, Edge3D*> > mEdgeMap;
        Int mEdgeMapNewVertexId;
    };
}
