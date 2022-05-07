#include "header.cpp"
#include "account_manage.cpp"
#include "student_manage.cpp"

//  DISPLAY THE LOGIN MENU
void display_loginMenu()    {
    cout << "+==========LOGIN MENU==========+" << endl;
    cout << "|" << setw(w*6) << left << "1. LOGIN" << "|" << endl;
    cout << "|" << setw(w*6) << left << "2. REGISTRATION" << "|" << endl;
    cout << "|" << setw(w*6) << left << "3. FORGOT PASSWORD" << "|" << endl;
    cout << "|" << setw(w*6) << left << "4. DELETE ACCOUNT" << "|" << endl;
    cout << "|" << setw(w*6) << left << "0. EXIT" << "|" << endl;
    cout << "+==============================+" << endl;
}

//  DISPLAY THE STUDENT MANAGE MENU
void display_studentManage_menu()   {
    cout << "+==========STUDENT MANAGE MENU==========+" << endl;
    cout << "|" << setw(w*8-1) << "  " << "|" << endl;
    cout << "|" << setw(w*8-1) << "--------ADMINISTRATOR REQUIRED---------" << "|" << endl;
    cout << "|" << setw(w*8-1) << left << "1. ADD STUDENT" << "|" << endl;
    cout << "|" << setw(w*8-1) << left << "2. DELETE STUDENT" << "|" << endl;
    cout << "|" << setw(w*8-1) << left << "3. ALTER STUDENT" << "|" << endl;
    cout << "|" << setw(w*8-1) << "---------------------------------------" << "|" << endl;
    cout << "|" << setw(w*8-1) << left << "4. SHOW STUDENT LIST" << "|" << endl;
    cout << "|" << setw(w*8-1) << left << "5. READ STUDENT.txt" << "|" << endl;
    cout << "|" << setw(w*8-1) << left << "6. FIND STUDENT" << "|" << endl;
    cout << "|" << setw(w*8-1) << left << "0. EXIT" << "|" << endl;
    cout << "+=======================================+" << endl;
}

//  MANAGE LOGIN MENU
void login_menu() {
    account_manage acc;

    ifstream adminFile("Admin.txt", ios::in);
    ifstream userFile("User.txt", ios::in);

    vector<account> admin_list;
    vector<account> user_list;

    acc.account_fileReader(adminFile, admin_list);
    acc.account_fileReader(userFile, user_list);
    
    // acc.account_display(admin_list);
    // acc.account_display(user_list);

    menu_loop:
    system("cls");
    display_loginMenu();
    char c;  cin >> c;   fflush(stdin);

    switch (c)  {

        //LOGIN
        case '1': {
            account tmp_acc;
            cout << "USERNAME: ";
            getline(cin, tmp_acc.username);
            cout << "PASSWORD: ";
            getline(cin, tmp_acc.password);

            if (acc.login(tmp_acc.username, tmp_acc.password, admin_list, user_list) == 'a')    {
                cout << "Login successful!" << endl;
                system("pause");
                status = 'a';
            }
            else if (acc.login(tmp_acc.username, tmp_acc.password, admin_list, user_list) == 'u')   {
                cout << "Login successful!" << endl;
                system("pause");
                status = 'u';
            }
            else    {
                cout << "USERNAME or PASSWORD is incorrect!" << endl;
                system("pause");
                goto menu_loop;
            }
        } break;

        //REGISTRATION AN USER ACCOUNT
        case '2': {
            userFile.close();
            fstream userFile("User.txt", ios::in | ios::app);

            acc.registration(userFile, admin_list, user_list);
            userFile.close();
            system("pause");
            goto menu_loop;
        } break;

        //FORGET PASSWORD
        case '3': {
            acc.forget_password(admin_list, user_list);
            system("pause");
            goto menu_loop;
        } break;

        //DELETE AN USER ACCOUNT
        case '4': {
            userFile.close();
            fstream userFile("User.txt", ios::out);
            acc.delete_account(userFile, user_list);
            for (int i=0; i<user_list.size(); i++)  {
                userFile << endl;
                userFile << ";" << user_list[i].username << ";" << user_list[i].password;
            }
            cout << "Delete complete!" << endl;
            system("pause");
            goto menu_loop;
        } break;

        case '0': {
            exit(0);
        } break;

        default:    {
            goto menu_loop;
        } break;
    }
}

//  STUDENT MANAGE MENU
void student_manage_menu()  {
    Student stu;
    vector<Student> student_list;
    ifstream student_file("Student.txt", ios::in);
    
    student_menu_loop:
    system("cls");
    display_studentManage_menu();

    char c;  cin >> c;   fflush(stdin);

    switch (c)  {

        //ADD STUDENT
        case '1':   {
            if (status == 'u')  {
                cout << "ACCESS DENIED!" << endl;
                system("pause");
                goto student_menu_loop;
            }
            student_file.close();
            ofstream student_file("Student.txt", ios::app);

            stu.add_student(student_file, student_list);
            student_file.close();

            cout << "SUCCESSFULLY ADDED STUDENT" << endl;
            system("pause");
            goto student_menu_loop;
        } break;

        //DELETE USER ACCOUNT
        case '2':   {
            if (status == 'u')  {
                cout << "ACCESS DENIED!" << endl;
                system("pause");
                goto student_menu_loop;
            }

            student_file.close();
            ofstream student_file("Student.txt", ios::out);

            stu.student_display(student_list);
            stu.delete_student(student_file, student_list);
            student_file.close();

            system("pause");
            goto student_menu_loop;
        } break;

        //ALTER STUDENT NOT FINISH YET
        case '3':   {
            if (status == 'u')  {
                cout << "ACCESS DENIED!" << endl;
                system("pause");
                goto student_menu_loop;
            }
        } break;

        //SHOW THE STUDENT TABLE
        case '4':   {
            system("cls");
            if (student_list.empty()) {
                cout << "You must read student.txt first!" << endl;
                cout << "PRESS 5. READ STUDENT.txt" << endl;
                system("pause");
                goto student_menu_loop;
            }
            stu.student_display(student_list);
            system("pause");
            goto student_menu_loop;
        } break;

        //READ STUDENT FILE
        case '5':   {
            system("cls");
            stu.student_fileReader(student_file, student_list);
            cout << "SUCCESSFULLY READ STUDENT.txt" << endl;
            system("pause");
            goto student_menu_loop;
        } break;

        //FIND STUDENT
        case '6':   {
            stu.find_student(student_list);
            system("pause");
            goto student_menu_loop;
        }

        
        case '0':   {
            exit(0);
        } break;


        default:    {
            goto student_menu_loop;
        } break;
    }

}

//  JUST IN CASE :)
void menu() {
    login_menu();
    student_manage_menu();
}

