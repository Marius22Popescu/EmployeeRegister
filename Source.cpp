/****************************************************************
*Employee Database
*Team Project
*Marius Popescu, Caleb Brothers, Derek Clark, and Baylee Ezati
*11/28/15
*Modified on 12/07/15
*This program keeps track of employees and their pay rates, commission, monthly sales, etc
*/
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Employee
{
	string name;
	int empID;
	string department;
	double payRate;
	double commission;
	int hoursWorked;
	double sales;
};
struct Pay
{
	int id;
	double rate;
};
struct Name
{
	string name;
	int id;
};

//Prototype functions
void fileInput(vector<Employee> &emp);
void fileOutput(vector<Employee> &emp);
int displayMenu();
void addEmp(vector<Employee> &emp);
void deleteEmp(vector<Employee> &emp);
int editMenu();
void editPayRate(vector<Employee> &emp);
void editCommission(vector<Employee>&emp);
void editHours(vector<Employee>&emp);
void sortByPayRate(vector <Employee> &emp);
void sortByName(vector <Employee> &emp);
void displayEmp(vector <Employee> &emp);
void getSales(vector<Employee> &emp);
double calcExpenses(vector<Employee> &emp);

int main()
{
	vector<Employee> emp;
	int userChoice;
	int editChoice;
	double totalExpenses = 0;
	do
	{
		userChoice = displayMenu();
		switch (userChoice)
		{
		case 1:
			fileInput(emp);
			addEmp(emp);
			fileOutput(emp);
			break;
		case 2:
			fileInput(emp);
			displayEmp(emp);
			fileOutput(emp);
			break;
		case 3:
			fileInput(emp);
			deleteEmp(emp);
			fileOutput(emp);
			break;
		case 4:
			fileInput(emp);
			editChoice = editMenu();
			if (editChoice == 1)
				editPayRate(emp);
			else if (editChoice == 2)
				editHours(emp);
			else
				editCommission(emp);
			fileOutput(emp);
			break;
		case 5:
			fileInput(emp);
			getSales(emp);
			fileOutput(emp);
			break;
		case 6:
			fileInput(emp);
			totalExpenses = calcExpenses(emp);
			cout << "\nTotal Expenses: $" << totalExpenses << endl;
			fileOutput(emp);

		default:
			break;
		}

	} while (userChoice != 0);
	
	return 0;
}

/*
fileInput
created by Baylee Ezati and Derek Clark
created on 12/04/15
This function takes a vector of employees passed by reference and fills it with information from a flat file
called "Employees.txt"
*/
void fileInput(vector<Employee> &emp)
{
	ifstream fin;
	Employee temp;

	emp.clear();
	fin.open("Employees.txt");
	if (fin.is_open())
	{
		while (isalnum(fin.peek()))
		{
			int i = 0;
			getline(fin, temp.name);
			fin >> temp.empID;
			fin.ignore(100, '\n');
			getline(fin, temp.department);
			fin >> temp.payRate;
			fin.ignore(100, '\n');
			fin >> temp.commission;
			fin.ignore(100, '\n');
			fin >> temp.hoursWorked;
			fin.ignore(100, '\n');
			fin >> temp.sales;
			fin.ignore(100, '\n');
			emp.push_back(temp);
			i++;
		}
		fin.close();
	}
	else
		cout << "\nError: The file could not be opened";
	return;
}

/*
fileOutput
created by Baylee Ezati and Derek Clark
created on 12/04/15
This function takes a vector of employees passed by reference and it outputs it into a flat file
called "Employees.txt"
*/
void fileOutput(vector<Employee> &emp)
{
	ofstream fout;
	fout.open("Employees.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < emp.size(); i++)
		{
			fout << emp[i].name << endl;
			fout << emp[i].empID << endl;
			fout << emp[i].department << endl;
			fout << emp[i].payRate << endl;
			fout << emp[i].commission << endl;
			fout << emp[i].hoursWorked << endl;
			fout << emp[i].sales << endl;
		}
		fout.close();
	}
	else
		cout << "\nError: The file could not be opened";
	return;
}

/*
addEmp
created by Baylee Ezati
created on 12/04/15
This program takes a vect of Employees passed by references and adds/fills
a new Employee element to the end of it
*/
void addEmp(vector<Employee> &emp)
{
	Employee temp;
	cout << endl;
	cout << "Please enter the name of the employee: ";
	getline(cin, temp.name);
	cout << "Please enter the employee ID number: ";
	cin >> temp.empID;
	cin.ignore(100, '\n');
	cout << "Please enter the department: ";
	getline(cin, temp.department);
	cout << "Please enter the pay rate: ";
	cin >> temp.payRate;
	cin.ignore(100, '\n');
	cout << "Please enter the commission rate (or 0 if not in sales department): ";
	cin >> temp.commission;
	cin.ignore(100, '\n');
	cout << "Please enter the weekly hours worked: ";
	cin >> temp.hoursWorked;
	cin.ignore(100, '\n');
	temp.sales = 0;
	emp.push_back(temp);
	return;
}

/*
deleteEmp
created by Baylee Ezati
created on 12/04/15
This program takes a vect of Employees passed by references and deletes
an employee based on the user's input
*/
void deleteEmp(vector<Employee> &emp)
{
	bool empFound = false;
	int empToDelete;
	cout << "Enter the ID number for the employee to delete: ";
	cin >> empToDelete;
	cin.ignore(100, '\n');

	for (int i = 0; i<emp.size(); i++)
	{
		if (emp[i].empID == empToDelete)
		{
			empFound = true;
			cout << emp[i].name << " was successfully deleted.";
			emp.erase(emp.begin() + i);
		}
	}
	if (empFound == false)
	{
		cout << "The employee could not be found.";
	}
	return;

}

/*
editPayRate
created by Baylee Ezati
created on 12/06/15
This function takes a vect of Employees passed by references and asks the user to enter the
new payRate for the employee of their choice
*/
void editPayRate(vector<Employee>&emp)
{
	int empToEdit;
	double newPayRate;
	bool empFound = false;
	cout << "Enter the ID number for the employee to edit: ";
	cin >> empToEdit;
	cin.ignore(100, '\n');

	for (int i = 0; i<emp.size(); i++)
	{
		if (emp[i].empID == empToEdit)
		{
			empFound = true;
			empToEdit = i;
		}
	}
	if (empFound == true)
	{
		cout << "Please enter the new pay rate for " << emp[empToEdit].name << ": ";
		cin >> newPayRate;
		cin.ignore(100, '\n');
		emp[empToEdit].payRate = newPayRate;
		cout << "Pay rate was successfully edited";
	}
	else
		cout << "The employee could not be found";
	return;
}
/*
editCommission
created by Marius Popescu
created on 12/06/15
This function takes a vect of Employees passed by references and asks the user to enter the
new commission rate for an employee of their choice
*/
void editCommission(vector<Employee>&emp)
{
	int empToEdit;
	double newCommission;
	bool empFound = false;
	cout << "Enter the ID number for the employee to edit: ";
	cin >> empToEdit;
	cin.ignore(100, '\n');

	for (int i = 0; i<emp.size(); i++)
	{
		if (emp[i].empID == empToEdit)
		{
			empFound = true;
			empToEdit = i;
		}
	}
	if (empFound == true)
	{
		cout << "Please enter the new commission rate for " << emp[empToEdit].name << ": ";
		cin >> newCommission;
		cin.ignore(100, '\n');
		emp[empToEdit].commission = newCommission;
		cout << "Pay rate was successfully edited";
	}
	else
		cout << "The employee could not be found";
	return;
}

/*
editHours
created by Marius Popescu
created on 12/06/15
This function takes a vect of Employees passed by references and asks the user to enter the
new hours worked for an employee of their choice
*/
void editHours(vector<Employee>&emp)
{
	int empToEdit;
	double newHours;
	bool empFound = false;
	cout << "Enter the ID number for the employee to edit: ";
	cin >> empToEdit;
	cin.ignore(100, '\n');

	for (int i = 0; i<emp.size(); i++)
	{
		if (emp[i].empID == empToEdit)
		{
			empFound = true;
			empToEdit = i;
		}
	}
	if (empFound == true)
	{
		cout << "Please enter the weekly hours worked for " << emp[empToEdit].name << ": ";
		cin >> newHours;
		cin.ignore(100, '\n');
		emp[empToEdit].hoursWorked = newHours;
		cout << "Weekly hours was successfully edited";
	}
	else
		cout << "The employee could not be found";
	return;
}

void sortByPayRate(vector <Employee> &emp)
{
	vector <Pay> payVec;
	Pay tempEmployee;

	//copies payrates into vector
	for (int j = 0; j < emp.size(); j++)
	{
		tempEmployee.id = j;
		tempEmployee.rate = emp[j].payRate;
		payVec.push_back(tempEmployee);
	}

	//sorts payrates
	for (int i = 0; i < payVec.size(); i++)
	{
		for (int j = 0; j < payVec.size() - 1; j++)
		{
			if (payVec[j + 1].rate >= payVec[j].rate)
			{
				Pay temp = payVec[j];
				payVec[j] = payVec[j + 1];
				payVec[j + 1] = temp;
			}
		}
	}

	//sorts emp vector based on original ID (backwards)
	Employee *temp = new Employee[payVec.size()];
	for (int i = 0; i < payVec.size(); i++)
	{
		temp[i] = emp[payVec[i].id];
	}
	for (int i = 0; i < emp.size(); i++)
	{
		emp[i] = temp[i];
	}
	delete[] temp;

	//reverses vector
	if (emp[0].payRate <= emp[emp.size() - 1].payRate)
	{
		for (int i = 0; i < emp.size() / 2; i++)
		{
			Employee temp = emp[i];
			emp[i] = emp[emp.size() - (1 + i)];
			emp[emp.size() - (1 + i)] = temp;
		}
	}

}

/*
*Written by Derek Clark
*Date created 12/6/15
*Last modified 12/6/15
*This function sorts the employee vector by name
*It requires the employee vector
*It returns the modified employee vector
*/
void sortByName(vector <Employee> &emp)
{
	vector <Name> nameList;
	Name tempName;

	//copies names to nameList
	for (int i = 0; i < emp.size(); i++)
	{
		tempName.id = i;
		tempName.name = emp[i].name;
		nameList.push_back(tempName);
	}

	//sorts names
	for (int i = 0; i < nameList.size(); i++)
	{
		for (int j = 0; j < nameList.size() - 1; j++)
		{
			if (nameList[j + 1].name >= nameList[j].name)
			{
				Name temp = nameList[j];
				nameList[j] = nameList[j + 1];
				nameList[j + 1] = temp;
			}
		}
	}

	//sorts name vector based on original ID (backwards)
	Employee *temp = new Employee[nameList.size()];
	for (int i = 0; i < nameList.size(); i++)
	{
		temp[i] = emp[nameList[i].id];
	}
	for (int i = 0; i < emp.size(); i++)
	{
		emp[i] = temp[i];
	}
	delete[] temp;

	//reverses vector
	for (int i = 0; i < emp.size() / 2; i++)
	{
		Employee temp = emp[i];
		emp[i] = emp[emp.size() - (1 + i)];
		emp[emp.size() - (1 + i)] = temp;
	}
}

/*
*Written by Derek Clark
*Date created 12/6/15
*Last modified 12/6/15
*This function displays details on one employee
*It requires the vector of employees
*it returns no value
*/
void displayEmp(vector <Employee> &emp)
{
	int choice;

	cout << "Select Employee to view: " << endl;
	for (int i = 0; i < emp.size(); i++)
	{
		cout << i + 1 << ". " << emp[i].name << endl;
	}
	cin >> choice;

	cout << "*********************************************" << endl;
	cout << emp[choice - 1].name << "        ID: " << emp[choice - 1].empID << endl;
	cout << "Department: " << emp[choice - 1].department << endl;
	cout << "Hours Worked: " << emp[choice - 1].hoursWorked << endl;
	if (emp[choice - 1].sales != 0)
		cout << "Sales: $" << emp[choice - 1].sales << endl;
	if (emp[choice - 1].commission != 0)
		cout << "Commission: " << emp[choice - 1].commission << "%" << endl;
	cout << "*********************************************";
}

/*
getSales
created by Baylee Ezati
created on 12/06/15
This function takes a vect of Employees passed by references and asks the user to enter the
month's sales for every employee in the sales department
*/
void getSales(vector<Employee> &emp)
{
	for (int i = 0; i<emp.size(); i++)
	{
		if (emp[i].department == "sales" || emp[i].department == "Sales" || emp[i].department == "SALES")
		{
			cout << "Please enter the month's sales for " << emp[i].name << ": $";
			cin >> emp[i].sales;
			cin.ignore(100, '\n');
		}
	}
}

/*
calcExpenses
created by Baylee Ezati
created on 12/06/15
This function takes a vect of Employees passed by references and calculates the amount
spent on employee salary and commission
*/
double calcExpenses(vector<Employee> &emp)
{
	double expenses = 0;
	for (int i = 0; i<emp.size(); i++)
	{
		expenses += (emp[i].hoursWorked*emp[i].payRate * 4);
		if (emp[i].commission != 0)
		{
			cout << "*********************************************" << endl;
			cout << emp[i].name << endl;
			cout << "$" << (emp[i].hoursWorked*emp[i].payRate) + (emp[i].commission*emp[i].sales) << endl;
			cout << "*********************************************" << endl;
			expenses += (emp[i].commission*emp[i].sales);
		}
		else
			cout << "*********************************************" << endl;
		cout << emp[i].name << endl;
		cout << "$" << (emp[i].hoursWorked*emp[i].payRate) << endl;
		cout << "*********************************************" << endl;

	}
	return expenses;
}

/*
displayMenu
created by Baylee Ezati
created on 12/06/15
This function displays a menu of options regarding employee information and
returns an int value between 0-6 representing the user's selection. If
the user attempts to input a number output a number out of the range,
the function will ask the user to input a valid option
*/
int displayMenu()
{
	int input;
	cout << "\nPlease select an option: " << endl;
	cout << "1-Add an employee" << endl;
	cout << "2-View employees" << endl;
	cout << "3-Delete an employee" << endl;
	cout << "4-Edit an employee" << endl;
	cout << "5-Input month's sales" << endl;
	cout << "6-View pay roll" << endl;
	cout << "0-Exit" << endl;
	cin >> input;
	cin.ignore(100, '\n');
	while (input<0 || input>6)
	{
		cout << "Please enter a valid option: ";
		cin >> input;
		cin.ignore(100, '\n');
	}
	return input;
}

/*
editMenu
created by Baylee Ezati
created on 12/06/15
This function displays a menu of options regarding editing employee information and
returns an int value between 1-3 representing the user's selection. If
the user attempts to input a number output a number out of the range,
the function will ask the user to input a valid option
*/
int editMenu()
{
	int input;
	cout << "Please select an option: " << endl;
	cout << "1-Edit pay rate" << endl;
	cout << "2-Edit weekly hours" << endl;
	cout << "3-Edit commission" << endl;
	cin >> input;
	while (input<1 || input>3)
	{
		cout << "Please enter a valid option: ";
		cin >> input;
		cin.ignore(100, '\n');
	}
	return input;
}
