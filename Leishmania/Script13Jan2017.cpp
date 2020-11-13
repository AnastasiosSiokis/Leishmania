#define UseMainLeishmania
#ifdef UseMainLeishmania

// ------------- Step 1: Include Moonfit. "moonfit.h" is enough to use the full library
#include "../Moonfit/moonfit.h"

// Note: You might want to have a look at Moonfit/common.h, (same location as Moonfit.h)
// The file common.h is already included from Moonfit.h and checks the system
//  -> it creates #define WINDOWS/UNIX/MAC and #define QT4/QT5 automatically if you need to use.
//  -> You can choose to compile without graphical interface nor Qt, then define WITHOUT_QT in common.h
//  -> It also defines useful functions (all platforms) like:
//            string createFolder(string folderName)
//            string currentDir()
//            string getParentFolder(string dir)
//            vector<string> listSubDirectories(string dir)
//            string codeTime()
//            void compileLatex(string folderRes, string texFile)
//            string printVector(vector<double> &v)
//  -> It gives predefined options for optimizers (for doing optimizations manually)
//            enum typeOptimizer {GeneticFast, SRESFast, Genetic25k,  ... SRES100k, ...
//            string optFileHeader(typeOptimizer toUse)





// ------------- Step 2: Now including all your models for the project, and the experiments defining what to do with them

#include "Models/modeleLeishmaniaMajor.h"
#include "expLeishmania.h"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

string folder;
string folderBaseResults;

// Note: you can define them manually. But not recommended as the main function already finds folders
// automatically, so you can move the project (better)
//      #define folder string("C:/Users/...")
//      #define defaultfolderBaseResults string("/home/phr13/...")


// declares the script functions that is defined lower
void bacicScriptLeishmania(int nb = -1,string newConfigFile = string(""), string newParameterSet = string(""));




/// @brief Main : to get help, launch without any argument. Graphical window will open, and when quitted, all options will be displayed.
int main(int argc, char *argv[]){

    /* Default RSS and NO_NORM
    enum{ SQUARE_COST, SQUARE_COST_STD, LOG_COST, PROPORTION_COST};
    enum{ NO_NORM, NORM_AVERAGE, NORM_NB_PTS, NORM_AVG_AND_NB_PTS, NORM_MAX, NORM_MAX_AND_NB_PTS};
    void setTypeCost(int _typeCost);
    void setTypeNorm(int _typeNorm);*/

    setTypeCost(SQUARE_COST); //SQUARE_COST
    setTypeNorm(NORM_MAX);

    cout << costConfig::CurrentCost();


    // ------------------ Step 3b finding folders when starting ...

    // 1- finds where the Sources/ folder is,
    string sourceFolder;
    #ifndef MAC
    sourceFolder = getParentFolder(currentDir()) /*+ string("Leishmania/")*/;
    if(!dirExists(sourceFolder)) sourceFolder = currentDir() /*+ string("Leishmania/")*/;   // i.e. 'try again !'
    if(!dirExists(sourceFolder)) cerr << "!! ERR: could not locate where are the files of your project. !! " << endl << "   ... " << sourceFolder << " doesn't exist" << endl;
    #else // MAC with QtCreator tends to put the files ***inside the application*** within subfolders /MACOS/content or so
    sourceFolder = getParentFolder(getParentFolder( getParentFolder(  getParentFolder(  currentDir() ))))  + string("Sources/");
    if(!dirExists(sourceFolder)) cerr << "!! ERR: could not locate where are the files of your project. !! " << endl << "   ... " << sourceFolder << " doesn't exist" << endl;
    #endif

    string currentProjectFolder = "Leishmania_July2019"; // you might need this on line 83...

    // 2-Finds/defines the current project folder and creastes a result folder aside Sources, in case.
    folder = sourceFolder + /*currentProjectFolder +*/ "Leishmania/";
    folderBaseResults = sourceFolder + string("Results/"); // Leishmania_Code_31Jan2019/Results/ might need this
    cout << "Working folders now detected: \n   -> Sources/ in " << sourceFolder << "\n   -> Current Project in " << folder << "\n   -> Results can be put in " << folderBaseResults << endl;
    if(!dirExists(folder)) cerr << "!! ERR: I tried to find the folder of this project inside the subfolder " << currentProjectFolder << " but couldn't find it.\n   ... folder was: " << folder << endl;
    if(!dirExists(folderBaseResults.c_str())) createFolder(folderBaseResults);

    // Note: if problems you can also use QCoreApplication::applicationDirPath() or applicationFilePath() but you need to
    // first create a QApplication by  QApplication b(argc, argv);

    // ¨Parsing main arguments for different options
    switch(argc){
        case 0: case 1: {
            string exeName = removeFolderFromFile(string(argv[0]));
            cout << "\n   Welcome !\n" << endl;
            cout << "   -> No option chosen from command line ..." << endl;
            cout << "   -> Other command line options are :\n" << endl;
            cout << "         "  << exeName << " NumScript " << endl;
            bacicScriptLeishmania();
            break;}
        case 2: {
            bacicScriptLeishmania(atoi(argv[1]));
            break;}
        //case 3: {
        //    if(!string(argv[2]).compare(string("option"))) {
        //        otherFunction(atoi(argv[1]));
        //    }
        //    ...
        //    break;}
        default:{cerr << "ERR: Too many arguments given !" << endl;}
    }
    return 0;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///         1 - Basic Script for different thymus models + graphical interface
///
///
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void bacicScriptLeishmania(int nb,string newConfigFile, string newParameterSet){

    // --------- Step 4: Initializing Qt if necessary
    #ifndef WITHOUT_QT
    char *args[] = {(char*)"Moonfit!",NULL};
    int argc = 1;
    QApplication b(argc, args);             // Starts the Qt application
    #endif



    // Here, I just added a graphical selection between different choices, if you like, it just happens if there is no argument when launching
    if(nb < 0){
        // A small code to choose before different options
        vector<string> options = {
            "0 : Model1",
            "1 : Model2",
            "2 : Model3",
            "3 : Model4",
            "4 : Model5"
            "5 : Model6"
        };

        cout << "Available scripts by command line:";
        for(int i = 0; i < (int) options.size(); ++i){
            cout << "   -> " << options[i] << endl;
        }

        #ifndef WITHOUT_QT
        cout << "Now choosing the option by a user dialog\n";
        // Make the list of choices as a list of QStrings for Qt
        QStringList items;
        for(int i = 0; i < (int) options.size(); ++i){
            items << QString(options[i].c_str());
        }

        // Open a small window to chose the option
        bool okPressed = false;
        QString chosenTextParameter = QInputDialog::getItem(NULL, QString("Model Choice."),QString("Please choose the model you would like to simulate among the following options:"), items,9, false, &okPressed);
        if(!okPressed) return; // means Cancel

        // retrieves which text was chosen and saves ID in nb
        for(int i = 0; i < (int) options.size(); ++i){
            if(!(QString(options[i].c_str())).compare(chosenTextParameter)) nb = i;
        }
        if(nb < 0) {cerr << "ERR: couldn't find which option was chosen - should not happen" << endl; return;}
        #else
        cout << "Tip: You need to run with an argument (nr of script) or re-compile without #define WITHOUT_QT in common.h to choose by clicking" << endl;
        return;
        #endif
    }

    cout << "Launching script nr. " << nb << " ... " << endl;


    // ----------- Step 5: Create a model and create an experiment with this model. Good to take a config file as well.
    // --- and --- Step 6: Give experimental data to the experiment.
    Model* currentModel = NULL;
    Experiment* currentExperiment = NULL;

    string configFile = string(); //string("configLMajor.txt");
    string configFileS1 = string(); // string("configLMajor.txt");
    string configFileS2 = string(); //string("configLMajor.txt");

    switch(nb){
        case 100: case 0: case 10: { currentModel = new model1();
        configFile=string("M1_HighDose.txt"); //M1_LowDose
        break;}
        case 20: { currentModel = new model1();
        configFileS1=string("M1_HighDose.txt"); //M1_LowDose
        break;}
        case 101: case 1: case 11: { currentModel = new model2();
        configFile=string("M2_HighDose.txt"); //M2_LowDose
        break;}
        case 21: { currentModel = new model2();
        configFileS1=string("M2_HighDose.txt"); //M2_LowDose
        break;}
        case 102: case 2: case 12: { currentModel = new model3();
        configFile=string("M3_HighDose.txt"); //M3_LowDose
        break;}
        case 22: { currentModel = new model3();
        configFileS1=string("M3_HighDose.txt"); //M3_LowDose
        break;}
        case 103: case 3: case 13: { currentModel = new model4();
        configFile=string("M4_HighDose.txt");  //M4_LowDose
        break;}
        case 23: { currentModel = new model4();
        configFileS1=string("M5_HighDose.txt"); //M4_LowDose
        break;}
        case 104: case 4: case 14: { currentModel = new model5();
        configFile=string("M5_HighDose.txt");  //M5_LowDose
        break;}
        case 24: { currentModel = new model5();
        configFileS1=string("M5_HighDose.txt"); //M5_LowDose
        break;}
        case 105: case 5: case 15: { currentModel = new model6();
        configFile=string("M6_HighDose.txt");  //M6_LowDose
        break;}
        case 25: { currentModel = new model6();
        configFileS1=string("M6_HighDose.txt"); //M6_LowDose
        break;}
    }

    cout << "   -> Using model : " << currentModel->name << "\n";

    currentModel->setBaseParameters(); // i think it's useless, but never bad

    // choice normal
    currentExperiment = new expLMajor(currentModel); // if i want to perturb only one parameter -> instead of this line i use the following

// choice double parameters for expDoubleLMajor model
//    modelExtended* doubleModel = new modelExtended(currentModel);
//    doubleModel->setBaseParameters();
//    currentExperiment = new expDoubleLMajor(doubleModel);
//    currentExperiment = new expLMajor(currentModel); // needs the correct configuration file...

//    currentExperiment =  new PerturbParam(currentModel, modeleLeishmania::k_a, currentModel->getParam(modeleLeishmania::k_a));




    // ======= Giving data to the evaluators of the experiment class (for getting a cost later & knowing what to record) ========

    TableCourse* Data = new TableCourse(folder + string("DATA/Data_HighDose.txt"));
//    TableCourse* DataNew = new TableCourse(folder + string("DATA/Data_LowDose.txt"));
    TableCourse* DataStd = new TableCourse(folder + string("DATA/Data_HighDose_sem.txt"));
//    TableCourse* DataNewStd = new TableCourse(folder + string("DATA/Data_LowDose_sem.txt"));
//    currentExperiment->giveData(Data, expLMajor::Small_Dose);
    currentExperiment->giveData(Data, expDoubleLMajor::Small_Dose, DataStd);     // with stddev:
//    currentExperiment->giveData(DataNew, expDoubleLMajor::Small_Dose, DataNewStd);     // with stddev:
//    currentExperiment->giveData(DataNew, expDoubleLMajor::Big_Dose, DataNewStd);     // with stddev:
    currentExperiment->loadEvaluators();


// For blockade experiments
//    currentExperiment = new expLMajor_Blocking((modeleLeishmania*) currentModel); // needs the correct configuration file...
//    currentExperiment->giveData(Data, expDoubleLMajor::Small_Dose, DataStd);
//    currentExperiment->giveData(DataNew, expLMajor_Blocking::Control, DataNewStd);     // with stddev:
    currentExperiment->loadEvaluators();


    bool useSplines = false;                  // false = linear interpolation, true = cubic splines
    overrider* OverData = new overrider(Data, useSplines);    // Note : never create overrider as a non pointer, to be used by the graphical interface because they will be erased when function closes and gives control to the interface --> use a pointer and new ...
    currentExperiment->setOverrider(expDoubleLMajor::Small_Dose, OverData);
//    overrider* OverDataNew = new overrider(DataNew, useSplines);    // Note : never create overrider as a non pointer, to be used by the graphical interface because they will be erased when function closes and gives control to the interface --> use a pointer and new ...
//    currentExperiment->setOverrider(expDoubleLMajor::Big_Dose, OverDataNew);

    //cerr << OverData->print();


    // normally, this is defined by the switch before

    if(newConfigFile.length() > 0) configFile = newConfigFile;


    if(newConfigFile.size() > 0)   {configFile = newConfigFile; cout << "   -> forcing configuration : " << newConfigFile << endl;}
    if(newParameterSet.size() > 0)  {
        cout << "   -> forcing parameter set : " << newParameterSet << endl;
        currentModel->loadParameters(newParameterSet);
    }


    currentExperiment->simulateAll(true);
    cout << currentExperiment->costReport() << endl;
    //exit(-1);







    // =============== Scripts 0, 1, 2, 3, 4, 5.... < 10 : no optimization, only launches the GUI ================

    if(nb < 10){
        #ifndef WITHOUT_QT
        simuWin* p = new simuWin(currentExperiment);
        cout << "Launching Graphical Interface ..." << endl;
        p->loadConfig(folder + configFile);
        if(newParameterSet.length() > 0) currentModel->loadParameters(newParameterSet);
        p->show();
        p->simulate();
        b.exec(); // leaves the hand to Qt,
        #else
        cout << "Script finished (without qt, because WITHOUT_QT was defined)\n";
        #endif
        return;
    }

    if(nb > 99){
         MultiExperiments* soupExperiments = new MultiExperiments(currentModel);
        // ======= Giving data to the evaluators of the experiment class (for getting a cost later & knowing what to record) ========
        soupExperiments->AddExperiment(currentExperiment);

        InitialPopulation * Experiment2 = new InitialPopulation(currentModel);
        Experiment2->giveData(Data, InitialPopulation::DoseDefault);
//        currentExperiment->giveData(Data, expLMajor::Small_Dose, DataStd);
        // does not exist anymore Experiment2->giveHowToReadNamesInKinetics(GlobalNamesVariables);
        Experiment2->loadEvaluators();
        soupExperiments->AddExperiment(Experiment2);

        {
            manageSims* p = new manageSims(soupExperiments);
            p->loadConfig(folder + configFile);
//            TableCourse* Data = new TableCourse(folder + string("DATA/Data_2019new.txt"))
        }
        for(int i = 0; i < modeleLeishmania::NbParameters; ++i){
            //Modele* support = new model1();
            PerturbParam * ExperimentParam1 = new PerturbParam(currentModel, i /*modeleLeishmania::k_a*/, currentModel->getParam(i));
            ExperimentParam1->giveData(Data, PerturbParam::ParamDefault);
            //currentExperiment->giveData(Data, Small_Dose, DataStd);
            // useless now: ExperimentParam1->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            ExperimentParam1->loadEvaluators();
            soupExperiments->AddExperiment(ExperimentParam1);
        }
#ifndef WITHOUT_QT
        simuWin* p = new simuWin(soupExperiments);
        cout << "Launching Graphical Interface ..." << endl;
        p->loadConfig(folder + configFile);
        if(newParameterSet.length() > 0) currentModel->loadParameters(newParameterSet);
        p->show();
#else
        cout << "Script finished (without qt, because WITHOUT_QT was defined)\n";
#endif
        b.exec();
        return;
    }


    // =============== Create folder for scripts requiring optimization or more ================
    stringstream fres; fres << folderBaseResults << currentModel->name << "_scr" << nb << "_" << codeTime() << "/";           // Define working directory (name = "sim" + date)
    //stringstream fres; fres << folderBaseResults << "2step_" << currentModel->name << "_scr" << nb << "_" << codeTime() << "/";           // Define working directory (name = "sim" + date)
    string folderRes = fres.str();
    createFolder(folderRes);


    // =============== Optimization options ... ================
#define TESTINGMODE false

    stringstream headerOptimizer;                                                   // each further script might use different optimizer options, will be stored in the following stringstream
    if(TESTINGMODE) headerOptimizer << optFileHeader(GeneticFast);
    else headerOptimizer << optFileHeader(Genetic500k);

    if(nb < 20) cout << "configFile:" << configFile << endl;
    else {
        cout << "configFileS1:" << configFileS1 << endl;
        cout << "configFileS2:" << configFileS2 << endl;
    }

    // ========== Takes a config, optimizes all configurations separately ===========

    switch(nb){ // fitting
    case 10: case 11: case 12: case 13: case 14: case 15: case 16:  {

        manageSims* msi = new manageSims(currentExperiment);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.

        msi->loadConfig(folder + configFile);                       // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one
        vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later


        for(int i = 0; i < msi->nbCombs; ++i){
            cerr << "Optimize combination" << i << endl;
            stringstream codeSimu;      codeSimu << "CombNr" << i << "-" << codeTime();               // generates a text code for this particular optimization, in case parallel optimizations are running
            stringstream folderComb;    folderComb << folderRes << codeSimu.str() << "/";        // creates a folder for this particular optimization, to create figures etc ...
            createFolder(folderComb.str());

            cout << "   -> Optimizing combination (" << i << ") with ID: " << codeSimu.str() << "\n";

            // re-takes the initial parameter set because parameters were probably changed by previous optimization for parameters that will not necessarily be optimized/modified in the next combinations
            msi->resetParamSetFromConfig(folder + configFile);

            // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
            currentExperiment->m->setPrintMode(false, 1);
            //currentExperiment->m->dt = 0.001;

            // creates the optimizer file for the combination of parameters to optimize, using boundaries from the configuration file, and the header from headeroptimizer
            string optOptions = msi->motherCreateOptimizerFile(i, headerOptimizer.str());       // for each combination, will need to re-create an optimizer file
            ofstream f1((folderComb.str() + string("Optimizer.txt")).c_str(), ios::out); if(f1) {f1 << optOptions << "\n"; f1.close();}

            // Optimize (using the data stated by this combination) !
            msi->motherOverrideUsingComb(i);                                                    // chose the variables to simulate and to replace by data according to this combination
            msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);              // DOES THE OPTIMIZATION !!!, and records the 1000 best sets

            // saves the best sets of parameters
            msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
            listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

            // if QT allowed, generates the plots for this best set
            #ifndef WITHOUT_QT
            simuWin tempWindow(currentExperiment);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...

            //tempWindow.loadConfig(folder + configFile);
            //tempWindow.useComb(i);// takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            //tempWindow.motherOverrideUsingComb(i);

            tempWindow.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
            tempWindow.useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            tempWindow.simulate();
            tempWindow.makeFigReportParamSet(folderComb.str());
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f3) {f3 << tempWindow.costRecords.print() << "\n"; f3.close();}
            #else
            msi->useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            msi->simulate();
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization.txt") + codeSimu.str()).c_str(), ios::out); if(f3) {f3 << msi->costRecords.print() << "\n"; f3.close();}
            #endif
        }
        break;
    }   // end case

   // ----------------- Scripts 2x : Fit first combination, put fitted parameters into the second, fitte, put parameters in the third, etc ...

    case 20: case 21: case 22: case 23: case 24: case 25: case 26: {

        manageSims* msi = new manageSims(currentExperiment);
        msi->loadConfig(folder + configFileS1);

        // ----------------- Part 1 : for each combination (parameters-variables), do a fitting -----------------------

        for(int i = 0; i < msi->nbCombs; ++i){
            cerr << "Optimize combination" << i << endl;
            stringstream codeSimu;      codeSimu << "CombNr" << i << "-" << codeTime();               // generates a text code for this particular optimization, in case parallel optimizations are running
            stringstream folderComb;    folderComb << folderRes << codeSimu.str() << "/";        // creates a folder for this particular optimization, to create figures etc ...
            createFolder(folderComb.str());
            cout << "   -> Optimizing combination (" << i << ") with ID: " << codeSimu.str() << ", using parameters from previous one\n";

            // re-takes the initial parameter set because parameters were probably changed by previous optimization for parameters that will not necessarily be optimized/modified in the next combinations
            // DO NOT RESET, because will use parameters from the previous combination
            //msi->resetParamSetFromConfig(folder + configFile);

            // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
            currentExperiment->m->setPrintMode(false, 1);
            //currentExperiment->m->dt = 0.001;

            // creates the optimizer file for the combination of parameters to optimize, using boundaries from the configuration file, and the header from headeroptimizer
            string optOptions = msi->motherCreateOptimizerFile(i, headerOptimizer.str());       // for each combination, will need to re-create an optimizer file
            ofstream f1((folderComb.str() + string("Optimizer.txt")).c_str(), ios::out); if(f1) {f1 << optOptions << "\n"; f1.close();}

            // Optimize (using the data stated by this combination), and uses best parameter for next combination
            msi->motherOverrideUsingComb(i); // for the last round, fits with all (previously fitted) parameters and all (previously used) variables // chose the variables to simulate and to replace by data according to this combination
            msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);              // DOES THE OPTIMIZATION !!!, and records the 1000 best sets
            msi->useParamSetFromHistory(0); // loads the best parameter

            // saves the best sets of parameters
            msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
            //listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

            // if QT allowed, generates the plots for this best set
            #ifndef WITHOUT_QT
            simuWin tempWindow(currentExperiment);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...
            //tempWindow.loadConfig(folder + configFileS1);
            //tempWindow.useComb(i);// takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            //tempWindow.motherOverrideUsingComb(i);
            tempWindow.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
            tempWindow.useParamSetFromHistory(0);
            tempWindow.simulate();
            tempWindow.makeFigReportParamSet(folderComb.str());
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f3) {f3 << tempWindow.costRecords.print() << "\n"; f3.close();}
            #else
            msi->useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            msi->simulate();
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization.txt") + codeSimu.str()).c_str(), ios::out); if(f3) {f3 << msi->costRecords.print() << "\n"; f3.close();}
            #endif
        }


        vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later


        // 'around' the parameter set, means allowing the parameters to vary +/- a certain percent of the value of the parameter set. Will optimize with different percents :
        vector<double> best = currentModel->getParameters();
        vector<double> percents = {90.0, 75.0, 50.0, 25.0, 10.0, 5.0, 2.0, 1.0};

        for(int k = 0; k < (int) percents.size(); ++k){

            stringstream codeSimu; codeSimu << "Percents(" << percents[k] << ")-" << codeTime();             // generates a text code for this particular optimization, in case parallel optimizations are running
            stringstream folderComb; folderComb << folderRes << codeSimu.str() << "/";                           // creates a folder for this particular optimization, to create figures etc ...
            createFolder(folderComb.str());
            cout << "   -> Optimizing " << percents[k] << " % around the best parameter set, with ID: " << codeSimu.str() << "\n";

            // set the boundaries for each parameter to best set +/- percent around. Note that here, should not start from the parameter set in the configuration, but rather the best one
            int NP = currentModel->getNbParams();
            currentModel->setParameters(best);
            for(int i = 0; i < NP; ++i){
                if(std::isnan(best[i]) || std::isinf(best[i])) best[i] = 1e12;
                double newLow  = best[i] * (1.0 - (percents[k] / 100.0));
                double newHigh = best[i] * (1.0 + (percents[k] / 100.0));
                //if(newLow > currentModel->getUpperBound(i)) newLow = currentModel->getLowerBound(i);
                //if(newHigh < currentModel->getLowerBound(i)) newHigh = currentModel->getUpperBound(i);
                //currentModel->setBounds(i, max(currentModel->getLowerBound(i), newLow) , min(currentModel->getUpperBound(i), newHigh));
                currentModel->setBounds(i, newLow ,newHigh);
            }
            msi->updateConfigParamsFromModel();
            stringstream conf_name;
            conf_name << folderRes << "configGlobalFor" << percents[k] << ".txt";
            msi->saveConfig(conf_name.str());

            // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
            currentExperiment->m->setPrintMode(false, 5000); // nt printing anything for optimizing
            //currentExperiment->m->dt = 10; // now defined into the model

            // creates the optimizer file for the combination of parameters to optimize, using boundaries from the configuration file, and the header from headeroptimizer
            string optOptions = msi->motherCreateOptimizerFile(-1, headerOptimizer.str());      // for each combination, will need to re-create an optimizer file. Note : this function uses the boundaries in the configuration, not from the model ...
            ofstream f1((folderComb.str() + string("Optimizer.txt")).c_str(), ios::out); if(f1) {f1 << optOptions << "\n"; f1.close();}

            // Optimize (all the parameters from all the configurations) !
            msi->motherOverrideUsingComb(-1);                                                   // chose the variables to simulate and to replace by data according to all cobinations
            msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);              // DOES THE OPTIMIZATION !!!, and records the 1000 best sets

            // saves the best sets of parameters
            msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
            listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

            // if QT allowed, generates the plots for this set
            #ifndef WITHOUT_QT
            simuWin tempWindow2(currentExperiment);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...
            tempWindow2.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
            tempWindow2.useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            tempWindow2.simulate();
            tempWindow2.makeFigReportParamSet(folderComb.str());
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f3) {f3 << tempWindow2.costRecords.print() << "\n"; f3.close();}
            #else
            // selects the best set of parameters, runs a simulation and saves simulation versus data
            msi->useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            msi->simulate();
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization.txt") + codeSimu.str()).c_str(), ios::out); if(f3) {f3 << msi->costRecords.print() << "\n"; f3.close();}
            #endif

        }
        break;


        break;
    } // end case





    //} // end switch -> moved after IDENTIFIABILITY
//} function continues



    // ----------------- Part 4 : Identifiability -----------------------

    case 30: case 31: case 32: case 33: case 34: case 35:{

        manageSims* msi = new manageSims(currentExperiment);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.
        msi->loadConfig(folder + configFile);                       // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one
        //vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later

        // ----------------- Part 1 : for each combination (parameters-variables), do a fitting -----------------------

        for(int i = 0; i < msi->nbCombs; ++i){

            stringstream codeSimu;      codeSimu << "IdentCombNr" << i << "-" << codeTime();               // generates a text code for this particular optimization, in case parallel optimizations are running
            stringstream folderComb;    folderComb << folderRes << codeSimu.str() << "/";                        // creates a folder for this particular optimization, to create figures etc ...
            createFolder(folderComb.str());

            cout << "Identifiability for combination (" << i << ") with ID: " << codeSimu.str() << "\n";

            // re-takes the initial parameter set because parameters were probably changed by previous optimization for parameters that will not necessarily be optimized/modified in the next combinations
            msi->resetParamSetFromConfig(folder + configFile);
            vector<double> initialSet = currentModel->getParameters();

            // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
            currentExperiment->m->setPrintMode(false, 5000);
            //currentExperiment->m->dt = 0.002;

            msi->motherOverrideUsingComb(i);
            vector<int> paramsInConfig = msi->parametersInConfig(i);
            for(int j = 0; j < (int) paramsInConfig.size(); ++j){
                int p = paramsInConfig[j];

                msi->prepareOptFilesForIdentifibiality(folderRes, p, i, headerOptimizer.str());
                msi->motherIdentifiability(initialSet, p);  // the parameters will be applied inside this function

                oneParameterAnalysis* opa = msi->identifiabilities[p];
                string res = opa->print();
                stringstream fname; fname << folderComb.str() << "resIdentifiabilityForParam" << p << ".txt";
                fstream fp(fname.str(), ios::out); if(fp) {fp << res; fp.close();}
                msi->makeIdentifibialityReport(p, folderComb.str(), i);
                cout << "      ... Details saved in " << fname.str() << endl;
                /*
                // saves the best sets of parameters
                msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
                listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

                // if QT allowed, generates the plots for this best set
                #ifndef WITHOUT_QT
                simuWin tempWindow(currentExperiment);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...
                tempWindow.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
                tempWindow.useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
                tempWindow.simulate();
                tempWindow.makeFigReportParamSet(folderComb.str());
                ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
                ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f3) {f3 << tempWindow.costRecords.print() << "\n"; f3.close();}
                #else
                msi->useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
                msi->simulate();
                ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
                ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization.txt") + codeSimu.str()).c_str(), ios::out); if(f3) {f3 << msi->costRecords.print() << "\n"; f3.close();}
                #endif
            */
            /*}
        }
        break;
    }

    } // end switch */

    cout << "   -> Script " << nb << " finished !\n   _____________________________________________________________\n";
                }
            }
        }
    }
}


#endif
