#include <iostream>
#include <random>
#include <bits/stdc++.h>
using namespace std;

double triangularFuzzification(double x, double a, double b, double c)
{
    double slope;
    double y;
    // (a,b) (b,c)
    slope = (c - b) / (b - a);
    // Y = mx + c
    double k = b - slope * a;
    y = slope * x + k;
    return y;
}

// Trapezoidal fuzzy set fuzzification function
double trapezoidalFuzzification(double x, double a, double b, double c, double d)
{
    double slope;
    double y;
    // (a,b) (d,c)
    slope = (c - b) / (d - a);
    // Y = mx + c
    double k = b - slope * a;
    y = slope * x + k;
    return y;
}

// AND Operator -> returning the minimal value.
double AND(double x, double y)
{
    if (x < y)
        return x;
    return y;
}
// OR Operator -> returning the maximal value
double OR(double x, double y)
{
    if (x > y)
        return x;
    return y;
}

struct FuzzyRules
{
    vector<string> variables;
    vector<pair<string,int>> sets;
    vector<string> ops; // Operator ("AND", "OR", "NOT".)
    vector<string> outVariables;
    vector<pair<string,int>> outSets;

    // Constructor
    FuzzyRules() {}
    FuzzyRules(const vector<string> &variable, const vector<pair<string,int>> &set, const vector<string> &operatorType,
               const vector<string> &outVariable,  vector<pair<string,int>> &s2)
            : variables(variable), sets(set), ops(operatorType), outVariables(outVariable), outSets(s2) {}
    void displayInfo() const
    {
        for(int i=0;i<variables.size();i++) {
            cout << "variables: " << variables[i] << endl;
            cout << "set: " << sets[i].first<<" "<<sets[i].second << endl;
            cout << "ops: " << ops[i] << endl;
        }
        for(int i=0;i<outVariables.size();i++) {
            cout << "outVariables: " << outVariables[i] << endl;
            cout << "outSets: " << outSets[i].first<<" "<<outSets[i].second << endl;
        }
    }
};
struct FuzzySet
{
    string variable;
    string set;
    string type;           // "TRI" for triangle, "TRAP" for trapezoid
    double v1, v2, v3, v4; // Parameters defining the fuzzy set

    // Constructor
    FuzzySet() {}
    FuzzySet(const string &setvariable, const string &setset, const string &setType, double setA, double setB, double setC, double setD)
        : variable(setvariable), set(setset), type(setType), v1(setA), v2(setB), v3(setC), v4(setD) {}
    FuzzySet(const string &setvariable, const string &setset, const string &setType, double setA, double setB, double setC)
        : variable(setvariable), set(setset), type(setType), v1(setA), v2(setB), v3(setC) {}

    void displayInfo() const
    {
        cout << "Fuzzy Set: " << variable << endl;
        cout << "Type: " << type <<endl;
        cout << "Parameters: (" << v1 << ", " << v2 << ", " << v3 << ", " << v4 << ")" << endl;
    }
};

class FuzzyVariable
{
private:
    string name;
    string type; // "IN" for input, "OUT" for output
    double lowerRange;
    double upperRange;
    vector<FuzzySet> FuzzySets;

public:
    // Constructor
    FuzzyVariable() {}

    string getName() const { return name; }
    string getType() const { return type; }
    double getLowerRange() const { return lowerRange; }
    double getUpperRange() const { return upperRange; }

    vector<FuzzySet> &getFuzzySets() { return FuzzySets; }

    void setName(string nam) { name = nam; }
    void setType(string typ) { type = typ; }
    void setLowerRange(double lr) { lowerRange = lr; }
    void setUpperRange(double ur) { upperRange = ur; }

    void addFuzzySet(const FuzzySet &FuzzySet)
    {
        FuzzySets.push_back(FuzzySet);
    }

    // Member function to display information
    void displayInfo() const
    {
        cout << "Fuzzy Variable: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Range: [" << lowerRange << ", " << upperRange << "]" << endl;
    }
};

class FuzzySystem
{
private:
    string name;
    string description;
    vector<FuzzyVariable> variables;
    vector<pair<string,double>> crispvalues;
    vector<FuzzyRules> Rules;

public:
    FuzzySystem(const string &systemName, const string &systemDescription)
        : name(systemName), description(systemDescription) {}

    vector<FuzzyVariable> &getVariables() { return variables; }
    vector<FuzzyRules> &getFuzzyRules() { return Rules; }

    void addFuzzyRules(const vector<FuzzyRules>  &Rule)
    {
        Rules=Rule;
    }

    void addVariables(const vector<FuzzyVariable> &variable)
    {
        variables=variable;
    }
    void addcrisp(string name,double crisp)
    {
        crispvalues.push_back({name,crisp});
    }

    void displayInfo() const
    {
        cout << "Fuzzy System: " << name << endl;
        cout << "Description: " << description << endl;
    }
};

int main()
{
    int start, choice;
    string menu = "1", name, discription, line;
    cout << "Fuzzy Logic Toolbox\n"
            "====================" << endl;
    cout << "1- Create a new fuzzy system \n"
            "2- Quit" << endl;
    cout << "------------------------------------------------ " << endl;
    while (cin >> start) {
        int set_count = 0;
        bool ch1, ch2, ch3, ch4;
        if (start == 2) {
            break;
        }
        cout << "Enter the system name and a brief description: " << endl;
        cout << "------------------------------------------------ " << endl;
        getline(cin, name);
        int ss=0;
        while (getline(cin, line)) {
            if(ss==2)
            {
                break;
            }
            discription += line;
            ss++;
        }
        // initialize fuzzy
        FuzzySystem Fuzzy(name, discription);
        vector<FuzzyVariable> Fvariables;
        vector<FuzzyRules> Frules;



        while (true) {
            cout << "\n Main Menu: " << endl;
            cout << "==========  " << endl;
            cout << "1- Add variables.  " << endl;
            cout << "2- Add fuzzy sets to an existing variable.  " << endl;
            cout << "3- Add rules.  " << endl;
            cout << "4- Run the simulation on crisp values. " << endl;

            cin >> menu;
            cout<<"menu "<<menu<<endl;
            if (menu == "close") {
                break;
            } else {
                choice = stoi(menu);
            }
            if (choice == 1 && !ch1) {
                cout << "Enter the variable name, type (IN/OUT) and range ([lower, upper]):\n"
                        "(Press x to finish) "
                     << endl;
                string variable, type;
                int range1, range2;
                while (cin >> variable) {
                    if (variable == "x") {
                        break;
                    }
                    FuzzyVariable Fvariable;
                    cin >> type >> range1 >> range2;

                    Fvariable.setName(variable);
                    Fvariable.setType(type);
                    Fvariable.setLowerRange(range1);
                    Fvariable.setUpperRange(range2);
                    Fvariables.push_back(Fvariable);
                    ch1 = true;
                }
                //cout<<"variables info"<<endl;
                //Fvariable.displayInfo();
            } else if (choice == 2 && !ch2) {
                cout << "Enter the variable’s name:  " << endl;
                cout << "--------------------------  " << endl;
                string variable, set, type;
                int val1, val2, val3, val4;
                cin >> variable;
                FuzzySet Fset;
                cout << "Enter the fuzzy set name, type (TRI/TRAP) and values: (Press x to finish)   " << endl;
                cout << "-------------------------------------------------------------------------  " << endl;
                while (cin >> set) {
                    if (set == "x") {
                        break;
                    }
                    cin >> type;
                    cout<<"sett "<<set<<endl;
                    cout<<"typee "<<type<<endl;
                    Fset.variable = set;
                    Fset.type = type;
                    if (type == "TRI") {
                        cin >> val1 >> val2 >> val3;
                        Fset.v1 = val1;
                        Fset.v2 = val2;
                        Fset.v3 = val3;
                    } else if (type == "TRAP") {
                        cin >> val1 >> val2 >> val3 >> val4;
                        Fset.v1 = val1;
                        Fset.v2 = val2;
                        Fset.v3 = val3;
                        Fset.v4 = val4;
                    }
                    //variable

                }
                for(int i=0;i<Fvariables.size();i++)
                {
                    if(Fvariables[i].getName()==variable)
                    {
                        Fvariables[i].addFuzzySet(Fset);
                        Fset.displayInfo();
                    }

                }
                set_count++;
                if (set_count == Fvariables.size()) {
                    ch2 = true;
                    Fuzzy.addVariables(Fvariables);
                    for(int i=0;i<Fuzzy.getVariables().size();i++) {
                        cout<<"fuzzy set info"<<endl;
                        Fuzzy.getVariables()[i].displayInfo();

                    }
                }
            } else if (choice == 3 && !ch3 && ch2) {
                string rule, word;
                while (getline(cin, rule)) {
                    if (rule == "x") {
                        break;
                    }
                    istringstream stream(rule);
                    vector<string> var1, op, outVar;
                    vector<pair<string, int>> set1, outSet;
                    bool var11 = false, set11 = false, then = false, op1 = false, outVar1 = false, outSet1 = false;
                    vector<FuzzyVariable> fuzzy_variables = Fuzzy.getVariables();

                    while (stream >> word) {
                        cout<<"word "<<word<<endl;
                        if (word == "then" || word == "=>") {
                            then = true;
                        }

                        if (!then ) {
                            if (!var11) {
                                for (int i = 0; i < fuzzy_variables.size(); i++) {
                                    if ((word == fuzzy_variables[i].getName()) &&
                                        fuzzy_variables[i].getType() == "IN") {
                                        var1.push_back(word);
                                        var11 = true;
                                        cout<<"var1 "<<word<<endl;
                                    }
                                }

                                // op1=false;
                            }
                        } else if (var11) {
                            int val = 1;
                            string name;
                            if (word == "not") {
                                val = 0;
                                stream >> word;
                            }
                            for (int i = 0; i < fuzzy_variables.size(); i++) {
                                vector<FuzzySet> fuzzy_sets = fuzzy_variables[i].getFuzzySets();
                                name = fuzzy_variables[i].getName();
                                for (int j = 0; j < fuzzy_sets.size(); j++) {
                                    if (word == fuzzy_sets[i].type && name == fuzzy_sets[i].variable) {
                                        set1.push_back({word, val});
                                        set11 = true;
                                        cout<<"set1 "<<word<<endl;
                                    }
                                }

                            }
                        } else if (set11) {
                            if (word == "or" || word == "and") {
                                op.push_back(word);
                                cout<<"op "<<word<<endl;
                                op1 = true;
                            }


                        } else if (!outVar1 && then) {
                            for (int i = 0; i < fuzzy_variables.size(); i++) {
                                if (word == fuzzy_variables[i].getName()) {
                                    outVar.push_back(word);
                                    outVar1 = true;
                                    cout<<"outvar1 "<<word<<endl;
                                }
                            }

                        } else if (outVar1 && then && !outSet1) {
                            int val = 1;
                            string name;
                            if (word == "not") {
                                val = 0;
                                stream >> word;
                            }
                            for (int i = 0; i < fuzzy_variables.size(); i++) {
                                vector<FuzzySet> fuzzy_sets = fuzzy_variables[i].getFuzzySets();
                                name = fuzzy_variables[i].getName();
                                for (int j = 0; j < fuzzy_sets.size(); j++) {
                                    if (word == fuzzy_sets[i].type && name == fuzzy_sets[i].variable) {
                                        outSet.push_back({word, val});
                                        outSet1 = true;
                                        cout<<"outset1 "<<word<<endl;
                                    }
                                }

                            }
                        } else if (outSet1) {
                            FuzzyRules Frule(var1, set1, op, outVar, outSet);
                            Frules.push_back(Frule);
                            Frule.displayInfo();
                        }


                    }
                }
                Fuzzy.addFuzzyRules(Frules);
                ch3 = true;
            } else if (choice == 4 && !ch4) {
                cout << "Enter the crisp values: " << endl;
                cout << "----------------------- " << endl;
                vector<FuzzyVariable> fuzzy_variables = Fuzzy.getVariables();
                string var;
                double crisp;
                for (int i = 0; i < fuzzy_variables.size(); i++) {
                    if (fuzzy_variables[i].getType() == "IN") {
                        var = fuzzy_variables[i].getName();
                        cout << var << ": " << endl;
                        cin >> crisp;
                        Fuzzy.addcrisp(var,crisp);
                    }
                }

            }
        }
    }
    return 0;
}
/*

Project Risk Estimation
The problem is to estimate the risk level of a project based on the project
funding and the technical experience of the project’s team members.

proj_funding IN 0 100
exp_level IN 0 60
risk OUT 0 100
x

exp_level

beginner TRI  0 15 30
intermediate TRI 15 30 45
expert TRI 30 60 60
x
 proj_funding
very_low TRAP 0 0 10 30
low TRAP 10 30 40 60
medium TRAP 40 60 70 90
high TRAP 70 90 100 100
x

 risk

low TRI 0 25 50
normal TRI 25 50 75
high TRI 50 100 100
x

proj_funding high or exp_level expert => risk low
proj_funding medium and exp_level intermediate => risk normal
proj_funding medium and exp_level beginner => risk normal
proj_funding low and exp_level beginner => risk high
proj_funding very_low and_not exp_level expert => risk high
x
 */