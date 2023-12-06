#include <iostream>
#include <random>
#include <bits/stdc++.h>
using namespace std;

struct FuzzyRules {
    std::string variable1;
    std::string set1;
    std::string op; // Operator ("AND", "OR", etc.)
    std::string variable2;
    std::string set2;
    std::string outVariable;
    std::string outSet;

    // Constructor
    FuzzyRules(){}
    FuzzyRules(const std::string& var1, const std::string& s1, const std::string& operatorType,
              const std::string& var2, const std::string& s2, const std::string& outVar, const std::string& outS)
            : variable1(var1), set1(s1), op(operatorType), variable2(var2), set2(s2), outVariable(outVar), outSet(outS) {}

    void displayInfo() const {
        std::cout << "Fuzzy Rule: " << variable1 << " " << set1 << " " << op << " "
                  << variable2 << " " << set2 << " -> " << outVariable << " " << outSet << std::endl;
    }
};
struct FuzzySet {
    string variable;
    string set;
    string type; // "TRI" for triangle, "TRAP" for trapezoid
    double v1, v2, v3, v4; // Parameters defining the fuzzy set

    // Constructor
    FuzzySet(){}
    FuzzySet(const std::string& setvariable,const std::string& setset, const std::string& setType, double setA, double setB, double setC, double setD)
            : variable(setvariable),set(setset), type(setType), v1(setA), v2(setB), v3(setC), v4(setD) {}
    FuzzySet(const std::string& setvariable,const std::string& setset, const std::string& setType, double setA, double setB, double setC)
            : variable(setvariable),set(setset), type(setType), v1(setA), v2(setB), v3(setC) {}


    void displayInfo() const {
        std::cout << "Fuzzy Set: " << variable << std::endl;
        std::cout << "Type: " << type << std::endl;
        std::cout << "Parameters: (" << v1 << ", " << v2 << ", " << v3 << ", " << v4 << ")" << std::endl;
    }
};

class FuzzyVariable {
private:
    string name;
    string type; // "IN" for input, "OUT" for output
    double lowerRange;
    double upperRange;
    vector<FuzzySet> FuzzySets;

public:
    // Constructor
    FuzzyVariable(){}

    string getName() const { return name; }
    string getType() const { return type; }
    double getLowerRange() const { return lowerRange; }
    double getUpperRange() const { return upperRange; }
    vector<FuzzySet>& getFuzzySets()  { return FuzzySets; }

    void setName(string nam)  {  name=nam; }
    void setType(string typ)  {  type=typ; }
    void setLowerRange(double lr)  {  lowerRange=lr; }
    void setUpperRange(double ur)  {  upperRange=ur; }
    void addFuzzySet(const FuzzySet& FuzzySet) {
        FuzzySets.push_back(FuzzySet);
    }

    // Member function to display information
    void displayInfo() const {
        std::cout << "Fuzzy Variable: " << name << std::endl;
        std::cout << "Type: " << type << std::endl;
        std::cout << "Range: [" << lowerRange << ", " << upperRange << "]" << std::endl;
    }
};

class FuzzySystem {
private:
    string name;
    string description;
    vector<FuzzyVariable> variables;
    vector<FuzzyRules> Rules;

public:

    FuzzySystem(const string& systemName, const string& systemDescription)
            : name(systemName), description(systemDescription) {}

    vector<FuzzyVariable>& getVariables()  { return variables; }
    vector<FuzzyRules>& getFuzzyRules()  { return Rules; }

    void addFuzzyRules(const FuzzyRules& Rule) {
        Rules.push_back(Rule);
    }

    void addVariable(const FuzzyVariable& variable) {
        variables.push_back(variable);
    }


    void displayInfo() const {
       cout << "Fuzzy System: " << name <<endl;
        cout << "Description: " << description << endl;
    }
};



int main() {
    int start,choice;
    string menu="1",name,discription,line;
    while(cin>>start)
    {
        int set_count=0;
        bool ch1,ch2,ch3,ch4;
        if(start==2)
        {
            break;
        }
       getline(cin,name);
       while(getline(cin,line))
       {
           discription+=line;
       }
       //initialize fuzzy
        FuzzySystem Fuzzy(name,discription);
        FuzzyVariable Fvariable;

        cout<<"Enter the system’s name and a brief description: "<<endl;
        cout<<"------------------------------------------------ "<<endl;

        while(true)
        {
            cout<<"Main Menu: "<<endl;
            cout<<"==========  "<<endl;
            cout<<"1- Add variables.  "<<endl;
            cout<<"2- Add fuzzy sets to an existing variable.  "<<endl;
            cout<<"3- Add rules.  "<<endl;
            cout<<"4- Run the simulation on crisp values. "<<endl;

            cin>>menu;
            if(menu=="close")
            {
                break;
            }
            else
            {
                choice=stoi(menu);
            }
            if(choice==1 &&!ch1)
            {
                cout<<" Enter the variable’s name, type (IN/OUT) and range ([lower, upper]):\n"
                      "                (Press x to finish) "<<endl;
                string variable,type;
                int range1,range2;
                while(cin>>variable)
                {
                    if(variable=="x")
                    {
                        break;
                    }
                    cin>>type>>range1>>range2;
                    //Fvariable(variable,type,range1,range2);
                    Fvariable.setName(variable);
                    Fvariable.setType(type);
                    Fvariable.setLowerRange(range1);
                    Fvariable.setUpperRange(range2);
                    Fuzzy.addVariable(Fvariable);
                    ch1=true;


                }

            }
            else if(choice==2 && !ch2)
            {
                cout<<"Enter the variable’s name:  "<<endl;
                cout<<"--------------------------  "<<endl;
                string variable,set,type;
                int val1,val2,val3,val4;
                cin>>variable;
                FuzzySet Fset;
                while(cin>>set)
                {
                    if(set=="x")
                    {
                        break;
                    }

                cout<<"Enter the fuzzy set name, type (TRI/TRAP) and values: (Press x to finish)   "<<endl;
                cout<<"-------------------------------------------------------------------------  "<<endl;
                cin>>set;
                cin>>type;
                Fset.variable=variable;
                Fset.type=type;
                if(type=="TRI")
                {
                    cin>>val1>>val2>>val3;
                    Fset.v1=val1; Fset.v2=val2;  Fset.v3=val3;
                }
                else if(type=="TRAP")
                {
                    cin>>val1>>val2>>val3>>val4;
                    Fset.v1=val1; Fset.v2=val2;  Fset.v3=val3;  Fset.v4=val4;
                }
                    Fvariable.addFuzzySet(Fset);

            }
          set_count++;
                if(set_count==Fuzzy.getVariables().size())
                {
                    ch2=true;
                }
            }
            else if(choice==3 && !ch3)
            {
                string rule,word;
                while(getline(cin,rule))
                {
                    if(rule=="x")
                    {
                        break;
                    }

                    istringstream stream(rule);
                    string var1,set1, op, var2, set2, outVar, outSet;
                    int counter=0;
                    while (stream >> word) {
                        if(counter==0)
                        {
                            var1=word;
                        }
                        else if(counter==1)
                        {
                            set1=word;
                        }
                        else if(counter==2)
                        {
                            op=word;
                        }
                        else if(counter==3)
                        {
                            var2=word;
                        }
                        else if(counter==4)
                        {
                            set2=word;
                        }
                        else if(counter==6)
                        {
                            outVar=word;
                        }
                        else if(counter==7)
                        {
                            outSet=word;
                        }
                        counter++;
                        FuzzyRules Frule(var1,set1,op,var2,set2,outVar,outSet);
                        Fuzzy.addFuzzyRules(Frule);

                    }

                }
                ch3=true;








            }
            else if(choice==4 && !ch4)
            {

            }


            }

    }


    return 0;
}
