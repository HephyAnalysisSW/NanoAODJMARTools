#include "PhysicsTools/NanoAODJMARTools/interface/ECFWrapper.h"
#include "fastjet/PseudoJet.hh"
#include "TLorentzVector.h"
#include <vector>

ECFWrapper::ECFWrapper( )
{
    pt_R_    =  fastjet::contrib::EnergyCorrelator::pt_R;
    E_theta_ =  fastjet::contrib::EnergyCorrelator::E_theta;
    E_inv_   = fastjet::contrib::EnergyCorrelator::E_inv;
}

void ECFWrapper::addECF( unsigned N, double alpha, double beta, std::string ecftype, unsigned  measure)
{
    fastjet::contrib::EnergyCorrelator::Measure const * measureDef = nullptr;
    switch ( measure ) {
        case fastjet::contrib::EnergyCorrelator::pt_R:    measureDef = &pt_R_; break;
        case fastjet::contrib::EnergyCorrelator::E_theta: measureDef = &E_theta_; break;
        case fastjet::contrib::EnergyCorrelator::E_inv:   measureDef = &E_inv_; break;
    };

    std::shared_ptr<fastjet::FunctionOfPseudoJet<double>> routine_;

    if (ecftype == "ECF" || ecftype.empty()) {
      routine_.reset( new fastjet::contrib::EnergyCorrelator(N, beta, *measureDef));
    } else if (ecftype == "C") {
      routine_.reset( new fastjet::contrib::EnergyCorrelatorCseries(N, beta, *measureDef));
    } else if (ecftype == "D") {
      routine_.reset( new fastjet::contrib::EnergyCorrelatorGeneralizedD2(alpha, beta, *measureDef));
    } else if (ecftype == "N") {
      routine_.reset(new fastjet::contrib::EnergyCorrelatorNseries(N, beta, *measureDef));
    } else if (ecftype == "M") {
      routine_.reset(new fastjet::contrib::EnergyCorrelatorMseries(N, beta, *measureDef));
    } else if (ecftype == "U") {
      routine_.reset(new fastjet::contrib::EnergyCorrelatorUseries(N, beta, *measureDef));
    }

    routines_.push_back( routine_ );
}

void ECFWrapper::setParticles( const std::vector<TLorentzVector> & particles ) {

    particles_.clear() ;
    for (std::vector<TLorentzVector>::const_iterator p = particles.begin(); p!=particles.end(); ++p ) {
        particles_.push_back(fastjet::PseudoJet(p->Px(), p->Py(), p->Pz(), p->Energy()));
    }
}

std::vector< double > ECFWrapper::result( ) {
    std::vector< double > results;
    results.clear();
    for ( std::vector<std::shared_ptr<fastjet::FunctionOfPseudoJet<double>>>::iterator routine_ = routines_.begin(); routine_!=routines_.end(); ++routine_ ) {
        results.push_back( (*routine_)->result( join(particles_) ) );
    }
    return results; 
}
