#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//global vector to store the total in days
vector<int> Daysin; 
//declaring function protocols
bool registeredAlready(vector<vector<string>>&window, string reg);

//function to display the record of one student
void display(vector<string> row, int index);

//function to register a new student
void registration(vector<vector<string>> &window);

//function to store data into data.csv file (file handling)
void save_data(vector<vector<string>> &window);

//to search the record for a student
int search(vector<vector<string>> window);

//function to change mess status from in to out or vice versa
void changestatus(vector<vector<string>> &window);

//function to display total number of students registered
void totalstu(vector<vector<string>>window);

//function to delete student
void delstu(vector<vector<string>>&window);

//function to calculate total bill
void caltotalbill(vector<vector<string>> &window);

int main()
{
    int option, index;
    vector<vector<string>> window; //A table to store names, regNo, and status

    //front page
    cout << "\n\t\t\t <<<<<GIKI MESS SYSTEM>>>>>";
    cout << "\n\t\t\t\t <<<<MAIN>>>" << endl;
    while(true)
    {
        cout << "|-> Enter <1> to register a new student"<<endl;;
        cout << "|-> Enter <2> to search the student record"<<endl;
        cout << "|-> Enter <3> to change mess status"<<endl;
        cout << "|-> Enter <4> to delete a student record"<<endl;
        cout << "|-> Enter <5> to print total in/out students"<<endl;
        cout << "|-> Enter <6> to calculate total bill of a student"<<endl;
        cout << "|-> Enter <0> to save data and exit"<<endl;
        cout << "Input the option you want to select"<<endl;
        cin >> option;

        switch(option)
        {
            case 1:
            {
                cout << "\n\n\t <<<Register New Student>>>"<<endl;
                registration(window);
                save_data(window);
                break;
            }
            case 2:
            {
                cout << "\n\n\t<<<Search Student Record>>>"<<endl;
                try
                {
                    index = search(window);
                    if(index==-1)
                    {
                        throw("Student not found !!!");
                        
                    }
                    else
                    {
                        cout << "Student found ..." << endl;
                        display(window[index],index);
                    }
                }
                catch(const char* error)
                {
                    cout << error;
                }

                break;
                
            }
            case 3:
            {
                cout << "\n\n\tChange Status"<<endl;
                changestatus(window);
                save_data(window);
                break;
            }
            case 4:
            {
                cout << "\n\n\tDelete Student Record"<<endl;
                delstu(window);
                save_data(window);
                break;
            }
            case 5:
            {
                cout << "\n\n\tTotal IN/OUT Students"<<endl;
                totalstu(window);
                break;
            }
            case 6:
            {
                cout<<"\n\n\tTotal bill of the student"<<endl;
                caltotalbill(window);
                break;
            }
            case 0:
            {
                save_data(window);
                break;
            }
            default:
            {
                cout << "Wrong option, Please enter the correct option" << endl;
                break;
            }

        }
        if(option==0)
        {
            break;
        }
        cout << endl;

    }
        cout << "Data has been saved, now exiting" << endl;
        cout << "Thank you for using GIKI mess system" << endl;
        save_data(window);
        return 0;
        
}

bool registeredAlready(vector<vector<string>>&window, string reg)
{
    int temp;
    for(int i=0;i<window.size();i++)
    {
        if(window[i][1]==reg)
        {
            temp = 1;
            
        }
        else
        {
            temp = 0;
        }
        
    }
    return temp;
}


void display(vector<string> row, int index)
{
    cout <<"\nStudent Name: "<<row[0];
    cout <<"\n Registration number: "<<row[1];
    cout <<"\n Mess status: "<<row[2];
    cout <<"\n Total in days: "<< Daysin[index];

}

void registration(vector<vector<string>> &window)
{
    try
    {
        string name, reg, status;
        vector<string> row;
        cin.ignore();
        cout << "Enter Student name: "<<endl;
        getline(cin,name);
        cout << "Enter registration number: ";
        cin >> reg;
        if(registeredAlready(window, reg))
        {
            throw("Student already registered!!!");
        }
    
        cout << "Enter mess status (In/Out): " << endl;
        cin>>status;
        row.push_back(name);
        row.push_back(reg);
        row.push_back(status);
        window.push_back(row);
        if(status=="In")
        {
            Daysin.push_back(1);
        }
        else
        {
            Daysin.push_back(0);
        }
        cout << "New student has been registered..."<<endl;
    }
    catch(const char* error)
    {
        cout << error;
    }

}

void save_data(vector<vector<string>> &window)
{
    fstream file("data.csv", ios::out); //writing in file data.csv
    file<<"Reg No., Name, Status, In-Days"<<endl; //columns
    for(int i=0; i<window.size();i++)
    {
        file<<window[i][1]<<","<<window[i][0]<<","<<window[i][2]<<","<<Daysin[i]<<endl;
    }
    file.close();
}

int search(vector<vector<string>> window)
{
    int index=-1;   //function used later in change status functions, therefore value taken -1 so that it dont intersect the value in loop later
    string reg;
    cout << "Enter student registration number: "<<endl;
    cin >> reg;
    for(int i=0;i<window.size();i++)
    {
        if(window[i][1]==reg)
        {
            index = i;
            break;
        }
    }
    return index;
}

void changestatus(vector<vector<string>> &window)
{
    try
    {
        int index = search(window);
        if(index== -1)
        {
            throw("\n Student not found!!!");
        }
        else
        {
            cout << "Student found: " << endl;
            display(window[index], index);
            string status;
            cout << endl;
            cout << "Enter new status (In/Out): "<<endl;
            cin >> status;
            window[index][2];
            int days;
            days = Daysin[index];
            if(status== "In")
            {
                days++;
                Daysin[index]=days;
                cout << "Status updated";
            }
            else if(status=="Out")
            {
                window[index][2]="Out";

            }

        }
    }
    catch(const char* error)
    {
        cout << error;
    }
}

void totalstu(vector<vector<string>>window)
{
    int in, out;
    in = 0;
    out = 0;
    for(int i=0;i<window.size();i++)
    {
        if(window[i][2]=="In")
        {
            in++;
        }
        else if(window[i][2]=="Out")
        {
            out++;
        }
    }
    cout << endl;
    cout << "Total in students: " << in << endl;
    cout << "Total out students: "<< out << endl;

}

void delstu(vector<vector<string>>&window)
{
    try
    {
        int index = search(window);
        if(index == -1)
        {
            throw("\nStudent not found !!!");
        }
        else
        {
            cout << "Student Found ... "<< endl;
            display(window[index], index);
            string status;
            window.erase(window.begin() + index);
            cout << "\nStudent record has been deleted"<<endl;
        }
    }
    catch(const char* error)
    {
        cout << error;
    }
}

void caltotalbill(vector<vector<string>> &window)
{
    try
    {
        int index = search(window);
        if(index == -1)
        {
            throw("Student not found !!!");
        }
        else
        {
            cout << "Student Found ..."<< endl;
            display(window[index], index);
            int totbill = Daysin[index] * 300;
            cout << "Total days in: " << Daysin[index]<<endl;
            cout << "Cost of mess per day: 300 "<< endl;
            cout << "Total Bill of the student: " << totbill << endl;

        }
    }
    catch(const char* error)
    {
        cout << error;
    }
}

