#ifndef PhysicsTools_NanoAODToolsJMAR_ECFWrapper_h
#define PhysicsTools_NanoAODToolsJMAR_ECFWrapper_h

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "TLorentzVector.h"

#include "fastjet/contrib/EnergyCorrelator.hh"

#include <string>
#include <vector>

class ECFWrapper {
    
    public:
        ECFWrapper( unsigned N, double alpha, double beta, std::string ecftype, unsigned  measure=0 );
        ECFWrapper();
        double result( std::vector<fastjet::PseudoJet> );
    private:
        unsigned N_;
        double   alpha_;
        double   beta_;
        std::string ecftype_;
        unsigned measure_;

        std::shared_ptr<fastjet::FunctionOfPseudoJet<double>> routine_;
};
#endif

