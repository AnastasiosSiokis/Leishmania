#include "modeleLeishmaniaMajor.h"



//int baseNbParameters;
//Model* baseModel;

modelExtended::modelExtended(Model* _baseModel) : baseNbParameters(_baseModel->getNbParams()), baseModel(_baseModel), Model(_baseModel->getNbVars(), 2*_baseModel->getNbParams()), background(modelExtended::WT) {
    name = string("Extended ") + baseModel->name;
    dt = baseModel->dt; // initial time step -> then it is adaptive
    print_every_dt = baseModel->print_every_dt;

    // new model has same variables with same meaning
    for(int i = 0; i < baseModel->getNbVars(); ++i){
        names[i] = baseModel->names[i];
        extNames[i] = baseModel->extNames[i];
    }

    // but twice the number of parameters, because second half are coefficients
    for(int i = 0; i < baseNbParameters; ++i){
        paramNames[i] = baseModel->paramNames[i];
        paramNames[baseNbParameters+i] = string("Coeff ") + baseModel->paramNames[i];

        setBounds(i,  baseModel->getLowerBound(i), baseModel->getUpperBound(i));
        setBounds(baseNbParameters + i, 00001, 100000);
     }
}

void modelExtended::initialise(long long _background){ // don't touch to parameters !

//    if((background != modelExtended::WT) && (background != _background)){
//        cerr << "WRN : modelExtended::initialize, when the background has been changed from WT, you should not change it again, because parameters can not be retrieved. Please load parameters again" << endl;
//    }
    background = _background;

    switch (background) {
    case WT:{
        for(int i = 0; i < baseNbParameters; ++i){
            baseModel->setParam(i, params[i]);
        }
        break;
    }

    case ApplyCoefficients:{
        for(int i = 0; i < baseNbParameters; ++i){
            baseModel->setParam(i, params[baseNbParameters+i] * params[i]);
            //cout << " parameter " << baseModel->getParamName(i) << " original" << params[i] << " applied " << baseModel->getParam(i) << endl;
        }
        break;
    }


    default:
        break;
    }

    baseModel->initialise();
    for(int i = 0; i < baseModel->getNbVars() ; ++i){
        val[i] = baseModel->val[i];}
    t = 0;
    initialiseDone();
}

modeleLeishmania::modeleLeishmania() : Model(NbVariables, NbParameters), background(Back::WT) {
    name = string("modeleLeishmania");
    dt = 0.005; // initial time step -> then it is adaptive

    // TAG PHI
    //print_all_secs = 1200; //every how many seconds it is plotting
    print_every_dt = 0.1;

    // Name of variables
    names[Mac] = string("Macrophages");
    names[Mi] = string("Macrophages infected");
    names[Mia] = string("Macrophages infected activated");
    names[Ma] = string("Macrophages activated");
//    names[Matot] = string("Macrophages activated total");
    names[P] = string("Parasite");
    names[D] = string("Delay");
//    names[DyingP] = string("Dying Parasite");
//    names[ProliferationP] = string("Proliferating Parasite");
	
	// the names of variables that can be accessed by outside (global name-space)
    extNames[Mac] = "Mac";
    extNames[Mi] = "Mi";
    extNames[Mia] = "Mia";
    extNames[Ma] = "Ma";
//    extNames[Matot] = "Matot";
    extNames[P] = "P";
    extNames[D] = "D";
//    extNames[DyingP] = "DyingP";
//    extNames[ProliferationP] = "ProliferationP";

	// Name of parameters

    paramNames[k_Mrec0] = "1. Basal recruitment rate";
    paramNames[alpha] 	= "2. alpha";
    paramNames[S_M] 	= "3. S_M";

    paramNames[k_i] 	= "4. k_i  - infection";
    paramNames[k_a] 	= "5. k_a  - activation";
    paramNames[k_ai] 	= "6. k_ai - activation of infected";
    paramNames[k_ia] 	= "7. k_ia - infection of activated";
    paramNames[k_P] 	= "8. k_P";
    paramNames[k_r] 	= "9. k_r";
    paramNames[k_D] 	= "10. k_D";

    paramNames[d_M] 	= "11. death rate M";
    paramNames[d_Mi] 	= "12. death rate Mi";
    paramNames[d_Mia] 	= "13. death rate Mia";
    paramNames[d_Ma] 	= "14. death rate Ma";
    paramNames[d_P] 	= "15. death rate P";

    paramNames[C_P] 	= "16. C_P";
    paramNames[C_im] 	= "17. C_im";

    paramNames[beta] 	= "18. beta";

    paramNames[C_iP] 	= "19. C_iP";

    paramNames[initM]   = "20. initial M";
    paramNames[initMi]  = "21. initial Mi";
    paramNames[initMia] = "22. initial Mia";
    paramNames[initMa]  = "23. initial Ma";
//    paramNames[initMatot]  = "24. initial Matot";
    paramNames[initP]   = "24. initial P";
    paramNames[initD]   = "25. initial D";
//    paramNames[ObserveTime]= "26. observation time";
//    paramNames[initDyingP]= "27. Initial DyingP";
//    paramNames[ObserveProlifTime]= "28. observation prolif time";
//    paramNames[initProliferationP]= "29. Initial ProliferationP";
//----------------------------------------------------------------------
    paramLowBounds[k_Mrec0] = 1e0;
    paramLowBounds[alpha]   = 1e0;
    paramLowBounds[S_M]     = 1e0;

    paramLowBounds[k_i] 	= 1e-3;
    paramLowBounds[k_a] 	= 1e-3;
    paramLowBounds[k_ai] 	= 1e-3;
    paramLowBounds[k_ia] 	= 1e-3;
    paramLowBounds[k_P] 	= 1e-3;
    paramLowBounds[k_r] 	= 1e-3;
    paramLowBounds[k_D] 	= 1e-3;

    paramLowBounds[d_M] 	= 1e-3;
    paramLowBounds[d_Mi] 	= 1e-3;
    paramLowBounds[d_Mia] 	= 1e-3;
    paramLowBounds[d_Ma] 	= 1e-3;
    paramLowBounds[d_P] 	= 1e-3;

    paramLowBounds[C_P] 	= 1e0;
    paramLowBounds[C_im] 	= 1e0;

    paramLowBounds[beta] 	= 1e-3;

    paramLowBounds[C_iP] 	= 1e0;

    paramLowBounds[initM] 	= 1e-3;
    paramLowBounds[initMi] 	= 1e-3;
    paramLowBounds[initMia] = 1e-3;
    paramLowBounds[initMa] 	= 1e-3;
//    paramLowBounds[initMatot] 	= 1e-3;
    paramLowBounds[initP] 	= 1e-3;
    paramLowBounds[initD] 	= 1e-6;
//    paramLowBounds[ObserveTime]= 1e-3;
//    paramLowBounds[initDyingP]= 1e-3;
//    paramLowBounds[ObserveProlifTime]= 1e-3;
//    paramLowBounds[initProliferationP]= 1e-3;
//-------------------------------------------------------------------
    paramUpBounds[k_Mrec0] 	= 1e5;
    paramUpBounds[alpha] 	= 1e4;
    paramUpBounds[S_M]      = 1e5;

    paramUpBounds[k_i]      = 1e4;
    paramUpBounds[k_a]      = 1e4;
    paramUpBounds[k_ai]     = 1e4;
    paramUpBounds[k_ia]     = 1e4;
    paramUpBounds[k_P]      = 1e4;
    paramUpBounds[k_r]      = 1e4;
    paramUpBounds[k_D]      = 1e4;

    paramUpBounds[d_M] 	    = 1e5;
    paramUpBounds[d_Mi] 	= 1e5;
    paramUpBounds[d_Mia] 	= 1e5;
    paramUpBounds[d_Ma] 	= 1e5;
    paramUpBounds[d_P]  	= 1e5;

    paramUpBounds[C_P] 	= 1e5;
    paramUpBounds[C_im] = 1e5;

    paramUpBounds[beta]	= 1e4;

    paramUpBounds[C_iP]	= 1e5;

    paramUpBounds[initM] 	= 1e5;
    paramUpBounds[initMi] 	= 1e5;
    paramUpBounds[initMia] 	= 1e5;
    paramUpBounds[initMa] 	= 1e5;
//    paramUpBounds[initMatot] 	= 1e5;
    paramUpBounds[initP]  	= 1e5;
    paramUpBounds[initD]  	= 1e2;
//    paramLowBounds[ObserveTime]= 1e5;
//    paramLowBounds[initDyingP]= 1e5;
//    paramLowBounds[ObserveProlifTime]= 1e5;
//    paramLowBounds[initProliferationP]= 1e5;
}

void modeleLeishmania::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    params[k_Mrec0] = 1500.2;
    params[alpha]   = 4500;
    params[S_M]     = 2524.4;

    params[k_i] 	= 3.57305e-07;
    params[k_a] 	= 962.72;
    params[k_ai] 	= 962.72;
    params[k_ia] 	= 1.04755e-06;
    params[k_P] 	= 0.0001562;
    params[k_r] 	= 0.0008;
    params[k_D] 	= 5.081e-07;

    params[d_M] 	= 0.00692693;
    params[d_Mi] 	= 0.01484;
    params[d_Mia] 	= 6.59742;
    params[d_Ma] 	= 1.39862;
    params[d_P] 	= 0.0984523;

    params[C_P] 	= 173088;
    params[C_im] 	= 13.7592;

    params[beta] 	= 1.5;

    params[C_iP] 	= 1e3;

    params[initM] 	= 92693;
    params[initMi] 	= 0.0;
    params[initMia] = 0.0;
    params[initMa] 	= 0.0;
//    params[initMatot] 	= 0.0;
    params[initP] 	= 9845.23;
    params[initD] 	= 9.23;

//    params[ObserveTime]= 0.5;
//    params[initDyingP]= 0.5;
//    params[ObserveProlifTime]= 0.5;
//    params[initProliferationP]= 0.5;

	setBaseParametersDone();
}

void modeleLeishmania::initialise(long long _background){ // don't touch to parameters !
	val.clear();
    val.resize(NbVariables, 0.0);
	init.clear();
    init.resize(NbVariables, 0.0);

    // test if each possible background is in the current combination of backgrounds (stored in the field background)
    if((background != Back::WT) && (background != _background)){
        cerr << "WRN : modeleLeishmania::initialize, when the background has been changed from WT, you should not change it again, because parameters can not be retrieved. Please load parameters again" << endl;
    }
    background = _background;

    // ex to filter options: if(background == Back::WT){}


    // if the initial values depend on parameters

    // Not normalized----------------------------------------

    init[Mac]   = params[initM];
    init[Ma]    = params[initMa];
    init[Mi]    = params[initMi];
    init[Mia]   = params[initMia];
//    init[Matot] = params[initMatot];
    init[P]     = params[initP];
    init[D]     = params[initD]; // maybe as a parameter is beter -> params[Delay] use a new name //*/s

    //cout << " Pathogens initialized " << params[initP] << endl;
//    init[DyingP]= params[initDyingP];
//    init[ProliferationP]=params[initProliferationP];

    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}

void modeleLeishmania::updateDerivedVariables(double _t){
//---- Model 1 ------------------------------------------------------------------------------------------------------------------------------------
//    val[DyingP] = 100.*(((params[k_r]*val[P]*val[Mia] + params[d_P]*val[P])*params[ObserveTime]) / (val[P]+1e-6));
//    val[ProliferationP] = 100*((params[k_P]*(1 - val[P]/params[C_P])*val[P]*(val[Mi] + val[Mia]))*params[ObserveProlifTime] / (val[P]+1e-6));// for Model 1
//-------------------------------------------------------------------------------------------------------------------------------------------------
//---- Model 2 ------------------------------------------------------------------------------------------------------------------------------------
//    val[DyingP] = 100*(((params[d_P]*val[P])*params[ObserveTime]) / (val[P]+1e-6));                                          // for Model 2
//    val[ProliferationP] = 100*((params[k_P]*(1 - val[P]/params[C_P])*val[P]*(val[Mi] + params[beta]*val[Mia]))*params[ObserveProlifTime] / (val[P]+1e-6));
//-------------------------------------------------------------------------------------------------------------------------------------------------
//---- Model 3 ------------------------------------------------------------------------------------------------------------------------------------
//    val[DyingP] = 100*(((params[k_r]*val[P]*val[Mia] + params[d_P]*val[P])*params[ObserveTime]) / (val[P]+1e-6));            // for Model 3
//    val[ProliferationP] = 100*((params[k_P]*(1 - val[P]/params[C_P])*val[P]*(val[Mi] + params[beta]*val[Mia]))*params[ObserveProlifTime] / (val[P]+1e-6));
//---- Model 4 ------------------------------------------------------------------------------------------------------------------------------------
//    val[DyingP] = 100*(((params[k_r]*val[P]*(val[Mia]+val[Ma]) + params[d_P]*val[P])*params[ObserveTime]) / (val[P]+1e-6));  // for Model 4
//    val[ProliferationP] = 100*((params[k_P]*(1 - val[P]/params[C_P])*val[P]*(val[Mi] + val[Mia]))*params[ObserveProlifTime] / (val[P]+1e-6));
//---- Model 5 ------------------------------------------------------------------------------------------------------------------------------------
//    val[DyingP] = 100*(((params[d_P]*val[P])*params[ObserveTime]) / (val[P]+1e-6));                                          // for Model 5
//    val[ProliferationP] = 100*((params[k_P]*(1 - val[P]/params[C_P])*val[P]*((val[Mi] + val[Mia])/(params[C_iP]+val[Mia]+val[Ma])))*params[ObserveProlifTime] / (val[P]+1e-6));
//---- Model 6 ------------------------------------------------------------------------------------------------------------------------------------
//    val[DyingP] = 100*(((params[k_r]*val[P]*(val[Mia]+val[Ma]) + params[d_P]*val[P])*params[ObserveTime]) / (val[P]+1e-6));  // for Model 6
//    val[ProliferationP] = 100*((params[k_P]*(1 - val[P]/params[C_P])*val[P]*((val[Mi] + val[Mia])/(params[C_iP]+val[Mia]+val[Ma])))*params[ObserveProlifTime] / (val[P]+1e-6));
}

void modeleLeishmania::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

        cerr << "ERROR" << endl;
}

//void model1::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

void model1::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

    if(!over(Mac)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]*x[P]/(params[S_M]*params[S_M] + x[P]*x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

//    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
//        dxdt[Matot] = (params[k_a]*x[Mac] + params[k_ai]*x[Mi])*x[D]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Ma]*x[Ma] - params[d_Mia]*x[Mia];
//        dxdt[Matot] = dxdt[Ma]+dxdt[Mia];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + x[Mia]) - params[k_r]*x[P]*x[Mia] - params[d_P]*x[P];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D]; //(1.8e-06)

//    if(!over(DyingP)) // if it is not overrided by data then make the computaiton below
//        dxdt[DyingP]= 0;
}

void model2::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

// Model 2
    if(!over(Mac)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]*x[P]/(params[S_M]*params[S_M] + x[P]*x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + params[beta]*x[Mia]) - params[d_P]*x[P];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D];

//    if(!over(DyingP)) // if it is not overrided by data then make the computaiton below
//        dxdt[DyingP]= 0;
}


void model3::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

// Model 3
    if(!over(Mac)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]*x[P]/(params[S_M]*params[S_M] + x[P]*x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

//    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
//        dxdt[Matot] = (params[k_a]*x[Mac] + params[k_ai]*x[Mi])*x[D]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Ma]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + params[beta]*x[Mia]) - params[k_r]*x[P]*x[Mia] - params[d_P]*x[P];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D]; //(1.8e-06)

//    if(!over(DyingP)) // if it is not overrided by data then make the computaiton below
//        dxdt[DyingP]= 0;
}


void model4::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

// Model 4
    if(!over(Mac)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]*x[P]/(params[S_M]*params[S_M] + x[P]*x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)){ // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + x[Mia]) - params[k_r]*x[P]*(x[Mia]+params[beta]*x[Ma]) - params[d_P]*x[P];
//        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + x[Mia]) - params[k_r]*x[P]*(x[Mia]+params[beta]*x[Ma]) - params[d_P]*x[P];
    }
//  if you use the above equation, i.e. with a parameter beta multiplying to params[k_r]*x[P]*(x[Mia]+params[beta]*x[Ma]),
//  and setting beta=0 then you get Model 1: Intrisic killing...


    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D]; //(1.8e-06)

//    if(!over(DyingP)) // if it is not overrided by data then make the computaiton below
//        dxdt[DyingP]= 0;
}

void model5::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

// Model 5
    if(!over(Mac)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]*x[P]/(params[S_M]*params[S_M] + x[P]*x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*((x[Mi] + x[Mia])/(params[C_iP]+x[Mia]+x[Ma])) - params[d_P]*x[P];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D]; //(1.8e-06)

//    if(!over(DyingP)) // if it is not overrided by data then make the computaiton below
//        dxdt[DyingP]= 0;
}

void model6::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

// Model 6
    if(!over(Mac)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]*x[P]/(params[S_M]*params[S_M] + x[P]*x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_ai]*x[D]*x[Mi]/(params[C_im] + x[Mia] + x[Ma]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Mia] + x[Ma]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*((x[Mi] + x[Mia])/(params[C_iP]+x[Mia]+x[Ma])) - params[k_r]*x[P]*(x[Mia]+x[Ma]) - params[d_P]*x[P];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D]; //(1.8e-06)

//    if(!over(DyingP)) // if it is not overrided by data then make the computaiton below
//        dxdt[DyingP]= 0;
}
