#include <bits/stdc++.h>

using namespace std;

class cnf{
    public:
      string proposition;
      int length;

      cnf(string s){
        proposition=s;
        length=s.length();
      }
      
    // convert all the bidirectional implications to implications i.e. a=b -> a>b
      void bidirectional_implication_to_implication(){
         int i=0;
         while(i<length){
            i=0;
            while(i<length){
                if(proposition[i]=='='){
                    int p=i, q=i, count=0;

                    do{
                        q++;
                        if(proposition[q]=='('){
                            count++;
                        }
                        if(proposition[q]==')'){
                            count--;
                        }
                    }while(count>-1);

                    count=0;
                    do{
                        p--;
                        if(proposition[p]==')'){
                            count++;
                        }
                        if(proposition[p]=='('){
                            count--;
                        }
                    }while(count>-1);

                    // cout<<p<<" "<<q<<endl;

                    string s=proposition;
                    proposition =  s.substr(0,p+1) + '('+s.substr(p+1, i-p-1)+'>'+s.substr(i+1, q-i-1)+')'+'&'+'('+s.substr(i+1, q-i-1)+'>'+s.substr(p+1, i-p-1)+')'+s.substr(q,length-q);
                    // cout<<proposition<<endl;

                    length = proposition.length();
                    break;
                }
            i++;
            }
         }
      }
    // end
   
    // Conversion of implication to negation and or i.e. a>b -> !a|b
    void implication_conversion(){
        int i=0;
        while(i<length){
            i=0;
            while(i<length){
                if(proposition[i]=='>'){
                    int p=i;
                    if(proposition[i-1]!=')'){
                        string s=proposition;
                        proposition =  s.substr(0,p-1) + '!'+s.substr(p-1, 1)+'|'+s.substr(p+1, length-p-1);
                    }
                    else{
                        while(1){
                            if(proposition[p]=='(') break;
                             p--;
                        }
                        string s=proposition;
                        proposition =  s.substr(0,p) + '!'+s.substr(p, i-p)+'|'+s.substr(i+1, length-i-1);
                    }
                    length=proposition.length();
                    break;
                }
                i++;
            }
        }
    }
    // end
   
   // Solving the negations  
   void solving_negation(){
        // cout<<length<<endl;
        int i=0;
        while(i<length){
            i=0;
            while(i<length){
                if(proposition[i]=='!'){
                    int p=i;
                    if(proposition[i+1]=='('){
                        string s=proposition;
                        string out;
                        out =  out + s.substr(0,p);
                        p++;
                        if(proposition[p+1]!='!'){
                            out = out + s[p] + '!' + s[p+1];

                            if(proposition[p+2]=='&'){
                                out=out+'|';
                            }
                            if(proposition[p+2]=='|'){
                                out=out+'&';
                            }
                            p=p+2;
                        }
                        else if(proposition[p+1]=='!'){
                            out=out+s[p]+s[p+2];

                            if(proposition[p+3]=='&'){
                                out=out+'|';
                            }
                            if(proposition[p+3]=='|'){
                                out=out+'&';
                            }
                            p=p+3;
                        }
                        // cout<<p<<endl;
                        if(proposition[p+1]!='!'){
                            out = out + '!' + s.substr(p+1, length-p-1);
                        }
                        else if(proposition[p+1]=='!'){
                            out=out+s.substr(p+2, length-p-2);
                        }
                        // cout<<out<<endl;
                        if(out.length()!=0){
                            proposition=out;
                        }
                        length=proposition.length();
                        break;
                    }
                }
                i++;
            }
        }
   }
   // end
   
   // separate all conjuction over disjunction
   void conjuction_over_disjunction(){
      int i=0;
      while(i<length){
        i=0;
        while(i<length){
            if(proposition[i]=='&'){
                int p = i;
                int q = i;
                int count=0;

                do{
                    q++;
                    if(proposition[q]=='('){
                        count++;
                    }
                    if(proposition[q]==')'){
                        count--;
                    }
                }while(count>-1);

                count=0;
                do{
                    p--;
                    if(proposition[p]==')'){
                        count++;
                    }
                    if(proposition[p]=='('){
                        count--;
                    }
                }while(count>-1);



                if(p>0 && proposition[p-1]=='|'){
                    int t=p-2;
                     count=0;
                do{
                    t--;
                    if(proposition[t]==')'){
                        count++;
                    }
                    if(proposition[t]=='('){
                        count--;
                    }
                }while(count>-1);

                string s = '('+proposition.substr(t+1, p-t-2)+'|'+proposition.substr(p+1, i-p-1)+')'+'&'+'('+proposition.substr(t+1, p-t-2)+'|'+proposition.substr(i+1, q-i-1)+')';
                proposition = proposition.replace(t+1, q-t, s);
                length=proposition.length();
                break;
                }

                if(q<length-1 && proposition[q+1]=='|'){
                    int t=q+2;
                     count=0;
                do{
                    t++;
                    if(proposition[t]==')'){
                        count--;
                    }
                    if(proposition[t]=='('){
                        count++;
                    }
                }while(count>-1);

                string s = '('+proposition.substr(p+1, i-p-1)+'|'+proposition.substr(q+2, t-q-2)+')'+'&'+'('+proposition.substr(i+1, q-i-1)+'|'+proposition.substr(q+2, t-q-2)+')';
                proposition = proposition.replace(p, t-p, s);
                length=proposition.length();
                break;
                }
            }
            i++;
        }
      }
   }
   // end
};

class ResolutionRefutation {
public:
    vector<string> KB;

    ResolutionRefutation(const vector<string>& v) : KB(v) {}

    bool uninformedSearch() {
        while (true) {
            vector<string> newClauses;
            for (int i = 0; i < KB.size(); ++i) {
                for (int j = i+1; j < KB.size(); ++j) {
                    string resolvent = resolve(KB[i], KB[j]);
                    // cout<<KB[i]<<" "<<KB[j]<<" "<<resolvent<<endl;
                    if (resolvent.empty()) {
                        // Empty resolvent means contradiction found, return true
                        cout << "[Path: " << KB[i] << ", " << KB[j] << ']'<<endl;
                        return true;
                    } else if (!contains(newClauses, resolvent) && !contains(KB, resolvent)) {
                        // Add unique resolvent to newClauses
                        newClauses.push_back(resolvent);
                    }
                }
            }

            if (newClauses.empty()) {
                return false;
            }

            // Print the path
            cout << '['<<"Path: ";
            for (const string& clause : newClauses) {
                cout << clause << ", ";
            }
            cout <<']'<< endl;


            KB.insert(KB.end(), newClauses.begin(), newClauses.end());
        }
    }

    bool informed_greedy_search() {
        // heuristic could be to prioritize resolving clauses that result in the smallest resolvents. This is based on the assumption that smaller resolvents are more likely to lead to a contradiction (an empty clause).
    while (true) {
        vector<string> newClauses;
        for (int i = 0; i < KB.size(); ++i) {
            for (int j = i + 1; j < KB.size(); ++j) {
                string resolvent = resolve(KB[i], KB[j]);
                if (resolvent.empty()) {
                    cout << "[Path: " << KB[i] << ", " << KB[j] << ']'<<endl;
                    return true;
                } else if (!contains(newClauses, resolvent) && !contains(KB, resolvent)) {
                    newClauses.push_back(resolvent);
                }
            }
        }

        if (newClauses.empty()) {
            return false;
        }
        
        // Print the path
        cout << '['<<"Path: ";
        for (const string& clause : newClauses) {
            cout << clause << ", ";
        }
        cout <<']'<< endl;

        // Sort newClauses based on the length of the clauses
        sort(newClauses.begin(), newClauses.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });

        KB.insert(KB.end(), newClauses.begin(), newClauses.end());
    }
}

private:
    bool contains(const vector<string>& clauses, const string& clause) const {
        return find(clauses.begin(), clauses.end(), clause) != clauses.end();
    }

    string resolve(const string& clause1, const string& clause2) {
        string result;
        unordered_set<string> lt;

        // Extract literals from clause1
        int i = 0;
        while (i < clause1.size()) {
            char t = clause1[i];
            if (t != '&' && t != '|') {
                if (t == '!') {
                    lt.insert(string(1, t) + clause1[i + 1]);
                    i += 2;
                } else {
                    lt.insert(string(1, t));
                    i++;
                }
            } else {
                i++;
            }
        }

        // Check for common literals and perform resolution
        i = 0;
        while (i < clause2.size()) {
            char t = clause2[i];
            if (t != '&' && t != '|') {
                if (t == '!') {
                    if (lt.find(string(1, clause2[i + 1])) != lt.end()) {
                        // Found a common literal, remove it from the set
                        lt.erase(string(1, clause2[i + 1]));
                        i += 2;
                        continue;
                    }
                    lt.insert(string(1, t) + clause2[i + 1]);
                    i += 2;
                } else {
                    lt.insert(string(1, t));
                    i++;
                }
            } else {
                i++;
            }
        }

        // Construct the result string
        for (const auto& literal : lt) {
            result += literal;
        }

        return result;
    }
};


vector<string> separateClauses(string& conjunction, vector<string>&literals) {
    std::vector<std::vector<std::string>> clauses;
    std::istringstream iss(conjunction);
    std::string clauseString;

    // Split the conjunction into individual clause strings
    while (std::getline(iss, clauseString, '&')) {
        // Remove leading and trailing whitespaces
        size_t start = clauseString.find_first_not_of(" \t");
        size_t end = clauseString.find_last_not_of(" \t");

        if (start != std::string::npos && end != std::string::npos) {
            clauseString = clauseString.substr(start, end - start + 1);
        }

        // Tokenize the clause string
        std::istringstream clauseIss(clauseString);
        std::string literal;
        // std::vector<std::string> literals;

        while (clauseIss >> literal) {
            literals.push_back(literal);
        }
    }

    return literals;
}

string convert_to_cnf(string proposition){
    cnf convert(proposition);
    convert.bidirectional_implication_to_implication();
    convert.implication_conversion();
    convert.solving_negation();
    convert.conjuction_over_disjunction();

    return convert.proposition;
}

bool uninformed_search(vector<string> KB){
    ResolutionRefutation resolver(KB);

    return resolver.uninformedSearch();
}

bool informed_greedy_search(vector<string> KB){
    ResolutionRefutation resolver(KB);

    return resolver.informed_greedy_search();
}

int main(){

    int n,m;
    cin>>n>>m;
    
    string proposition, query;
    
    vector<string> KB;

    for(int i=0; i<n; i++){
        cin>>proposition;
        KB.push_back(proposition);
    }
    
    cin >>query;

    if(query.size()>2) KB.push_back("!("+query+")");

    vector<string> KB_cnf;
    vector<string> literals;

    // Convert the KB to CNF

    for (auto& e : KB) {
        // cout<<'(' + e + ')'<<endl;
        // cout<<e<<endl;
        string s = convert_to_cnf('(' + e + ')');
        if(s[1]=='('){
            s = s.substr(2, s.length() - 4);
        }
        else{
            s = s.substr(1, s.length() - 2);
        }
        // Separate CNF clauses and add to KB_cnf
        separateClauses(s, literals);
        for (const auto& clause : literals) {
            KB_cnf.push_back(clause);
        }
        literals.clear();
    }
    
    if(query.size()==2) KB_cnf.push_back(query.substr(1,1));
    if(query.size()==1) KB_cnf.push_back("!"+query);

    for(int i=0; i<KB_cnf.size(); i++){
        if(KB_cnf[i][0]=='('){
            KB_cnf[i]=KB_cnf[i].substr(1,KB_cnf[i].length()-2);
        }
        cout<<KB_cnf[i]<<endl;
    }
    cout<<endl;

    cout << "Result by uninformed search" << endl;
    cout << "----------------------------" << endl;
    if (uninformed_search(KB_cnf)) {
        cout << "Contradiction found, the knowledge base is unsatisfiable." << endl;
    } else {
        cout << "No contradiction found, the knowledge base is satisfiable." << endl;
    }
    cout << endl;

    cout << "Result by informed search" << endl;
    cout << "--------------------------" << endl;
    if (informed_greedy_search(KB_cnf)) {
        cout << "Contradiction found, the knowledge base is unsatisfiable." << endl;
    } else {
        cout << "No contradiction found, the knowledge base is satisfiable." << endl;
    }

    return 0;
}