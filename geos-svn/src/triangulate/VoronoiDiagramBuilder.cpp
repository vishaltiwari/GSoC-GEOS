#include<geos/triangulate/VoronoiDiagramBuilder.h>

#include<vector>

#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/CoordinateSequence.h>
#include <geos/triangulate/IncrementalDelaunayTriangulator.h>
#include <geos/triangulate/quadedge/QuadEdgeSubdivision.h>
#include <geos/triangulate/quadedge/Vertex.h>


namespace geos{
namespace triangulate{

namespace quadedge{
	class QuadEdgeSubdivision;
}

VoronoiDiagramBuilder::VoronoiDiagramBuilder()
{
	siteCoords(NULL);
	tolerance(0.0);
	subdiv(NULL);
	clipEnv(NULL);
	diagramEnv(NULL);
}

VoronoiDiagramBuilder::~VoronoiDiagramBuilder()
{
	if(siteCoords)
		delete siteCoords;
	if(subdiv)
		delete subdiv;
	if(clipEnv)
		delete clipEnv;
	if(diagramEnv)
		delete diagramEnv;
}


void VoronoiDiagramBuilder::setSites(const geom::Geometry& geom)
{
	siteCoords = DelaunayTriangulationBuilder.extractUniqueCoordinates(geom);
}

void VoronoiDiagramBuilder::setSites(CoordinateSequence& coords)
{
	siteCoords = coords.clone();
	DelaunayTriangulationBuilder.unique(siteCoords);
}

void VoronoiDiagramBuilder::setClipEnvelope(geom::Envelope& clipEnv)
{
	this.clipEnv = clipEnv;
}

void VoronoiDiagramBuilder::setTolerance(double tolerance)
{
	this.tolerance = tolerance;
}

private:
	void create();
	
	/**
	 * Gets the {@link QuadEdgeSubdivision} which models the computed diagram.
	 * 
	 * @return the subdivision containing the triangulation
	 */

public:
	quadedge::QuadEdgeSubdivision& getSubdivision();

	/**
	 * Gets the faces of the computed diagram as a {@link GeometryCollection} 
	 * of {@link Polygon}s, clipped as specified.
	 * 
	 * @param geomFact the geometry factory to use to create the output
	 * @return the faces of the diagram
	 */

	geom::Geometry& getDiagram(geom::GeometryFactory *geomFact);

private:
	static geom::Geometry& clipGeometryCollection(geom::Geometry *g, geom::Envelope clipEnv);
}

}
}
#endif
