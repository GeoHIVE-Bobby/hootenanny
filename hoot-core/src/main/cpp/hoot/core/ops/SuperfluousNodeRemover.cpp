/*
 * This file is part of Hootenanny.
 *
 * Hootenanny is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * The following copyright notices are generated automatically. If you
 * have a new notice to add, please use the format:
 * " * @copyright Copyright ..."
 * This will properly maintain the copyright information. DigitalGlobe
 * copyrights will be updated automatically.
 *
 * @copyright Copyright (C) 2015, 2016, 2017 DigitalGlobe (http://www.digitalglobe.com/)
 */

#include "SuperfluousNodeRemover.h"

// Hoot
#include <hoot/core/OsmMap.h>
#include <hoot/core/util/MapProjector.h>
#include <hoot/core/util/Factory.h>
#include <hoot/core/ops/RemoveNodeOp.h>

// Standard
#include <iostream>

// TGS
#include <tgs/StreamUtils.h>
using namespace Tgs;

namespace hoot
{

HOOT_FACTORY_REGISTER(OsmMapOperation, SuperfluousNodeRemover)

SuperfluousNodeRemover::SuperfluousNodeRemover()
{
}

void SuperfluousNodeRemover::apply(boost::shared_ptr<OsmMap> &map)
{
  _usedNodes.clear();

  const WayMap& ways = map->getWays();
  for (WayMap::const_iterator it = ways.begin(); it != ways.end(); ++it)
  {
    const ConstWayPtr& w = it->second;
    const vector<long>& nodeIds = w->getNodeIds();

    _usedNodes.insert(nodeIds.begin(), nodeIds.end());
  }

  const NodeMap nodes = map->getNodes();
  for (NodeMap::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
  {
    const Node* n = it->second.get();
    if (n->getTags().getNonDebugCount() != 0)
    {
      _usedNodes.insert(n->getId());
    }
  }

 boost::shared_ptr<OsmMap> reprojected;
  const NodeMap* nodesWgs84 = &nodes;
  // if the map is not in WGS84
  if (MapProjector::isGeographic(map) == false)
  {
    // create a new copy of the map and reproject it. This way we can be sure we do the bounds
    // calculation correctly.
    reprojected.reset(new OsmMap(map));
    MapProjector::projectToWgs84(reprojected);
    nodesWgs84 = &reprojected->getNodes();
  }

  for (NodeMap::const_iterator it = nodesWgs84->begin(); it != nodesWgs84->end();
       ++it)
  {
    const Node* n = it->second.get();
    if (_usedNodes.find(n->getId()) == _usedNodes.end())
    {
      if (_bounds.isNull() || _bounds.contains(n->getX(), n->getY()))
      {
        LOG_TRACE("Removing node. " << n->getElementId());
        RemoveNodeOp::removeNodeNoCheck(map, n->getId());
      }
      else
      {
        LOG_TRACE("node not in bounds. " << n->getElementId());
        LOG_VART(_bounds);
      }
    }
  }
}

void SuperfluousNodeRemover::readObject(QDataStream& is)
{
  bool hasBounds;
  is >> hasBounds;
  if (hasBounds)
  {
    double minx, miny, maxx, maxy;
    is >> minx >> miny >> maxx >> maxy;
    _bounds = Envelope(minx, maxx, miny, maxy);
  }
}

boost::shared_ptr<OsmMap> SuperfluousNodeRemover::removeNodes(boost::shared_ptr<const OsmMap> map)
{
 boost::shared_ptr<OsmMap> result(new OsmMap(map));
  SuperfluousNodeRemover().apply(result);
  return result;
}

void SuperfluousNodeRemover::removeNodes(boost::shared_ptr<OsmMap> &map, const Envelope& e)
{
  SuperfluousNodeRemover s;
  s.setBounds(e);
  s.apply(map);
}

void SuperfluousNodeRemover::setBounds(const Envelope &bounds)
{
  LOG_INFO("Setting bounds.");
  _bounds = bounds;
}

void SuperfluousNodeRemover::writeObject(QDataStream& os) const
{
  if (_bounds.isNull())
  {
    os << false;
  }
  else
  {
    os << true;
    os << _bounds.getMinX() << _bounds.getMinY() << _bounds.getMaxX() << _bounds.getMaxY();
  }
}

}
