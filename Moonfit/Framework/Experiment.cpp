#include "Experiment.h"

#include <iostream>
#include <fstream>
#include <sstream>

void    Experiment::simulate(int /*IdExp*/, Evaluator* /*E*/,  bool force){cerr << "ERR: Experiment::simulate() should be reimplemented in daughter class\n";}
int     Experiment::getNbCond(){return names_exp.size();}
string  Experiment::getNameCondition(int i){if((i >= 0) && (i < getNbCond())) return names_exp[i]; else {cerr << "ERR: Experiment::expName(" << i << "), index out of scope\n"; return string("");}}

Experiment::Experiment(Model* _m, int _nbConditions, string _Identification) : m(_m), nbConditions(_nbConditions), Identification(_Identification), totalPenalities(0.0) {
    if((_nbConditions < 0) || (_nbConditions > 100000)) {cerr << "ERR : Experiment::Experiment(m, nbConditions=" << _nbConditions << "), invalid nb of Experiment\n"; return;}
    names_exp.resize(nbConditions, string("NoName"));
    Overs.resize(nbConditions, NULL);
    VTG.resize(nbConditions, NULL);
    ExpData.resize(nbConditions);       // to avoid segfault at reset
    //for(int i = 0; i < nbConditions; ++i){
    //    ExpData[i] = vector<TableCourse*>(); // not sure this is neccessary
    //}
    ExpStdDevs.resize(nbConditions);
    evaluatorLoaded = false;
    reset();    // to fill the other vectors
}

void Experiment::motherReset(){
    for(int i = 0; i < nbConditions; ++i){
        if(VTG[i]) delete VTG[i];
        VTG[i] = new Evaluator();
        int S = ExpData[i].size();
        if(S > 0) {
            for(int j = 0; j < S; ++j){
                delete ExpData[i][j];
            }
        }
        int S2 = ExpStdDevs[i].size();
        if(S2 > 0) {
            for(int j = 0; j < S2; ++j){
                delete ExpStdDevs[i][j];
            }
        }
    }
    ExpData.clear();
    ExpData.resize(nbConditions);
    ExpStdDevs.clear();
    ExpStdDevs.resize(nbConditions);
    evaluatorLoaded = false;
}

void Experiment::motherInit(){
    totalPenalities = 0; /// Requires ??
    for(int i = 0; i < nbConditions; ++i){
        VTG[i]->resetDataKeepingExpected();
    }
}

void Experiment::motherSimulateAll( bool force){
    totalPenalities = 0;
    for(int i = 0; i < nbConditions; ++i){
        simulate(i, NULL, force);
        totalPenalities += m->penalities;
    }
}

double Experiment::motherCostExp(int IDcondition){
    if(IDcondition >= nbConditions) cerr << "Experiment::motherCostExp(" << IDcondition << "), exp ID incorrect (only " << nbConditions << " Experiment)" << endl;
    int nbIntVars = this->m->getNbVars();
    double res = 0;
    if(IDcondition < 0){ // this case is to check that motherCostPart(-1) and mlotherCostExp(-1) give the same result.
        for(int i = 0; i < nbIntVars; ++i){
            for(int j = 0; j < nbConditions; ++j){
                if((VTG[j])->contains(i)){
                    double subFit = VTG[j]->getFitnessSpecies(i);
                    if(! std::isnan(subFit)) res += subFit;
                }
            }
        }
    } else {
        for(int i = 0; i < nbIntVars; ++i){
            if((VTG[IDcondition])->contains(i)){
                double subFit = VTG[IDcondition]->getFitnessSpecies(i);;
                if(! std::isnan(subFit)) res += subFit;
            }
        }
    }
    return res;
}

double Experiment::motherCostVarInModel(int varID){
    double res = 0;
    if(varID < 0){
        for(int i = 0; i < nbConditions; ++i){
            double subFitness = VTG[i]->getTotalFitness();
            //cerr << subFitness << endl;
            if(! std::isnan(subFitness)) res += subFitness;
            ///else cerr << "Note : Exp " << i << " Has no data" << endl;
            //cout << " =========0 Cost Report for exp " << expName(i) << " 0========\n";
            //cout << VTG[i]->reportTotalFitness();
        }
        return res;
    } else {
        for(int i = 0; i < nbConditions; ++i){
            double subFit = VTG[i]->getFitnessSpecies(varID);
            if(!std::isnan(subFit)) res += subFit;
        }
        return res;
    }
}

double Experiment::motherCostExternalVariable(string extName){
    if(extName.size() == 0) return motherCostVarInModel(-1);
    double res = 0;
    vector<int> list = m->internValName(extName); // multiple variables might simulate the same data... just allows it even if it's weird...
    if(list.size() > 1) {
        static int errOnce = 0; // only displays the error once
        if(errOnce == 0) cerr << "Warning: you take the cost of an external variable that is simulated by more than one variable in parallel. (extName = " << extName << "). The cost will be the sum of all variables. Might make sense, might not make sense... Only showing this error once, maybe other external Names have the problem " << endl;
        errOnce++;
    }
    for(int k = 0; k < (int) list.size(); ++k){
        res += motherCostVarInModel(list[k]);
    }
    return res;
}




bool Experiment::motherPrepareSimulate(int IdExp, Evaluator* &E, bool force){
    if((IdExp < 0) || (IdExp >= getNbCond())) {   // to avoid simulation if not doable with this model\n";
        m->initialise(); return false;}     // do initialize to be sure there is no track of a previous simulation
    if(!E) E = VTG[IdExp]; if(! E){
        cerr << "ERR : ExpTHs::simulate(), internal VTG[] Evaluators are not defined, seg faults on approach ...\n"; return false;};
    if(E) E->recordingCompleted();                                  // in case it has not been done
    if((force == false) && E && (E->size() == 0))                   // to avoid simulation if not required for cost
        return false;
    else {
        //if(m->saveKinetics) cout << "   -> -------------- " << names_exp[IdExp].c_str() << " -----------\n";
        m->setOverrider(Overs[IdExp]);                              // Caution, this erases the previous overrider from the model.
        return true;
    }
}


double Experiment::getPenalities(){return totalPenalities;}



void Experiment::giveData(TableCourse* kineticData, int IdExp, TableCourse* kineticStds){
    if((IdExp < 0) || (IdExp >= getNbCond())) {cerr << "ERR: ExperimentThAll::giveData, out of bounds ExpID(" << IdExp << ")\n"; return;}
    ExpData[IdExp].push_back(new TableCourse(kineticData));
    if(kineticStds) ExpStdDevs[IdExp].push_back(new TableCourse(kineticStds));
    else ExpStdDevs[IdExp].push_back(NULL);
}
//void Experiment::giveStdDevs(TableCourse* kineticStds, int IdExp){
//    if((IdExp < 0) || (IdExp >= nbCond())) {cerr << "ERR: ExperimentThAll::giveData, out of bounds ExpID(" << IdExp << ")\n"; return;}
//    ExpStdDevs[IdExp].push_back(new TableCourse(kineticStds));
//}


void Experiment::loadEvaluators(){
    if(evaluatorLoaded) cerr << "ERR: You are loading twice data for the same experiment(" << Identification << ", make sure you don't call 'load Evaluators' twice for this experiment ..." << endl;
    // the problem is that an evaluator should have the local indices of the model
    // but here the data is provided with global names, so use m->getListExternalNames() to give which variable is called how
    for(int i = 0; i < getNbCond(); ++i){
        if(VTG[i]) {
            int S = ExpData[i].size();
            int S2 = ExpStdDevs[i].size();
            if(S != S2) cerr << "ERR: the same number of exp data and standard deviation (even if empty) should be given. Exp. " << i << ", DataTables " << S << " and StdDevTables" << S2 << endl;
            if(S > 0){
                cout << "   -> Create evaluators for experiment " << i << " with " << S << " datasets with standard deviations for " << S2 << " of them " << endl;
                for(int j = 0; j < S; ++j){
                    if(ExpData[i][j]){
                        // then, pass ExpStdDev as well even if it's NULL
                        VTG[i]->getValsFromKinetics(ExpData[i][j], m->getListExternalNames(), ExpStdDevs[i][j]);
                    }
                }
            }
            VTG[i]->recordingCompleted();
            cout << "   -> Data recorded for condition " << getNameCondition(i) << endl;
        }
    }
    if(!evaluatorLoaded) evaluatorLoaded = true;
}







void Experiment::setOverrider(int IdExp, overrider* _ov){
    if((IdExp < 0) || (IdExp >= getNbCond())) {cerr << "ERR: ExperimentThAll::setOverrider, out of bounds ExpID(" << IdExp << ")\n"; return;}
    Overs[IdExp] = _ov;
}

/// CAREFULL, the overriders will erase those from the model ...
void Experiment::overrideVariable(string extVarName, bool override, int IdExp){
    if((IdExp >= getNbCond())) {cerr << "ERR: ExperimentThAll::overrideVariable, out of bounds ExpID(" << IdExp << ")\n"; return;}
    if(IdExp >= 0){
        if(Overs[IdExp]){
            (* Overs[IdExp]).setOver(extVarName, override);
        }
    } else {
        for(int i = 0; i < getNbCond();++i){
            if(Overs[i]){
                //cerr << "Override " << ((override) ? "TRUE" : "FALSE") << endl;
                (* Overs[i]).setOver(extVarName, override);
            }
        }
    }
}

bool Experiment::canOverride(string extVarName, int IdExp){
    if(extVarName.size() == 0) return false;
    bool canDo = true;
    if((IdExp < -1) << (IdExp >= getNbCond())) return false;
    if(IdExp == -1){
        for(int i = 0; i < getNbCond(); ++i){
            canDo = canDo && (Overs[i] != NULL) && (Overs[i]->hasData(extVarName));
        }
    } else canDo = canDo && (Overs[IdExp] != NULL) && (Overs[IdExp]->hasData(extVarName));    
    //cerr << "   ... asking if can override " << extVarName << ", exp= " << IdExp << " Answer:" << ((canDo)? "Yes" : "No") << endl;
    //if(Overs[IdExp] != NULL) cerr << "Overrides defined ";
    //if(( nbCond() > 0) && (Overs[0]->hasData(IdGlobalVariable))) cerr << "At least one condition ok";
    //cerr << endl;*/
    return canDo;
}









string Experiment::extractData(vector<int> timePoints, vector<string> extNamesToSelect, vector<int> IDexps){

    int nbIdExps = IDexps.size();
    int nbTP = timePoints.size();
    int nbGlVars = extNamesToSelect.size();

    if((nbGlVars == 0) || (nbTP == 0)) {cerr << "ERR: Experiment::generateDataFile, no variable or time point given " << endl; return string("");}
    init();
    // puts data to the evaluators

    if(nbIdExps == 0){
        IDexps.resize(getNbCond());
        nbIdExps = getNbCond();
        for(int i = 0; i < nbIdExps; ++i){
            IDexps[i] = i;
        }
    }

    vector<Evaluator*> EVs;
    EVs.resize(nbIdExps);
    for(int i = 0; i < nbIdExps; ++i){
        EVs[i] = new Evaluator();
    }

    for(int i = 0; i < nbIdExps; ++i){
        Evaluator* locE = EVs[i];
        for(int j = 0; j < nbTP; ++j){
            for(int k = 0; k < nbGlVars; ++k){
                // Here you can not fill it with two variables, does not make sense
                locE->getVal(m->uniqueInternValName(extNamesToSelect[k]), timePoints[j]);
                /*if(m->saveKinetics) {
                    cout << "I want : " << m->getName(m->internValName(idGlobalVariables[k])) << ", t=" << timePoints[j] << endl;
                }*/
            }
        }
        locE->recordingCompleted();
    }
    for(int i = 0; i < nbIdExps; ++i){
        simulate(IDexps[i], EVs[i]);
    }

    //   writes a string with data as tables :
    //  NB_EXPS
    //  ID_EXP  NameEXP NbLg    NbVars
    //  Time    NameV1  NameV2  ...
    //  data    ...     ...
    //
    //  ID_EXP  NameExp ...

    stringstream fi;
    //fi << "# Automatically generated Data\n";
    fi << IDexps.size() << "\n";
    for(int i = 0; i < nbIdExps; ++i){
        fi << "\n" << IDexps[i];
        //if(isDoable(IDexps[i])){  // is doable removed from Moonfit V2.0
            fi << "\t" << nbTP << "\t" << nbGlVars << "\t#" << getNameCondition(IDexps[i]) << "\n";

            Evaluator* locE = EVs[i];
            if(! locE) {cerr << "ERR: GenerateDataFile Part, Evaluators are not defined, seg faults on approach ...\n";};


            fi << "time(s)";
            for(int k = 0; k < nbGlVars; ++k){
                fi << "\t" << extNamesToSelect[k]; //m->getName(m->internValName(idGlobalVariables[k]));
            }
            /* fi << " #";
            for(int k = 0; k < nbGlVars; ++k){
                fi << "\t" << m->getName(m->internValName(idGlobalVariables[k])); //m->getName(m->internValName(idGlobalVariables[k]));
            }*/
            fi << "\n";

            for(int j = 0; j < nbTP; ++j){
                fi << timePoints[j];
                for(int k = 0; k < nbGlVars; ++k){
                    double v = locE->getVal(m->uniqueInternValName(extNamesToSelect[k]), timePoints[j]);
                    fi << "\t" << v;
                }
                fi << "\n";
            }

        //} else {fi << "\t0\t0\t#" << getNameCondition(IDexps[i]) << "\n";;}
    }
    return fi.str();
}


string Experiment::print(){
    stringstream res;
    res << "========== Sum up of experiment content ========\n";
    res << "Name: " << Identification << "\n";
    res << "\n---------- Model used \n\n";
    res << m->print();
    res << "\n---------- " << nbConditions << " Experiments declared\n\n";
    for(int i = 0; i < nbConditions; ++i){
        res << "\t" << i << "\t" << getNameCondition(i); // << (isDoable(i) ? "\tCan Be Simulated\n" : "\tNot doable with this model\n");
    }
    for(int i = 0; i < nbConditions; ++i){
        res << "\n---------- Additional information for " << getNameCondition(i) << "\n\n";
        if((! VTG[i]) || (VTG[i]->size() == 0)) res << "No Evaluator / Empty evaluator for this experiment\n";
        else{ res << VTG[i]->printState();}
        int S = ExpData[i].size();
        int S2 = ExpStdDevs[i].size();
        if(S != S2) cerr << "ERR: ExpData and ExpStdDevs should have same size, exp " << i << ", DataTables " << S << " and Stddevtables " << S2 << endl;
        if(S > 0){
            res << "Experimental data :\n";
            for(int j = 0; j < S; ++j){
                if(ExpData[i][j]) res << ExpData[i][j]->print(false);
                else res << "Empty data";
                if(ExpStdDevs[i][j]) res << ExpStdDevs[i][j]->print(false);
                else res << "Empty Standard Deviations";
                res << endl;
            }
        } else res << "No Experimental data\n";
    }
    return res.str();
}

string Experiment::costReport(){
    stringstream res;
    for(int i = 0; i < nbConditions; ++i){
        res << names_exp[i] << "\n";
        res << VTG[i]->reportTotalFitness();
    }
    res << "\n\nCost per condition : \nExpNr\tCost\tName\n";
    for(int i = 0; i < nbConditions; ++i){
        res << i << "\t" << this->costExp(i) << "\t" << names_exp[i] << endl;
    }
    res << "\n\nCost per Variable : \nVarLocalNr\tVarGlobID\nCost\tName\n";
    for(int i = 0; i < m->getNbVars(); ++i){
        res << i << "\t" << m->getExternalName(i) << "\t" << this->costVariableInModel(i) << "\t" << m->getName(i) << endl;
    }
    return res.str();
}




















































/// TODO : remove evaluator from here
void    MultiExperiments::simulate(int /*IdExp*/, Evaluator* /*E*/,  bool force){cerr << "ERR: Experiments::simulate() should be reimplemented in daughter class, or call simulateAll !\n";}
int     MultiExperiments::nbBigExp(){return NbBigExps;}
string  MultiExperiments::BigExpName(int i){if((i >= 0) && (i < nbBigExp())) return ListBigExperiments[i]->Identification; else {cerr << "ERR: Experiments::BigExpName(" << i << "), index out of scope\n"; return string("");}}
MultiExperiments::MultiExperiments(Model* _m) : m(_m), NbBigExps(0) {reset();}
void MultiExperiments::AddExperiment(Experiment* Ex){
    coefficients.push_back(1.0);
    ListBigExperiments.push_back(Ex);
    NbBigExps++;}
Experiment* MultiExperiments::getExperiment(int BigExpID){
    if((BigExpID < 0) || (BigExpID > NbBigExps)) {cerr << "ERR: MultiExperiments::getExperiment(" << BigExpID << "), only " << NbBigExps << " experiments\n"; return NULL;}
    return ListBigExperiments[BigExpID];}
void MultiExperiments::reset(){
    cptNbSimus = 0;
    coefficients.clear();
    for(int i = 0; i < NbBigExps; ++i){
        ListBigExperiments[i]->reset();}}
void MultiExperiments::init(){
    for(int i = 0; i < NbBigExps; ++i){
        ListBigExperiments[i]->init();}}
void MultiExperiments::simulateAll(bool force){
    politics();     // to change the coefficients if necessary !
    for(int i = 0; i < NbBigExps; ++i){
        if(coefficients[i] > 0){
            ListBigExperiments[i]->simulateAll(force);
        } else { ///§§§ Danger ! be sure that the cost from previous experiment does not appear anywhere then
            ListBigExperiments[i]->init();
        }
    }
    postPolitics();
    cptNbSimus++;
}
double MultiExperiments::getCoefficient(int BigExpID){
    if((BigExpID < 0) || (BigExpID > NbBigExps)) {cerr << "ERR: MultiExperiments::getCoefficient(" << BigExpID << "), only " << NbBigExps << " experiments\n"; return 0.0;}
    return coefficients[BigExpID];}
void MultiExperiments::setCoefficient(int BigExpID, double newValue){
    if((BigExpID < 0) || (BigExpID > NbBigExps)) {cerr << "ERR: MultiExperiments::setCoefficient(" << BigExpID << "), only " << NbBigExps << " experiments\n"; return ;}
    if(newValue < -1e12) cerr << "WRN!!! : MultiExperiments::setCoefficient, are you serious ? you are giving a negative coefficient (" << newValue << ") to an experiment (" << getExperiment(BigExpID)->Identification << ")" << endl;
    coefficients[BigExpID] = newValue;}

/*double MultiExperiments::costBigExp(int BigExpID){
    double res = 0;
    if(BigExpID < 0){
        for(int i = 0; i < NbBigExps; ++i){
            res += ListBigExperiments[i]->costPart();
        }
    } else {
        if(BigExpID >= NbBigExps) cerr << "MultiExperiments::motherCostExp(" << BigExpID << "), BigExp ID incorrect (only " << NbBigExps << " experiments)" << endl;
        res = ListBigExperiments[BigExpID]->costPart();
    }
    return res;
}*/
/*double MultiExperiments::costPart(int species){
    double res = 0;
    for(int i = 0; i < NbBigExps; ++i){
        res += ListBigExperiments[i]->costPart(species);
    }
    return res;
}*/




double MultiExperiments::costBigExp(int BigExpID){
    double res = 0;
    cptNbSimus++;
    if(BigExpID < 0){
        for(int i = 0; i < NbBigExps; ++i){
            res += coefficients[i] * ListBigExperiments[i]->costVariableInModel();        // careful, mixing between indices and enum in
        }
    } else {
        if(BigExpID >= NbBigExps) cerr << "MultiExperiments::motherCostExp(" << BigExpID << "), BigExp ID incorrect (only " << NbBigExps << " experiments)" << endl;
        res = coefficients[BigExpID] * ListBigExperiments[BigExpID]->costVariableInModel();
    }
    return res;
}

double MultiExperiments::costVariableInModel(int idVarInModel){
    double res = 0;
    for(int i = 0; i < NbBigExps; ++i){
        res += coefficients[i] * ListBigExperiments[i]->costVariableInModel(idVarInModel);
    }
    return res;
}

double MultiExperiments::costExternalVariable(string extName){
    double res = 0;
    for(int i = 0; i < NbBigExps; ++i){
        res += coefficients[i] * ListBigExperiments[i]->costExternalVariable(extName);
    }
    return res;
}


void MultiExperiments::loadEvaluators(){
    for(int i = 0; i < NbBigExps; ++i){
        ListBigExperiments[i]->loadEvaluators();}}




string MultiExperiments::print(){
    stringstream res;
    res << "********** Multi-Experiments sum up ********\n";
    for(int i = 0; i < NbBigExps; ++i){
        res << ListBigExperiments[i]->print();
    }
    return res.str();
}

double MultiExperiments::getPenalities(){
    double res = 0;
    for(int i = 0; i < NbBigExps; ++i){
        res += ListBigExperiments[i]->getPenalities();
    }
    return res;
}

string MultiExperiments::costReport(){
    stringstream res;
    for(int i = 0; i < NbBigExps; ++i){
        res << ListBigExperiments[i]->costReport();
    }
    return res.str();
}

void MultiExperiments::overrideVariable(string extNameVar, bool override){
    for(int i = 0; i < NbBigExps; ++i){
        ListBigExperiments[i]->overrideVariable( extNameVar, override, -1);
    }
}
