#ifndef EXPERIMENTSTHALL_H
#define EXPERIMENTSTHALL_H

#include "../Moonfit/moonfit.h"
#include "Models/modeleLeishmaniaMajor.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;




struct expLMajor : public Experiment {
    enum EXP{Small_Dose, /*Big_Dose,*/ NB_EXP}; // experiments    - use expLMajor::Small_Dose
    expLMajor(Model* _m) : Experiment(_m, NB_EXP) {

        Identification = string("Leishmaniasis");
        names_exp[Small_Dose] = string("Small_Dose"); // activation (TCR Only)");
        //m->setBaseParameters();
    }

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false) {// if no E is given, VTG[i] is used
        if(motherPrepareSimulate(IdExp, E, force)){
            switch(IdExp){

            default: {m->initialise(Back::WT); break;}
            }
            switch(IdExp){
            case Small_Dose:{
                //            m->setValue("P", 3391.69); // it was 5000
                m->simulate(105, E); break;} // 124 days -> might change later
            }
            m->setOverrider(NULL);
        }
    }
};

struct expLMajor_Blocking : public Experiment {
    enum EXP{Control,
             ActivationInhibition25,ActivationInhibition50,ActivationInhibition75,ActivationInhibition100,
             RecruitmentInhibition25,RecruitmentInhibition50,RecruitmentInhibition75,RecruitmentInhibition100,
             ActivationRecruitmentInhibition25,ActivationRecruitmentInhibition50,ActivationRecruitmentInhibition75,ActivationRecruitmentInhibition100,
             RagNoAct,RagNoActRecInhib25,RagNoActRecInhib50, RagNoActRecInhib75, RagNoActRecInhib100,
             NB_EXP}; // experiments    - use expLMajor::Small_Dose
    expLMajor_Blocking(modeleLeishmania* _m) : Experiment(_m, NB_EXP) {

        Identification = string("Leishmaniasis");
        names_exp[Control] = string("Control");
        names_exp[ActivationInhibition25]             = string("Activation Inhibition 25%");
        names_exp[ActivationInhibition50]             = string("Activation Inhibition 50%");
        names_exp[ActivationInhibition75]             = string("Activation Inhibition 75%");
        names_exp[ActivationInhibition100]            = string("Activation Inhibition 100%");
        names_exp[RecruitmentInhibition25]            = string("Recruitment Inhibition 25%");
        names_exp[RecruitmentInhibition50]            = string("Recruitment Inhibition 50%");
        names_exp[RecruitmentInhibition75]            = string("Recruitment Inhibition 75%");
        names_exp[RecruitmentInhibition100]           = string("Recruitment Inhibition 100%");
        names_exp[ActivationRecruitmentInhibition25]  = string("Activation-Recruitment Inhibition 25%");
        names_exp[ActivationRecruitmentInhibition50]  = string("Activation-Recruitment Inhibition 50%");
        names_exp[ActivationRecruitmentInhibition75]  = string("Activation-Recruitment Inhibition 75%");
        names_exp[ActivationRecruitmentInhibition100] = string("Activation-Recruitment Inhibition 100%");
        names_exp[RagNoAct] = string("Rag1-No Activation");
        names_exp[RagNoActRecInhib25]  = string("Rag1-No Activation-Recruitment Inhibition 25%");
        names_exp[RagNoActRecInhib50]  = string("Rag1-No Activation-Recruitment Inhibition 50%");
        names_exp[RagNoActRecInhib75]  = string("Rag1-No Activation-Recruitment Inhibition 75%");
        names_exp[RagNoActRecInhib100] = string("Rag1-No Activation-Recruitment Inhibition 100%");
        //m->setBaseParameters();
    }

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false) {// if no E is given, VTG[i] is used
        if(motherPrepareSimulate(IdExp, E, force)){
            switch(IdExp){

            default: {m->initialise(Back::WT); break;}
            }
            switch(IdExp){
            case Control:{
                m->simulate(21, E); // need to reduce the data to only include up to day 21..otherwise it plots the entire duration of the infection
//                m->simulate(51, E);
//                double p1 = m->getParam(modeleLeishmania::beta);
//                m->setParam(modeleLeishmania::beta, 0);
//                m->simulate(82,E);
//                m->setParam(modeleLeishmania::beta, p1);
                break;
            }
//            case ActivationInhibition25:{ // still 75% is activating
//                m->simulate(18, E); // change the day (18) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                m->setParam(modeleLeishmania::k_a, p1*0.75);
//                m->setParam(modeleLeishmania::k_ai, p2*0.75);
//                m->simulate(3,E);// simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
////                m->simulate(112,E);
//                break;
//            }
//            case ActivationInhibition50:{
//                m->simulate(18, E); // change the day (18) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                m->setParam(modeleLeishmania::k_a, p1*0.5);
//                m->setParam(modeleLeishmania::k_ai, p2*0.5);
//                m->simulate(3,E);// simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
////                m->simulate(112,E);
//                break;
//            }
//            case ActivationInhibition75:{ // still 25% is activating
//                m->simulate(18, E); // change the day (18) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                m->setParam(modeleLeishmania::k_a, p1*0.25);
//                m->setParam(modeleLeishmania::k_ai, p2*0.25);
//                m->simulate(3,E);// simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
////                m->simulate(112,E);
//                break;
//            }
//            case ActivationInhibition100:{
//                m->simulate(18, E); // change the day (18) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                m->setParam(modeleLeishmania::k_a, 0);
//                m->setParam(modeleLeishmania::k_ai, 0);
//                m->simulate(3,E);// simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
////                m->simulate(112,E);
//                break;
//            }
//            case RecruitmentInhibition25:{
//                m->simulate(18, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p2 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_Mrec0, p1*0.75);
//                m->setParam(modeleLeishmania::alpha, p2*0.75);
//                m->simulate(3,E); // simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_Mrec0, p1);
//                m->setParam(modeleLeishmania::alpha, p2);
////                m->simulate(112,E);
//                break;
//            }
//            case RecruitmentInhibition50:{
//                m->simulate(18, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p2 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_Mrec0, p1*0.50);
//                m->setParam(modeleLeishmania::alpha, p2*0.50);
//                m->simulate(3,E); // simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_Mrec0, p1);
//                m->setParam(modeleLeishmania::alpha, p2);
////                m->simulate(112,E);
//                break;
//            }
//            case RecruitmentInhibition75:{
//                m->simulate(18, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p2 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_Mrec0, p1*0.25);
//                m->setParam(modeleLeishmania::alpha, p2*0.25);
//                m->simulate(3,E); // simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_Mrec0, p1);
//                m->setParam(modeleLeishmania::alpha, p2);
////                m->simulate(112,E);
//                break;
//            }
//            case RecruitmentInhibition100:{
//                m->simulate(18, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p2 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_Mrec0, 0);
//                m->setParam(modeleLeishmania::alpha, 0);
//                m->simulate(3,E); // simulate the rest days after blockade...
//                m->setParam(modeleLeishmania::k_Mrec0, p1);
//                m->setParam(modeleLeishmania::alpha, p2);
////                m->simulate(112,E);
//                break;
//            }
            case ActivationRecruitmentInhibition25:{
                m->simulate(18, E); // change the day (21) of blockade
                double p1 = m->getParam(modeleLeishmania::k_a);
                double p2 = m->getParam(modeleLeishmania::k_ai);
                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
                double p4 = m->getParam(modeleLeishmania::alpha);
                m->setParam(modeleLeishmania::k_a, p1*0.75);
                m->setParam(modeleLeishmania::k_ai, p2*0.75);
                m->setParam(modeleLeishmania::k_Mrec0, p3*0.75);
                m->setParam(modeleLeishmania::alpha, p4*0.75);
                m->simulate(3,E); // simulate the rest days after blockade...
                m->setParam(modeleLeishmania::k_a, p1);
                m->setParam(modeleLeishmania::k_ai, p2);
                m->setParam(modeleLeishmania::k_Mrec0, p3);
                m->setParam(modeleLeishmania::alpha, p4);
//                m->simulate(112,E);
                break;
            }
            case ActivationRecruitmentInhibition50:{
                m->simulate(18, E); // change the day (21) of blockade
                double p1 = m->getParam(modeleLeishmania::k_a);
                double p2 = m->getParam(modeleLeishmania::k_ai);
                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
                double p4 = m->getParam(modeleLeishmania::alpha);
                m->setParam(modeleLeishmania::k_a, p1*0.50);
                m->setParam(modeleLeishmania::k_ai, p2*0.50);
                m->setParam(modeleLeishmania::k_Mrec0, p3*0.50);
                m->setParam(modeleLeishmania::alpha, p4*0.50);
                m->simulate(3,E); // simulate the rest days after blockade...
                m->setParam(modeleLeishmania::k_a, p1);
                m->setParam(modeleLeishmania::k_ai, p2);
                m->setParam(modeleLeishmania::k_Mrec0, p3);
                m->setParam(modeleLeishmania::alpha, p4);
//                m->simulate(112,E);
                break;
            }
            case ActivationRecruitmentInhibition75:{
                m->simulate(18, E); // change the day (21) of blockade
                double p1 = m->getParam(modeleLeishmania::k_a);
                double p2 = m->getParam(modeleLeishmania::k_ai);
                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
                double p4 = m->getParam(modeleLeishmania::alpha);
                m->setParam(modeleLeishmania::k_a, p1*0.25);
                m->setParam(modeleLeishmania::k_ai, p2*0.25);
                m->setParam(modeleLeishmania::k_Mrec0, p3*0.25);
                m->setParam(modeleLeishmania::alpha, p4*0.25);
                m->simulate(3,E); // simulate the rest days after blockade...
                m->setParam(modeleLeishmania::k_a, p1);
                m->setParam(modeleLeishmania::k_ai, p2);
                m->setParam(modeleLeishmania::k_Mrec0, p3);
                m->setParam(modeleLeishmania::alpha, p4);
//                m->simulate(112,E);
                break;
            }
            case ActivationRecruitmentInhibition100:{
                m->simulate(18, E); // change the day (21) of blockade
                double p1 = m->getParam(modeleLeishmania::k_a);
                double p2 = m->getParam(modeleLeishmania::k_ai);
                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
                double p4 = m->getParam(modeleLeishmania::alpha);
                m->setParam(modeleLeishmania::k_a, 0);
                m->setParam(modeleLeishmania::k_ai, 0);
                m->setParam(modeleLeishmania::k_Mrec0, 0);
                m->setParam(modeleLeishmania::alpha, 0);
                m->simulate(3,E); // simulate the rest days after blockade...
                m->setParam(modeleLeishmania::k_a, p1);
                m->setParam(modeleLeishmania::k_ai, p2);
                m->setParam(modeleLeishmania::k_Mrec0, p3);
                m->setParam(modeleLeishmania::alpha, p4);
//                m->simulate(112,E);
                break;
            }
//            case RagNoAct:{
//                m->simulate(0, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                m->setParam(modeleLeishmania::k_a, 0);
//                m->setParam(modeleLeishmania::k_ai, 0);
////                m->simulate(133,E); // simulate the rest days after blockade...
//                m->simulate(21,E);
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
//                break;
//            }
//            case RagNoActRecInhib25:{
//                m->simulate(0, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p4 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_a, p1*0.75);
//                m->setParam(modeleLeishmania::k_ai, p2*0.75);
//                m->setParam(modeleLeishmania::k_Mrec0, p3*0.75);
//                m->setParam(modeleLeishmania::alpha, p4*0.75);
////                m->simulate(133,E); // simulate the rest days after blockade...
//                m->simulate(21,E);
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
//                m->setParam(modeleLeishmania::k_Mrec0, p3);
//                m->setParam(modeleLeishmania::alpha, p4);
//                break;
//            }
//            case RagNoActRecInhib50:{
//                m->simulate(0, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p4 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_a, p1*0.50);
//                m->setParam(modeleLeishmania::k_ai, p2*0.50);
//                m->setParam(modeleLeishmania::k_Mrec0, p3*0.50);
//                m->setParam(modeleLeishmania::alpha, p4*0.50);
////                m->simulate(133,E); // simulate the rest days after blockade...
//                m->simulate(21,E);
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
//                m->setParam(modeleLeishmania::k_Mrec0, p3);
//                m->setParam(modeleLeishmania::alpha, p4);
//                break;
//            }
//            case RagNoActRecInhib75:{
//                m->simulate(0, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p4 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_a, p1*0.25);
//                m->setParam(modeleLeishmania::k_ai, p2*0.25);
//                m->setParam(modeleLeishmania::k_Mrec0, p3*0.25);
//                m->setParam(modeleLeishmania::alpha, p4*0.25);
////                m->simulate(133,E); // simulate the rest days after blockade...
//                m->simulate(21,E);
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
//                m->setParam(modeleLeishmania::k_Mrec0, p3);
//                m->setParam(modeleLeishmania::alpha, p4);
//                break;
//            }
//            case RagNoActRecInhib100:{
//                m->simulate(0, E); // change the day (21) of blockade
//                double p1 = m->getParam(modeleLeishmania::k_a);
//                double p2 = m->getParam(modeleLeishmania::k_ai);
//                double p3 = m->getParam(modeleLeishmania::k_Mrec0);
//                double p4 = m->getParam(modeleLeishmania::alpha);
//                m->setParam(modeleLeishmania::k_a, 0);
//                m->setParam(modeleLeishmania::k_ai, 0);
//                m->setParam(modeleLeishmania::k_Mrec0, 0);
//                m->setParam(modeleLeishmania::alpha, 0);
////                m->simulate(133,E); // simulate the rest days after blockade...
//                m->simulate(21,E);
//                m->setParam(modeleLeishmania::k_a, p1);
//                m->setParam(modeleLeishmania::k_ai, p2);
//                m->setParam(modeleLeishmania::k_Mrec0, p3);
//                m->setParam(modeleLeishmania::alpha, p4);
//                break;
//            }
            default: {
            }
            }
            m->setOverrider(NULL);
        }
    }
};


struct expDoubleLMajor : public Experiment {
    enum EXP{Small_Dose, Big_Dose, NB_EXP}; // experiments    - use expLMajor::Small_Dose

    // please call this experiment with an extended model
    expDoubleLMajor(modelExtended* _m) : Experiment((Model*) _m, NB_EXP) {
        Identification = string("DoubleLeishmaniasis");
        names_exp[Small_Dose] = string("Small_Dose");
        names_exp[Big_Dose] = string("Big_Dose");
        //m->setBaseParameters();
    }

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false) {// if no E is given, VTG[i] is used
        if(motherPrepareSimulate(IdExp, E, force)){
            switch(IdExp){
                case Small_Dose:{
                    //            m->setValue("P", 3391.69); // it was 5000

                    m->initialise(modelExtended::ApplyCoefficients);
                    m->simulate(133, E);
                    break;
                } // 124 days -> might change later
                case Big_Dose:{
                    //            m->setValue("P", 3391.69); // it was 5000
                    m->initialise(modelExtended::WT);
                    m->simulate(133, E);
                    break;
                } // 124 days -> might change later
            }
            m->setOverrider(NULL);
        }
    }
};

struct InitialPopulation : public Experiment {
    enum{DoseDefault,/*Dose1k,*/Dose3k,Dose5k,/*Dose7k,Dose9k,*/Dose10k,Dose15k,Dose20k,Dose30k,Dose50k,Dose75k,Dose100k,
         Dose200k,Dose300k,NbInitDoses};    // experiments    - use InitialPopulation::Small_Dose
    InitialPopulation(Model* _m) : Experiment(_m, NbInitDoses) {

        Identification = string("Initial Dose leishmaniasis");
        names_exp[DoseDefault] = string("dose default");
//        names_exp[Dose1k] = string("dose 1k");
        names_exp[Dose3k] = string("dose 3k");
        names_exp[Dose5k] = string("dose 5k");
        names_exp[Dose10k] = string("dose 10k");
        names_exp[Dose15k] = string("dose 15k");
        names_exp[Dose20k] = string("dose 20k");
        names_exp[Dose30k] = string("dose 30k");
        names_exp[Dose50k] = string("dose 50k");
        names_exp[Dose75k] = string("dose 75k");
        names_exp[Dose100k] = string("dose 100k");
        names_exp[Dose200k] = string("dose 200k");
        names_exp[Dose300k] = string("dose 300k");
//        names_exp[Dose7k] = string("dose 7k");
//        names_exp[Dose9k] = string("dose 9k");

        //m->setBaseParameters();
    }

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false) {// if no E is given, VTG[i] is used
        if(motherPrepareSimulate(IdExp, E, force)){
            switch(IdExp){

            default: {m->initialise(Back::WT); break;}
            }
            switch(IdExp){
            case DoseDefault:{
                m->setValue("P", 54743.5); // here instead of the fitted default, it uses this one..
                m->simulate(150, E); break;}
//            case Dose1k:{
//                m->setValue("P", 1000);
//                m->simulate(130, E); break;}
//            case Dose3k:{
//                m->setValue("P", 3000);
//                m->simulate(150, E); break;}
            case Dose5k:{
                m->setValue("P", 5000); //5000
                m->simulate(150, E); break;}
//            case Dose7k:{
//                m->setValue("P", 7000); //7000
//                m->simulate(130, E); break;}
            case Dose10k:{
                m->setValue("P", 10000);
                m->simulate(150, E); break;}
//            case Dose9k:{
//                m->setValue("P", 9000); //9000
//                m->simulate(130, E); break;}
//            case Dose15k:{
//                m->setValue("P", 15000);
//                m->simulate(150, E); break;}
            case Dose20k:{
                m->setValue("P", 20000);
                m->simulate(150, E); break;}
            case Dose30k:{
                m->setValue("P", 30000);
                m->simulate(150, E); break;}
            case Dose50k:{
                m->setValue("P", 50000);
                m->simulate(150, E); break;}
//            case Dose75k:{
//                m->setValue("P", 75000);
//                m->simulate(150, E); break;}
            case Dose100k:{
                m->setValue("P", 100000);
                m->simulate(150, E); break;}
            case Dose200k:{
                m->setValue("P", 200000);
                m->simulate(150, E); break;}
            case Dose300k:{
                m->setValue("P", 300000);
                m->simulate(150, E); break;}
        }
            m->setOverrider(NULL);
        }
    }
};



struct PerturbParam : public Experiment {
    enum{Param005, Param01, Param02,Param05,Param08,Param12,Param15,Param20, Param50, Param100, ParamDefault, NbParamChange};
    int parameter;
    double valueAround;
    PerturbParam(Model* _m, int _parameter, double _valueAround) : Experiment(_m, NbParamChange), parameter(_parameter), valueAround(_valueAround) {

        Identification = string("Perturbate") + _m->getParamName(parameter);
        stringstream valInString; valInString << valueAround; string val = valInString.str();
        names_exp[ParamDefault] = string("default=") + val;
        names_exp[Param005] = string("5%");
        names_exp[Param01] = string("10%");
        names_exp[Param02] = string("20%");
        names_exp[Param05] = string("50%");
        names_exp[Param08] = string("80%");
        names_exp[Param12] = string("120%");
        names_exp[Param15] = string("150%");
        names_exp[Param20] = string("x2");
        names_exp[Param50] = string("x5");
        names_exp[Param100] = string("x10");

        //m->setBaseParameters();
    }

    /// 2018-11-21 Should not use the parameter value from creation, but the current from the table
    void init(){
        valueAround = m->getParam(parameter);
        motherInit();
    }

    /// Careful, this function should restore the exact same paameter values as before being called
    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false) {// if no E is given, VTG[i] is used
        if(motherPrepareSimulate(IdExp, E, force)){
            switch(IdExp){

            default: {m->initialise(Back::WT); break;}
            }
            switch(IdExp){
            case Param005:{
                m->setParam(parameter, valueAround * 0.05);
                m->simulate(130, E); break;}
            case Param01:{
                m->setParam(parameter, valueAround * 0.1);
                m->simulate(130, E); break;}
            case Param02:{
                m->setParam(parameter, valueAround * 0.2);
                m->simulate(130, E); break;}
            case Param05:{
                m->setParam(parameter, valueAround * 0.5);
                m->simulate(130, E); break;}
            case Param08:{
                m->setParam(parameter, valueAround * 0.8);
                m->simulate(130, E); break;}
            case Param12:{
                m->setParam(parameter, valueAround * 1.2);
                m->simulate(130, E); break;}
            case Param15:{
                m->setParam(parameter, valueAround * 1.5);
                m->simulate(130, E); break;}
            case Param20:{
                m->setParam(parameter, valueAround * 2.0);
                m->simulate(130, E); break;}
            case Param50:{
                m->setParam(parameter, valueAround * 5.0);
                m->simulate(130, E); break;}
            case Param100:{
                m->setParam(parameter, valueAround * 10.0);
                m->simulate(130, E); break;}
            // cheating: finishing by the original parameter value to restore the good one
            case ParamDefault:{
                m->setParam(parameter, valueAround);
                cerr << " value for param " << m->getParamName(parameter) << " is " << valueAround << endl;
                m->simulate(130, E); break;}
            }
            m->setOverrider(NULL);
        }
    }
};



#endif // EXPERIMENTSTHALL_H
