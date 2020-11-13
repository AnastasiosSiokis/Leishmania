#ifndef modeleLeishmania_h
#define modeleLeishmania_h
#include "../../Moonfit/moonfit.h"

// A list of backgrounds that can be simulated by the model.
namespace Back {enum : long long {WT= 1};}


// double the model size: 1/ parameters 2/ coefficients for each parameter
struct modelExtended : public Model {
    enum twoChoices{WT, ApplyCoefficients};
    // this model will have twice the number of parameters
    // 1- parameters of the base model
    // 2- a coefficient for each parameter, default value 1

    int baseNbParameters;
    Model* baseModel;

    modelExtended(Model* _baseModel);

    long long background;

    virtual void updateDerivedVariables(double _t){
         return baseModel->updateDerivedVariables(_t);
    }

    virtual void derivatives(const vector<double> &x, vector<double> &dxdt, const double _t){
        return baseModel->derivatives(x, dxdt, _t);
    }

    void initialise(long long _background = WT);

    void setBaseParameters(){
          if(!baseModel) return;
          baseModel->setBaseParameters();
          for(int i = 0; i < baseNbParameters; ++i){
              params[i] = baseModel->getParam(i);
              params[baseNbParameters+i] = 1.0;
          }
          setBaseParametersDone();
    }

    void action(string name, double parameter){
        baseModel->action(name, parameter);
    }

};

struct modeleLeishmania : public Model {
    modeleLeishmania();
    enum{k_Mrec0,
         alpha,
         S_M,

         k_i,
         k_a,
         k_ai,
         k_ia,
         k_P,
         k_r,
         k_D,

         d_M,
         d_Mi,
         d_Mia,
         d_Ma,
         d_P,

         C_P,
         C_im,

         beta,

         C_iP,

         initM, initMi, initMia, initMa, /*initMatot,*/ initP, initD, //ObserveTime, initDyingP, ObserveProlifTime, initProliferationP,
         //Delay,
         NbParameters};

    enum{Mac, Mi, Mia, Ma, /*Matot,*/ P, D, /*DyingP, ProliferationP,*/ NbVariables};

    long long background; // for different models / options of simulation
    virtual void updateDerivedVariables(double _t);
    virtual void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
    void initialise(long long _background = Back::WT);
	void setBaseParameters();

    void action(string name, double parameter){
        if(!name.compare("wash")){
            if((parameter > 1.0) || (parameter < 0)) {cerr << "ERR: ModeleMinLatent::action(" << name << ", " << parameter << "), wrong parameter value\n"; return;}
            // val[IL2] =    (1 - parameter) * val[IL2]; // example of how the hell it works
            return;
        }
    }
};

struct model1 : public modeleLeishmania {
   model1() : modeleLeishmania(){ name = string("model 1"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model1Dimensionless : public modeleLeishmania {
   model1Dimensionless() : modeleLeishmania(){ name = string("model 1 D"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};

struct model1Fixed : public modeleLeishmania {
   model1Fixed() : modeleLeishmania(){ name = string("model 1 Fixed"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};

struct model2 : public modeleLeishmania {
   model2() : modeleLeishmania(){ name = string("model 2"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model3 : public modeleLeishmania {
   model3() : modeleLeishmania(){ name = string("model 3"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model4 : public modeleLeishmania {
   model4() : modeleLeishmania(){ name = string("model 4"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model5 : public modeleLeishmania {
   model5() : modeleLeishmania(){  name = string("model 5"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model6 : public modeleLeishmania {
   model6() : modeleLeishmania(){  name = string("model 6"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};

struct modelToy : public modeleLeishmania {
   modelToy() : modeleLeishmania(){ name = string("model Toy"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
#endif

