#include <iostream>
#include <random>
#include <bits/stdc++.h>
using namespace std;

double getfuzz(double crisp, double x1, double y1, double x2, double y2)
{
    double slope;
    double y;
    slope = (y2 - y1) / (x2 - x1);
    double b;

    b = y1 - (slope * x1);
    y = slope * crisp + b;
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
    vector<pair<string, int>> sets;
    vector<string> ops; // Operator ("AND", "OR", "NOT".)
    vector<string> outVariables;
    vector<pair<string, int>> outSets;

    // Constructor
    FuzzyRules() {}
    FuzzyRules(const vector<string> &variable, const vector<pair<string, int>> &set, const vector<string> &operatorType,
               const vector<string> &outVariable, vector<pair<string, int>> &s2)
        : variables(variable), sets(set), ops(operatorType), outVariables(outVariable), outSets(s2) {}
    void displayInfo() const
    {
        for (int i = 0; i < variables.size(); i++)
        {
            cout << "variables: " << variables[i] << endl;
            cout << "set: " << sets[i].first << " " << sets[i].second << endl;
            if (i < ops.size())
            {
                cout << "ops: " << ops[i] << endl;
            }
        }
        for (int i = 0; i < outVariables.size(); i++)
        {
            cout << "outVariables: " << outVariables[i] << endl;
            cout << "outSets: " << outSets[i].first << " " << outSets[i].second << endl;
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
        cout << "Type: " << type << endl;
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
    vector<pair<string,double>> Centriodes;

public:
    // Constructor
    FuzzyVariable() {}

    string getName() const { return name; }
    string getType() const { return type; }
    double getLowerRange() const { return lowerRange; }
    double getUpperRange() const { return upperRange; }

    vector<FuzzySet> &getFuzzySets() { return FuzzySets; }
    vector<pair<string,double>>&getCentroids() { return Centriodes; }

    void setName(string nam) { name = nam; }
    void setType(string typ) { type = typ; }
    void setLowerRange(double lr) { lowerRange = lr; }
    void setUpperRange(double ur) { upperRange = ur; }

    void addFuzzySet(const FuzzySet &FuzzySet)
    {
        FuzzySets.push_back(FuzzySet);
    }
    void addCentroid(const   vector<pair<string,double>> &cent)
    {
        Centriodes=cent;
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
    vector<pair<string, double>> crispvalues;
    vector<FuzzyRules> Rules;
    vector<pair<pair<string, string>, double>> Fuzz;
    vector<double> output;
    vector<pair<string, double>> Inf;

public:
    FuzzySystem(const string &systemName, const string &systemDescription)
        : name(systemName), description(systemDescription) {}

    vector<FuzzyVariable> &getVariables() { return variables; }
    vector<FuzzyRules> &getFuzzyRules() { return Rules; }
    vector<double> &getoutput() { return output; }

    void addFuzzyRules(const vector<FuzzyRules> &Rule)
    {
        Rules = Rule;
    }

    void addVariables(const vector<FuzzyVariable> &variable)
    {
        variables = variable;
    }
    void addcrisp(string name, double crisp)
    {
        crispvalues.push_back({name, crisp});
    }

    void displayInfo() const
    {
        cout << "Fuzzy System: " << name << endl;
        cout << "Description: " << description << endl;
        for (int i = 0; i < crispvalues.size(); i++) {
            cout << "crispvalues variable: " << crispvalues[i].first << endl;
            cout << "crispvalues value: " << crispvalues[i].second<< endl;
        }
    }
    void displayfuzz() const
    {
        for (int i = 0; i < Fuzz.size(); i++) {
            cout << "Fuzzy variable: " << Fuzz[i].first.first << endl;
            cout << "Fuzzy set: " << Fuzz[i].first.second << endl;
            cout << "Fuzzy value: " << Fuzz[i].second<< endl;}
    }
    void displayInf() const
    {
        for (int i = 0; i < Inf.size(); i++) {
            cout << "Fuzzy set: " << Inf[i].first << endl;
            cout << "Fuzzy value: " << Fuzz[i].second<< endl;}
    }
    void Fuzzification()
    {
        for (int i = 0; i < variables.size(); i++)
        {
            if (variables[i].getType() == "IN")
            {
                vector<FuzzySet> fset = variables[i].getFuzzySets();
                for (int j = 0; j < fset.size(); j++)
                {
                    for (int k = 0; k < crispvalues.size(); k++)
                    {
                        if (crispvalues[k].first == variables[i].getName())
                        {
                            double crisp = crispvalues[k].second, fuzz;
                            if (fset[j].type == "TRI")
                            {
                                if ((fset[j].v1 != fset[j].v2) && (fset[j].v2 >= crisp && crisp >= fset[j].v1))
                                {
                                    fuzz = getfuzz(crisp, fset[j].v1, 0, fset[j].v2, 1);
                                    Fuzz.push_back({{variables[i].getName(), fset[j].variable}, fuzz});
                                }
                                if ((fset[j].v1 == fset[j].v2) && (fset[j].v1 <= crisp && fset[j].v3 >= crisp))
                                {
                                    fuzz = getfuzz(crisp, fset[j].v2, 1, fset[j].v3, 0);
                                    Fuzz.push_back({{variables[i].getName(), fset[j].variable}, fuzz});
                                }
                                if ((fset[j].v3 != fset[j].v2) && (fset[j].v2 <= crisp && fset[j].v3 >= crisp))
                                {
                                    fuzz = getfuzz(crisp, fset[j].v2, 1, fset[j].v3, 0);
                                    Fuzz.push_back({{variables[i].getName(), fset[j].variable}, fuzz});
                                }
                            }
                            else
                            {
                                if ((fset[j].v1 != fset[j].v2) && (fset[j].v2 >= crisp && crisp >= fset[j].v1))
                                {
                                    fuzz = getfuzz(crisp, fset[j].v1, 0, fset[j].v2, 1);
                                    Fuzz.push_back({{variables[i].getName(), fset[j].variable}, fuzz});
                                }
                                if ((fset[j].v1 == fset[j].v2) && (fset[j].v1 <= crisp && fset[j].v3 >= crisp))
                                {
                                    fuzz = getfuzz(crisp, fset[j].v2, 1, fset[j].v3, 1);
                                    Fuzz.push_back({{variables[i].getName(), fset[j].variable}, fuzz});
                                }
                                if ((fset[j].v3 != fset[j].v2) && (fset[j].v2 <= crisp && fset[j].v3 >= crisp))
                                {
                                    fuzz = getfuzz(crisp, fset[j].v2, 1, fset[j].v3, 1);
                                    Fuzz.push_back({{variables[i].getName(), fset[j].variable}, fuzz});
                                }
                                if ((fset[j].v3 != fset[j].v4) && (fset[j].v3 <= crisp && fset[j].v4 >= crisp))
                                {
                                    fuzz = getfuzz(crisp, fset[j].v3, 1, fset[j].v4, 0);
                                    Fuzz.push_back({{variables[i].getName(), fset[j].variable}, fuzz});
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // under development
    void Inference()
    {
        string var, set, op = "no", op2, var2, set2, outvar, outset;
        int setint, outsetint;
        double val1, val2;
        double value;
        for (int i = 0; i < Rules.size(); i++)
        {
            FuzzyRules rule = Rules[i];
            vector<double> values;
            vector<string> ops = rule.ops; // and or and_not or_not
            vector<string> outvar = rule.outVariables;
            vector<pair<string, int>> outset = rule.outSets;
            for (int j = 0; j < rule.variables.size(); j++)
            {
                var = rule.variables[j];
                set = rule.sets[j].first;
                setint = rule.sets[j].second;
                for (int k = 1; k < Fuzz.size(); k++)
                {
                    if (Fuzz[k].first.first == var && Fuzz[k].first.second == set)
                    {
                        val1 = Fuzz[k].second;
                        if (setint == 0)
                        {
                            val1 = 1 - val1;
                        }
                        values.push_back(val1);
                    }
                }
            }
            if (ops.size() == 1)
            {
                double Value = values[0];
                double Value2 = values[1];
                string oper = ops[0];
                if (oper == "and")
                {
                    double Final = AND(Value, Value2);
                    if (outset[0].second == 0)
                        Final = 1 - Final;
                    Inf.push_back({outset[0].first, Final});
                }
                else if (oper == "and_not")
                {
                    double Final = AND(Value, 1 - Value2);
                    if (outset[0].second == 0)
                        Final = 1 - Final;
                    Inf.push_back({outset[0].first, Final});
                }
                else if (oper == "or")
                {
                    double Final = OR(Value, Value2);
                    if (outset[0].second == 0)
                        Final = 1 - Final;
                    Inf.push_back({outset[0].first, Final});
                }
                else
                {
                    double Final = OR(Value, 1 - Value2);
                    if (outset[0].second == 0)
                        Final = 1 - Final;
                    Inf.push_back({outset[0].first, Final});
                }
            }
            else if (op.size() == 3)
            {
                double Value = values[0];
                double Value2 = values[1];
                double Value3 = values[2];
                double Value4 = values[3];
                double Final1;
                double Final2;
                string oper1 = ops[0];
                string oper2 = ops[0];
                string oper3 = ops[0];
                if (oper1 == "and")
                {
                    Final1 = AND(Value, Value2);
                }
                else if (oper1 == "and_not")
                {
                    Final1 = AND(Value, 1 - Value2);
                }
                else if (oper1 == "or")
                {
                    Final1 = OR(Value3, Value4);
                }
                else
                {
                    Final1 = OR(Value3, 1 - Value4);
                }

                if (oper3 == "and")
                {
                    Final2 = AND(Value3, Value4);
                }
                else if (oper3 == "and_not")
                {
                    Final2 = AND(Value3, 1 - Value4);
                }
                else if (oper3 == "or")
                {
                    Final2 = OR(Value3, Value4);
                }
                else
                {
                    Final2 = OR(Value3, 1 - Value4);
                }
                double Final3;
                if (oper2 == "and")
                {
                    Final3 = AND(Final1, Final2);
                }
                else if (oper2 == "and_not")
                {
                    Final3 = AND(Final1, Final2);
                }
                else if (oper2 == "or")
                {
                    Final3 = OR(Final1, Final2);
                }
                else
                {
                    Final3 = OR(Final1, Final2);
                }
                if (outset[0].second == 0)
                    Final3 = 1 - Final3;
                Inf.push_back({outset[0].first, Final3});
            }
        }
    }
    void getCentroides()
    {
        for (int i = 0; i < variables.size(); i++) {
            if (variables[i].getType() == "OUT") {
                vector<pair<string,double>> centroid;
                double total=0;
                vector<FuzzySet> fset = variables[i].getFuzzySets();
                for (int j = 0; j < fset.size(); j++)
                {
                     if(fset[j].type=="TRI")
                     {
                         total+=(fset[j].v1+fset[j].v2+fset[j].v3)/3;
                         centroid.push_back({fset[j].set,total});
                     }
                     else
                     {
                         total+=(fset[j].v1+fset[j].v2+fset[j].v3+fset[j].v4)/4;
                         centroid.push_back({fset[j].set,total});
                     }
                }
                variables[i].addCentroid(centroid);

            }
        }

    }

    vector<double> Defuzzification() {
        double ans=0;
        for (int i = 0; i < variables.size(); i++) {
            if (variables[i].getType() == "OUT") {
                double total1 = 0,total2=0;
                vector<pair<string, double>> centroid = variables[i].getCentroids();
                for (int j = 0; j < Inf.size(); j++) {
                    total2+=Inf[j].second;
                    for (int k = 0; k < centroid.size(); k++) {
                        if (Inf[j].first==centroid[k].first)
                        {
                            total1+=(Inf[j].second)*(centroid[k].second);
                        }
                    }
                }
                ans=total1/total2;
                output.push_back(ans);
            }

        }
        return output;
    }
};

int main()
{
    int start, choice;
    string menu = "1", name, discription, line;
    cout << "Fuzzy Logic Toolbox\n"
            "===================="
         << endl;
    cout << "1- Create a new fuzzy system \n"
            "2- Quit"
         << endl;
    cout << "------------------------------------------------ " << endl;
    while (cin >> start)
    {
        int set_count = 0;
        bool ch1, ch2, ch3, ch4;
        if (start == 2)
        {
            break;
        }
        cout << "Enter the system name and a brief description: " << endl;
        cout << "------------------------------------------------ " << endl;
        getline(cin, name);
        int ss = 0;
        while (getline(cin, line))
        {
            if (ss == 2)
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

        while (true)
        {
            cout << "\n Main Menu: " << endl;
            cout << "==========  " << endl;
            cout << "1- Add variables.  " << endl;
            cout << "2- Add fuzzy sets to an existing variable.  " << endl;
            cout << "3- Add rules.  " << endl;
            cout << "4- Run the simulation on crisp values. " << endl;

            cin >> menu;
            cout << "menu " << menu << endl;
            if (menu == "close")
            {
                break;
            }
            else
            {
                choice = stoi(menu);
            }
            if (choice == 1 && !ch1)
            {
                cout << "Enter the variable name, type (IN/OUT) and range ([lower, upper]):\n"
                        "(Press x to finish) "
                     << endl;
                string variable, type;
                int range1, range2;
                while (cin >> variable)
                {
                    if (variable == "x")
                    {
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
                // cout<<"variables info"<<endl;
                // Fvariable.displayInfo();
            }
            else if (choice == 2 && !ch2)
            {
                cout << "Enter the variable name:  " << endl;
                cout << "--------------------------  " << endl;
                string variable, set, type;
                int val1, val2, val3, val4;
                cin >> variable;
                FuzzySet Fset;
                cout << "Enter the fuzzy set name, type (TRI/TRAP) and values: (Press x to finish)   " << endl;
                cout << "-------------------------------------------------------------------------  " << endl;
                while (cin >> set)
                {
                    if (set == "x")
                    {
                        break;
                    }
                    cin >> type;
                    Fset.variable = set;
                    Fset.type = type;
                    if (type == "TRI")
                    {
                        cin >> val1 >> val2 >> val3;
                        Fset.v1 = val1;
                        Fset.v2 = val2;
                        Fset.v3 = val3;
                    }
                    else if (type == "TRAP")
                    {
                        cin >> val1 >> val2 >> val3 >> val4;
                        Fset.v1 = val1;
                        Fset.v2 = val2;
                        Fset.v3 = val3;
                        Fset.v4 = val4;
                    }

                    for (int i = 0; i < Fvariables.size(); i++)
                    {
                        if (Fvariables[i].getName() == variable)
                        {
                            Fvariables[i].addFuzzySet(Fset);
                            Fset.displayInfo();
                        }
                    }
                }
                set_count++;
                if (set_count == Fvariables.size())
                {
                    ch2 = true;
                    Fuzzy.addVariables(Fvariables);
                    for (int i = 0; i < Fuzzy.getVariables().size(); i++)
                    {
                        cout << "fuzzy set info" << endl;
                        Fuzzy.getVariables()[i].displayInfo();
                    }
                }
            }
            else if (choice == 3 && !ch3 && ch2)
            {
                string rule, word, name;
                bool then = false, outSet1 = false;
                while (getline(cin, rule))
                {
                    if (rule == "x")
                    {
                        break;
                    }
                    istringstream stream(rule);
                    vector<string> var1, op, outVar;
                    vector<pair<string, int>> set1, outSet;
                    vector<FuzzyVariable> fuzzy_variables = Fuzzy.getVariables();

                    while (stream >> word)
                    {

                        cout << "word " << word << endl;
                        if (word == "then" || word == "=>")
                        {
                            then = true;
                        }

                        if (!then)
                        {

                            for (int i = 0; i < fuzzy_variables.size(); i++)
                            {
                                if ((word == fuzzy_variables[i].getName()) &&
                                    fuzzy_variables[i].getType() == "IN")
                                {
                                    var1.push_back(word);
                                    name = word;

                                    cout << "var1 " << word << endl;
                                    break;
                                }
                            }
                            int val = 1;

                            if (word == "not")
                            {
                                val = 0;
                                stream >> word;
                            }
                            for (int i = 0; i < fuzzy_variables.size(); i++)
                            {
                                vector<FuzzySet> fuzzy_sets = fuzzy_variables[i].getFuzzySets();
                                for (int j = 0; j < fuzzy_sets.size(); j++)
                                {
                                    if (word == fuzzy_sets[j].variable && name == fuzzy_variables[i].getName())
                                    {
                                        cout << "Fuzzyset info " << endl;
                                        fuzzy_sets[j].displayInfo();
                                        set1.push_back({word, val});

                                        cout << "set1 " << word << endl;
                                        break;
                                    }
                                }
                            }
                            if (word == "or" || word == "and" || word == "and_not" || word == "or_not")
                            {
                                op.push_back(word);
                                cout << "op " << word << endl;
                            }
                        }
                        else
                        {
                            for (int i = 0; i < fuzzy_variables.size(); i++)
                            {
                                if (word == fuzzy_variables[i].getName())
                                {
                                    outVar.push_back(word);
                                    name = word;
                                    cout << "outVar " << word << endl;
                                    break;
                                }
                            }

                            int val = 1;

                            if (word == "not")
                            {
                                val = 0;
                                stream >> word;
                            }
                            for (int i = 0; i < fuzzy_variables.size(); i++)
                            {
                                vector<FuzzySet> fuzzy_sets = fuzzy_variables[i].getFuzzySets();

                                for (int j = 0; j < fuzzy_sets.size(); j++)
                                {
                                    if (word == fuzzy_sets[j].variable && name == fuzzy_variables[i].getName())
                                    {
                                        outSet.push_back({word, val});
                                        outSet1 = true;
                                        cout << "outset1 " << word << endl;
                                        break;
                                    }
                                }
                            }

                            if (outSet1)
                            {
                                FuzzyRules Frule(var1, set1, op, outVar, outSet);
                                Frules.push_back(Frule);
                                Frule.displayInfo();
                                then = false;
                                outSet1 = false;
                            }
                        }
                    }
                }
                Fuzzy.addFuzzyRules(Frules);
                ch3 = true;
            }
            else if (choice == 4)
            {
                if (ch1 && ch2 && ch3)
                {
                    cout << "Enter the crisp values: " << endl;
                    cout << "----------------------- " << endl;
                    vector<FuzzyVariable> fuzzy_variables = Fuzzy.getVariables();
                    string var;
                    double crisp;
                    for (int i = 0; i < fuzzy_variables.size(); i++)
                    {
                        if (fuzzy_variables[i].getType() == "IN")
                        {
                            var = fuzzy_variables[i].getName();
                            cout << var << ": " << endl;
                            cin >> crisp;
                            Fuzzy.addcrisp(var, crisp);
                        }
                    }
                    Fuzzy.Fuzzification();
                    Fuzzy.displayfuzz();
                    Fuzzy.Inference();
                    Fuzzy.displayInf();
                    Fuzzy.getCentroides();
                    Fuzzy.Defuzzification();
                    cout<<"ANSWERRRRRRRRRRR "<<Fuzzy.getoutput()[0]<<endl;
                }
                else
                {
                    cout << "CANNOT START THE SIMULATION! Please add the fuzzy sets and rules first.  " << endl;
                }
                cout << "fuzzy info  " << endl;

                Fuzzy.displayInfo();
                cout << "fuzzy varibles  " << endl;
                for (int i = 0; i < Fuzzy.getVariables().size(); i++)
                {
                    Fuzzy.getVariables()[i].displayInfo();
                    cout << "fuzzy sets  " << endl;
                    for (int j = 0; j < Fuzzy.getVariables()[i].getFuzzySets().size(); j++)
                    {
                        Fuzzy.getVariables()[i].getFuzzySets()[j].displayInfo();
                    }
                }
                cout << "fuzzy rules  " << endl;
                for (int i = 0; i < Fuzzy.getFuzzyRules().size(); i++) {
                    Fuzzy.getFuzzyRules()[i].displayInfo();

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