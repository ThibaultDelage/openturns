//                                               -*- C++ -*-
/**
 *  @brief This class is a top-level class for the history mechanism of
 *  simulation algorithms. It delegates to its children the effective
 *  history strategy.
 *
 *  Copyright 2005-2017 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OPENTURNS_FULL_HXX
#define OPENTURNS_FULL_HXX

#include "openturns/HistoryStrategyImplementation.hxx"
#include "openturns/NumericalSample.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class Full
 */

class OT_API Full
  : public HistoryStrategyImplementation
{

  CLASSNAME;

public:


  /** Constructor with parameters */
  Full();

  /** Virtual constructor */
  virtual Full * clone() const;

  /** Store the point according to the strategy */
  void store(const NumericalPoint & point);
  void store(const NumericalSample & sample);

  /** String converter */
  String __repr__() const;

protected:

} ; /* class Full */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_FULL_HXX */
