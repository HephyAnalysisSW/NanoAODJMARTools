#ifndef PhysicsTools_NanoAODToolsJMAR_ECFWrapper_h
#define PhysicsTools_NanoAODToolsJMAR_ECFWrapper_h

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "TLorentzVector.h"
#include "TVectorT.h"

#include "fastjet/contrib/EnergyCorrelator.hh"
#include "fastjet/PseudoJet.hh"

#include <string>
#include <vector>

class ECFWrapper {

    public:
        ECFWrapper();

        void addECF( unsigned N, double alpha, double beta, std::string ecftype, unsigned  measure=0 );

        void setParticles( const std::vector<TLorentzVector> & particles );
        std::vector<double> result( );

    private:
        fastjet::contrib::EnergyCorrelator::Measure pt_R_;
        fastjet::contrib::EnergyCorrelator::Measure E_theta_;
        fastjet::contrib::EnergyCorrelator::Measure E_inv_;

        std::vector<std::shared_ptr<fastjet::FunctionOfPseudoJet<double>>> routines_;
        std::vector<fastjet::PseudoJet> particles_;
};
#endif

