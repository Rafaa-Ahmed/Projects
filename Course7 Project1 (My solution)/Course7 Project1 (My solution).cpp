#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = R"(C:\Users\DELL 5490\source\repos\Courses\Projects\Course7 Project1 (My solution)\ClientsRecords.txt)";

enum enChoice
{
    ShowClients = 1,
    Add = 2,
    Delete = 3,
    Update = 4,
    Find = 5,
    Exit = 6
};

struct stClientRecord
{
    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

// Prototypes
void MainMenu();
void MoveToScreen(enChoice Choice, vector<stClientRecord>& vClientsRecords);

enChoice GetChoice(short Choice)
{
    switch (Choice)
    {
    case 1:
        return enChoice::ShowClients;

    case 2:
        return enChoice::Add;

    case 3:
        return enChoice::Delete;

    case 4:
        return enChoice::Update;

    case 5:
        return enChoice::Find;

    case 6:
        return enChoice::Exit;

    default:
        return enChoice::ShowClients;
    }
}

stClientRecord ReadClientRecord(string AccountNumber)
{
    stClientRecord Client;

    Client.AccountNumber = AccountNumber;

    cout << "\nEnter PIN code? ";
    getline(cin >> ws, Client.PINCode);

    cout << "\nEnter Name? ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);

    cout << "\nEnter account balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;

    short pos = 0;
    string sWord = "";

    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

string ConvertRecordToLine(stClientRecord Client, string Separator = "#//#")
{
    string sClientRecord = "";

    sClientRecord += Client.AccountNumber + Separator;
    sClientRecord += Client.PINCode + Separator;
    sClientRecord += Client.Name + Separator;
    sClientRecord += Client.Phone + Separator;
    sClientRecord += to_string(Client.AccountBalance);

    return sClientRecord;
}

stClientRecord ConvertLineToRecord(string Line, string Separator = "#//#")
{
    stClientRecord Client;

    vector<string> vClientsRecords =
        SplitString(Line, Separator);

    if (vClientsRecords.size() >= 5)
    {
        Client.AccountNumber = vClientsRecords[0];
        Client.PINCode = vClientsRecords[1];
        Client.Name = vClientsRecords[2];
        Client.Phone = vClientsRecords[3];
        Client.AccountBalance = stod(vClientsRecords[4]);
    }

    return Client;
}

vector<stClientRecord> LoadClientsDataFromFile(string FileName)
{
    vector<stClientRecord> vClientsRecords;

    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;

        stClientRecord Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClientsRecords.push_back(Client);
        }

        MyFile.close();
    }

    return vClientsRecords;
}

void SaveClientsDataToFile(vector<stClientRecord>& vClientsRecords, string FileName)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        string DataLine;

        for (stClientRecord& C : vClientsRecords)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);

                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber;

    cout << "\nPlease enter account number? ";
    cin >> AccountNumber;

    return AccountNumber;
}

void PrintClientCard(stClientRecord Client)
{
    cout << "\nThe following are the client details:\n";

    cout << "----------------------------------------\n";

    cout << "Account Number : " << Client.AccountNumber;
    cout << "\nPIN Code       : " << Client.PINCode;
    cout << "\nName           : " << Client.Name;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAccount Balance: "
        << Client.AccountBalance;

    cout << "\n----------------------------------------\n";
}

bool FindClientByAccountNumber(const string& AccountNumber, const vector<stClientRecord>& vClientsRecords,stClientRecord& Client)
{
    for (const stClientRecord& C : vClientsRecords)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;

            return true;
        }
    }

    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClientRecord>& vClientsRecords)
{
    for (stClientRecord& C : vClientsRecords)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;

            return true;
        }
    }

    return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClientRecord>& vClientsRecords)
{
    stClientRecord Client;

    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClientsRecords, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to delete "
            << "this client? Y/N? ";

        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            MarkClientForDeleteByAccountNumber(
                AccountNumber,
                vClientsRecords);

            SaveClientsDataToFile(
                vClientsRecords,
                ClientsFileName);

            vClientsRecords =
                LoadClientsDataFromFile(
                    ClientsFileName);

            cout << "\nClient deleted successfully.\n";

            return true;
        }
    }

    else
    {
        cout << "\nClient with account number (" << AccountNumber << ") is not found.\n";
    }

    return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClientRecord>& vClientsRecords)
{
    stClientRecord Client;

    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClientsRecords, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to update "
            << "this client? Y/N? ";

        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            for (stClientRecord& C : vClientsRecords)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ReadClientRecord(AccountNumber);

                    break;
                }
            }

            SaveClientsDataToFile(
                vClientsRecords,
                ClientsFileName);

            cout << "\nClient updated successfully.\n";

            return true;
        }
    }
    else
    {
        cout << "\nClient with account number (" << AccountNumber << ") is not found.\n";
    }

    return false;
}

void AddNewClientByAccountNumber(string AccountNumber, vector<stClientRecord>& vClientsRecords)
{
    stClientRecord Client;

    char Answer = 'Y';

    while (toupper(Answer) == 'Y')
    {
        while (FindClientByAccountNumber(AccountNumber, vClientsRecords, Client))
        {
            cout << "\nClient with account number (" << AccountNumber << ") already exists.\n";

            cout << "Enter another account number? ";

            cin >> AccountNumber;
        }

        Client = ReadClientRecord(AccountNumber);

        vClientsRecords.push_back(Client);

        SaveClientsDataToFile(vClientsRecords, ClientsFileName);

        cout << "\nClient added successfully.\n";

        cout << "\nDo you want to add more clients? "
            << "Y/N? ";

        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            AccountNumber = ReadClientAccountNumber();
        }
    }
}

void PrintClientData(stClientRecord Client)
{
    cout << left << "| " << setw(16) << Client.AccountNumber;
    cout << left << "| " << setw(10) << Client.PINCode;
    cout << left << "| " << setw(30) << Client.Name;
    cout << left << "| " << setw(14) << Client.Phone;
    cout << left << "| " << setw(10) << Client.AccountBalance;
}

void GoBackToMainMenu()
{
    cout << "\n\nPress any key to continue...";
    system("pause >0");

    system("cls");
    MainMenu();
}

void ShowClientList(const vector<stClientRecord> vClientsRecords)
{
    cout << "\t\t\t\tClient List (" << vClientsRecords.size() << ") Client(s).";

    cout << "\n____________________________________________________________________________________________________________________\n";

    cout << "| " << left << setw(16) << "Account Number";
    cout << "| " << left << setw(10) << "PIN Code";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(14) << "Phone";
    cout << "| " << left << setw(10) << "Balance";

    cout << "\n____________________________________________________________________________________________________________________\n";

    for (const stClientRecord& C : vClientsRecords)
    {
        PrintClientData(C);

        cout << endl;
    }

    cout << "\n____________________________________________________________________________________________________________________\n";

    GoBackToMainMenu();
}

void AddNewClientsScreen(vector<stClientRecord>& vClientsRecords)
{
    cout << "---------------------------------------------\n";

    cout << "\t\t Add New Clients Screen\n";

    cout << "---------------------------------------------\n";

    AddNewClientByAccountNumber(ReadClientAccountNumber(), vClientsRecords);

    GoBackToMainMenu();
}

void DeleteClientScreen(vector<stClientRecord>& vClientsRecords)
{
    cout << "---------------------------------------------\n";

    cout << "\t\t Delete Client Screen\n";

    cout << "---------------------------------------------\n";

    DeleteClientByAccountNumber(ReadClientAccountNumber(), vClientsRecords);

    GoBackToMainMenu();
}

void UpdateClientScreen(vector<stClientRecord>& vClientsRecords)
{
    cout << "---------------------------------------------\n";

    cout << "\t\t Update Client Info Screen\n";

    cout << "---------------------------------------------\n";

    UpdateClientByAccountNumber(ReadClientAccountNumber(), vClientsRecords);

    GoBackToMainMenu();
}

void FindClientScreen(vector<stClientRecord>& vClientsRecords)
{
    stClientRecord Client;

    cout << "---------------------------------------------\n";

    cout << "\t\t Find Client Screen\n";

    cout << "---------------------------------------------\n";

    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClientsRecords, Client))
    {
        PrintClientCard(Client);
    }

    else
    {
        cout << "\nClient with account number (" << AccountNumber << ") is not found.\n";
    }

    GoBackToMainMenu();
}

void ExitScreen()
{
    cout << "---------------------------------------------\n";

    cout << "\t\tProgram Ends :-)\n";

    cout << "---------------------------------------------\n";
}

void MoveToScreen(enChoice Choice, vector<stClientRecord>& vClientsRecords)
{
    system("cls");

    switch (Choice)
    {
    case enChoice::ShowClients:
        ShowClientList(vClientsRecords);
        break;

    case enChoice::Add:
        AddNewClientsScreen(vClientsRecords);
        break;

    case enChoice::Delete:
        DeleteClientScreen(vClientsRecords);
        break;

    case enChoice::Update:
        UpdateClientScreen(vClientsRecords);
        break;

    case enChoice::Find:
        FindClientScreen(vClientsRecords);
        break;

    case enChoice::Exit:
        ExitScreen();
        break;
    }
}

void MainMenu()
{
    vector<stClientRecord> vClientsRecords = LoadClientsDataFromFile(ClientsFileName);

    short Choice = 1;

    cout << "=========================================\n";

    cout << "\t Main Menu Screen\n";

    cout << "=========================================\n";

    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";

    cout << "=========================================\n";

    cout << "Choose what you want to do? [1 to 6]? ";

    cin >> Choice;

    MoveToScreen(GetChoice(Choice), vClientsRecords);
}

int main()
{
    MainMenu();

    return 0;
}