//                                               -*- C++ -*-
/**
 *  @brief The test file of class NormalCopula for standard methods
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
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"

using namespace OT;
using namespace OT::Test;

int main(int argc, char *argv[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  setRandomGenerator();

  try
  {
    // Instanciate one distribution object
    UnsignedInteger dim = 3;

    CorrelationMatrix R = IdentityMatrix(dim);
    for(UnsignedInteger i = 0; i < dim - 1; i++)
    {
      R(i, i + 1) = 0.25;
    }
    NormalCopula copula(R);
    copula.setName("a normal copula");
    fullprint << "Copula " << copula << std::endl;
    std::cout << "Copula " << copula << std::endl;
    fullprint << "Mean " << copula.getMean() << std::endl;
    // Is this copula an elliptical distribution?
    fullprint << "Elliptical distribution= " << (copula.isElliptical() ? "true" : "false") << std::endl;

    // Is this copula elliptical ?
    fullprint << "Elliptical copula= " << (copula.hasEllipticalCopula() ? "true" : "false") << std::endl;

    // Is this copula independent ?
    fullprint << "Independent copula= " << (copula.hasIndependentCopula() ? "true" : "false") << std::endl;

    // Test for realization of copula
    NumericalPoint oneRealization = copula.getRealization();
    fullprint << "oneRealization=" << oneRealization << std::endl;

    // Test for sampling
    UnsignedInteger size = 10;
    NumericalSample oneSample = copula.getSample( size );
    fullprint << "oneSample=" << oneSample << std::endl;

    // Test for sampling
    size = 10000;
    NumericalSample anotherSample = copula.getSample( size );
    fullprint << "anotherSample mean=" << anotherSample.computeMean() << std::endl;
    fullprint << "anotherSample covariance=" << anotherSample.computeCovariance() << std::endl;

    // Define a point
    NumericalPoint point(dim, 0.2);

    // Show DDF, PDF and CDF of point
    NumericalPoint  pointDDF = copula.computeDDF( point );
    NumericalScalar pointPDF = copula.computePDF( point );
    NumericalScalar pointCDF = copula.computeCDF( point );
    fullprint << "point= " << point
              << " ddf=" << pointDDF
              << " ddf (FD)=" << copula.ContinuousDistribution::computeDDF(point)
              << " pdf=" << pointPDF
              << " cdf=" << pointCDF
              << std::endl;
    NumericalScalar Survival = copula.computeSurvivalFunction(point);
    fullprint << "Survival      =" << Survival << std::endl;
    fullprint << "Survival (ref)=" << copula.computeSurvivalFunction(point) << std::endl;
    NumericalPoint InverseSurvival = copula.computeInverseSurvivalFunction(0.95);
    fullprint << "Inverse survival=" << InverseSurvival << std::endl;
    fullprint << "Survival(inverse survival)=" << copula.computeSurvivalFunction(InverseSurvival) << std::endl;
    // Get 50% quantile
    NumericalPoint quantile = copula.computeQuantile( 0.5 );
    fullprint << "Quantile=" << quantile << std::endl;
    fullprint << "CDF(quantile)=" << copula.computeCDF(quantile) << std::endl;

    if (copula.getDimension() <= 2)
    {
      // Confidence regions
      NumericalScalar threshold;
      fullprint << "Minimum volume interval=" << copula.computeMinimumVolumeIntervalWithMarginalProbability(0.95, threshold) << std::endl;
      fullprint << "threshold=" << threshold << std::endl;
      NumericalScalar beta;
      LevelSet levelSet(copula.computeMinimumVolumeLevelSetWithThreshold(0.95, beta));
      fullprint << "Minimum volume level set=" << levelSet << std::endl;
      fullprint << "beta=" << beta << std::endl;
      fullprint << "Bilateral confidence interval=" << copula.computeBilateralConfidenceIntervalWithMarginalProbability(0.95, beta) << std::endl;
      fullprint << "beta=" << beta << std::endl;
      fullprint << "Unilateral confidence interval (lower tail)=" << copula.computeUnilateralConfidenceIntervalWithMarginalProbability(0.95, false, beta) << std::endl;
      fullprint << "beta=" << beta << std::endl;
      fullprint << "Unilateral confidence interval (upper tail)=" << copula.computeUnilateralConfidenceIntervalWithMarginalProbability(0.95, true, beta) << std::endl;
      fullprint << "beta=" << beta << std::endl;
    }

    // Covariance and correlation
    CovarianceMatrix covariance = copula.getCovariance();
    fullprint << "covariance=" << covariance << std::endl;
    CorrelationMatrix correlation = copula.getCorrelation();
    fullprint << "correlation=" << correlation << std::endl;
    CorrelationMatrix spearman = copula.getSpearmanCorrelation();
    fullprint << "spearman=" << spearman << std::endl;
    CorrelationMatrix kendall = copula.getKendallTau();
    fullprint << "kendall=" << kendall << std::endl;
    // Extract the marginals
    for (UnsignedInteger i = 0; i < dim; i++)
    {
      Copula margin(copula.getMarginal(i));
      fullprint << "margin=" << margin << std::endl;
      fullprint << "margin PDF=" << margin.computePDF(NumericalPoint(1, 0.25)) << std::endl;
      fullprint << "margin CDF=" << margin.computeCDF(NumericalPoint(1, 0.25)) << std::endl;
      fullprint << "margin quantile=" << margin.computeQuantile(0.95) << std::endl;
      fullprint << "margin realization=" << margin.getRealization() << std::endl;
    }

    // Extract a 2-D marginal
    Indices indices(2, 0);
    indices[0] = 1;
    indices[1] = 0;
    fullprint << "indices=" << indices << std::endl;
    Copula margins(copula.getMarginal(indices));
    fullprint << "margins=" << margins << std::endl;
    fullprint << "margins PDF=" << margins.computePDF(NumericalPoint(2, 0.25)) << std::endl;
    fullprint << "margins CDF=" << margins.computeCDF(NumericalPoint(2, 0.25)) << std::endl;
    quantile = margins.computeQuantile(0.95);
    fullprint << "margins quantile=" << quantile << std::endl;
    fullprint << "margins CDF(quantile)=" << margins.computeCDF(quantile) << std::endl;
    fullprint << "margins realization=" << margins.getRealization() << std::endl;
    // Creation of the correlation matrix from a Spearman correlation matrix
    spearman = CorrelationMatrix(dim);
    for (UnsignedInteger i = 1; i < dim; i++)
    {
      spearman(i, i - 1) = 0.25;
    }
    correlation = NormalCopula::GetCorrelationFromSpearmanCorrelation(spearman);
    fullprint << "Normal copula correlation=" << correlation << " from the Spearman correlation=" << spearman << std::endl;
  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }


  return ExitCode::Success;
}

