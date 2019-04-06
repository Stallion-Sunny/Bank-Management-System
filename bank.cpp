// Declaration of header files
#include <iostream.h>
#include <fstream.h>
#include <process.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iomanip.h>


typedef char option[15];
const int ROW = 10,COL = 10;

int scan;	// To hold the special characters for moving the prompt in menu
int ascii;

// To display the main menu options
option a[]= {
			  "NewAccount",
			 "ListofAccounts",
			 "IndAccount",
			 "DailyTrans",
			 "MonthlyReport",
			 "EditAccount",
			 "Exit"};

// Displays the modify menu options
option b[] = {
				"Modify Account",
				"Closeaccount",
				"Quit"
			};

// Function used to do screening
class main_menu
{
	int i,done;

	public:
		void normalvideo(int x,int y,char *str);
		void reversevideo(int x,int y,char *str);
		void box(int x1,int y1,int x2,int y2);
		char menu();
		void control_menu();
		char e_menu();
		void edit_menu();
		void help(void);
};

/* Class member functions for drawing boxes */
class shape
{
	public:
		void line_hor(int, int, int, char);
		void line_ver(int, int, int, char);
		void box(int, int, int, int, char);
};


// Class contains the initial deposit of customers
class initial
{
	public:
		void add_to_file(int, char t_name[30], char t_address[30], float);	// For initial deposits in customers account
		void display_list(void); // Displaying customers account list
		void delete_account(int); // Deleting customers account
		void update_balance(int, char t_name[30], char t_address[30], float); // For updating the customer account
		void modify(void);   	// To modify the customer account information
		int last_accno(void); // To know the last account number
		int found_account(int); // To found the account is in "INITIAL.dat" or not

		char *return_name(int); // Function for validation entry of customer name
		char *return_address(int); // Function for validation entry of customer address
		float give_balance(int); // To print the balance amount of a particular customer
		int recordno(int);
		void display(int); // To display the customer account

	private:
		void modify_account(int, char t_name[30], char t_address[30]);	// Function to modify the customer account
		int accno;
		char name[30], address[30];
		float balance;
};

// Class contains the customers daily transaction entry

class account
{
	public:
		void new_account(void);  // Function to create a new account
		void close_account(void);	// Function to close an account
		void display_account(void); // Function to display the accounts
		void transaction(void); // To display the transaction process
		void clear(int, int); // Function to perform a clear screen function
		void month_report(void); // Function to list monthWise transaction report

	private:
		void add_to_file(int, int, int, int, char, char t_type[10], float, float, float); // Function to add transaction records
		void delete_account(int); // Function to delete a transaction record
		int no_of_days(int, int, int, int, int, int); // Function to find the total days
		float calculate_interest(int, float); // Function for calculating interest of an account
		void display(int); // Function to display a transaction account
		void box_for_display(int); // Function for displaying box
		int accno;
		char type[10];	// Account type as Cheque or Cash
		int dd, mm, yy; // To store the system date/ Enter date
		char tran;			// As the account type is Deposit or Withdraw
		float interest, amount, balance;
};

// Function to displays all the menu prompt messages from the pointer array of option a[]
void main_menu::normalvideo(int x,int y,char *str)
{
   gotoxy(x,y);
   cprintf("%s",str);
}

// Function to move the cursor on the menu prompt with a reverse video color
void main_menu::reversevideo(int x,int y,char *str)
{
	textcolor(5+143);
	textbackground(WHITE);
	gotoxy(x,y);
	cprintf("%s",str);
	textcolor(GREEN);
	textbackground(BLACK);
}

void main_menu::box(int x1,int y1,int x2,int y2)
{
	 for(int col=x1;col<x2;col++)
	 {
		   gotoxy(col,y1);
		   cprintf("%c",196);
		   gotoxy(col,y2);
		   cprintf("%c",196);
	 }

	 for(int row=y1;row<y2;row++)
	 {
		   gotoxy(x1,row);
		   cprintf("%c",179);
		   gotoxy(x2,row);
		   cprintf("%c",179);
	 }
	 gotoxy(x1,y1);
	 cprintf("%c",218);
	 gotoxy(x1,y2);
	 cprintf("%c",192);
	 gotoxy(x2,y1);
	 cprintf("%c",191);
	 gotoxy(x2,y2);
	 cprintf("%c",217);
}

char main_menu::menu()
{
	clrscr();

	textcolor(22);
	box(20, 6, 65, 20);
	box(18, 4, 67, 22);
	textcolor(5+143);
	gotoxy(36, 5);
	textbackground(BLUE);
	gotoxy(20,5);
	cputs(" $$$$$$$$$$$$$$ B A N K I N G  $$$$$$$$$$$$$$$");
	textbackground(BLACK);
	textcolor(22);
	for(i = 1; i < 7; i++)
	normalvideo(32, i+10, a[i]);
	reversevideo(32, 10, a[0]);
	i = done = 0;
	_setcursortype(_NOCURSOR);
	do
	{
		int key = getch();
		switch (key)
		{
			case 00:
				key = getch();
				switch (key)
				{
					case 72:
						normalvideo(32, i+10, a[i]);
						i--;
						if (i == -1)
							i = 6;
						reversevideo(32,i+10,a[i]);
						break;
					case 80:
						normalvideo(32, i+10, a[i]);
						i++;
						if (i == 7)
							i = 0;
						reversevideo(32, i+10, a[i]);
						break;
				}
				break;
			case 13:
				done = 1;
		}
	}
	while (!done);
	_setcursortype(_NOCURSOR);
	return(i+49);
}

/* The function main_menu() is used to display the main menu of banking system/
 The function uses 6 main options and each has its specific purposes for maintaining the account. In this memu
 if the user will press within 1 to 6 then the subsequent facility will avail, otherwise, if will press any other key
 then the prompt will come back from the menu to your source program. Or it is better to press '0' for existing from the menu. Other than 0 and 1..6 if your press
 any other key the banking system does not response you but still in same screen till a valid number. */
void main_menu::control_menu()
{

	char choice;
	account a;

	do
	{
		choice = menu();
		clrscr();
		switch (choice)
		{
			case '1':
				_setcursortype(_NORMALCURSOR);
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				a.new_account(); // New account member function
				break;
			case '2':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				initial ini;
				ini.display_list(); // Glogal list of account function
				break;
			case '3':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				 _setcursortype(_NORMALCURSOR);
				a.display_account(); // Displaying individual accounts all transactions
				break;
			case '4':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				account a;
				_setcursortype(_NORMALCURSOR);
				a.transaction(); // Daily transaction for individual account
				 break;
			case '5':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				_setcursortype(_NORMALCURSOR);
				a.month_report(); // Monthly report for any account
				break;
			case '6':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				gotoxy(10,10);
				edit_menu(); // Sub menu for modifying or deleting any account
				break;
			case '7' :exit(0);
		   }
	  } while (choice != 6);
}

/* This function is used to return the cursor position to the edit menu function where the
menu prompt will valid */

char main_menu::e_menu()
{
	clrscr();

	textcolor(22);
	box(25,6,60,15);
	box(23,4,62,17);
	textcolor(5+143);

	gotoxy(34,5);
	textbackground(GREEN);
	cprintf("E D I T  -  M E N U");
	textcolor(22);
	textbackground(BLACK);
	for (i = 1;i < 3; i++)
		normalvideo(32, i+10, b[i]);

	reversevideo(32, 10, b[0]);
	i = done = 0;

	_setcursortype(_NOCURSOR);
	do
	{
		int key = getch();
		switch (key)
		{
			case 00:
				key = getch();
				switch (key)
				{
					case 72:
						normalvideo(32, i+10, b[i]);
						i--;
						if (i == -1)
							i = 2;
						reversevideo(32, i+10, b[i]);
						break;
					case 80:
						normalvideo(32, i+10, b[i]);
						i++;
						if (i == 3)
							i=0;
						reversevideo(32, i+10, b[i]);
						break;
				}
				break;
			case 13:
				done = 1;
		}
	}
	while (!done);
	_setcursortype(_NOCURSOR);
	return(i+49);
}

/* Function for edit menu with account modification and close
 This is the one of the submenu which manages two basic operations as:
		-	Editing any account
		-	Deleting any account
 While editing any account, you have to enter the account no, and will display the name and address of that
 particular accountee and will display a prompt as "Modify this account <y/n> :". If you will press 'y' then
 the respective information will be modified other wise will return to main menu.
 While deleting any account, you have to enter the account no. and will display the name and address of that
 particular accountee and will display a prompt as "Close this account?? ". If you will press 'y' then all the transactions from "BANKING.dat" file
 and initial deposit from "INITIAL.dat" file will be delete the information of the entered account number. */

void main_menu::edit_menu()
{

	char choice;
	account a;

	do
	{
		choice = e_menu();
		clrscr();
		switch (choice)
		{
			case '1':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				initial ini;
				_setcursortype(_NORMALCURSOR);
				ini.modify();
				break;

			case '2':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				account a;
				_setcursortype(_NORMALCURSOR);
				a.close_account();
				break;
			case '3':
				return;
		}
	} while (choice != 6);
}

/* Function to draw horizontal line
 This public function draws one horizontal line at a time */
void shape::line_hor(int column1, int column2, int row, char c)
{
	for (column1; column1 <= column2; column1++)
	{
		gotoxy(column1, row);
		cout << c;
	}
}

/* Function to draw vertical line
 This public function draws one vertical line at a time */
void shape::line_ver(int row1, int row2, int column, char c)
{
	for (row1; row1 <= row2; row1++)
	{
		gotoxy(column, row1);
		cout << c;
	}
}

/* Function for drawing box
 This function draws a box for menus */
void shape::box(int column1, int row1, int column2, int row2, char c)
{
	char ch = 218;
	char c1, c2, c3, c4;
	char l1 = 196, l2 = 179;
	if (c == ch)
	{
		c1 = 218;
		c2 = 191;
		c3 = 217;
		c4 = 217;
		l1 = 196;
		l2 = 179;
	}
	else
	{
		c1 = c;
		c2 = c;
		c3 = c;
		c4 = c;
		l1 = c;
		c2 = c;
	}
	gotoxy(column1, row1);
	cout << c1;
	gotoxy(column2, row1);
	cout << c2;
	gotoxy(column1, row2);
	cout << c3;
	gotoxy(column2, row2);
	cout << c4;
	column1++;
	column2--;
	line_hor(column1, column2, row1, l1); //Horizontal line
	line_hor(column1, column2, row2, l1);
	column1--;
	column2++;
	row1++;
	row2--;
	line_ver(row1, row2, column1, l2); // Vertical line
	line_ver(row1, row2, column2, l2);
}


/* Function to display help about this project
 This help function is the first screen output display to know about the menu options and about the
 banking project */
void main_menu::help(void)
{      textbackground(RED);

       textcolor(YELLOW);
       clrscr();
       textcolor(RED+BLINK);

	gotoxy(1,1) ;
	delay(900);
	gotoxy(1,1);
	cout<<"\n This program is capable of holding any no. of account.";
	delay(500);
	gotoxy(1,30);cout<< "\n -In first option you can open new account";
	delay(500);
	gotoxy(1,40);cout<<"\n -In second option you can see the list of all the accounts";
	delay(500);
	gotoxy(5,60);cout<<"\n -In third option you can see all the transaction of individual account";
	delay(500);
	gotoxy(6,70);cout<< "\n -Through fourth optiion you can do banking transactions";
	delay(300);
	gotoxy(7,80);cout<< "  (Deposit/Withdraw)";
	delay(500);
	gotoxy(8,90); "\n -In fifth option you can take monthWise individual account report";
	delay(500);
	gotoxy(9,100);cout<<"\n -In sixth option you can modify or delete any account";
	delay(500);
	gotoxy(10,110);cout<<"\nNote-: Opening amount should not less that Rs. 500/-" ;
	delay(500);
	gotoxy(11,120);cout<< "\n -And last option is Quit (Exit to Window)";
	delay(500);
	gotoxy(12,130);
       cout<<"\n	Press any key to continue.........";
	getch();

}

/* Function for modifying the existing accounts
 The modify() function is used to modify an existing account for its address part only
 While modifying, a prompt is always displays as "Do you want to save change <y/n>" means
 if you will press 'y' then the current memory information will change with existing information
 otherWise the previous information remain intact in your data file.
 While entering the name and address their is a proper validation and a blank check facility is there,
 to prevent mistake and mishandling of data etc.. */
void initial::modify(void)
{
	clrscr();
	int j;
	char t_acc[10];
	int t, t_accno;
	gotoxy(17, 1);
	cout << "<0>=Exit";
	gotoxy(5,5);
	cout << "Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	if (!found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}
	gotoxy(71, 1);
	cout << "<0>=Exit";
	textbackground(WHITE);
	gotoxy(3, 3);
	for (j = 1; j<= 76; j++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(30, 3);
	cprintf("Modify Account Screen");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;		// For extracting system date
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(4, 2);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	char ch;
	display(t_accno);
	account a;
	do
	{
		a.clear(5, 13);
		gotoxy(5, 13);
		cout << "Modify this account <y/n>: ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	int modified = 0, valid;
	char t_name[30], t_address[30];
	gotoxy(5, 15);
	cout << "Name : ";
	gotoxy(5, 16);
	cout << "Address : ";

	do
	{
		a.clear(15, 15);
		a.clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Name or Press Enter for No Change";
		valid = 1;
		gotoxy(15, 15);
		gets(t_name);
		strupr(t_name);
		if (t_name[0] == '0')
			return;
		if (strlen(t_name) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Name should not greater than 25");
			getch();
		}
	} while (!valid);

	do
	{
		a.clear(15, 16);
		a.clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Address or press enter for no Change";
		valid = 1;
		gotoxy(15, 16);
		gets(t_address);
		strupr(t_address);
		if (t_address[0] == '0')
			return;
		if (strlen(t_address) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Address should not greater than 25");
			getch();
		}
	}while (!valid);

	if (strlen(t_address) > 0)
		modified = 1;
	if (!modified)
		return;
	// clears the screen at 23rd row and from 5th column
	a.clear(5,23);

	do
	{
		a.clear(5, 23);
		gotoxy(5, 18);
		cout << "Do you want to save Changes <Y/N>: ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');

	if (ch == 'N')
		return;

	// Passes the parameter to add in data file
	modify_account(t_accno, t_name, t_address);
	gotoxy(5, 21);
	cout << "\7Record modified";
	gotoxy(5, 23);
	cout << "Press any key to continue...";
	getch();
}

/* Function for displaying an account when modified
 This display() function is used to display all the account holders account no, name, address, and
 balance amount at screen.
 Here the fstream object is declared to read the data from "INITIAL.dat" data file in input mode only.
 Whenever there is record in data file, the read() statement will read the records linearly till end-of-file. */

void initial::display(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);

	// Displays the record contents matching with t_accno from INITIAL.dat data file
	while (file.read((char *)this, sizeof(initial)))
	{
		if (t_accno == accno)
		{
			gotoxy(8, 5);
			cout << "Account no. " << accno;
			gotoxy(10, 8);
			cout << "Name : ";
			puts(name);
			gotoxy(10, 9);
			cout << "Address : ";
			puts(address);
			gotoxy(10, 10);
			cout << "Balance : " << setw(15)    // setwidth
						<< setprecision(2)    // set position of decimal point
						<< setiosflags(ios::left)   // set left justified output
						<< setiosflags(ios::showpoint)  // always show decimal point
						<< setiosflags(ios::fixed)    // set fixed notation for display
						<< balance;
			break;
		}
	}
	file.close();
}

/* Function for updating the modified account into INITIAL.dat file
 This function modify_account() receives number parameters such as, account number, name, address etc, and
 will overWrite at the existing place in the "INITIAL.dat" data file.
 The main logic of the function is that, it uses a function called seekp(location), which means that
 when a particular record is tends to modify, first we have to know the record position according to data file.
 Once we find the position (location) then, a single value is decremented from its original location and overwritten
 by the same ofstream command write into the data file. */

void initial::modify_account(int t_accno, char t_name[30], char t_address[30])
{
	int recno;
	recno = recordno(t_accno);
	fstream file;
	file.open("INITIAL.dat", ios::out|ios::ate);
	strcpy(name, t_name);
	strcpy(address, t_address);
	int location;
	// finds the position in data file

	location = (recno-1) * sizeof(initial);
	file.seekp(location);

	// Overwrites the modified record into INITIAL.dat data file
	file.write((char *)this, sizeof(initial));
	file.close();
	return;
}

/* Function to find the last account number
 This is an interesting function who is creating the account number automatically.
 At the first memoment when there is no record, the new account number is created as 1.
 If any account number is there then, the file will travel all the records
 and store the last account number with a variable count. At that state the function return the same value
 the called program for automatic code generation. */
int initial::last_accno(void)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	int count = 0;

	// Founds the last account no.
	while (file.read((char *)this, sizeof(initial)))
		count = accno;
	file.close();
	return count;
}
/* This function add_to_file() is used to create new/fresh record in the data file, and the parameters
 is the actual value which will be write into the "INITIAL.dat" file. Every time when any account
 makes transaction for either Withdraw (W) or Deposit (D) the balance amount will modified in the data file*/

void initial::add_to_file(int t_accno, char t_name[30], char t_address[30], float t_balance)
{
	accno = t_accno;
	strcpy(name, t_name);
	strcpy(address, t_address);
	balance = t_balance;
	fstream file;

	// Appends new account record with the balance into INITIAL.dat data file
	file.open("INITIAL.dat", ios::out|ios::app);
	file.write((char *)this, sizeof(initial));
	file.close();
}
// Function for deleting a account from INITIAL.dat file
// This function is used to delete any account from data file. By this function
void initial::delete_account(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	fstream temp;
	temp.open("TEMP.dat", ios::out);
	file.seekg(0,ios::beg);

	// Uses a copy method to delete the account from INTITAL.dat data file
	while (!file.eof())
	{
		file.read((char *)this, sizeof(initial));
		if (file.eof())
			break;
		if (accno != t_accno)
			temp.write((char *)this, sizeof(initial));
	}
	file.close();
	temp.close();
	file.open("INITIAL.dat", ios::out);
	temp.open("TEMP.dat", ios::in);
	temp.seekg(0, ios::beg);

	// Copy the TEMP.dat contents into INTITAL.dat data file
	while (!temp.eof())
	{
		temp.read((char *)this, sizeof(initial));
		if (temp.eof())
			break;
		if (accno != t_accno)
			file.write((char *)this, sizeof(initial));
	}
	file.close();
	temp.close();
}

/* Function for add an account details of daily tranaction into BANKING.dat file.
By using the parameters the information of daily transaction appended into "BANKING.dat"
data file including amount transaction and the current balance value. */
void account::add_to_file(int t_accno, int d1, int m1, int y1, char t_tran, char t_type[10], float t_interest, float t_amount, float t_balance)
{
	fstream file;
	file.open("BANKING.dat", ios::app);
	accno = t_accno;
	getch();
	dd = d1;
	mm = m1;
	yy = y1;
	tran = t_tran;
	strcpy(type, t_type);
	interest = t_interest;
	amount = t_amount;
	balance = t_balance;

	// Appends the transaction record into BANKING.dat data file
	file.write((char *)this, sizeof(account));
	file.close();
}
/* Function for deleting an account from BANKING.dat file. This is a copy method like, when the user will input any acccount no,
 the same account no. will checked in the "BANKING.dat" file, if the account no. matched in your data file then, it will remain in
 your data file otherwise other remaining records will transferred into "TEMP.dat" data file. So, your new "TEMP.dat" file holds all
 the records execept inputed account no. On the same way make copy of all the "TEMP.dat" records back into your "BANKING.dat" file
 for restoring that your data file deletes the matched account no. */

void account::delete_account(int t_accno)
{
	fstream file;
	file.open("BANKING.dat", ios::in); // Open to read records
	fstream temp;
	temp.open("TEMP.dat", ios::out); // Open to write records
	file.seekg(0, ios::beg);	// Positioned from begining of the file

	// Uses the copy method for deleting the transaction record from BANKING.dat data file
	while (!file.eof())
	{
		file.read((char *)this, sizeof(account));
		if (file.eof())
			break;
		if (accno != t_accno)
			temp.write((char *)this, sizeof(account));
	}
	file.close();
	temp.close();
	file.open("BANKING.dat", ios::out);
	temp.open("TEMP.dat", ios::in);
	temp.seekg(0, ios::beg);

	// Uses copy method to transfer the record from TEMP.dat file to BANKING.dat data file
	while (!temp.eof())
	{
		temp.read((char *)this, sizeof(account));
		if (temp.eof())
			break;
		if (accno != t_accno)
			file.write((char *)this, sizeof(account));
	}
	file.close();
	temp.close();
}

/* Function for displaying an account from "INITIAL.dat". This function shows all account holders
 data records and their respective current balance amount at screen. Thus, the bank will be a position to know
 that there is a particular sum is available in bank. Thus, the total balance in bank can easily realised or status
 of the bank can known in the management  */
void initial::display_list(void)
{
	clrscr();
	int flag;
	float t_bal = 0.0;
	fstream file;
	gotoxy(25,2);

	cout << "Accounts List in Bank";
	gotoxy(25, 3);
	cout << "=====================";
	int d1, m1, y1;
	struct date d;		// For extracting system date
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(62, 3);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	gotoxy(1, 4);
	for (int j = 1; j <= 79; j++)
		cout << "=";

	gotoxy(1, 5);
	cout << "Accno#";
	gotoxy(10,5);
	cout << "Name";
	gotoxy(30,5);
	cout << "Address";
	gotoxy(65,5);
	cout << "Balance";
	gotoxy(1, 6);
	for (j = 1; j <= 79; j++)
		cout << "=";
	file.open("INITIAL.dat", ios::in);
	file.seekg(0,ios::beg);
	int row = 7;

	// Reads all the records to display on the screen
	while (file.read((char *)this, sizeof(initial)))
	{
		flag = 0;
		delay(2);
		gotoxy(3, row);
		cout << accno;
		gotoxy(10, row);
		puts(name);
		gotoxy(30, row);
		puts(address);
		gotoxy(65, row);

		cout <<  setw(15)
			<< setprecision(2)
			<< setiosflags(ios::left)
			<< setiosflags(ios::showpoint)
			<< setiosflags(ios::fixed)
			<< balance;
		t_bal = t_bal + balance;
		row++;
		if (row > 23)
		{
			flag = 1;
			row = 6;
			gotoxy(4, 24);
			cout << "Press any key to continue.... ";
			getch();
			clrscr();
		}
	}

	gotoxy(1, row);
	for (j = 1; j <= 79; j++)
		cout << "=";
	row++;
	gotoxy(3, row);
	cout << "Total Balance in Bank is : ";
	gotoxy(65, row);

	cout << setw(15)
		<< setprecision(2)
		<< setiosflags(ios::left)
		<< setiosflags(ios::showpoint)
		<< setiosflags(ios::fixed)
		<< t_bal;

	file.close();
	if (!flag)
	{
		gotoxy(4, 24);
		cout << "Press any key to continue...";
		getch();
	}
}

/* Function for clearing specified row and column. By using this function you can clear from a specified row and column
 from your screen. Here the function utilizes two parameter for clearing the row and column. */
void account::clear(int col, int row)
{
	for (int j = col; j <= 79; j++)
	{
		gotoxy(j, row);
		cout << " ";
	}
}

/* Function to found an account for display account function. This function is used to found any account
in the "INITIAL.dat" data file, where the file is searched from the beginning position and search
wheather the entered account exist or not. If exist then the found variable will return a value 1 or return 0 as
the parameter */
int initial::found_account(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	int found = 0;

	// Searches the specified record in INITIAL.dat data file
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			found = 1;
			break;
		}
	}
	file.close();
	return found;
}

/* Function for return name of the account holder from INITIAL.dat. This  function
basically used to return only name of the account holder if the account in the "INITIAL.dat"
data file. When the name will returned it may simply display / modify at other functions */
char *initial::return_name(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	char t_name[30];

	// Return the name to display at report screen if found
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			strcpy(t_name, name);
			break;
		}
	}
	file.close();
	return t_name;
}

/* Function for return address of the account holder from INITIAL.dat. This  function
basically used to return only address of the account holder if the account in the "INITIAL.dat"
data file. When the address will returned it may simply display / modify at other functions */
char *initial::return_address(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	char t_address[30];

	// Return the address to display at report screen if found
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			strcpy(t_address, address);
			break;
		}
	}
	file.close();
	return t_address;
}

/* Function for display account details as: This function displays the heading and the account no. name, address and current date
on the screen with other function like display_account(), month_report() etc.. Also the same function returns the account holders
name and address by using two pointer type function like return_name() and return_address(). */
void account::box_for_display(int t_accno)
{
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(63, 2);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	gotoxy(4, 2);
	cout << "Account No. " << t_accno;

	initial ini;

	char t_name[30];
	strcpy(t_name, ini.return_name(t_accno));

	char t_address[30];
	strcpy(t_address, ini.return_address(t_accno));

	gotoxy(25, 2);
	cout << t_name;
	gotoxy(25, 3);
	cout << t_address;
	gotoxy(4, 5);
	cout << "Global Report of Account";
	textbackground(WHITE);
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(1, 6);
	for (int i = 1; i <=79; i++)
		cout << "=";
	gotoxy(4, 7);
	cprintf("Date       Particular   Deposit      Withdraw                Balance");
	gotoxy(1, 8);
	for (i = 1; i <=79; i++)
		cout << "=";
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
}

/* Function for display an account from BANKING.dat file. This is a function who displays
 all the transaction of any account on screen. And the function show the account no. name, and address
 through the function box_for_display(). Also through this function it shows the total deposit, total withdraw
 and current balance amount globally. */
void account::display_account(void)
{
	clrscr();
	char t_acc[10];
	int j;
	int tamt = 0, damt = 0, wamt = 0;
	int t, t_accno;
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}

	// Display the heading from this function
	box_for_display(t_accno);

	int row = 9, flag;
	fstream file;
	file.open("BANKING.dat", ios::in);
	while (file.read((char *)this, sizeof(account)))
	{
		if (accno == t_accno)
		{
			flag = 0;
			delay(2);
			gotoxy(4, row);
			cout << dd << "-" << mm << "-" << yy;
			gotoxy(16, row);
			puts(type);
			if (tran == 'D')
			{
				damt = damt + amount;
				tamt = tamt + amount;
				gotoxy(30, row);
			}
			else
			{
				wamt = wamt + amount;
				tamt = tamt - amount;
				gotoxy(42, row);
			}

			cout <<  setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< amount;

			gotoxy(66, row);
			cout << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< balance;

			row++;
			if (row > 23)
			{
				flag = 1;
				row = 7;
				gotoxy(4, 24);
				cout << "Press any key to continue";
				getch();
				clrscr();
				box_for_display(t_accno);
			}
		}
	}
	file.close();
	gotoxy(1, row);
	for (j = 1; j <= 79; j++)
		cout << "=";
	row++;
	gotoxy(4, row);
	cout << "Total-->:";
	gotoxy(30, row);
	cout << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< damt;
	gotoxy(42, row);
	cout << setw(15)
			<< setprecision(2)
			<< setiosflags(ios::left)
			<< setiosflags(ios::showpoint)
			<< setiosflags(ios::fixed)
			<< wamt;
	gotoxy(66, row);
	cout << setw(15)
			<< setprecision(2)
			<< setiosflags(ios::left)
			<< setiosflags(ios::showpoint)
			<< setiosflags(ios::fixed)
			<< tamt;
	if (!flag)
	{
		gotoxy(4, 24);
		cout << "Press any key to continue...";
		getch();
	}
}

/* Function to list monthWise transaction report. This is a monthwise status report for any
account, and the user has to feed only any date of any month and the account no. When the date
and account no. entered the function will check all the transactions of previous month of your entered date
and find the previous balance in the variable pre_balance, which will be the "B/F ......" amount for reporting month.
Then, from that period all remaining transactions of the same entered month will display on your screen. */

void account::month_report(void)
{

	int dd1, mm1, yy1;
	clrscr();
	gotoxy(10, 5);
	cout << "Enter any date of a month ";
	gotoxy(38, 5);
	cin >> dd1;
	gotoxy(40, 5);
	cout << "-";
	gotoxy(41, 5);
	cin >> mm1;
	gotoxy(43, 5);
	cout << "-";
	gotoxy(44, 5);
	cin >> yy1;
	clrscr();
	char t_acc[10];
	int j;
	int tamt = 0, damt = 0, wamt = 0;
	int t, t_accno;
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}
	box_for_display(t_accno);
	gotoxy(4, 5);
	cout << "Statement Month: " << dd1 << "/" << mm1 << "/" << yy1;
	getch();

	int row = 9, flag;
	fstream file;
	file.open("BANKING.dat", ios::in);
	float pre_balance = 0.0; // Previous balance amount

	// The loop finds the last months balance
	while (file.read((char *)this, sizeof(account)))
	{
		// Checks the account no. and till the previous month and till current year
		if ((accno == t_accno) && ((mm < mm1 && yy <= yy1) || (mm1 < mm && yy < yy1)))
		{
			pre_balance = balance;
		}
	}

	file.close();
	file.open("BANKING.dat", ios::in);
	gotoxy(54, row);

	cout << "B/F ....    " << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< pre_balance;
	row++;

	// The loop displays the current months transaction after previous month
	while (file.read((char *)this, sizeof(account)))
	{
		if ((accno == t_accno) && (mm1 == mm && yy1 <= yy))
		{
			flag = 0;
			delay(2);
			gotoxy(4, row);
			cout << dd << "-" << mm << "-" << yy;
			gotoxy(16, row);
			puts(type);
			if (tran == 'D')
			{
				damt = damt + amount;
				tamt = tamt + amount;
				gotoxy(30, row);
			}
			else
			{
				wamt = wamt + amount;
				tamt = tamt - amount;
				gotoxy(42, row);
			}

			cout <<  setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< amount;

			gotoxy(66, row);
			cout << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< balance;
			row++;

			// If row increases 23 then the next screen continues
			if (row > 23)
			{
				flag = 1;
				row = 7;
				gotoxy(4, 24);
				cout << "Press any key to continue";
				getch();
				clrscr();
				box_for_display(t_accno);
			}
		}
	}
	file.close();
	gotoxy(1, row);
	for (j = 1; j <= 79; j++)
		cout << "=";
	row++;

	gotoxy(4, row);
	cout << "Total-->:";
	gotoxy(30, row);

	// Deposited amount
	cout << setw(15)    // setwidth
		<< setprecision(2)    // set position of decimal point
		<< setiosflags(ios::left)   // set left justified output
		<< setiosflags(ios::showpoint)  // always show decimal point
		<< setiosflags(ios::fixed)    // set fixed notation for display
		<< damt;

	gotoxy(42, row);
	// Withdraw amount
	cout << setw(15)
		<< setprecision(2)
		<< setiosflags(ios::left)
		<< setiosflags(ios::showpoint)
		<< setiosflags(ios::fixed)
		<< wamt;

	gotoxy(66, row);
	tamt = tamt + pre_balance;
	// Balance amount
	cout << setw(15)
		<< setprecision(2)
		<< setiosflags(ios::left)
		<< setiosflags(ios::showpoint)
		<< setiosflags(ios::fixed)
		<< tamt;

	if (!flag)
	{
		gotoxy(4, 24);
		cout << "Press any key to continue...";
		getch();
	}

}

/* Function for creating new account for new customer. This is a very important function
which used to create new account with all the details of the customer. This function used number
member function like last_accno(), add_to_file(), delete_account etc. The last_accno() function will create
a automatic account no. after checking from the "INITIAL.dat" file. Here the account numbers started from 1 onwards if it is the
first record.
Also in this function the validation checking occurs to the name, address, verifying person and initial deposit amount. At the time of validation checking
the name and address should not blank and not more than the specified length. And the initial deposit amount not less than Rs. 500/-. */

void account::new_account(void)
{
	char ch;
	int i, valid;
	clrscr();
	initial ini;

	shape s;
	s.box(2, 1, 79, 25, 218);
	s.box(25, 2, 54, 4, 219);

	gotoxy(65, 2);
	cout << "<0>=Exit";
	gotoxy(3,3);
	for (i = 1; i<= 76; i++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(30, 3);
	cprintf("Open New Account");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;		// For extracting system date
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	int t_accno;
	t_accno = ini.last_accno();
	t_accno++;

	// Appends and deletes a false record to create primary position in data files
	if (t_accno == 1)
	{
		ini.add_to_file(t_accno, "abc", "xyz", 1.1);
		ini.delete_account(t_accno);
		add_to_file(t_accno, 1, 1, 1997, 'D', "INITIAL", 1.1, 1.1, 1.1);
		delete_account(t_accno);
	}
	char t_name[30], t[10], t_address[30];
	float t_bal = 0.0, t_balance = 0.0;
	gotoxy(5, 6);
	cout << "Date: " << d1 << '/' << m1 << '/' << y1;
	gotoxy(5, 8);
	cout << "Account No # " << t_accno;
	gotoxy(5, 10);
	cout << "Name : ";
	gotoxy(5, 11);
	cout << "Address : ";
	gotoxy(5, 12);
	cout << "Name of verifying Person : ";
	gotoxy(5, 14);
	cout << "Initial Deposit : ";

	do
	{
		clear(15, 10);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Name of the Person";
		valid = 1;
		gotoxy(15, 10);
		gets(t_name);
		strupr(t_name);
		if (t_name[0] == '0')
			return;
		if (strlen(t_name) == 0 || strlen(t_name) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Name should not greater than 25");
			getch();
		}
	}while (!valid);

	do
	{
		clear(25, 15);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Address of the Person ";
		valid = 1;
		gotoxy(15, 11);
		gets(t_address);
		strupr(t_address);
		if (t_address[0] == '0')
			return;
		if (strlen(t_address) == 0 || strlen(t_address) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Address should not greater than 25");
			getch();
		}
	}while (!valid);

	do
	{
		char vari[30];
		clear(13, 12);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter name of the varifying Person ";
		valid = 1;
		gotoxy(31, 12);
		gets(vari);
		strupr(vari);
		if (vari[0] == '0')
			return;
		if (strlen(vari) == 0 || strlen(vari) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("Should not blank or greater than 25");
			getch();
		}
	}while (!valid);

	do
	{
		clear(13, 12);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter initial amount to be deposit ";
		valid = 1;
		gotoxy(23, 14);
		gets(t);
		t_bal = atof(t);
		t_balance = t_bal;
		if (t[0] == '0')
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Should not less than 500");
			getch();
		}
	}while (!valid);
	clear(5, 23);

	do
	{
		clear(5, 17);
		valid = 1;
		gotoxy(5, 17);
		cout << "Do you want to save the record <Y/N>: ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');

	if (ch == 'N')
		return;
	float t_amount, t_interest;
	t_amount = t_balance;
	t_interest = 0.0;
	char t_tran, t_type[10];
	t_tran = 'D';
	strcpy(t_type, "INITIAL");

	// Appends the records contents into both INITIAL.dat and BANKING.dat data files
	ini.add_to_file(t_accno, t_name, t_address, t_balance);
	add_to_file(t_accno, d1, m1, y1, t_tran, t_type, t_interest, t_amount, t_balance);
}

/* Function for returning balance amount of an account. This function returns the balance amount of any account
to know the current balance from "INITIAL.dat" data file. */

float initial::give_balance(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	float t_balance;

	// Gives the last balance of an individual account
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			t_balance = balance;
			break;
		}
	}
	file.close();
	return t_balance;
}

/* Function for returning the record no. for updating balance
 This function check the position of the account number for updating new balance amount
 into either "INITIAL.dat" or "BANKING.dat" data files. */
int initial::recordno(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	int count = 0;

	// Finds the record position in INITIAL.dat data file
	while (file.read((char *)this, sizeof(initial)))
	{
		count++;
		if (t_accno == accno)
			break;
	}
	file.close();
	return count;
}
/* Function for updating the balance for the given account no.
  This function is used to update the balance after making any transaction in "INITIAL.dat" data file.
  While updating balance in "INITIAL.dat" data file, all the fields will transfer into at the specified
  position in the file, because with random file handling when we update any record the size of the record becomes
  over write at the same place. So, all the fields including balance amount will write into the same position in
  "INITIAL.dat" data file. Here this function uses a function seekp(), which searches the location in the data file
  where the record will be write. */

void initial::update_balance(int t_accno, char t_name[30], char t_address[30], float t_balance)
{
	int recno;
	recno = recordno(t_accno);
	fstream file;
	file.open("INITIAL.dat", ios::out|ios::ate);
	strcpy(name, t_name);
	strcpy(address, t_address);
	balance = t_balance;
	int location;
	location = (recno-1) * sizeof(initial); // Find the location in file
	file.seekp(location);	// Searches the insertion position in data file

	// Updates the balance amount in INITIAL.dat data file
	file.write((char *)this, sizeof(initial));
	file.close();
}

/* Function to return no. days between two dates.
  The function calculates total number of days between two date. And the function passes parameters as related to date (day, month, year). */

int account::no_of_days(int d1, int m1, int y1, int d2, int m2, int y2)
{
	static int month[] = {31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
	int days = 0;
	while (d1 != d2 || m1 != m2 || y1 != y2)
	{
		days++;
		d1++;
		if (d1 > month[m1-1])
		{
			d1 = 1;
			m1++;
		}
		if (m1 > m2)
		{
			m1 = 1;
			y1++;
		}
	}
	return days;
}

/* Function for calculates interest
This function calculate the interest of any account accouding to the account no. and balance from "BANKING.data" data file
Before calculate the interest, the funcation also finds total number of days and then find the interest. */

float account::calculate_interest(int t_accno, float t_balance)
{
	fstream file;
	file.open("BANKING.dat", ios::in);
	file.seekg(0, ios::beg);
	int d1, m1, y1, days;
	while (file.read((char *)this, sizeof(account)))
	{
		if (accno == t_accno)
		{
			d1 = dd;
			m1 = mm;
			y1 = yy;
			break;
		}
	}
	int d2, m2, y2;
	struct date d;
	getdate(&d);
	d2 = d.da_day;
	m2 = d.da_mon;
	y2 = d.da_year;
	float t_interest = 0.0;
	if ((y2 < y1) || (y2 == y1 && m2 < m1) || (y2 == y1 && m2 == m1) && (d2 < d1))
		return t_interest;
	days = no_of_days(d1, m1, y1, d2, m2, y2);
	int months = 0;
	if (days > 30)
	{
		months = days / 30;
		t_interest = ((t_balance*2)/100 * months);
	}
	file.close();
	return t_interest;
}

/* Function for making daily transaction (Deposit 'D'/Withdraw 'W'.
  This is the function used to make daily transaction either for Deposit(D) or for Withdraw(W). When the screen appears
  the user has to press the account no. and either for deposit or withdraw and then either Cash or Cheque. While screening
  the same screen also shows the previous balance for deposit or withdraw. After the final entry, it speaks "Save Transaction <y/n>?" and if yes.
  then the transaction data saved in "BANKING.dat" data file and the current balance updated in the "INITIAL.dat" data file. */

void account::transaction(void)
{
	clrscr();
	char t_acc[10];
	int t, t_accno, valid;
	gotoxy(71,1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(3, 3);
	for (int i = 1; i <= 76; i++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(29, 3);
	cprintf ("Transaction in Account");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(5, 6);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	gotoxy(5, 8);
	cout << "Accnount no. " << t_accno;
	char t_name[30];
	char t_address[30];
	float t_balance;
	strcpy(t_name, ini.return_name(t_accno));
	strcpy(t_address, ini.return_address(t_accno));
	t_balance = ini.give_balance(t_accno);
	gotoxy(27, 11);
	cout << "Name : " << t_name;
	gotoxy(27, 12);
	cout << "Address : " << t_address;

	gotoxy(5, 15);
	cout << "Last balance Rs. " << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< t_balance;

	char t_tran, t_type[10], tm[10];
	float t_amount, t_amt;

	do
	{
		clear(5, 10);
		valid = 1;
		gotoxy(5, 10);
		cout << "Deposit or Withdraw (D/W) : ";
		t_tran = getch();
		if (t_tran == '0')
			return;
		t_tran = toupper(t_tran);
	}while (t_tran != 'D' && t_tran != 'W');

	do
	{
		clear(5, 19);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Transaction by Cash or Cheque ";
		valid = 1;
		gotoxy(5, 19);
		cout << "Cash/Cheque : ";
		gets(t_type);
		strupr(t_type);
		if (t_type[0] == '0')
			return;
		if (strcmp(t_type, "CASH") && strcmp(t_type, "CHEQUE"))
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Enter correctly");
			getch();
		}
	}while (!valid);

	do
	{
		clear(5, 21);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Amount for Transaction ";
		valid = 1;
		gotoxy(5, 21);
		cout << "Amount Rs. ";
		gets(tm);
		t_amt = atof(tm);
		t_amount = t_amt;
		if (tm[0] == '0')
			return;
		if ((t_tran == 'W' && t_amount > t_balance) || (t_amount < 1))
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Invalid Data entered");
			getch();
		}
	}while (!valid);

	char ch;
	clear(5, 23);
	do
	{
		clear(20, 23);
		valid = 1;
		gotoxy(40, 20);
		cout << "Save Transaction <Y/N> : ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	float t_interest;

	t_interest = calculate_interest(t_accno, t_balance);

	if (t_tran == 'D')
		t_balance = t_balance + t_amount + t_interest;
	else
		t_balance = (t_balance - t_amount) + t_interest;

	// Modified records are updated in data bases.
	ini.update_balance(t_accno, t_name, t_address, t_balance);
	add_to_file(t_accno, d1, m1, y1, t_tran, t_type, t_interest, t_amount, t_balance);
}

/* Function for closing any account after inputing account number.
When any account holder interested to close his/her account then this function helps to close
the account completely, means all the transactions from the "BANKING.dat" and "INITIAL.dat" file deletes
the particular record information. The function also uses no. of other functions which fullfill the the total
close_account procedure as well. */

void account::close_account(void)
{
	clrscr();
	char t_acc[10];
	int t, t_accno;
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found ";
		getch();
		return;
	}
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(3, 3);
	textbackground(WHITE);
	for (int i = 1; i <= 76; i++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(30, 3);
	cprintf("Close account screen");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(5, 6);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	char ch;
	ini. display(t_accno);
	do
	{
		clear(5, 15);
		gotoxy(5, 15);
		cout << "Close this account <y/n?? ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;

	// Function calls to delete the existing account no.
	ini.delete_account(t_accno);
	delete_account(t_accno);
	gotoxy(5, 20);
	cout << "\7Account Deleted";
	gotoxy(5, 23);
	cout << "Press any key to continue...";
	getch();
}

//1st page
void page1()
{
   int i;
   textbackground(BLACK);
   textcolor(RED+BLINK);
   clrscr();
   textcolor(11);
   {
   gotoxy(1,25);
   cputs("@@@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@@@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@@");
   gotoxy(1,1) ;
   cputs("@@@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@@@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@ @@@@");
   }
   for(i=2;i<=24;i++)
   {delay(150);
    gotoxy(80,i);
    cout<<"@";
    gotoxy(1,i);
    cout<<"@";
   }
gotoxy(10,6);
   textbackground(WHITE);
   textcolor(BLACK+BLINK);  delay(250);
cputs("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");delay(250);
int a=1;
int b=0;
y:
if(a+2==4)
textbackground(RED);
if(a+2==4)
textcolor(BLACK+BLINK);
gotoxy(10,6);
cputs("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");delay(250);

b++;
int j=17;
gotoxy(j,10);cputs(" P ");delay(200);
gotoxy(j=j+3,10); cputs(" R ");delay(200);
gotoxy(j=j+3,10); cputs(" O ");delay(200);
gotoxy(j=j+3,10); cputs(" J ");delay(200);
gotoxy(j=j+3,10); cputs(" E ");delay(200);
gotoxy(j=j+3,10); cputs(" C ");delay(200);
gotoxy(j=j+3,10); cputs(" T ");delay(200);
gotoxy(j=j+3,10); cputs("   ");delay(200);
gotoxy(j=j+3,10); cputs(" W ");delay(200);
gotoxy(j=j+3,10); cputs(" O ");delay(200);
gotoxy(j=j+3,10); cputs(" R ");delay(200);
gotoxy(j=j+3,10); cputs(" K ");delay(200);
gotoxy(j=j+3,10); cputs("   ");delay(200);
gotoxy(j=j+3,10); cputs(" O ");delay(200);
gotoxy(j=j+3,10); cputs(" F ");delay(200);
gotoxy(j=j+3,10); cputs("   ");delay(200);
 i=15;
gotoxy(i,13 );cputs(" C ");delay(200);
gotoxy(i=i+3,13 ); cputs(" O ");delay(200);
gotoxy(i=i+3,13 ); cputs(" M ");delay(200);
gotoxy(i=i+3,13 ); cputs(" P ");delay(200);
gotoxy(i=i+3,13 ); cputs(" U ");delay(200);
gotoxy(i=i+3,13 ); cputs(" T ");delay(200);
gotoxy(i=i+3,13 ); cputs(" E ");delay(200);
gotoxy(i=i+3,13 ); cputs(" R ");delay(200);
gotoxy(i=i+3,13 ); cputs("   ");delay(200);
gotoxy(i=i+3,13 ); cputs(" S ");delay(200);
gotoxy(i=i+3,13 ); cputs(" C ");delay(200);
gotoxy(i=i+3,13 ); cputs(" I ");delay(200);
gotoxy(i=i+3,13 ); cputs(" E ");delay(200);
gotoxy(i=i+3,13 ); cputs(" N ");delay(200);
gotoxy(i=i+3,13 ); cputs(" C ");delay(200);
gotoxy(i=i+3,13 ); cputs(" E   ");delay(200);
gotoxy(10,16);
cputs("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");delay(360) ;
if(a==1 && b==1 )
{ a++;b++;
goto y;
}
;
delay(700);gotoxy(50,22) ;
cout<<"press any key to continue....";
getch();
}
//for 2nd page
void page2()
{
   textbackground(BLUE);
   textcolor(RED+BLINK);
   clrscr();
   textcolor(YELLOW);
   gotoxy(1,25);delay(500);{
   cputs("#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*");
   gotoxy(1,1)   ;
   cputs("********************************************************************************");
 }  gotoxy(1,2);
   delay(500);
   cout<<"################################################################################";
   delay(500);
   cputs("********************************************************************************\n");
   gotoxy(10,6);
   delay(600);
   cputs(" sl. no.                 N A M E                     Roll No. ");
   delay(500) ;
   cout<<"\t \n \n   \t   01";
   delay(300);
   cout<<"\t\t\t";cputs("  SUNNY KUMAR SINGH  ");
   delay(300);
   cout<<"\t \t";cputs(" 38 ");
   delay(500);
   cout<<"\t \n \n   \t   02";
   delay(300);
   cout<<"\t\t\t";cputs("  RATNESH DHAN  ");
   delay(300);
   cout<<"\t \t";cputs(" 21 ");
   delay(500);
   
   gotoxy(10,20);
   delay(600);
   cout<<"Guided by:- ";cputs(" Mr. NITIN UPADHYAY ");
   delay(800) ;
   cout<<" \n\n\n \t\t\t\t\tpress any key to continue......";
   getch();
}
	/********************************************************/
	/*   THIS CLASS CONTROL ALL THE FUNCTION IN THE MENU	*/
	/********************************************************/
int flag=0;
int password()
    {
	clrscr();
	textbackground(YELLOW)  ;
	char p1,p2,p3,p4,p5;
	gotoxy(20,13);
	cout<<"Enter password(5 characters):";
	gotoxy(50,13);
	p1=getch();
	p1=toupper(p1);
	cout<<"*";
	p2=getch();
	p2=toupper(p2);
	cout<<"*";
	p3=getch();
	p3=toupper(p3);
	cout<<"*";
	p4=getch();
	p4=toupper(p4);
	cout<<"*";
	p5=getch();
	p5=toupper(p5);
	cout<<"*";
	if((p1=='N')&&(p2=='I')&&(p3=='T')&&(p4=='I')&&(p5=='N'))
      {	flag=1;
		return flag;
		}
	else
	{
		clrscr();
		char mess[]="INCORRECT PASSWORD \n YOU ARE NOT AUTHORISED TO OPEN ";
		for(int i=0,j=20;mess[i]!='\0';i++,j++)
		{
			gotoxy(j,13);
			delay(50);
			textbackground(4);
			textcolor(WHITE+BLINK);
			cprintf("%c",mess[i]);
		}
		  delay(500);
		  gotoxy(15,20);
	       gotoxy(15,20);  cout<<" FOR MORE DETAILS \n ";
	       gotoxy(15,22);  cputs("  BANK MANAGER ")  ;
	       gotoxy(15,21);  cputs("  Mr. Sunny Kumar Singh ")  ;

		textbackground(BLACK);
		textcolor(WHITE);
		delay(4500);
		flag=0;
		return flag;

	}

}

// Main program logic which control the class members and member functions.
void main()
{
       page1();
       page2();
	main_menu  m_menu;
       password();
      if(flag==1)
       {	m_menu.help();

	m_menu.control_menu();
	}
      else
      exit(0);

}
