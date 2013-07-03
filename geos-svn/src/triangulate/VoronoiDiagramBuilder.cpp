/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2012 Excensus LLC.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: triangulate/DelaunayTriangulationBuilder.java rev. r524
 *
 **********************************************************************/

#include <geos/triangulate/VoronoiDiagramBuilder.h>

#include <algorithm>
#include <math.h>

#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/Envelope.h>
#include <geos/geom/CoordinateSequence.h>
#include <geos/triangulate/IncrementalDelaunayTriangulator.h>
#include <geos/triangulate/DelaunayTriangulationBuilder.h>
#include <geos/triangulate/quadedge/QuadEdgeSubdivision.h>

namespace geos {
namespace triangulate { //geos.triangulate

using namespace geos::geom;


VoronoiDiagramBuilder::VoronoiDiagramBuilder() :
	siteCoords(NULL), tolerance(0.0), subdiv(NULL) , clipEnv(NULL), diagramEnv(NULL)
{
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
   siteCoords = DelaunayTriangulationBuilder::extractUniqueCoordinates(geom);
}

void VoronoiDiagramBuilder::setSites(const geom::CoordinateSequence& coords)
{
   CoordinateSequence* coords_cpy = coords.clone();
   DelaunayTriangulationBuilder::unique(*coords_cpy);
   *siteCoords = *coords_cpy;
}

void VoronoiDiagramBuilder::setClipEnvelope(const geom::Envelope& clpEnv)
{
   *clipEnv = clpEnv;
}

void VoronoiDiagramBuilder::setTolerance(const double toler)
{
   tolerance = toler;
}


void VoronoiDiagramBuilder::create()
{
   if(subdiv!=NULL)
      return;
   geom::Envelope siteEnv = DelaunayTriangulationBuilder::envelope(*siteCoords);
   *diagramEnv = siteEnv;
   //adding buffer around the final envelope
   double expandBy = fmax(diagramEnv->getWidth() , diagramEnv->getHeight());
   diagramEnv->expandBy(expandBy);
   if(clipEnv!=NULL)
      diagramEnv->expandToInclude(clipEnv);

   IncrementalDelaunayTriangulator::VertexList* vertices = DelaunayTriangulationBuilder::toVertices(*siteCoords);

   quadedge::QuadEdgeSubdivision qes(siteEnv,tolerance);
   *subdiv = qes;
   IncrementalDelaunayTriangulator triangulator(subdiv);
   triangulator.insertSites(*vertices);
}

quadedge::QuadEdgeSubdivision* VoronoiDiagramBuilder::getSubdivision()
{
   create();
   return subdiv;
}

/*
geom::GeometryCollection VoronoiDiagramBuilder::clipGeometryCollection(const geom::GeometryCollection& geom, const geom::Envelope& clipEnv)
{
   geom::GeometryFactory* geomfact = geom.getFactory();
   geom::GeometryCollection* clipPoly = (*geomfact).toGeometry((Envelope*)&clipEnv);

}
*/


} //namespace geos.triangulate
} //namespace goes
