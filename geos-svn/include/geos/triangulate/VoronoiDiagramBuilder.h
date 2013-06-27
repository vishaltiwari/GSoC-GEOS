#ifndef GEOS_TRIANGULATE_VORONOIDIAGRAMBUILDER_H
#define GEOS_TRIANGULATE_VORONOIDIAGRAMBUILDER_H

#include<list>

#include <geos/triangulate/VoronoiDiagramBuilder.h>


namespace geos{
namespace geom{
	class Geometry;
	class GeometryFactory;
	class Envelope;
	class CoordinateSequence;
}
namespace triangulate{
	namespace quadedge{
		class QuadEdgeSubdivision;
	}
}

namespace geos{
namespace triangulate{

namespace quadedge{
	class QuadEdgeSubdivision;
}
/**
 * A utility class which creates Voronoi Diagrams
 * from collections of points.
 * The diagram is returned as a {@link GeometryCollection} of {@link Polygon}s,
 * clipped to the larger of a supplied envelope or to an envelope determined
 * by the input sites.
 * 
 * @author Martin Davis
 *
 */
class GEOS_DLL VoronoiDiagramBuilder
{
private:
	geom::CoordinateSequence *siteCoords;
	double tolerance;
	quadedge::QuadEdgeSubdivision *subdiv;
	geom::Envelope *clipEnv;
	geom::Envelope *diagramEnv;
public:
	/**
	 * Creates a new Voronoi diagram builder.
	 *
	*/
	VoronoiDiagramBuilder();

	~VoronoiDiagramBuilder();

	/**
	 * Sets the sites (point or vertices) which will be diagrammed.
	 * All vertices of the given geometry will be used as sites.
	 * 
	 * @param geom the geometry from which the sites will be extracted.
	 */
	void setSites(geom::Geometry *g);

	/**
	 * Sets the sites (point or vertices) which will be diagrammed
	 * from a collection of {@link Coordinate}s.
	 * 
	 * @param geom a collection of Coordinates.
	 */
	void setSites(std::vector<geom::CoordinateSequence> coords);

	/**
	 * Sets the envelope to clip the diagram to.
	 * The diagram will be clipped to the larger
	 * of this envelope or an envelope surrounding the sites.
	 * 
	 * @param clipEnv the clip envelope.
	 */
	void setClipEnvelope(geom::Envelope *clipEnv);

	/**
	 * Sets the snapping tolerance which will be used
	 * to improved the robustness of the triangulation computation.
	 * A tolerance of 0.0 specifies that no snapping will take place.
	 * 
	 * @param tolerance the tolerance distance to use
	 */

	void setTolerance(double tolerance);

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
};

}
}
}
#endif
