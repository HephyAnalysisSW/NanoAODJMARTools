#include "PhysicsTools/NanoAODJMARTools/interface/ECFWrapper.h"
#include "fastjet/PseudoJet.hh"

ECFWrapper::ECFWrapper( unsigned N, double alpha, double beta, std::string ecftype, unsigned  measure):
    N_(N), alpha_(alpha), beta_(beta), ecftype_(ecftype), measure_(measure)
{
    fastjet::contrib::EnergyCorrelator::Measure pt_R_( fastjet::contrib::EnergyCorrelator::pt_R );
    fastjet::contrib::EnergyCorrelator::Measure E_theta_( fastjet::contrib::EnergyCorrelator::E_theta );
    fastjet::contrib::EnergyCorrelator::Measure E_inv_( fastjet::contrib::EnergyCorrelator::E_inv );

    fastjet::contrib::EnergyCorrelator::Measure const * measureDef = nullptr;
    switch ( measure_ ) {
        case fastjet::contrib::EnergyCorrelator::pt_R:    measureDef = &pt_R_; break;
        case fastjet::contrib::EnergyCorrelator::E_theta: measureDef = &E_theta_; break;
        case fastjet::contrib::EnergyCorrelator::E_inv:   measureDef = &E_inv_; break;
    };

    if (ecftype_ == "ECF" || ecftype_.empty()) {
      routine_.reset( new fastjet::contrib::EnergyCorrelator(N_, beta_, *measureDef));
    } else if (ecftype_ == "C") {
      routine_.reset( new fastjet::contrib::EnergyCorrelatorCseries(N_, beta_, *measureDef));
    } else if (ecftype_ == "D") {
      routine_.reset( new fastjet::contrib::EnergyCorrelatorGeneralizedD2(alpha_, beta_, *measureDef));
    } else if (ecftype_ == "N") {
      routine_.reset(new fastjet::contrib::EnergyCorrelatorNseries(N_, beta_, *measureDef));
    } else if (ecftype_ == "M") {
      routine_.reset(new fastjet::contrib::EnergyCorrelatorMseries(N_, beta_, *measureDef));
    } else if (ecftype_ == "U") {
      routine_.reset(new fastjet::contrib::EnergyCorrelatorUseries(N_, beta_, *measureDef));
    }
}

ECFWrapper::ECFWrapper() : 
    N_(1), alpha_(1.), beta_(1.), ecftype_("ECF"), measure_( fastjet::contrib::EnergyCorrelator::pt_R ) 
{};

double ECFWrapper::result( std::vector<fastjet::PseudoJet> particles ) {
    return routine_ ->result( join(particles) );
}
