#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

using namespace std;

const int maxrow = 100;
class Client{
    public:
        string ClientName[maxrow]={};
        string AccountNumber[maxrow]={};
        string Pin[maxrow]={};
        string Amount[maxrow]={};

        int choice;
        int i = 0;
        int x = 0;

        char name[50];
        char accnum[10];
        char pin[10];
        char amount[10];

        int dispalyChoice() {
            cout << "Enter 1 to create account" << endl;
            cout << "Enter 2 to check balance" << endl;
            cout << "Enter 3 to deposite balance " << endl;
            cout << "Enter 4 to withdraw balance " << endl;
            cout << "Enter 5 to Exit " << endl;
            cout << "Enter your choice " << endl;
            cin >> choice;
            return choice;
        }

        bool displayOption(){ 
            bool status = false;          
            cin.ignore();   
            cout << "Enter your name " << endl;
            cin.getline(name, 50);
            cout << "Enter your account number " << endl;
            cin.getline(accnum, 10);
            cout << "Enter your pin " << endl;
            cin.getline(pin, 10);

            if (choice == 1){
                cout << "Enter opening balance amount " << endl;
                cin.getline(amount, 10);
            }
            

            for (i; i < maxrow; i++){
                if (choice == 1 && Amount[i] == "\0"){ //check if array is empty or not
                   Amount[i] = amount;
                   Pin[i] = pin;
                   AccountNumber[i] = accnum;
                   ClientName[i] = name;
                   status = true;
                   break;

                }else if ( ClientName[i] == name && AccountNumber[i] == accnum && Pin[i] == pin){
                    status = true;
                    break;
                }
                
            }

            return status;

        }

        void createAccount(){
            bool status = displayOption();
            if (status == true)
            {
                saveToFile();
                cout << "Account created successfully " << endl;
            }else{ 
                cout<<"Account already exist or something went wrong"<< endl;
            }
            i = 0;            
        }

        void displayBalance(){
            bool status = displayOption();
            if (status == true)
            {
                cout << "      Name        |    Account number     |      Balance      " <<endl
                << "--------------------------------------------------------------------\n";
                cout << "      "<<  ClientName[i] <<"            "<< AccountNumber[i] <<"              "<< Amount[i] << endl;
                cout <<"--------------------------------------------------------------------"<<endl<<endl;
            }else{
                cout << "Account not found " << endl;
            }

            i = 0;
        }

        void deposite(){
            bool status = displayOption();
            if (status == true){
                double deposite_amount;
                cout << "Enter amount to deposite " << endl;
                cin >> deposite_amount;
                double oldAmount = stod(Amount[i]);
                Amount[i] = to_string(oldAmount + deposite_amount);
                cout << "Amount deposited successfully " << endl;
            }
            else{
                cout << "Account not found " << endl;
            }

            i = 0;
        }

        void withdraw(){
            bool status = displayOption();
            if (status == true){
                double withdraw_amount;
                cout << "Enter amount to withdraw " << endl;
                cin >> withdraw_amount;
                double oldAmount = stod(Amount[i]);
                if (oldAmount > withdraw_amount)
                {
                    Amount[i] = to_string(oldAmount - withdraw_amount);
                    cout << "Amount withdrawn successfully, thank you! " << endl;
                }else{
                    cout << "Insufficient balance " << endl;
                }
                
            }else{
                cout << "Account not found " << endl;
            }

            i = 0;
        }

        void openFile(){
            string line;
            ifstream file("client.txt");
            if (file.is_open()) {
                while (getline(file, line)) {
                    // Split the line into individual values
                    stringstream ss(line);
                    string value;
                    vector<string> values;
                    while (getline(ss, value, ' ')) {
                        values.push_back(value);
                    }

                    // Check if the line has the expected number of values
                    if (values.size() == 5) {
                        // Extract the values and store them in the arrays
                        Amount[x] = values[4];
                        Pin[x] = values[3];
                        AccountNumber[x] = values[2];
                        ClientName[x] = values[0] + " " + values[1];
                    }
                    x++;
                }
                file.close();
            } else{
                cout << "File not found " << endl;
            }

        }

        void saveToFile(){
            ofstream file("client.txt", ios::out);
            if (file.is_open()) {
                for (int i = 0; i <= x; i++) {
                    if (Pin[i] == "\0"){
                        break;
                    }else{
                        file << ClientName[i] << " " << AccountNumber[i] << " " << Pin[i] << " " << Amount[i] << endl;
                    }
                }
                file.close();
            }
        }

        

        
};

int main() {
    Client client;
    system("CLS");
    client.openFile();
    int choice = 0;
    do{
        choice = client.dispalyChoice();
        switch (choice){
            case 1:
                client.createAccount();
                break;
            
            case 2:
                client.displayBalance();
                break;

            case 3:
                client.deposite();
                break;

            case 4:
                client.withdraw();
                break;

            default:
                break;
        }

    } while(choice!=5);
    
    return 0;
}