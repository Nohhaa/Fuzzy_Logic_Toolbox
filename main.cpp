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

double AND(double x, double y)
{
    if (x < y)
        return x;
    return y;
}

double OR(double x, double y)
{
    if (x > y)
        return x;
    return y;
}

struct FuzzyRules
{
    vector<string> variables;
    vector<pair<string, double>> sets;
    vector<string> ops;
    vector<string> outVariables;
    vector<pair<string, double>> outSets;

    FuzzyRules() {}
    FuzzyRules(const vector<string> &variable, const vector<pair<string, double>> &set, const vector<string> &operatorType,
               const vector<string> &outVariable, vector<pair<string, double>> &s2)
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
    string type;
    double v1, v2, v3, v4;

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
    string type;
    double lowerRange;
    double upperRange;
    vector<FuzzySet> FuzzySets;
    vector<pair<string, double>> Centriodes;

public:
    FuzzyVariable() {}

    ~FuzzyVariable() {}

    string getName() const { return name; }
    string getType() const { return type; }
    double getLowerRange() const { return lowerRange; }
    double getUpperRange() const { return upperRange; }

    vector<FuzzySet> &getFuzzySets() { return FuzzySets; }
    vector<pair<string, double>> &getCentroids() { return Centriodes; }

    void setName(string nam) { name = nam; }
    void setType(string typ) { type = typ; }
    void setLowerRange(double lr) { lowerRange = lr; }
    void setUpperRange(double ur) { upperRange = ur; }

    void addFuzzySet(const FuzzySet &FuzzySet)
    {
        FuzzySets.push_back(FuzzySet);
    }
    void addCentroid(const vector<pair<string, double>> cent)
    {

        Centriodes = cent;
    }

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
    ~FuzzySystem(){}

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
        for (int i = 0; i < crispvalues.size(); i++)
        {
            cout << "crispvalues variable: " << crispvalues[i].first << endl;
            cout << "crispvalues value: " << crispvalues[i].second << endl;
        }
    }
    void displayfuzz() const
    {
        for (int i = 0; i < Fuzz.size(); i++)
        {
            cout << "Fuzzy variable: " << Fuzz[i].first.first << endl;
            cout << "Fuzzy set: " << Fuzz[i].first.second << endl;
            cout << "Fuzzy value: " << Fuzz[i].second << endl;
        }
    }
    void displayInf() const
    {
        for (int i = 0; i < Inf.size(); i++)
        {
            cout << "INF set: " << Inf[i].first << endl;
            cout << "INF value: " << Inf[i].second << endl;
        }
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
                                if ((fset[j].v2 <= crisp && fset[j].v3 >= crisp))
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
                                if ((fset[j].v2 <= crisp && fset[j].v3 >= crisp))
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

    void Inference()
    {
        string var, set;
        double setint, outsetint;
        double val1, val2;
        double value;
        for (int i = 0; i < Rules.size(); i++) {
            FuzzyRules rule = Rules[i];
            vector<double> values;
            vector<string> ops = rule.ops;
            vector<pair<string, double>> outset = rule.outSets;
            for (int j = 0; j < rule.variables.size(); j++) {
                var = rule.variables[j];
                set = rule.sets[j].first;
                setint = rule.sets[j].second;

                bool found = false;
                for (int k = 0; k < Fuzz.size(); k++) {

                    if (Fuzz[k].first.first == var && Fuzz[k].first.second == set) {

                        val1 = Fuzz[k].second;
                        if (setint == 0) {
                            val1 = 1 - val1;
                        }
                        values.push_back(val1);
                        found = true;
                        break;
                    }
                }
                if (!found)
                    values.push_back(0);
            }
            vector<string> ops2;
            vector<double> values2;
            for (int j = 0; j < ops.size(); j++) {
                double vall;
                double Value = values[j];
                double Value2 = values[j + 1];
                if (ops[j] == "and") {
                    vall = AND(Value, Value2);
                    values[j+1]=vall;
                    values2.push_back(vall);

                } else if (ops[j] == "and_not") {
                    vall = AND(Value, (1.0 - Value2));
                    values[j+1]=vall;
                    values2.push_back(vall);

                } else {

                    ops2.push_back(ops[j]);
                    if(j==0)
                    {
                        values2.push_back(Value);
                        if((j==ops.size()-1)||(ops.size()>j+1&&(ops[j+1]=="or" ||ops[j+1]=="or_not") ))
                        {

                            values2.push_back(Value2);
                        }
                    }
                    else
                    {
                        if(j==ops.size()-1||(ops.size()>j+1&&(ops[j+1]=="or" ||ops[j+1]=="or_not") ))
                        {
                            values2.push_back(Value2);
                        }

                    }
                }
            }

            double final=0;

            if( values2.size()==0)
            {
                final=values[values.size()-1];
            }
            for (int j = 0; j < ops2.size(); j++) {
                double vall;
                double Value = values2[j];
                double Value2 = values2[j + 1];

                if (ops2[j] == "or") {
                    vall = OR(Value, Value2);
                    values2[j+1]=vall;
                } else if (ops2[j] == "or_not") {
                    vall = OR(Value, 1 - Value2);
                    values2[j+1]=vall;
                }


            }

            if(values2.size()>0)
            { final=values2[values2.size() - 1]; }
            if(outset[0].second==0)
            {
                final=1-final;
            }

                Inf.push_back({outset[0].first, final});

        }
    }
    void getCentroides()
    {
        for (int i = 0; i < variables.size(); i++)
        {
            if (variables[i].getType() == "OUT")
            {
                vector<pair<string, double>> centroid;
                double total = 0;
                vector<FuzzySet> fset = variables[i].getFuzzySets();
                for (int j = 0; j < fset.size(); j++)
                {

                    if (fset[j].type == "TRI")
                    {
                        total = (fset[j].v1 + fset[j].v2 + fset[j].v3) / 3;
                        centroid.push_back({fset[j].variable, total});
                    }
                    else
                    {
                        total = (fset[j].v1 + fset[j].v2 + fset[j].v3 + fset[j].v4) / 4;
                        centroid.push_back({fset[j].variable, total});
                    }
                }
                variables[i].addCentroid(centroid);
            }
        }
    }

    vector<double> Defuzzification()
    {
        double ans = 0;
        for (int i = 0; i < variables.size(); i++)
        {
            if (variables[i].getType() == "OUT")
            {
                double total1 = 0, total2 = 0;
                vector<pair<string, double>> centroid = variables[i].getCentroids();
                for (int j = 0; j < Inf.size(); j++)
                {
                    total2 += Inf[j].second;
                    for (int k = 0; k < centroid.size(); k++)
                    {
                        if (Inf[j].first == centroid[k].first)
                        {
                            total1 += (Inf[j].second) * (centroid[k].second);
                        }
                    }
                }
                ans = total1 / total2;
                output.push_back(ans);
            }
        }
        return output;
    }
};

int main()
{
    int start;


    bool N=true;
    while (N)
    {
        cout << "Fuzzy Logic Toolbox\n"
                "===================="
             << endl;
        cout << "1- Create a new fuzzy system \n"
                "2- Quit"
             << endl;
        cout << "------------------------------------------------ " << endl;
        bool M;
        cin >> start;
        int choice;
        string menu = "1", name, discription, line;
        int set_count = 0;
        bool ch1= false, ch2=false, ch3=false, ch4=false;
        if (start == 2)
        {
            N= false;
            break;
        }
        else {
            M = true;

            cout << "Enter the system name and a brief description: " << endl;
            cout << "------------------------------------------------ " << endl;
            getline(cin, name);
            int ss = 0;
            while (getline(cin, line)) {
                discription += line;
                if (ss == 2) {
                    break;
                }

                ss++;
            }

            FuzzySystem Fuzzy(name, discription);
            vector<FuzzyVariable> Fvariables;
            vector<FuzzyRules> Frules;


            while (M) {
                cout << "\n Main Menu: " << endl;
                cout << "==========  " << endl;
                cout << "1- Add variables.  " << endl;
                cout << "2- Add fuzzy sets to an existing variable.  " << endl;
                cout << "3- Add rules.  " << endl;
                cout << "4- Run the simulation on crisp values. " << endl;

                cin >> menu;
                cout << "menu " << menu << endl;
                if (menu == "close") {
                    M = false;
                    break;
                } else {
                    choice = stoi(menu);

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
                    } else if (choice == 2 && !ch2) {
                        cout << "Enter the variable name:  " << endl;
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

                            for (int i = 0; i < Fvariables.size(); i++) {
                                if (Fvariables[i].getName() == variable) {
                                    Fvariables[i].addFuzzySet(Fset);
                                }
                            }
                        }
                        set_count++;
                        if (set_count == Fvariables.size()) {
                            ch2 = true;
                            Fuzzy.addVariables(Fvariables);
                        }
                    } else if (choice == 3 && !ch3 && ch2) {
                        string rule, word, name;
                        bool then = false, outSet1 = false;
                        vector<string> var1, op, outVar;
                        vector<pair<string, double>> set1, outSet;
                        while (getline(cin, rule)) {
                            if (rule == "x") {
                                break;
                            }
                            istringstream stream(rule);
                            vector<FuzzyVariable> fuzzy_variables = Fuzzy.getVariables();
                            while (stream >> word) {

                                if (word == "then" || word == "=>") {
                                    then = true;
                                }

                                if (!then) {

                                    for (int i = 0; i < fuzzy_variables.size(); i++) {
                                        if ((word == fuzzy_variables[i].getName()) &&
                                            fuzzy_variables[i].getType() == "IN") {
                                            var1.push_back(word);
                                            name = word;

                                            break;
                                        }
                                    }
                                    int val = 1;

                                    if (word == "not") {
                                        val = 0;
                                        stream >> word;
                                    }
                                    for (int i = 0; i < fuzzy_variables.size(); i++) {
                                        vector<FuzzySet> fuzzy_sets = fuzzy_variables[i].getFuzzySets();
                                        for (int j = 0; j < fuzzy_sets.size(); j++) {
                                            if (word == fuzzy_sets[j].variable &&
                                                name == fuzzy_variables[i].getName()) {

                                                set1.push_back({word, val});

                                                break;
                                            }
                                        }
                                    }
                                    if (word == "or" || word == "and" || word == "and_not" || word == "or_not") {
                                        op.push_back(word);
                                    }
                                } else {
                                    for (int i = 0; i < fuzzy_variables.size(); i++) {
                                        if (word == fuzzy_variables[i].getName()) {
                                            outVar.push_back(word);
                                            name = word;

                                            break;
                                        }
                                    }

                                    int val = 1;

                                    if (word == "not") {
                                        val = 0;
                                        stream >> word;
                                    }
                                    for (int i = 0; i < fuzzy_variables.size(); i++) {
                                        vector<FuzzySet> fuzzy_sets = fuzzy_variables[i].getFuzzySets();

                                        for (int j = 0; j < fuzzy_sets.size(); j++) {
                                            if (word == fuzzy_sets[j].variable &&
                                                name == fuzzy_variables[i].getName()) {
                                                outSet.push_back({word, val});
                                                outSet1 = true;

                                                break;
                                            }
                                        }
                                    }

                                    if (outSet1) {
                                        FuzzyRules Frule(var1, set1, op, outVar, outSet);
                                        Frules.push_back(Frule);
                                        then = false;
                                        outSet1 = false;
                                        var1.clear();
                                        set1.clear();
                                        op.clear();
                                        outVar.clear();
                                        outSet.clear();
                                    }
                                }
                            }
                        }
                        Fuzzy.addFuzzyRules(Frules);
                        ch3 = true;
                    } else if (choice == 4) {
                        if (ch1 && ch2 && ch3) {
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
                                    Fuzzy.addcrisp(var, crisp);
                                }
                            }

                            cout << "Running the simulation… " << endl;
                            Fuzzy.Fuzzification();
                            cout << "Fuzzification => done " << endl;
                            Fuzzy.Inference();
                            cout << "Inference => done " << endl;
                            Fuzzy.getCentroides();
                            Fuzzy.Defuzzification();
                            fuzzy_variables = Fuzzy.getVariables();
                            cout << "Defuzzification => done " << endl;
                            string ans;
                            string ri;
                            for (int k = 0; k < fuzzy_variables.size(); k++) {
                                if (fuzzy_variables[k].getType() != "OUT")
                                    continue;
                                ri = fuzzy_variables[k].getName();
                                vector<pair<string, double>> cent = fuzzy_variables[k].getCentroids();
                                double mini = 105;
                                for (int z = 0; z < cent.size(); z++) {

                                    if (mini > abs(cent[z].second - Fuzzy.getoutput()[0])) {
                                        mini = abs(cent[z].second - Fuzzy.getoutput()[0]);
                                        ans = cent[z].first;
                                    }
                                }
                            }
                            cout << "The predicted " << ri << " is " << ans << " (" << Fuzzy.getoutput()[0] << ").";
                        } else {
                            cout << "CANNOT START THE SIMULATION! Please add the fuzzy sets and rules first.  " << endl;
                        }
                    }
                }
            }

        }

    }
    return 0;
}
