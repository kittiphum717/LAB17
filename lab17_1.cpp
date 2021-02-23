#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream source;
    source.open(filename);
    string textline;
    while(getline(source,textline)){
        char format[] = "%[^:]: %f %f %f";
        char name[100];
        float a,b,c;
        sscanf(textline.c_str(),format,name,&a,&b,&c);
        names.push_back(name);
        int s;
        s = a+b+c;
        scores.push_back(s);
        char g;
        g = score2grade(s);
        grades.push_back(g);
    }
    source.close();
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    string text;
    getline(cin,text);
    char format[] = "%s %[^\n]";
    char a[100];
    char b[100];
    sscanf(text.c_str(),format,a,b);
    command = a;
    key = b;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0;i < names.size();i++){
        if(key == toUpperStr(names[i])){
            count = 1;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
        }
    }
    if(count == 0){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    int count = 0;
    cout << "---------------------------------\n";
    const char *z = key.c_str();
    for(unsigned int i = 0;i < names.size();i++){
        if(*z == grades[i]){
            count = 1;
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }
    if(count == 0){
        cout << "Cannot found." << endl;
    }

    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}