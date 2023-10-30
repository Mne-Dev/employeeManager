#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

string Username;
string Password;

class Employee
{
    public:
        int Age;
        string Gender;
        string BloodType; // AB+,AB-,A+,A-,B+,B-,0+,0-
        string FullName;
        string University;
        string Field;


        int Experience;
        int Salary;
};

void printEmployees()
{
    DIR *dr;
   struct dirent *en;
   dr = opendir("Employees/"); //open all directory
   if (dr) {
      while ((en = readdir(dr)) != NULL) {
         cout<<" \n"<<en->d_name; //print all directory name
      }
      closedir(dr); //close all directory
   }
}

void DatabaseCreator(Employee object)
{
    ofstream Data("Employees/" + object.FullName, std::ios_base::app | std::ios_base::out);

    Data << "Yas: "          << object.Age          << "\n";
    Data << "Cinsiyet: "     << object.Gender       << "\n";
    Data << "Kan grubu: "    << object.BloodType    << "\n";
    Data << "Tam Ad: "       << object.FullName     << "\n";
    Data << "Universite: "   << object.University   << "\n";
    Data << "Alan: "         << object.Field        << "\n";
    Data << "Tecrube: "      << object.Experience   << "\n";
    Data << "Maas: "         << object.Salary       << "\n";
}

bool login(string username, string password)
{
    if(username == Username && password == Password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{

    fstream fileUsername("Data/username", ios::in);
    fstream filePassword("Data/password", ios::in);

    fileUsername >> Username;
    filePassword >> Password;


    if (Username == "admin" && Password == "admin")
    {
        cout << "Yeni kullanici adini girin: (bosluk yerine alt tire kullanin)" << endl;
        cin >> Username;
        cout << "Yeni sifreyi girin: (bosluk yerine alt tire kullanin)" << endl;
        cin >> Password;

        fileUsername.close();
        filePassword.close();

        fileUsername.open("Data/username", ios::out | ios::trunc);
        filePassword.open("Data/password", ios::out | ios::trunc);

        fileUsername << Username;
        filePassword << Password;

        cout << "Lutfen yeniden giris yapin" << endl;
        return 0;
    }
    else
    {
        string credUsername;
        string credPassword;

        cout << "Lutfen kullanici adinizi yaziniz" << endl;
        cin >> credUsername;
        cout << "Lutfen sifrenizi yaziniz" << endl;
        cin >> credPassword;

        if(login(credUsername, credPassword))
        {
            int choice;

            cout << "Merhabalar! Lutfen bir islem seciniz." << endl;
            cout << "1-Calisan ekleme" << endl;
            cout << "2-Calisan silme" << endl;
            cin >> choice;
            

            if(choice == 1)
            {
                    Employee human;
                    cout << "Lutfen cevaplarken bosluk yerine alt tire (_) kullanin" << endl;
                    cout << "Calisanin yasini giriniz" << endl;
                    cin >> human.Age;
                    cout << "Calisanin cinsiyetini giriniz (M-Erkek F-Kadin)" << endl;
                    cin >> human.Gender;
                    cout << "Calisanin kan grubunu giriniz" << endl;
                    cin >> human.BloodType;
                    cout << "Calisanin tam adini giriniz" << endl;
                    cin >> human.FullName;
                    cout << "Calisanin bitirdigi universiteyi giriniz" << endl;
                    cin >> human.University;
                    cout << "Calisanin ilgilendigi alani giriniz" << endl;
                    cin >> human.Field;
                    cout << "Calisanin deneyimini yil cinsinden giriniz" << endl;
                    cin >> human.Experience;
                    cout << "Calisanin yillik maasini giriniz" << endl;
                    cin >> human.Salary;

                    DatabaseCreator(human);

                    cout << "Calisan olusturuldu!" << endl;
                    return 0;
            }
            else if(choice == 2)
            {
                string fileName;
                printEmployees();
                cout << "\nLutfen bilgisi silinecek calisani giriniz" << endl;
                cin >> fileName;
                fileName = "Employees/" + fileName;
                if(remove(fileName.c_str()) != 0)
                {
                    cout << "Calisan silinemedi!" << endl;
                }
                else
                {
                    cout << "Calisan silindi!" << endl;
                }
            }
            else
            {
                cout << "Yanlis giris!" << endl;
                fileUsername.close();
                filePassword.close();
                return 0;
            }
        }
        else
        {
            cout << "Sifre veya kullanici adinizi yanlis girdiniz!";
        }

    }

    fileUsername.close();
    filePassword.close();

}
