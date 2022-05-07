#pragma once
#include "header.cpp"

struct account  {
    string username, password;
};

static char status;

class account_manage    {

public:
    //NHAP XUAT
    void account_fileReader(ifstream &accountFile, vector<account> &account_list);
    void account_display(vector<account> account_list);

    //THAO TAC VOI TAI KHOAN
    char login(string loginUsername, string loginPassword, vector<account> admin_list, vector<account> user_list);
    void registration(fstream &accountFile, vector<account> &admin_list, vector<account> &user_list);
    void forget_password(vector<account> &admin_list, vector<account> &user_list);
    void delete_account(fstream &user_file, vector<account> &user_list);
};

void account_manage::account_fileReader(ifstream &accountFile, vector<account> &account_list)   {
    char tmp;
    while (!accountFile.eof())  {
        account tmp_account;
        accountFile >> tmp;
        getline(accountFile, tmp_account.username, ';');
        getline(accountFile, tmp_account.password);
        account_list.push_back(tmp_account);
    }
}

void account_manage::account_display(vector<account> account_list)  {
    for (int i=0; i<account_list.size(); i++)   {
        cout << setw(w*4) << account_list[i].username << setw(w*4) << account_list[i].password << endl;
    }
}

char account_manage::login(string loginUsername, string loginPassword, vector<account> admin_list, vector<account> user_list) {
    for (int i=0; i<admin_list.size(); i++) {
        if (loginUsername == admin_list[i].username)    {
            if (loginPassword == admin_list[i].password)    {
                return 'a';
            }
        }
    }
    for (int i=0; i<user_list.size(); i++)  {
        if (loginUsername == user_list[i].username) {
            if (loginPassword == user_list[i].password) {
                return 'u';
            }
        }
    }
}

void account_manage::registration(fstream &accountFile, vector<account> &admin_list, vector<account> &user_list)  {
    account tmp_acc;
    getusername:
    cout << "USERNAME: ";
    getline(cin, tmp_acc.username);
    if (tmp_acc.username == "") {
        goto getusername;
    }
    else    {
        for (int i=0; i<admin_list.size(); i++)  {
        if (tmp_acc.username == admin_list[i].username)  {
            cout << "This username has already been taken!" << endl;
            goto getusername;
        }
    }
        for (int i=0; i<user_list.size(); i++)  {
            if (tmp_acc.username == user_list[i].username)  {
                cout << "This username has already been taken!" << endl;
                goto getusername;
            }
        }
    }
    
    get_password:
    cout << "PASSWORD: ";
    getline(cin, tmp_acc.password);
    if (tmp_acc.password == "") {
        goto get_password;
    }
    user_list.push_back(tmp_acc);
    accountFile << endl;
    accountFile << ";" << tmp_acc.username << ";" << tmp_acc.password;
    cout << "Successfully registered!" << endl;
}

void account_manage::forget_password(vector<account> &admin_list, vector<account> &user_list) {
    vector<account> account_list;
    for (int i=0; i<admin_list.size(); i++) {
        account_list.push_back(admin_list[i]);
    }
    for (int i=0; i<user_list.size(); i++)  {
        account_list.push_back(user_list[i]);
    }
    
    string fusername;
    forgetP:
    cout << "Enter USERNAME: ";
    getline(cin, fusername);
    for (int i=0; i<account_list.size(); i++)   {
        if (fusername == account_list[i].username)  {
            cout << "Your password is: " << account_list[i].password << endl;
            break;
        }
        else if (i==account_list.size()-1)   {
            cout << "Your username did not match any account!" << endl;
            goto forgetP;
            break;
        }
    }
}

void account_manage::delete_account(fstream &user_file, vector<account> &user_list)   {
    del_username:
    cout << "Enter username you want to delete: ";
    string dusername;
    getline(cin, dusername);
    if (dusername == "")    {
        goto del_username;
    }
    else    {
        for (int i=0; i<user_list.size(); i++)  {
            if (dusername == user_list[i].username) {
                cout << "Enter password to confirm: ";
                string dpassword;
                getline(cin, dpassword);
                if (dpassword == user_list[i].password) {
                    user_list.erase(user_list.begin()+i);
                }
            }
        }
    }
}