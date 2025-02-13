// language: C++

// *******************************************************************************************
// Employee Management System (Payroll Management System)
// This console-based application manages employee records including secure user 
// authentication (login/signup) and CRUD operations for employee data.
// 
// Target Users: Developers and HR personnel responsible for managing payroll details.
// Code Style: Follows a Doxygen-inspired documentation style for clarity and maintainability.
// *******************************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <functional>

using namespace std;

/**
 * @brief Moves the cursor to the specified (x, y) position on the console.
 *
 * This function is used to enhance the UI by placing prompts and output at 
 * specific locations on the console screen, improving readability.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 */
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

class Menu;  // Forward declaration to resolve circular dependency

/**
 * @brief Encapsulates various income-related attributes for an employee.
 *
 * This class handles salary components such as base salary, bonus, allowances,
 * tax, and loan deductions. Each setter enforces the constraint that the value
 * must be positive.
 */
class Income
{
private:
    float baseSalary;
    float loan;
    float bonus;
    float tax;
    float medicalAllowance;
    float travelAllowance;

public:
    Income()
    {
        // Initialize income components to zero.
        baseSalary = 0.0;
        loan = 0.0;
        bonus = 0.0;
        tax = 0.0;
        medicalAllowance = 0.0;
        travelAllowance = 0.0;
    }

    float GetBaseSalary() const { return baseSalary; }

    /**
     * @brief Sets the base salary after validating it's greater than zero.
     * @param baseSalary The base salary input from the user.
     */
    void SetBaseSalary(float baseSalary)
    {
        if (baseSalary > 0)
        {
            this->baseSalary = baseSalary;
        }
        else
        {
            // Loop until a valid salary is provided.
            do
            {
                cout << "\nEnter a valid salary (must be greater than 0): ";
                cin >> baseSalary;
            } while (baseSalary < 0);
            this->baseSalary = baseSalary;
        }
    }

    float GetLoan() const { return loan; }

    void SetLoan(float loan)
    {
        if (loan > 0)
        {
            this->loan = loan;
        }
        else
        {
            // Prompt repeatedly until loan is valid
            do
            {
                cout << "\nEnter a valid loan amount (must be greater than 0): ";
                cin >> loan;
            } while (loan < 0);
            this->loan = loan;
        }
    }

    float GetBonus() const { return bonus; }

    void SetBonus(float bonus)
    {
        if (bonus > 0)
        {
            this->bonus = bonus;
        }
        else
        {
            // Allow only positive bonus values.
            do
            {
                cout << "\nEnter a valid bonus (must be greater than 0): ";
                cin >> bonus;
            } while (bonus < 0);
            this->bonus = bonus;
        }
    }

    float GetTax() const { return tax; }

    void SetTax(float tax)
    {
        if (tax > 0)
        {
            this->tax = tax;
        }
        else
        {
            // Ensure tax value is non-negative.
            do
            {
                cout << "\nEnter a valid tax amount (must be greater than 0): ";
                cin >> tax;
            } while (tax < 0);
            this->tax = tax;
        }
    }

    float GetMedicalAllowance() const { return medicalAllowance; }

    void SetMedicalAllowance(float medicalAllowance)
    {
        if (medicalAllowance > 0)
        {
            this->medicalAllowance = medicalAllowance;
        }
        else
        {
            // Validate medical allowance input.
            do
            {
                cout << "\nEnter a valid medical allowance (must be greater than 0): ";
                cin >> medicalAllowance;
            } while (medicalAllowance < 0);
            this->medicalAllowance = medicalAllowance;
        }
    }

    float GetTravelAllowance() const { return travelAllowance; }

    void SetTravelAllowance(float travelAllowance)
    {
        if (travelAllowance > 0)
        {
            this->travelAllowance = travelAllowance;
        }
        else
        {
            // Validate travel allowance ensuring positive value.
            do
            {
                cout << "\nEnter a valid travel allowance (must be greater than 0): ";
                cin >> travelAllowance;
            } while (travelAllowance < 0);
            this->travelAllowance = travelAllowance;
        }
    }
};

/**
 * @brief Represents an employee and associates personal details with income.
 *
 * This class stores basic employee data such as code, grade, date of joining,
 * name, address, phone, designation, and income details. It also contains input 
 * routines to safely read user input.
 */
class Employee
{
protected:
    int employeeCode;
    int grade;
    int dd;
    int mm;
    int yy;
    char name[26];
    char address[31];
    char phone[11];
    char designation[16];

public:
    Income income;

    int GetEmployeeCode() const { return employeeCode; }

    void SetEmployeeCode(int employeeCode)
    {
        if (employeeCode > 0)
        {
            this->employeeCode = employeeCode;
        }
        else
        {
            // Loop to enforce a valid employee code.
            do
            {
                cout << "\nEmployee Code must be greater than 0. Re-enter: ";
                cin >> employeeCode;
            } while (employeeCode < 0);
            this->employeeCode = employeeCode;
        }
    }

    int GetGrade() const { return grade; }

    void SetGrade(int grade)
    {
        if (grade > 0)
        {
            this->grade = grade;
        }
        else
        {
            // Validate employee grade ensuring positive value.
            do
            {
                cout << "\nGrade must be greater than 0. Re-enter grade: ";
                cin >> grade;
            } while (grade < 0);
            this->grade = grade;
        }
    }

    int GetDd() const { return dd; }
    void SetDd(int dd) { this->dd = dd; }

    int GetMm() const { return mm; }
    void SetMm(int mm) { this->mm = mm; }

    int GetYy() const { return yy; }
    void SetYy(int yy) { this->yy = yy; }

    string GetName() const { return name; }

    void SetName(string Name)
    {
        // Copy only up to the buffer limit and ensure null termination.
        int length = (Name.size() < 25 ? Name.size() : 25);
        Name.copy(name, length);
        name[length] = '\0';  
    }

    string GetAddress() const { return address; }

    void SetAddress(string Address)
    {
        int length = (Address.size() < 30 ? Address.size() : 30);
        Address.copy(address, length);
        address[length] = '\0';
    }

    string GetPhone() const { return phone; }

    void SetPhone(string Phone)
    {
        int length = (Phone.size() < 10 ? Phone.size() : 10);
        Phone.copy(phone, length);
        phone[length] = '\0';
    }

    string GetDesignation() const { return designation; }

    void SetDesignation(string Designation)
    {
        int length = (Designation.size() < 15 ? Designation.size() : 15);
        Designation.copy(designation, length);
        designation[length] = '\0';
    }

    /**
     * @brief Validates the provided date ensuring realistic employee birth or joining dates.
     *
     * The date is considered valid if it is within the realistic range (days, months)
     * and the year is between 1950 and 2004.
     *
     * @param day Day part of the date.
     * @param month Month part of the date.
     * @param year Year part of the date.
     * @return int Returns 1 if valid; otherwise, returns 0.
     */
    int validDate(int day, int month, int year)
    {
        int valid = 1;
        if (month < 1 || month > 12)
            valid = 0;
        if (day < 1 || day > 31)
            valid = 0;
        else if (((year % 4) != 0 && month == 2 && day > 28) || ((year % 4) == 0 && month == 2 && day > 29))
            valid = 0;
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            valid = 0;
        if (year < 1950 || year > 2004)
            valid = 0;
        return valid;
    }

    /**
     * @brief Reads employee details interactively from the console.
     *
     * This method clears the console and then collects all required details.
     * It ensures proper validation for fields such as date and positive numeric inputs.
     */
    void Get_Input(void)
    {
        int ecode;
        string ename, eaddress, ephone, edesig;
        int egrade, d, m, y;
        float ebaseSalary, eloan, ebonus, etax, emedicalAllowance, etravelAllowance;
        system("CLS");  // Clear console for a fresh input screen.
        gotoxy(30, 10);
        cout << "\nEnter Employee Name: ";
        fflush(stdin);
        getline(cin, ename);
        this->SetName(ename);
        
        cout << "\nEnter Employee Code: ";
        cin >> ecode;
        this->SetEmployeeCode(ecode);
        
        cout << "\nEnter Employee Address: ";
        fflush(stdin);
        getline(cin, eaddress);
        this->SetAddress(eaddress);
        
        cout << "\nEnter Employee Phone Number: ";
        fflush(stdin);
        getline(cin, ephone);
        this->SetPhone(ephone);
        
        // Enforce valid date input for employee record.
        cout << "\nEnter Date (DD MM YY): ";
        do
        {
            cin >> d >> m >> y;
            if (!validDate(d, m, y))
            {
                cout << "\nInvalid date. Please re-enter (DD MM YY): ";
            }
        } while (!validDate(d, m, y));
        this->dd = d;
        this->mm = m;
        this->yy = y;
        
        cout << "\nEnter Designation: ";
        fflush(stdin);
        getline(cin, edesig);
        this->SetDesignation(edesig);
        
        cout << "\nEnter Employee Grade: ";
        cin >> egrade;
        this->SetGrade(egrade);
        
        cout << "\nEnter Employee Base Salary: ";
        cin >> ebaseSalary;
        this->income.SetBaseSalary(ebaseSalary);
        
        cout << "\nEnter Employee Loan Amount: ";
        cin >> eloan;
        this->income.SetLoan(eloan);
        
        cout << "\nEnter Employee Bonus: ";
        cin >> ebonus;
        this->income.SetBonus(ebonus);
        
        cout << "\nEnter Employee Tax Amount: ";
        cin >> etax;
        this->income.SetTax(etax);
        
        cout << "\nEnter Employee Medical Allowance: ";
        cin >> emedicalAllowance;
        this->income.SetMedicalAllowance(emedicalAllowance);
        
        cout << "\nEnter Employee Travel Allowance: ";
        cin >> etravelAllowance;
        this->income.SetTravelAllowance(etravelAllowance);
    }
};

/**
 * @brief Outputs the details of an employee to the provided stream.
 *
 * This helper function calculates the final salary after applying bonuses and deductions,
 * and then outputs the formatted employee information.
 *
 * @param output The output stream (console, file, etc.).
 * @param obj The Employee object containing the data.
 */
void Output(ostream& output, const Employee &obj)
{
    float Salary = obj.income.GetBaseSalary() + obj.income.GetBonus() +
                   obj.income.GetMedicalAllowance() + obj.income.GetTravelAllowance() -
                   obj.income.GetTax() - obj.income.GetLoan();
    output << endl << right << "Employee Code: " << obj.GetEmployeeCode();
    output << left << "\nEmployee Name: " << obj.GetName() << "\nEmployee Address: " << obj.GetAddress();
    output << "\nEmployee Phone Number: " << obj.GetPhone() << "\nEmployee Designation: " << obj.GetDesignation();
    output << "\nEmployee Grade: " << obj.GetGrade() << "\nEmployee Salary: " << Salary << endl;
    Sleep(50);  // Brief pause for UI readability.
}

/**
 * @brief Manages user authentication via login and signup.
 *
 * This class handles input and validation for user credentials. It ensures 
 * password input is masked and verifies credentials against stored data.
 */
class Log_Sign
{
private:
    string UserName;
    string Password = "";
    string User;
    string Pass;

public:
    Log_Sign() {}  ///< Default constructor

    /**
     * @brief Authenticates a user based on input credentials.
     *
     * The function reads username and masks user password input, then checks
     * credentials against stored records. Loops for a maximum of 3 attempts.
     *
     * @return true if authentication is successful, false otherwise.
     */
    bool Login()
    {
        int count = 0, temp = 1;
        system("CLS");
        cout << "Enter Username: " << endl;
        fflush(stdin);
        getline(cin, UserName);
        cout << "Enter Password: " << endl;
        fflush(stdin);

        // Mask password input for security.
        char ch;
        Password.clear();
        ch = _getch();
        while (ch != 13)  // Enter key has ASCII 13.
        {
            Password.push_back(ch);
            cout << '*';
            ch = _getch();
        }

        // Validate credentials from user data file.
        ifstream myfile("userData.txt");
        while (myfile >> User >> Pass)
        {
            if (User == UserName && Pass == Password)
            {
                count = 1;
            }
        }
        myfile.close();

        if (count == 1)
        {
            cout << "\nLOGIN SUCCESSFUL." << endl;
            system("PAUSE");
            return true;
        }
        else
        {
            temp += 1;
            if (temp > 3)  // Allow a maximum of three attempts.
            {
                return false;
            }
            else
            {
                cout << "\nInvalid credentials. Please try again." << endl;
                system("PAUSE");
                return false;
            }
        }
    }

    /**
     * @brief Registers a new user by storing credentials into a persistent file.
     *
     * The function prompts for a username and masks the password input before appending 
     * the credentials to a storage file.
     */
    void Signup()
    {
        system("CLS");
        gotoxy(40, 8);
        cout << "\nEnter a new Username: ";
        cin >> UserName;
        cout << "\nEnter a Password: ";
        fflush(stdin);

        char ch;
        Password.clear();
        ch = _getch();
        while (ch != 13)
        {
            Password.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        // Append new user credentials to persistent storage.
        ofstream file("userData.txt", ios::app);
        file << UserName << " " << Password << endl;
        file.close();

        cout << "\nRegistration Successful." << endl;
        system("PAUSE");
    }
};

/**
 * @brief Provides administrative functionalities for employee data management.
 *
 * Inherits from Employee for record manipulation and includes methods to 
 * add, search, delete, and list employee records stored in a file.
 */
class Admin : public Employee
{
private:
    /**
     * @brief Finds the record number for a given employee code.
     *
     * This helper method iterates over the file records to locate the matching employee.
     *
     * @param ecode Employee code for which the record number is searched.
     * @return int The record number or position in the file.
     */
    int RECORDNO(int ecode)
    {
        Employee employee;
        fstream file;
        file.open("EMPLOYEE.DAT", ios::in);
        file.seekg(0, ios::beg);
        int recno = 0;
        while (file.read((char *)&employee, sizeof(employee)))
        {
            recno++;
            if (employee.GetEmployeeCode() == ecode)
                break;
        }
        file.close();
        return recno;
    }

public:
    Admin() {}  ///< Default constructor

    /**
     * @brief Adds a new employee record to the persistent storage.
     *
     * Facilitates user input and then writes the record to the "EMPLOYEE.DAT" file.
     */
    void addEmployee(void)
    {
        Employee obj;
        // Collect employee details interactively.
        obj.Get_Input();
        ofstream file;
        file.open("EMPLOYEE.DAT", ios::out | ios::app);
        file.write((char *)&obj, sizeof(Employee));
        file.close();
    }

    /**
     * @brief Deletes an employee record based on provided employee code.
     *
     * The function copies all records except the one matching the code into a temporary file,
     * then replaces the original file with the temporary file.
     */
    void deleteRecord(void)
    {
        int ecode;
        cout << "\nEnter Employee Code to delete record: ";
        cin >> ecode;
        fstream file;
        file.open("EMPLOYEE.DAT", ios::in);
        fstream temp;
        temp.open("temp.dat", ios::out);
        file.seekg(0, ios::beg);
        while (!file.eof())
        {
            file.read((char *)this, sizeof(Employee));
            if (file.eof())
                break;
            if (this->GetEmployeeCode() != ecode)
                temp.write((char *)this, sizeof(Employee));
        }
        file.close();
        temp.close();

        // Replace original file with modified data.
        file.open("EMPLOYEE.DAT", ios::out);
        temp.open("temp.dat", ios::in);
        temp.seekg(0, ios::beg);
        while (!temp.eof())
        {
            temp.read((char *)this, sizeof(Employee));
            if (temp.eof())
                break;
            file.write((char *)this, sizeof(Employee));
        }
        file.close();
        temp.close();
    }

    /**
     * @brief Searches for and displays an employee record by code.
     *
     * Reads the employee record from the file and outputs the data if found.
     */
    void searchRecord(void)
    {
        int ecode;
        cout << "\nEnter Employee Code to search for: ";
        cin >> ecode;
        Employee obj;
        ifstream file;
        file.open("EMPLOYEE.DAT", ios::in);
        if (!file.fail())
        {
            file.seekg(0, ios::beg);
            file.read((char *)&obj, sizeof(Employee));
            while (!file.eof())
            {
                if (obj.GetEmployeeCode() == ecode)
                {
                    Output(cout, obj);
                    break;
                }
                file.read((char *)&obj, sizeof(Employee));
            }
            if (file.eof())
            {
                cout << "\nRecord Not Found. Please check the Employee Code." << endl;
            }
        }
        file.close();
    }

    /**
     * @brief Lists all employee records sorted by grade in descending order.
     *
     * Reads records into a vector, sorts them based on grade, and outputs the list.
     */
    void list(void)
    {
        Employee obj, temp;
        vector<Employee> x;
        ifstream file;
        file.open("EMPLOYEE.DAT", ios::in);
        if (!file.fail())
        {
            file.seekg(0, ios::beg);
            file.read((char *)&obj, sizeof(Employee));
            while (!file.eof())
            {
                x.push_back(obj);
                file.read((char *)&obj, sizeof(Employee));
            }
            // Sort employees by grade in descending order.
            for (int i = 0; i < x.size(); i++)
            {
                for (int j = 0; j < x.size() - i - 1; j++)
                {
                    if (x[j].GetGrade() < x[j + 1].GetGrade())
                    {
                        temp = x[j + 1];
                        x[j + 1] = x[j];
                        x[j] = temp;
                    }
                }
            }
            file.close();
            if (x.empty())
            {
                cout << "\nNo employee records found." << endl;
                return;
            }
            // Output each employee record.
            for (int i = 0; i < x.size(); i++)
            {
                Output(cout, x[i]);
            }
        }
    }
};

/**
 * @brief Provides the main menu structure for the payroll management system.
 *
 * Displays options for both authentication and administrative operations.
 */
class Menu
{
private:
    Admin admin;

public:
    /**
     * @brief Displays the main menu and handles user navigation.
     *
     * Manages the login/signup process and then routes the user to various admin functions.
     */
    void mainMenu(void)
    {
        system("CLS");
        gotoxy(65, 2);
        int choice2;
        int success;
y:
        cout << "\n:::::::::::: XYZ Payroll Management System ::::::::::::::" << endl;
        gotoxy(60, 5);
        cout << "\n1. Login\n2. Register\n";
        cout << "Enter your choice: ";
        cin >> choice2;
        Log_Sign A;
        switch (choice2)
        {
        case 1:
x:
            success = A.Login();
            break;
        case 2:
            A.Signup();
            goto x;
            break;
        default:
            cout << "\nInvalid choice. Exiting application." << endl;
            exit(EXIT_FAILURE);
            break;
        }
        if (success)
        {
            int exitStatus = 0;
            while (!exitStatus)
            {
                system("CLS");
                gotoxy(50, 2);
                cout << "\n1. Add Employee Record\n2. Delete Employee Record\n3. Search Employee\n4. Display Employee List\n5. Exit Program\n";
                int choice;
                cout << "\nEnter your option: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    admin.addEmployee();
                    system("PAUSE");
                    break;
                case 2:
                    admin.deleteRecord();
                    system("PAUSE");
                    break;
                case 3:
                    admin.searchRecord();
                    Sleep(55);
                    system("PAUSE");
                    break;
                case 4:
                    admin.list();
                    system("PAUSE");
                    break;
                case 5:
                    exitStatus = 1;
                    exit(EXIT_SUCCESS);
                default:
                    cout << "Invalid option selected. Exiting program." << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        system("CLS");
        goto y;  // Return to the main menu loop.
    }

    /**
     * @brief Displays an introductory welcome screen.
     *
     * Outputs a banner message along with developer credits using a timed animation
     * to enhance user experience.
     */
    void Intro(void)
    {
        int i;
        string p = " WELCOME TO OUR CONSOLE BASED PAYROLL MANAGEMENT SYSTEM ";
        gotoxy(20, 10);

        // Display border characters with slight delays.
        for (i = 0; i < 12; i++)
        {
            Sleep(55);
            cout << ":";
        }
        for (i = 0; i < p.size(); i++)
        {
            Sleep(50);
            cout << p[i];
        }
        for (i = 0; i < 12; i++)
        {
            Sleep(55);
            cout << ":";
        }

        // Show project developer information.
        string d = "A Project developed by:";
        gotoxy(49, 0);
        for (i = 0; i < d.size(); i++)
        {
            Sleep(50);
            cout << d[i];
        }
        string S = "Muhammad Talha Bilal (21K-3349)";
        string I = "Emmanuel (21K-4871)";
        string Y = "Muhammad Hamza (21K-4579)";
        gotoxy(50, 1);
        for (i = 0; i < S.size(); i++)
        {
            Sleep(50);
            cout << S[i];
        }
        gotoxy(50, 2);
        for (i = 0; i < I.size(); i++)
        {
            Sleep(50);
            cout << I[i];
        }
        gotoxy(50, 3);
        for (i = 0; i < Y.size(); i++)
        {
            Sleep(50);
            cout << Y[i];
        }
    }
};

/**
 * @brief The application's main entry point.
 *
 * Initializes the menu, displays the introduction, and then starts the main menu flow.
 *
 * @return int Application exit status.
 */
int main()
{
    system("color f4");  // Sets console color for visual consistency.
    Menu menu;
    menu.Intro();
    system("CLS");
    menu.mainMenu();
    return 0;
}