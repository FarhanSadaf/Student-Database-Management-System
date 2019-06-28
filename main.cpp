            /*Student Database Management System*/

#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

void AddRecord();
void ListRecord();
void DeleteRecord();
void SearchRecord(int);
bool SearchRecord_ext(int);
void ModifyRecord();
void ListCourses();
void TotalStudents();
bool PasswordMatched();
void ChangePassword();

class Info
{
public:
    string name;
    string roll;
    int st = -1;
    virtual int getStudents() {};

};

class Result : public virtual Info
{
protected:
    float cgpa = 0;
public:
    float gpa[8];

    virtual float get_cgpa() = 0;

    void print_cgpa()
    {
        printf("CGPA: %.2f", cgpa);
    }
};

class Student : public Result, virtual public Info
{
public:
    Student()
    {
        for(int i = 0; i < 8; i++) gpa[i] = 0;
    }

    float get_cgpa()
    {
        int i = 0;
        float temp = 0;
        while(i < 8 && gpa[i]){
            temp += gpa[i];
            i++;
        }
        cgpa = temp/i;
        return cgpa;
    }

    int getStudents()
    {
        return st;
    }

    Student operator++(int)
    {
        st++;
    }
};

bool PasswordMatched(string inp)
{
    ifstream fin("password.csv");

    string pass;
    fin >> pass;
    if(inp == pass) return 1;
    else return 0;
}

void TotalStudents()
{
    Student s;
    Info *i = &s;

    ifstream fin("studentdbms.csv");

    string line, word;

    while(fin){
        getline(fin, line);

        s++;
    }

    cout << "Record of " << i->getStudents() << " students" << endl;
    fin.close();

}

void AddRecord()
{
    Student s;
    cout << "Enter name: "; getline(cin, s.name);
    cout << "Enter roll: "; cin >> s.roll;

    ofstream fout("studentdbms.csv", ios::app);

    int i = 0;
    char deci;
    string temp;
    while(i != 8){
        cout << "\nEnter GPA of semester " << i+1 << "\nPress 'e' to exit: ";
        cin >> temp;
        if(temp == "e"){
            break;
        }
        s.gpa[i] = stof(temp);
        i++;
    }

    fout << s.name << ","
        << s.roll << ","
        << s.get_cgpa() << "\n";

    fout.close();
}

void ListRecord()
{
    string pass;
    cout << "Enter password: "; cin >> pass;
    if(!PasswordMatched(pass)){
        cout << "Incorrect password" << endl;
        return;
    }

    ifstream fin("studentdbms.csv");

    string line, word;

    cout << endl << right << setw(15) << "NAME";
    cout << right << setw(23) << "ROLL";
    cout << right << setw(22) << "CGPA" << endl;

    while(fin){
        getline(fin, line);

        stringstream s(line);

        while(getline(s, word, ',')){
            cout << setw(20) << word;
        }
        cout << "\n";
    }
    fin.close();
    cout << "\n\t\t\t";
    TotalStudents();

}

void DeleteRecord()
{
    string pass;
    cout << "Enter password: "; cin >> pass;
    if(!PasswordMatched(pass)){
        cout << "Incorrect password" << endl;
        return;
    }

    int rollnum;
    cout << "Enter ROLL of the record to be deleted: ";
    cin >> rollnum;

    ifstream fin("studentdbms.csv");
    ofstream fout("studentdbmsnew.csv");

    string line, word;
    vector<string> row;
    bool flag = false;

    while(fin){
        row.clear();

        getline(fin, line);

        stringstream s(line);

        while(getline(s, word, ',')){
            row.push_back(word);
        }

        int row_size = row.size(), rl = stoi(row[1]);
        if(rl != rollnum){
            if(fin){
                for(int i = 0; i < row_size-1; i++){
                    fout << row[i] << ",";
                }
                fout << row[row_size-1] << "\n";
            }
        }
        else{
            flag = true;
        }
    }

    if(flag){
        cout << "Record deleted" << endl;
    }
    else{
        cout << "Record not found" << endl;
    }

    fin.close();
    fout.close();

    remove("studentdbms.csv");
    rename("studentdbmsnew.csv", "studentdbms.csv");
}


void SearchRecord(int rollnum)
{

    ifstream fin("studentdbms.csv");

    string line, word, pass;
    vector<string> row;
    bool flag = false;

    while(fin){
        row.clear();

        getline(fin, line);

        stringstream s(line);

        while(getline(s, word, ',')){
            row.push_back(word);
        }

        int row_size = row.size(), rl = stoi(row[1]);
        if(rl == rollnum){
            flag = true;
            cout << "Name: " << row[0] << endl
                << "Roll: " << row[1] << endl;

            cout << endl << "For CGPA, enter password (0 to skip): "; cin >> pass;
            if(PasswordMatched(pass)){
                cout << "CGPA: " << row[2] << endl;
            }
        }
    }

    if(!flag){
        cout << "Record not found" << endl;
    }

    fin.close();
}

bool SearchRecord_ext(int rollnum)
{

    ifstream fin("studentdbms.csv");

    string line, word, pass;
    vector<string> row;
    bool flag = false;

    while(fin){
        row.clear();

        getline(fin, line);

        stringstream s(line);

        while(getline(s, word, ',')){
            row.push_back(word);
        }

        int row_size = row.size(), rl = stoi(row[1]);
        if(rl == rollnum){
            flag = true;
            cout << "Name: " << row[0] << endl
                << "Roll: " << row[1] << endl
                << "CGPA: " << row[2] << endl;
        }
    }

    if(!flag){
        cout << "Record not found" << endl;
    }

    fin.close();
    return flag;
}


void ModifyRecord()
{
    string pass;
    cout << "Enter password: "; cin >> pass;
    if(!PasswordMatched(pass)){
        cout << "Incorrect password" << endl;
        return;
    }

    int rollnum, index;
    cout << "Enter ROLL of the record to be modified: ";
    cin >> rollnum;
    if(!SearchRecord_ext(rollnum)){
        return;
    }

    cout << "What will be modified? (N/R/C)";
    char choice; cin >> choice;
    if(choice == 'N' || choice == 'n') index = 0;
    else if(choice == 'R' || choice == 'r') index = 1;
    else if(choice == 'C' || choice == 'c') index = 2;
    else{
        cout << "Invalid choice" << endl;
        ModifyRecord();
    }

    ifstream fin("studentdbms.csv");
    ofstream fout("studentdbmsnew.csv");

    string line, word, temp;
    vector<string> row;

    while(fin){
        row.clear();

        getline(fin, line);

        stringstream s(line);

        while(getline(s, word, ',')){
            row.push_back(word);
        }

        int row_size = row.size(), rl = stoi(row[1]);
        if(rl == rollnum){
            if(index == 0){
                cout << "Enter new Name: ";
                cin >> temp;
            }
            else if(index == 1){
                cout << "Enter new Roll: ";
                cin >> temp;
                rollnum = stoi(temp);
            }
            else if(index == 2){
                cout << "Enter new CGPA: ";
                cin >> temp;
            }

            row[index] = temp;

            if(fin){
                for(int i = 0; i < row_size-1; i++){
                    fout << row[i] << ",";
                }
                fout << row[row_size-1] << "\n";
            }
        }
        else{
            if(fin){
                for(int i = 0; i < row_size-1; i++){
                    fout << row[i] << ",";
                }
                fout << row[row_size-1] << "\n";
            }
        }
    }

    fin.close();
    fout.close();

    remove("studentdbms.csv");
    rename("studentdbmsnew.csv", "studentdbms.csv");

    cout << "Modified record:\n";
    SearchRecord_ext(rollnum);
}

void  ListCourses(int course)
{
    ifstream fin;
    if(course == 11){
        fin.open("1_1.csv");
        cout << right << setw(45) << "1st Year 1st Semester" << endl << endl << endl;
    }
    else if(course == 12){
        fin.open("1_2.csv");
        cout << right << setw(45) << "1st Year 2nd Semester" << endl << endl << endl;
    }
    else if(course == 21){
        fin.open("2_1.csv");
        cout << right << setw(45) << "2nd Year 1st Semester" << endl << endl << endl;
    }
    else if(course == 22){
        fin.open("2_2.csv");
        cout << right << setw(45) << "2nd Year 2nd Semester" << endl << endl << endl;
    }
    else if(course == 31){
        fin.open("3_1.csv");
        cout << right << setw(45) << "3rd Year 1st Semester" << endl << endl << endl;
    }
    else if(course == 32){
        fin.open("3_2.csv");
        cout << right << setw(45) << "3rd Year 2nd Semester" << endl << endl << endl;
    }
    else if(course == 41){
        fin.open("4_1.csv");
        cout << right << setw(45) << "4th Year 1st Semester" << endl << endl << endl;
    }
    else if(course == 42){
        fin.open("4_2.csv");
        cout << right << setw(45) << "4th Year 2nd Semester" << endl << endl << endl;
    }
    else{
        cout << "Enter a valid Year or Semester" << endl;
    }

    string line;

    while(fin){
        getline(fin, line);
        cout << line;
        cout << "\n";
    }
    fin.close();
}


void ChangePassword()
{
    string pass;
    cout << "Enter old password: "; cin >> pass;
    if(!PasswordMatched(pass)){
        cout << "Incorrect password" << endl;
        return;
    }

    cout << "Enter a new password: "; cin >> pass;
    while(pass.length() < 4){
        cout << "Password must be grater than 3 words\n";
        cout << "Enter a new password: "; cin >> pass;
    }
    ofstream fout("password.csv");
    if(fout << pass)
        cout << "Password successfully changed\n";
    fout.close();
}





int main()
{
    char choice;
    int roll, c, t;
    while(true){
        system("CLS");
        cout << "\t\t\t  STUDENT DATABASE MANAGEMENT SYSTEM       ";
        cout <<"\n\n";
        cout << "\n \t\t\t\t 1. Add    Records";
        cout << "\n \t\t\t\t 2. List   Records";
        cout << "\n \t\t\t\t 3. List Courses";
        cout << "\n \t\t\t\t 4. Delete Records";
        cout << "\n \t\t\t\t 5. Modify Records";
        cout << "\n \t\t\t\t 6. Search   Record";
        cout << "\n \t\t\t\t 7. Change Password";
        cout << "\n \t\t\t\t 8. Exit   Program";
        cout << "\n\n";
        cout << "\t\t\t\t Select Your Choice :=> ";
        choice = getche();
        switch(choice){
        case '1':
            system("CLS");
            AddRecord();
            break;

        case '2':
            system("CLS");
            ListRecord();
            cout << "\n\n\t\t\t\tPress any key";
            getche();
            break;

        case '4':
            system("CLS");
            DeleteRecord();
            cout << "\n\n\t\t\t\tPress any key";
            getche();
            break;

        case '5':
            system("CLS");
            ModifyRecord();
            cout << "\n\n\t\t\t\tPress any key";
            getche();
            break;

        case '6':
            system("CLS");
            cout << "Enter Roll: "; cin >> roll;
            SearchRecord(roll);
            cout << "\n\n\t\t\t\tPress any key";
            getche();
            break;

        case '3':
            system("CLS");
            cout << "Year: "; cin >> c;
            cout << "Semester: "; cin >> t;
            c = c*10 + t;
            ListCourses(c);
            cout << "\n\n\t\t\t\tPress any key";
            getche();
            break;

        case '7':
            system("CLS");
            ChangePassword();
            cout << "\n\n\t\t\t\tPress any key";
            getche();
            break;
        case '8':
            cout << "\n\n \t\t\t\t Thanks for your patience" << "\n";
            exit(0);
        }

    }
    return 0;
}
