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
 * @copyright Copyright (C) 2013, 2014 DigitalGlobe (http://www.digitalglobe.com/)
 */

// Hoot
#include <hoot/core/util/Factory.h>
#include <hoot/core/cmd/BaseCommand.h>
#include <hoot/core/util/Log.h>
#include <hoot/hadoop/convert/WriteOsmSqlStatementsDriver.h>

// Qt
#include <QStringList>

namespace hoot
{

class BigConvertCmd : public BaseCommand
{
public:

  static string className() { return "hoot::BigConvertCmd"; }

  BigConvertCmd() { }

  virtual QString getName() const { return "big-convert"; }

  virtual int runSimple(QStringList args)
  {
    if (args.size() != 2)
    {
      cout << getHelp() << endl << endl;
      throw HootException(QString("%1 takes two parameters.").arg(getName()));
    }
    if (!args[0].endsWith(".pbf"))
    {
      throw HootException(QString("%1 must take a .pbf file as input.").arg(getName()));
    }
    if (!args[1].endsWith(".sql"))
    {
      throw HootException(QString("%1 must take a .sql file as output.").arg(getName()));
    }

    WriteOsmSqlStatementsDriver().write(args[0], args[1]);

    return 0;
  }

};

HOOT_FACTORY_REGISTER(Command, BigConvertCmd)

}
