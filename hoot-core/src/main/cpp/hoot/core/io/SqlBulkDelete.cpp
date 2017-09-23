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
 * @copyright Copyright (C) 2017 DigitalGlobe (http://www.digitalglobe.com/)
 */
#include "SqlBulkDelete.h"

// hoot
#include <hoot/core/util/HootException.h>
#include <hoot/core/util/Log.h>

// Qt
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QStringBuilder>

// tgs
#include <tgs/System/Time.h>

namespace hoot
{

SqlBulkDelete::SqlBulkDelete(QSqlDatabase& db, const QString tableName, const int batchSize) :
_db(db),
_tableName(tableName),
_time(0),
_pendingCount(0),
_batchSize(batchSize)
{
  QString sql = "DELETE FROM " + _tableName + " WHERE ID in (?)";
//  for (int i = 0; i < _batchSize; i++)
//  {
//    sql += "?, ";
//  }
//  sql.chop(2);
//  sql += ")";
  LOG_VART(sql);
  _query.reset(new QSqlQuery(_db));
  if (!_query->prepare(sql))
  {
    LOG_ERROR("Unable to prepare query: " << sql);
  }
  LOG_VART(_query->executedQuery());
}

SqlBulkDelete::~SqlBulkDelete()
{
  LOG_DEBUG("(" << _tableName << ") Total time deleting: " << _time);
  if (_pendingCount > 0)
  {
    LOG_WARN("(" << _tableName << ") There are " << _pendingCount << " pending deletes in " <<
      "SqlBulkDelete. You should call flush before destruction.");
  }
  if (_query)
  {
    _query->finish();
    _query->clear();
  }
  _pending.clear();
  _pendingCount = 0;
}

void SqlBulkDelete::flush()
{
  LOG_TRACE("Flushing bulk delete...");
  LOG_VART(_pending.size());
  LOG_VART(_pendingCount);

  if (_pendingCount > 0)
  {
    assert(_pending.size() > 0);
    assert(_pendingCount == _pending.size());
    double start = Tgs::Time::getTime();

    _query->addBindValue(_pending);
    LOG_TRACE(_query->lastQuery());

    if (_query->execBatch() == false)
    {
      _pending.clear();
      LOG_ERROR(_query->executedQuery().left(500));
      LOG_ERROR(_query->lastError().text().left(500));
      throw HootException(
        QString("Error executing bulk insert: %1 (%2)")
        .arg(_query->lastError().text().left(500)).arg(_query->executedQuery()).left(500));
    }
    LOG_VART(_query->numRowsAffected());
    _pending.clear();
    _pendingCount = 0;

    double elapsed = Tgs::Time::getTime() - start;
    _time += elapsed;
  }
}

void SqlBulkDelete::deleteElement(const long id)
{
  _pending.append(QString::number(id));
  _pendingCount++;
}

}
