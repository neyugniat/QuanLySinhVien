#pragma once
#include "header.cpp"

struct Date {
    int day, month, year;
};

class Student   {
private:
    vector<double> score;
    string stu_name;
    Date dob;

public:
    void student_fileReader(ifstream &studentFile, vector<Student> &student_list);
    void student_display(vector<Student> student_list);
    void add_student(ofstream &student_flie, vector<Student> &student_list);
    void delete_student(ofstream &student_flie, vector<Student> &student_list);
    void alter_student(vector<Student> &student_list);
    void find_student(vector<Student> student_list);
};

//  READ STUDENT FILE
void Student::student_fileReader(ifstream &studentFile, vector<Student> &student_list)  {
    char tmp;
    while (!studentFile.eof())  {
        Student tempStudent;
        studentFile >> tmp;
        getline(studentFile, tempStudent.stu_name, ';');
        studentFile >> tempStudent.dob.day >> tempStudent.dob.month >> tempStudent.dob.year;
        studentFile >> tmp;
        double tempScore;
        for (int i=0; i<3; i++) {
            studentFile >> tempScore;
            tempStudent.score.push_back(tempScore);
        }
        student_list.push_back(tempStudent);
    }
}

//  DISPLAY INFORMATION AS A TABLE
void Student::student_display(vector<Student> student_list) {
        cout << "+-----+--------------------+----------+---------------+---------------+---------------+" << endl;
        cout << "|" << setw(w) << "ID";
        cout << "|" << setw(w*4) << "FULL NAME";
        cout << "|" << setw(w*2) << "DOB";
        cout << "|" << setw(w*3) << "MATHEMATICS";
        cout << "|" << setw(w*3) << "PHYSICS";
        cout << "|" << setw(w*3) << "CHEMISTRY";
        cout << "|" << endl;
        cout << "+-----+--------------------+----------+---------------+---------------+---------------+" << endl;

        for (int i=0; i<student_list.size(); i++)   {
            cout << "|" << setw(w) << i+1;
            cout << "|" << setw(w*4) << student_list[i].stu_name << "|";
            if (student_list[i].dob.day < 10) {
                cout << "0" << student_list[i].dob.day << "/";
            }
            else    {
                cout << student_list[i].dob.day << "/";
            }
            if (student_list[i].dob.month < 10) {
                cout << "0" << student_list[i].dob.month << "/";
            }
            else    {
                cout << student_list[i].dob.month << "/";
            }
            cout << setw(4) << student_list[i].dob.year;
            for (int j=0; j<student_list[i].score.size(); j++)  {
                cout << "|" << setw(w*3) << student_list[i].score[j];
            }
            cout << "|" << endl;
        }
        cout << "+-----+--------------------+----------+---------------+---------------+---------------+" << endl;
}

//  ADD STUDENT TO THE LIST
void Student::add_student(ofstream &student_flie, vector<Student> &student_list)    {
    Student temp_stu;
    cout << "Full name: ";
    getline(cin, temp_stu.stu_name);
    cout << "Date of birth (dd/mm/yyyy): ";
    cin >> temp_stu.dob.day >> temp_stu.dob.month >> temp_stu.dob.year;
    cout << "MATHEMATICS / PHYSICS / CHEMISTRY: ";
    double tempScore;
    for (int i=0; i<3; i++) {
        cin >> tempScore;
        temp_stu.score.push_back(tempScore);
    }

    student_list.push_back(temp_stu);

    student_flie << endl;
    student_flie << ";" << temp_stu.stu_name;
    student_flie << ";" << temp_stu.dob.day << " " << temp_stu.dob.month << " " << temp_stu.dob.year;
    student_flie << ";";
    
    student_flie << temp_stu.score[0] << " ";
    student_flie << temp_stu.score[1] << " ";
    student_flie << temp_stu.score[2];
}

//  DELETE STUDENT FROM THE LIST BY ID
void Student::delete_student(ofstream &student_flie, vector<Student> &student_list)  {
    cout << "Enter ID you want to delete: ";
    int id; cin >> id;  fflush(stdin);
    student_list.erase(student_list.begin()+id-1);

    for (int i=0; i<student_list.size(); i++)   {
        student_flie << endl;
        student_flie << ";" << student_list[i].stu_name;
        student_flie << ";" << student_list[i].dob.day << " " << student_list[i].dob.month << " " << student_list[i].dob.year;
        student_flie << ";";
        
        student_flie << student_list[i].score[0] << " ";
        student_flie << student_list[i].score[1] << " ";
        student_flie << student_list[i].score[2];
    }

    cout << "SUCCESSFULLY DELETED STUDENT WITH ID: " << id << endl;
}

//  FIND STUDENT BY A NAME OR A CHARACTER
void Student::find_student(vector<Student> student_list) {
    cout << "Enter a name or a character: ";
    string fname;
    getline(cin, fname);

    cout << "+-----+--------------------+----------+---------------+---------------+---------------+" << endl;
    cout << "|" << setw(w) << "ID";
    cout << "|" << setw(w*4) << "FULL NAME";
    cout << "|" << setw(w*2) << "DOB";
    cout << "|" << setw(w*3) << "MATHEMATICS";
    cout << "|" << setw(w*3) << "PHYSICS";
    cout << "|" << setw(w*3) << "CHEMISTRY";
    cout << "|" << endl;
    cout << "+-----+--------------------+----------+---------------+---------------+---------------+" << endl;

    int fcount = 0;
    for (int i=0; i<student_list.size(); i++)   {
        if (student_list[i].stu_name.find(fname) != -1) {
            cout << "|" << setw(w) << i+1;
            cout << "|" << setw(w*4) << student_list[i].stu_name << "|";
            if (student_list[i].dob.day < 10) {
                cout << "0" << student_list[i].dob.day << "/";
            }
            else    {
                cout << student_list[i].dob.day << "/";
            }
            if (student_list[i].dob.month < 10) {
                cout << "0" << student_list[i].dob.month << "/";
            }
            else    {
                cout << student_list[i].dob.month << "/";
            }
            cout << setw(4) << student_list[i].dob.year;
            for (int j=0; j<student_list[i].score.size(); j++)  {
                cout << "|" << setw(w*3) << student_list[i].score[j];
            }
            cout << "|" << endl;
            fcount ++;
        }
    }
    if (fcount == 0)    {
        cout << "|" << setw(w*17) << left << "No such name!" << "|" << endl;
    }
    cout << "+-----+--------------------+----------+---------------+---------------+---------------+" << endl;
}

