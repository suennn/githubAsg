#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <time.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
SYSTEMTIME systemTime;
#define child_price 12
#define adult_price 16
#define service_tax 0.10

//function declaration
string upper(string);
void Main_Menu(string);
void CinemaManagement(int);
void AdministratorMenu(int);
//Customer Feedback (for user)
void CustomerFeedback();
void SearchFeedback(); //by rating
void WriteFeedback();
void ViewFeedback();
void OpenCustomerFeedback(int&, double&);
//open member info files
void OpenMemberDetails(int&);
void OpenPurchaseHistory();
void ViewMemberDetails(int&);
void ViewPurchaseHistory(int&);
//Membership Details
void MembershipDetails();
void UserLogIn();
void UserRegister();
//Membership management
void WriteMemberDetails(int&);
void WritePurchaseHistory(int&);
void MembershipManagement();
void Admin_MemberDetails();
void Admin_PurchaseHistory();
void Admin_SearchMember();
void Admin_DeleteMember();
void Admin_UpdateMember();
void UpdatedMember(int&);
//movie management
void CinemaHallManagement(int);
void ReadCinemaHallRecord(int&);
void CinemaSeatPrinting(int, int);
void HallSeatPrinting(int, int, int);
bool AddCinemaHall(bool);
void ModifyCinemaHall(int&);
void DeleteCinemaHall(int&);
void LoadCinemaHallRecord(int&);
void AddCinemaSeat(int&);
void DeleteCinemaSeat(int&);
void ConfirmAddCinemaSeat(int, int, int);
//movie function
void MovieManagement(int);
void AddMovie(int&);
void ReadMovieRecord(int&);
void LoadMovieRecord(int&);
void ModifyMovie(int&);
void DeleteMovie(int&);
void MoviePrinting(int&, int);
bool MovieStartDetection(string);
void MovieEndDetection(string, int, double, int&, int&, int);
void MovieIntoStruct(string, string, string, string, double, int, int&);
//employee function
void EmployeeManagement(int);
void ReadEmployeeRecord(int&);
void LoadEmployeeRecord(int&);
void AddEmployee(int&);
void DeleteEmployee(int&);
void ModifyEmployee(int&);
bool EmployeeID(string, int&);
//Movie details
void MovieDetails(int);
//Purchase now
void PurchaseNow(int);
void BookMovie(int);
void NumberTicket(int, int&, int&, int row[], int column[]);
void MemberChecking(string&, int&);
void TimeChecking(int, int, int, int, int, int, int&);
void DateRecord(int, int, int, int, int, int, int&);
void BookSeatPrinting(int, int, int);
//refresh the cinema hall
void CinemaRefresh(int);
//read ascii text
void ReadTextRecord(int);
//fnb management
void inventoryMenu(int); //menu with available stock 
void addFB(); //function to add new fnb 
void deleteFB(int); //function to delete existing fnb
void inventoryFB(int); //function to add stock or delete stock
void FBManagement(); //add new item, delete item, add and reduce stock
//purchase fnb
void purchaseFB(int); //function to purchase fnb
void UpdateHistory(int&, int&);
void MenuList();
void ReadFBRecord(int&); //read txt file
void LoadFBRecord(int&); //update txt file
//structure declaration
void LoadMemberDetail(int&);
void LoadPurchaseHistory(int&);
struct mapping_seats {
	int hall, data, row[70], column[70];
}unavailable[50];//cinema hall	//a set of column and row = 1 data
struct MemberDetails {
	string Details_user, Details_name, Details_password, Details_join, Details_phone, Details_email, Details_status, Details_point;
}Member[100];
struct PurchaseHistory {
	string Purchase_user, Purchase_name, Purchase_movie[5], Purchase_date[5], Purchase_pax[5], Purchase_food[5];
}Purchase[100];
struct Feedback {
	int rating;
	string comment;
}feedback[100];
struct foodAndBeverage {
	string foodcode, foodname;
	double regular_price, large_price;
	int stock;
}FNB[100];
struct PurchasedSeatType {
	int data, purchased_row[50], purchased_column[50];
};
struct CinemaHallSeatType {
	int data, row[70], column[70];
};
struct movie {
	string movie_id, movie_name, description, movie_time;
	double movie_length;
	int movie_hall;
	PurchasedSeatType seats;
	CinemaHallSeatType backup;
}movie[100];
struct employee {
	string id, name, department, position;
	int password;
}employee[100];
string department[5] = { "INFORMATION TECHNOLOGY","HUMAN RESOURCES","FINANCE","MARKETING","BUSINESS" };
string text[40][7];

int main() {
	system("chcp 65001");
	ReadTextRecord(0);
	string selection;
	bool decision = true;
	do {
		system("cls");
		Main_Menu("MAIN");
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, selection);
		if (selection == "1")//Movie details
			MovieDetails(1);
		else if (selection == "2")//f&b
			MenuList();
		else if (selection == "3")//purchase now
			PurchaseNow(3);
		else if (selection == "4")//membership details
			MembershipDetails();
		else if (selection == "5")//admin page
			AdministratorMenu(5);
		else if (selection == "6")//customer feedback
			CustomerFeedback();
		else if (selection == "7")//exit
			decision = false;
		else {
			cout << "\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
			Sleep(600);
		}
		cin.clear();
	} while (decision);
	system("pause");
	return 0;
}
string upper(string uppercase) {//change string to uppercase
	for (int i = 0; i < uppercase.size(); i++)
		uppercase[i] = toupper(uppercase[i]);
	return uppercase;
}
//CustomerFeedback
void SearchFeedback() {
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[24][i] << endl;
	}
	int nocomment = 0, rating, j = 0, found = 0;
	double averagerating = 0;
	OpenCustomerFeedback(nocomment, averagerating);
	cout << "\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	cout << "\t\t\t\t\t\t\t\t\tEnter rating to sort comment (1-5): ";
	cin >> rating;
	cout << endl << endl;
	if (rating > 0 && rating < 6)
	{
		cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
		for (int i = 0; i < nocomment; i++)
		{
			if (rating == feedback[i].rating)
			{
				found = i;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << ++j << ". Rating: " << feedback[i].rating << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tComment: " << feedback[i].comment << endl << endl;
				cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
			}
		}

		if (!(rating == feedback[found].rating))
		{
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t\033[1;91mNo comment with rating of " << rating << ". \033[0m" << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
		}
	}
	else
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91mInvalid input! \033[0m" << endl;
	system("PAUSE");
}
void OpenCustomerFeedback(int& nocomment, double& averagerating)
{
	ifstream CusFeedback;
	int i = 0, totalrating = 0;

	CusFeedback.open("CustomerFeedback.txt");
	if (CusFeedback.is_open())
	{
		while (!CusFeedback.eof())
		{
			CusFeedback >> feedback[i].rating;
			CusFeedback.ignore();
			getline(CusFeedback, feedback[i].comment);
			i++;
			nocomment = i;
		}
	}
	else
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91mPlease contact admin for further assistance...\033[0m" << endl;
	for (int i = 0; i < nocomment; i++)
	{
		totalrating += feedback[i].rating;
	}
	averagerating = double(totalrating) / nocomment;
	CusFeedback.close();
}
void ViewFeedback()
{
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[23][i] << endl;
	}
	cout << "\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	int nocomment = 0, j = 0, totalrating = 0;
	double averagerating = 0;
	OpenCustomerFeedback(nocomment, averagerating);
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tTotal comment: " << nocomment << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tAverage rating: " << fixed << setprecision(1) << averagerating << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
	for (int i = 0; i < nocomment; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << ++j << ". Rating: " << feedback[i].rating << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tComment: " << feedback[i].comment << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
	}
	system("PAUSE");
}
void WriteFeedback()
{
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[22][i] << endl;
	}
	char Continue = 'y';
	int i = 0;
	ofstream cusfeedback;
	cusfeedback.open("CustomerFeedback.txt", ios::app);
	cout << "\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	cout << "\t\t\t\t\t\t\t\t\t\033[1;95mGood day! \n\t\t\t\t\t\t\t\t\tThis comment is anonymous. \n\t\t\t\t\t\t\t\t\tPlease feel free to leave your thoughts. \n\n\n\033[0m";

	cout << "\t\t\t\t\t\t\t\t\tPlease rate our cinema (1-5): ";
	cin >> feedback[i].rating;
	cusfeedback << endl << feedback[i].rating << endl;
	cout << "\t\t\t\t\t\t\t\t\tPlease leave your feedback here. (in 100 words) " << endl << "\t\t\t\t\t\t\t\t\t";
	cin.ignore();
	getline(cin, feedback[i].comment);
	cusfeedback << feedback[i].comment;
	cout << endl << "\t\t\t\t\t\t\t\t\t\033[1;95mThank you. \033[0m" << endl;
	system("PAUSE");
	cusfeedback.close();
}
void CustomerFeedback()
{
	system("cls");
	int selection;
	bool decision = true;
	do
	{
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n\033[1;96m" << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t\t\t\t\t" << text[23][i] << endl;
		}
		cout << "\033[0m\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
		cout << "\t\t\t\t\t\t\t\t\t<1> Leave comment " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<2> View comment " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<3> Search comment " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<4> Exit \n\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\033[1;34mPlease input your selection >>> \033[0m";
		cin >> selection;
		switch (selection)
		{
		case(1)://allow customer to leave feedback (anonymous)
		{
			WriteFeedback();
			break;
		}
		case(2)://to view others feedback
		{
			ViewFeedback();
			break;
		}
		case(3)://search particular feedback using rating
		{
			SearchFeedback();
			break;
		}
		case(4)://exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\t\t\t\t\t\t\t\033[1;91mInvalid input! \033[0m" << endl;
			break;
		}
		}
	} while (decision);
}
//Administrator Menu (havent implement employee function)
void AdministratorMenu(int option) {
	bool decision = true, access = true;
	do {	//login menu
		cin.clear();
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n" << endl;
		for (int i = 0; i < 7; i++) {
			cout << "\t\t\t\t\t\t\t\t" << text[14][i] << endl;
		}
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\tDear Admin, kindly key in your Admin ID and password" << endl;
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		string id, pass_word;
		int record = 0, password = 0, found = 0, number = 0;
		ReadEmployeeRecord(record);
		cout << "\n\n\t\t\t\tID=ew001 and password=12345 for lecturer used only!!" << endl;
		cout << "\n\t\t\t\t\tADMIN ID <E>xit >>>";
		getline(cin, id);
		id = upper(id);
		if (id == "E") {
			decision = false;
			break;
		}
		cout << "\t\t\t\t\tPassword >>>";
		getline(cin, pass_word);
		for (int i = 0; i < pass_word.size(); i++) {
			if (isdigit(pass_word[i]))//ensure pass_word only in numeric numbers
				number++;
		}
		if (pass_word.size() == number)		//comparing
			password = stoi(pass_word);	//string to integer
		if (id.length() == 5) {
			for (int i = 0; i < record; i++) {//checking corrent password
				if (password == employee[i].password && id == employee[i].id) {
					found++;
				}
			}
		}
		if (found == 0 || id.length() != 5) {
			cout << "\t\t\t\033[1;31mInvalid user ID and password detected.\033[0m" << endl;
			Sleep(1000);
		}
		else if (found == 1)
			access = false;
	} while (access);
	while (decision) {
		system("cls");
		ReadTextRecord(0);
		cout << "\n";
		for (int i = 0; i < 7; i++) {
			SetConsoleTextAttribute(console, 14);
			cout << "\t\t\t" << text[1][i] << endl;
			SetConsoleTextAttribute(console, 7);
		}
		string selection;
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t<1> Cinema Refreshing" << endl;
		cout << "\t\t\t<2> Cinema management" << endl;
		cout << "\t\t\t<3> Food & Beverages management" << endl;
		cout << "\t\t\t<4> Membership Management" << endl;
		cout << "\t\t\t<5> Employee management" << endl;
		cout << "\t\t\t<6> Exit " << endl;
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, selection);
		if (selection == "1")
			CinemaRefresh(1);
		else if (selection == "2")//Cinema management
			CinemaManagement(2);
		else if (selection == "3")//F&B management
			FBManagement();
		else if (selection == "4")//Membership managements
			MembershipManagement();
		else if (selection == "5")//Employee management
			EmployeeManagement(5);
		else if (selection == "6") {
			decision = false;
		}
		else//reinput
		{
			cout << "\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
			Sleep(600);

		}
	}
}
//Open member info files
void OpenPurchaseHistory() {
	ifstream Ad_purchase;
	int k = 0;
	Ad_purchase.open("Admin_purchase.txt");
	if (Ad_purchase.is_open()) {
		while (!Ad_purchase.eof()) {
			getline(Ad_purchase, Purchase[k].Purchase_user);
			getline(Ad_purchase, Purchase[k].Purchase_name);
			for (int i = 0; i < 5; i++) {
				getline(Ad_purchase, Purchase[k].Purchase_date[i]);
				getline(Ad_purchase, Purchase[k].Purchase_pax[i]);
				getline(Ad_purchase, Purchase[k].Purchase_movie[i]);
				getline(Ad_purchase, Purchase[k].Purchase_food[i]);
			}
			k++;
		}
	}
	else
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91mPlease contact admin for further assistance...\033[0m" << endl;
	Ad_purchase.close();
}
void OpenMemberDetails(int& nomember) {
	int i = 0;
	ifstream Ad_memberlist;
	Ad_memberlist.open("Admin_memberlist.txt");
	if (Ad_memberlist.is_open()) {
		while (!Ad_memberlist.eof()) {
			getline(Ad_memberlist, Member[i].Details_user);
			getline(Ad_memberlist, Member[i].Details_password);
			getline(Ad_memberlist, Member[i].Details_name);
			getline(Ad_memberlist, Member[i].Details_status);
			getline(Ad_memberlist, Member[i].Details_join);
			getline(Ad_memberlist, Member[i].Details_point);
			getline(Ad_memberlist, Member[i].Details_phone);
			getline(Ad_memberlist, Member[i].Details_email);
			i++;
			nomember = i;
		}
	}
	else
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91mPlease contact admin for further assistance...\033[0m" << endl;
	Ad_memberlist.close();
}
void ViewMemberDetails(int& need)
{
	int nomember = 0;
	cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tUsername: " << Member[need].Details_user << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tPassword: " << Member[need].Details_password << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tName: " << Member[need].Details_name << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tStatus: " << Member[need].Details_status << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tJoin date: " << Member[need].Details_join << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tAccumulated point(s): " << Member[need].Details_point << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tPhone number: " << Member[need].Details_phone << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tEmail address: " << Member[need].Details_email << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
}
void ViewPurchaseHistory(int& need)
{
	OpenPurchaseHistory();
	cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tUsername: " << Purchase[need].Purchase_user << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tName: " << Purchase[need].Purchase_name << endl << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << i + 1 << ". Purchase Date: " << Purchase[need].Purchase_date[i] << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tNumber of pax (Child Adult): " << Purchase[need].Purchase_pax[i] << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tMovie: " << Purchase[need].Purchase_movie[i] << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tF&B: " << Purchase[need].Purchase_food[i] << endl << endl;
	}
	cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
}
//Membership Details (for user)
void UserRegister() {//add new member
	ofstream Add_member, Add_purchase;
	int i = 0, newmember = 0, existing = 0, nomember = 0;
	string username, password;

	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[15][i] << endl;
	}
	cout << "\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	cout << "\t\t\t\t\t\t\t\t\t\033[1;95mGood day!\n\t\t\t\t\t\t\t\t\tWelcome to be part of us!\n\n";
	cout << "\t\t\t\t\t\t\t\t\tKindly fill in the below information. \033[0m\n";
	cout << "\t\t\t\t\t\t\t\t\t\033[1;91m*Compulsory\n\n";
	cout << "\t\t\t\t\t\t\t\t\t*Username: \033[0m";
	cin.ignore();
	getline(cin, username);

	OpenMemberDetails(nomember);

	for (int i = 0; i < nomember; i++)
	{
		if (!(upper(username) == upper(Member[i].Details_user)))
			newmember = i;
		else if (upper(username) == upper(Member[i].Details_user))
			existing = i;
	}

	if (!(upper(username) == upper(Member[existing].Details_user)))
	{
		Member[newmember].Details_user = username;
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91m*Full name as per NRIC: \033[0m";
		getline(cin, Member[newmember].Details_name);
		Member[newmember].Details_status = "Classic";
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91m*Password: \033[0m";
		getline(cin, Member[newmember].Details_password);
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91m*Register date (DD MM YYYY): \033[0m";
		getline(cin, Member[newmember].Details_join);
		Member[newmember].Details_point = "0";
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91m*Phone number: \033[0m";
		getline(cin, Member[newmember].Details_phone);
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91m*Email: \033[0m";
		getline(cin, Member[newmember].Details_email);
		cout << "\n\t\t\t\t\t\t\t\t\t\033[1;92mCongratulations!\n\t\t\t\t\t\t\t\t\tYour registration was successful!\n\t\t\t\t\t\t\t\t\tKindly log in to access more.\n\t\t\t\t\t\t\t\t\tThank you ^^\n\033[0m";
		system("PAUSE");
	}
	else if (upper(username) == upper(Member[existing].Details_user))
	{
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91mRegistered member!\n\t\t\t\t\t\t\t\t\tPlease log in to access your account.\n\033[0m";
		system("PAUSE");
	}

	Add_member.open("Admin_memberlist.txt", ios::app);
	{
		Add_member << endl << Member[newmember].Details_user << endl;;
		Add_member << Member[newmember].Details_password << endl;
		Add_member << Member[newmember].Details_name << endl;
		Add_member << Member[newmember].Details_status << endl;
		Add_member << Member[newmember].Details_join << endl;
		Add_member << Member[newmember].Details_point << endl;
		Add_member << Member[newmember].Details_phone << endl;
		Add_member << Member[newmember].Details_email;
	}
	Add_member.close();

	Add_purchase.open("Admin_purchase.txt", ios::app);
	{
		Purchase[newmember].Purchase_user = Member[newmember].Details_user;
		Purchase[newmember].Purchase_name = Member[newmember].Details_name;
		Add_purchase << Purchase[newmember].Purchase_user << endl;
		Add_purchase << Purchase[newmember].Purchase_name << endl;
		for (int i = 0; i < 5; i++)
		{
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
		}
	}
	Add_purchase.close();
}
void UserLogIn() //for existing member
{
	int selection, nomember = 0;
	bool decision = true;
	int i = 0, found = 0;
	string username, password;
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t" << text[14][i] << endl;
	}
	cout << "\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	cout << "\t\t\t\t\t\t\t\t\t\033[1;95mGood day! " << endl;
	cout << "\t\t\t\t\t\t\t\t\tKindly log in for more access. \033[0m" << endl << endl;

	cout << "\t\t\t\t\t\t\t\t\tPlease enter your username: ";
	cin >> username;

	OpenMemberDetails(nomember);
	for (int i = 0; i < nomember; i++)
	{
		if (upper(username) == upper(Member[i].Details_user))
			found = i;
	}
	OpenPurchaseHistory();
	if (upper(username) == upper(Member[found].Details_user))
	{
		cout << "\t\t\t\t\t\t\t\t\tPlease enter your password: ";
		cin >> password;
		if (password == Member[found].Details_password)
		{
			do {
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\t\033[1;95mWelcome back, our beloved member! \033[0m" << endl;
				cout << "\t\t\t\t\t\t\t\t\t<1> Profile" << endl;
				cout << "\t\t\t\t\t\t\t\t\t<2> Purchase history" << endl;
				cout << "\t\t\t\t\t\t\t\t\t<3> Exit \n\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\033[1;34mPlease input your selection >>> \033[0m";
				cin >> selection;
				switch (selection) {
				case(1)://Check personal details
				{
					system("cls");
					ReadTextRecord(0);
					cout << "\n\n" << endl;
					for (int i = 0; i < 7; i++)
					{
						cout << "\t\t\t\t\t\t\t\t\t\t" << text[17][i] << endl;
					}
					cout << endl << endl;
					ViewMemberDetails(found);
					system("PAUSE");
					break;
				}
				case(2)://Check purchase history
				{
					system("cls");
					ReadTextRecord(0);
					cout << "\n\n" << endl;
					for (int i = 0; i < 7; i++)
					{
						cout << "\t\t\t\t\t\t\t\t\t" << text[16][i] << endl;
					}
					cout << endl << endl;
					ViewPurchaseHistory(found);
					system("PAUSE");
					break;
				}
				case(3): //Exit
				{
					decision = false;
					break;
				}
				default://reinput
				{
					cout << "\t\t\t\t\t\t\t\t\t\033[1;91mInvalid input! \033[0m" << endl;
					break;
				}
				}
			} while (decision);
		}
		else
			cout << "\033[1;91m\t\t\t\t\t\t\t\t\tInvalid password!\n\t\t\t\t\t\t\t\t\tPlease contact admin to reset password. \033[0m" << endl;
	}
	else if (!(upper(username) == upper(Member[found].Details_user)))
		cout << "\033[1;91m\t\t\t\t\t\t\t\t\tMember doesn't exist! \n\033[0m";

	system("PAUSE");
}
void MembershipDetails() //membership details menu
{
	int selection;
	bool decision = true;
	system("cls");
	do {
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n\033[1;96m" << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t\t\t\t\t" << text[12][i] << endl;
		}
		cout << "\033[0m\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
		cout << "\t\t\t\t\t\t\t\t\t<1> Log in" << endl;
		cout << "\t\t\t\t\t\t\t\t\t<2> Register" << endl;
		cout << "\t\t\t\t\t\t\t\t\t<3> Exit \n\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\033[1;34mPlease input your selection >>> \033[0m";
		cin >> selection;
		switch (selection)
		{
		case(1)://Existing member log in
		{
			UserLogIn();
			break;
		}
		case(2)://New member
		{
			UserRegister();
			break;
		}
		case(3): //Exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\t\t\t\t\t\t\t\033[1;91mInvalid input! \033[0m" << endl;
			break;
		}
		}
	} while (decision);
}
//Membership Management (Admin)
void WritePurchaseHistory(int& nomember) //store updated info
{
	ofstream Ad_purchase;
	Ad_purchase.open("Admin_purchase.txt");
	for (int k = 0; k < nomember; k++)
	{
		Ad_purchase << Purchase[k].Purchase_user << endl;
		Ad_purchase << Purchase[k].Purchase_name << endl;
		for (int i = 0; i < 5; i++)
		{
			Ad_purchase << Purchase[k].Purchase_date[i] << endl;
			Ad_purchase << Purchase[k].Purchase_pax[i] << endl;
			Ad_purchase << Purchase[k].Purchase_movie[i] << endl;
			Ad_purchase << Purchase[k].Purchase_food[i] << endl;
		}
	}
	Ad_purchase.close();
}
void WriteMemberDetails(int& nomember) //store updated info
{
	ofstream Ad_memberlist;
	Ad_memberlist.open("Admin_memberlist.txt");
	for (int i = 0; i < nomember; i++)
	{
		Ad_memberlist << Member[i].Details_user << endl;
		Ad_memberlist << Member[i].Details_password << endl;
		Ad_memberlist << Member[i].Details_name << endl;
		Ad_memberlist << Member[i].Details_status << endl;
		Ad_memberlist << Member[i].Details_join << endl;
		Ad_memberlist << Member[i].Details_point << endl;
		Ad_memberlist << Member[i].Details_phone << endl;
		Ad_memberlist << Member[i].Details_email;
		if (i < (nomember - 1))
		{
			Ad_memberlist << endl;
		}
	}
	Ad_memberlist.close();
}
void UpdatedMember(int& update) //show updated info
{
	int nomember = 0;

	system("cls");
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\033[1;92mUpdated Details \033[0m" << endl << endl;
	ViewMemberDetails(update);
	system("PAUSE");
}
void Admin_DeleteMember() //delete expired member
{
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n\t\t\t" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t" << text[19][i] << endl;
	}
	cout << "\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	int nomember = 0, dlt = 0;
	string username;
	char choice = 'y';
	OpenMemberDetails(nomember);
	OpenPurchaseHistory();

	cout << "\t\t\t\t\t\t\t\t\t\t\t\tEnter member's username: ";
	cin.ignore();
	getline(cin, username);
	cout << endl << endl;
	for (int i = 0; i < nomember; i++)
	{
		if (username == Member[i].Details_user)
			dlt = i;
	}
	if (username == Member[dlt].Details_user)
	{
		ViewMemberDetails(dlt);
		ViewPurchaseHistory(dlt);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\033[1;34mDo you sure to remove this member? (Y/N): \033[0m";
		cin >> choice;
		if (toupper(choice) == toupper('y'))
		{
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t\033[1;92mMember deleted successfully. \033[0m" << endl;
			for (int i = dlt; i < nomember; i++)
			{
				Member[i].Details_user = Member[i + 1].Details_user;
				Member[i].Details_password = Member[i + 1].Details_password;
				Member[i].Details_name = Member[i + 1].Details_name;
				Member[i].Details_status = Member[i + 1].Details_status;
				Member[i].Details_join = Member[i + 1].Details_join;
				Member[i].Details_point = Member[i + 1].Details_point;
				Member[i].Details_phone = Member[i + 1].Details_phone;
				Member[i].Details_email = Member[i + 1].Details_email;

				Purchase[i].Purchase_user = Purchase[i + 1].Purchase_user;
				Purchase[i].Purchase_name = Purchase[i + 1].Purchase_name;

				for (int w = 0; w < 5; w++)
				{
					Purchase[i].Purchase_date[w] = Purchase[i + 1].Purchase_date[w];
					Purchase[i].Purchase_pax[w] = Purchase[i + 1].Purchase_pax[w];
					Purchase[i].Purchase_movie[w] = Purchase[i + 1].Purchase_movie[w];
					Purchase[i].Purchase_food[w] = Purchase[i + 1].Purchase_food[w];
				}
			}
			nomember = nomember - 1;
		}
	}
	else
		cout << "\033[1;91m\t\t\t\t\t\t\t\t\tMember doesn't exist! \033[0m" << endl;
	WriteMemberDetails(nomember);
	WritePurchaseHistory(nomember);
	system("PAUSE");
}
void Admin_UpdateMember() //update specific info
{
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[25][i] << endl;
	}
	cout << "\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	string search;
	bool decision = true;
	ifstream Ad_memberlist;
	int i = 0, j = 0, nomember = 0, update = 0, selection;
	OpenMemberDetails(nomember);
	OpenPurchaseHistory();

	cout << "\t\t\t\t\t\t\t\t\t\t\t\tEnter member's username: ";
	cin.ignore();
	getline(cin, search);
	cout << endl << endl;
	for (int j = 0; j < nomember; j++)
	{
		if (upper(search) == upper(Member[j].Details_user))
			update = j;
	}
	if (upper(search) == upper(Member[update].Details_user))
	{
		do
		{
			system("cls");
			cout << "\t\t\t\t\t\t\t\t\t<1> Name" << endl;
			cout << "\t\t\t\t\t\t\t\t\t<2> Status " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<3> Username " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<4> Password " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<5> Join date " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<6> Phone number " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<7> Email address " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<8> Accumulated point " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<9> Exit \n\n" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\033[1;34mPlease input your selection >>> \033[0m";
			cin >> selection;
			switch (selection)
			{
			case(1)://New name
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent name: " << Member[update].Details_name << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new name: ";
				cin.ignore();
				getline(cin, Member[update].Details_name);
				Purchase[update].Purchase_name = Member[update].Details_name;
				UpdatedMember(update);
				break;
			}
			case(2)://New status
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent status: " << Member[update].Details_status << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new status: ";
				cin.ignore();
				getline(cin, Member[update].Details_status);
				UpdatedMember(update);
				break;
			}
			case(3)://New username
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent username: " << Member[update].Details_user << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new username: ";
				cin.ignore();
				getline(cin, Member[update].Details_user);
				Purchase[update].Purchase_user = Member[update].Details_user;
				UpdatedMember(update);
				break;
			}
			case(4)://New password
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent password: " << Member[update].Details_password << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new password: ";
				cin.ignore();
				getline(cin, Member[update].Details_password);
				UpdatedMember(update);
				break;
			}
			case(5)://New join date
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent join date: " << Member[update].Details_join << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new join date: ";
				cin.ignore();
				getline(cin, Member[update].Details_join);
				UpdatedMember(update);
				break;
			}
			case(6)://New phone number
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent phone number: " << Member[update].Details_phone << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new phone number: ";
				cin.ignore();
				getline(cin, Member[update].Details_phone);
				UpdatedMember(update);
				break;
			}
			case(7)://New email address
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent email address: " << Member[update].Details_email << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new email address: ";
				cin.ignore();
				getline(cin, Member[update].Details_email);
				UpdatedMember(update);
				break;
			}
			case(8)://New accumulated point
			{
				system("cls");
				cout << "\t\t\t\t\t\t\t\t\tCurrent accumulated point(s): " << Member[update].Details_point << endl;
				cout << "\t\t\t\t\t\t\t\t\tEnter new accumulated point(s): ";
				cin.ignore();
				getline(cin, Member[update].Details_point);
				UpdatedMember(update);
				break;
			}
			case(9)://exit
			{
				decision = false;
				break;
			}
			default://reinput
			{
				cout << "\t\t\t\t\t\t\t\t\t\033[1;91mInvalid input! \033[0m" << endl;
				break;
			}
			}
		} while (decision);
		WriteMemberDetails(nomember);
		WritePurchaseHistory(nomember);
	}
	else
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91mMember doesn't exist! \033[0m" << endl;
	system("PAUSE");
}
void Admin_SearchMember() //search for specific member
{
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t" << text[18][i] << endl;
	}
	cout << "\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
	string search;
	bool decision = true;
	int i = 0, j = 0, nomember = 0, found = 0, selection;
	OpenMemberDetails(nomember);
	OpenPurchaseHistory();

	cout << "\t\t\t\t\t\t\t\t\tEnter member's username: ";
	cin.ignore();
	getline(cin, search);
	cout << endl << endl;

	for (int j = 0; j < nomember; j++)
	{
		if (upper(search) == upper(Member[j].Details_user))
			found = j;
	}
	if (upper(search) == upper(Member[found].Details_user))
	{
		do
		{
			system("cls");
			cout << "\t\t\t\t\t\t\t\t\t<1> Member details " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<2> Member purchase history " << endl;
			cout << "\t\t\t\t\t\t\t\t\t<3> Exit \n\n" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\033[1;34mPlease input your selection >>> \033[0m";
			cin >> selection;
			switch (selection)
			{
			case(1)://Member personal info
			{
				system("cls");
				ReadTextRecord(0);
				cout << "\n\n" << endl;
				for (int i = 0; i < 7; i++)
				{
					cout << "\t\t\t\t\t\t\t\t\t\t" << text[17][i] << endl;
				}
				cout << "\n\n";
				ViewMemberDetails(found);
				system("PAUSE");
				break;
			}
			case(2)://Member Purchase history (Only store 5 latest history)
			{
				system("cls");
				ReadTextRecord(0);
				cout << "\n\n" << endl;
				for (int i = 0; i < 7; i++)
				{
					cout << "\t\t\t\t\t\t\t\t\t" << text[16][i] << endl;
				}
				cout << "\n\n";
				ViewPurchaseHistory(found);
				system("PAUSE");
				break;
			}
			case(3)://exit
			{
				decision = false;
				break;
			}
			default://reinput
			{
				cout << "\t\t\t\t\t\t\t\t\t\033[1;91mInvalid input! \033[0m" << endl;
				break;
			}
			}
		} while (decision);
	}
	else if (!(upper(search) == upper(Member[found].Details_user)))
		cout << "\t\t\t\t\t\t\t\t\t\033[1;91mMember doesn't exist! \033[0m" << endl;
	system("PAUSE");
}
void Admin_PurchaseHistory() //Members' purchase history (Only store 5 latest history)
{
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t" << text[16][i] << endl;
	}
	int nomember = 0;
	OpenMemberDetails(nomember);
	OpenPurchaseHistory();

	cout << "\n\n\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;

	for (int j = 0; j < nomember; j++)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tUsername: " << Purchase[j].Purchase_user << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tName: " << Purchase[j].Purchase_name << endl << endl;
		for (int i = 0; i < 5; i++)
		{
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << i + 1 << ". Purchase Date: " << Purchase[j].Purchase_date[i] << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tNumber of pax (Child Adult): " << Purchase[j].Purchase_pax[i] << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tMovie: " << Purchase[j].Purchase_movie[i] << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tF&B: " << Purchase[j].Purchase_food[i] << endl << endl;
		}
		cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
	}
	system("PAUSE");
}

void Admin_MemberDetails() { //All members' info
	system("cls");
	ReadTextRecord(0);
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t" << text[17][i] << endl;
	}
	int nomember = 0;
	OpenMemberDetails(nomember);
	cout << "\n\n\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
	for (int i = 0; i < nomember; i++)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << i + 1 << ". Username: " << Member[i].Details_user << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tPassword: " << Member[i].Details_password << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tName: " << Member[i].Details_name << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tStatus: " << Member[i].Details_status << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tJoin date: " << Member[i].Details_join << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tAccumulated point(s): " << Member[i].Details_point << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tPhone number: " << Member[i].Details_phone << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEmail address: " << Member[i].Details_email << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\033[5;93m******************************************************************************************************************************************\033[0m" << endl << endl;
	}
	system("PAUSE");
}
void MembershipManagement() {
	system("cls");
	int selection;
	bool decision = true;
	do {
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n\033[1;96m" << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t\t\t\t\t\t\t\t" << text[13][i] << endl;
		}
		cout << "\033[0m\n\n\t\t\t\t\t\t\t" << string(150, char(95)) << "\n\n";
		cout << "\t\t\t\t\t\t\t\t\t<1> Member details " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<2> Member purchase history " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<3> Search member " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<4> Delete member " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<5> Update member " << endl;
		cout << "\t\t\t\t\t\t\t\t\t<6> Exit \n\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\033[1;34mPlease input your selection >>> \033[0m";
		cin >> selection;
		switch (selection)
		{
		case(1)://Member personal info
		{
			Admin_MemberDetails();
			break;
		}
		case(2)://Member Purchase history (Only store 5 latest history)
		{
			Admin_PurchaseHistory();
			break;
		}
		case(3)://Search for specific member info
		{
			Admin_SearchMember();
			break;
		}
		case(4)://Delete member
		{
			Admin_DeleteMember();
			break;
		}
		case(5)://Update member details
		{
			Admin_UpdateMember();
			break;
		}
		case(6)://exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\t\t\t\t\t\t\t\033[1;91mInvalid input! \033[0m" << endl;
			break;
		}
		}
	} while (decision);
}
void CinemaManagement(int option) {
	cin.clear();
	string selection;
	bool decision = true;
	do {
		system("cls");
		cout << "\n\n" << endl;
		for (int i = 0; i < 7; i++) {
			cout << "\t\t\t\t" << text[3][i] << endl;
		}
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\n\n\t\t\t<1> Movies management " << endl;
		cout << "\t\t\t<2> Cinema Hall management " << endl;
		cout << "\t\t\t<3> Exit " << endl;
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, selection);
		if (selection == "1")//Movie management
			MovieManagement(1);
		if (selection == "2")//Cinema Hall Modification
			CinemaHallManagement(2);
		if (selection == "3")//exit
			decision = false;
		else//reinput
			cout << "\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
	} while (decision);
}
//Cinema Hall Management
void CinemaHallManagement(int option) {
	string selection;
	bool decision = true;
	do {
		system("cls");
		int record = 0;
		bool result = false;
		for (int i = 0; i < 7; i++) {
			cout << "\t\t\t\t\t\t\t\t" << text[5][i] << endl;
		}
		ReadCinemaHallRecord(record);
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		for (int w = 0; w < record; w++) {
			cout << "\n\n\t\t\t\t HALL " << unavailable[w].hall << "\n\n";
			CinemaSeatPrinting(w, 99);
		}
		cin.clear();
		cout << "\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\t<1> Add Cinema Hall" << endl;
		cout << "\t\t\t<2> Modify Cinema Hall space" << endl;
		cout << "\t\t\t<3> Delete Cinema Hall" << endl;
		cout << "\t\t\t<4> Exit" << endl;
		cout << "\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\tInput your selection >>> ";
		getline(cin, selection);
		//Add cinema Hall
		if (selection == "1") {
			result = AddCinemaHall(result);
			if (result) {
				record++;
				unavailable[record - 1].hall = record;
				unavailable[record - 1].data = 0;
				unavailable[record - 1].row[0] = 0;
				unavailable[record - 1].column[0] = 0;
				LoadCinemaHallRecord(record);
			}
		}
		else if (selection == "2")//Modify Cinema Seat
			ModifyCinemaHall(record);
		else if (selection == "3")//Delete Cinema Hall
			DeleteCinemaHall(record);
		else if (selection == "4")//exit
			decision = false;
		else//reinput
			cout << "\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
	} while (decision);
}
void ReadCinemaHallRecord(int& record) { //read cinema hall and store into struct
	int i = 0;
	ifstream infile;
	infile.open("seatcontrol.txt");
	if (infile.fail())
		cout << "Please contact admin for further assistance..." << endl;
	else
	{
		while (!infile.eof())
		{
			infile >> unavailable[i].hall;
			infile >> unavailable[i].data;
			infile.ignore();
			if (unavailable[i].data > 0)
			{
				for (int j = 0; j < unavailable[i].data; j++)
					infile >> unavailable[i].row[j];
				for (int j = 0; j < unavailable[i].data; j++)
					infile >> unavailable[i].column[j];
			}
			else
			{
				infile >> unavailable[i].row[0];
				infile >> unavailable[i].column[0];
			}

			infile.ignore();
			i++;
			record++;
		}
	}
	infile.close();
}
void LoadCinemaHallRecord(int& record)//write file from struct to text file
{
	ofstream outfile;
	outfile.open("seatcontrol.txt");
	for (int i = 0; i < record; i++) {
		outfile << unavailable[i].hall << endl;
		outfile << unavailable[i].data << endl;
		if (unavailable[i].data > 0) {
			for (int j = 0; j < unavailable[i].data; j++) {
				if (j > 0)//X X X (a blank space in between)
					outfile << " ";
				outfile << unavailable[i].row[j];
			}
			outfile << endl;
			for (int j = 0; j < unavailable[i].data; j++) {
				if (j > 0)
					outfile << " ";
				outfile << unavailable[i].column[j];
			}

		}
		else {
			outfile << unavailable[i].row[0] << endl;
			outfile << unavailable[i].column[0];
		}
		if (i != record - 1)
			outfile << endl;
	}
	outfile.close();
}
//print selected cinema seat mapping
void CinemaSeatPrinting(int w, int f)
{
	for (int i = 0; i < 10; i++)//for loop i for row, for loop j for column
	{
		cout << "\t\t\t\t\t";
		cout << i;
		if (i == 0)
		{
			for (int j = 1; j < 15; j++)
			{
				if (j == 2 || j == 12)
					cout << setw(2) << j << " ";
				else
					cout << setw(2) << j;
			}
			cout << endl;
		}
		else
		{
			for (int j = 1; j < 3; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);
			}
			cout << " ";
			for (int j = 3; j < 13; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);
			}
			cout << " ";
			for (int j = 13; j < 15; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);;
			}
			cout << endl;
		}

	}
}
//check availability of seat
void HallSeatPrinting(int w, int i, int j) {
	int checking = 1;
	if (unavailable[w].data != 0) {	//only selected cinema hall will be display
		for (int z = 0; z < unavailable[w].data; z++) {	//check if unavailable
			if (i == unavailable[w].row[z] && j == unavailable[w].column[z]) {
				cout << setw(2) << "X";
				checking = 0;
			}
		}
	}
	if (checking)
		cout << setw(2) << "A";
}
//add cinema hall
bool AddCinemaHall(bool result) {// add cinema hall without editing
	cin.clear();
	string confirms;
	bool decision = true;
	do {
		cout << "\t\t\tDo you want to add a new cinema hall <Y>es or <N>o >>> ";
		getline(cin, confirms);
		confirms = upper(confirms);
		if (confirms == "Y" || confirms == "N")
			decision = false;

	} while (decision);
	if (confirms == "Y")
		return true;
	else
		return false;
}
void ModifyCinemaHall(int& record) {//modify seat of cinema
	string selection;
	bool decision = true;
	cin.clear();
	do {
		cout << "\t\t\t<1> Add Cinema Unavailable Seat" << endl;
		cout << "\t\t\t<2> Delete Cinema Unavailable Seat" << endl;
		cout << "\t\t\t<3> Exit" << endl;
		cout << "\t\t\tInput your selection >>> ";
		getline(cin, selection);
		if (selection == "1")//	Add
			AddCinemaSeat(record);
		else if (selection == "2")//Delete
			DeleteCinemaSeat(record);
		else if (selection == "3")//Exit
			decision = false;
		else//reinput
			cout << "\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
	} while (decision);
}
void DeleteCinemaHall(int& record) {//delete entire cinema hall
	int number;
	cout << "\t\t\tPlease input the cinema hall number >>>";
	cin >> number;
	if (number > 0 && number <= record) {
		for (int i = 0; i < record; i++) {//search if cinema hall is valid
			if (unavailable[i].hall == number) {
				for (int j = i; j < record; j++) {//replace that cinema hall to next cinema hall
					unavailable[j].hall = j + 1;
					unavailable[j].data = unavailable[j + 1].data;
					if (unavailable[j].data > 0) {
						for (int z = 0; z < unavailable[j].data; z++) {//replace the row and column data
							unavailable[j].row[z] = unavailable[j + 1].row[z];
							unavailable[j].column[z] = unavailable[j + 1].column[z];
						}
					}
					else {
						unavailable[j].row[0] = 0;
						unavailable[j].column[0] = 0;
					}
					number++;
				}
			}
		}
		record--;
		cout << "\t\t\t\033[1;36msuccessfully deleted...\033[0m" << endl;
		LoadCinemaHallRecord(record);
	}
	else
		cout << "\t\t\t\033[1; 31mno cinema hall found\033[0m" << endl;
}
void AddCinemaSeat(int& record) {//add unavailable seats
	int number;
	string continued;
	cout << "\t\t\tInput the number of cinema hall >>>";
	cin >> number;
	if (number > 0 && number <= record) {
		bool decision = true;
		cout << "\n\n\t\t\t" << string(100, char(61)) << "\n\n";
		cout << "\t\t\tCinema hall " << number << endl;
		CinemaSeatPrinting(number - 1, 99);
		do {
			int row, column;
			cout << "\t\t\tInput the row that you want to modify >>>";
			cin >> row;
			cout << "\t\t\tInput the column that you want to modify >>>";
			cin >> column;
			if (unavailable[number - 1].data > 0) {
				int found = 0;
				for (int i = 0; i < unavailable[number - 1].data; i++) {//check row and column in struct
					if (row > 10 || column > 14) {//invalid input
						found++;
						cout << "\t\t\t\033[1;31mplease ensure row and column within the range: 0 < row < 10 and 0 < column < 15\033[0m" << endl;
						cout << "\t\t\t\033[1;31mPlease reinput row and column\033[0m" << endl;
						break;
					}
					else if (unavailable[number - 1].row[i] == row && unavailable[number - 1].column[i] == column) {//row and column found
						found++;
						cout << "\t\t\t\033[1;31mInput have found inside the system...\033[0m" << endl;
						cout << "\t\t\t\033[1;31mPlease reinput row and column\033[0m" << endl;
						break;
					}
				}
				if (found == 0) {//no row and column found
					ConfirmAddCinemaSeat(number, row, column);
				}
			}
			else
				ConfirmAddCinemaSeat(number, row, column);
			LoadCinemaHallRecord(record);
			cout << "\t\t\tDo you want to continue <Y>es to continue... >>";
			cin >> continued;
			continued = upper(continued);
			if (continued != "Y")
				decision = false;
		} while (decision);
	}
	else
		cout << "\t\t\t\033[1; 31mno cinema hall found\033[0m" << endl;
	cin.ignore();
}
void DeleteCinemaSeat(int& record) {
	int number;
	cout << "\t\t\tPlease input the cinema hall number >>>";
	cin >> number;
	if (number > 0 && number <= record) {
		cout << "\n\n\t\t\t" << string(100, char(61)) << "\n\n";
		cout << "\t\t\tCinema hall " << number << endl;
		CinemaSeatPrinting(number - 1, 99);
		bool decision = true;
		do {
			char continued;
			int row, column;
			cout << "\t\t\tInput the row of the seat >> ";
			cin >> row;
			cout << "\t\t\tInput the column of the seat >> ";
			cin >> column;
			int found = 0;
			for (int i = 0; i < unavailable[number - 1].data; i++) {
				if (row > 10 || column > 14) {
					cout << "\t\t\t\033[1;31mplease ensure row and column within the range: 0 < row < 10 and 0 < column < 15\033[0m" << endl;
					break;
				}
				else if (unavailable[number - 1].row[i] == row && unavailable[number - 1].column[i] == column) {//row and column found
					found++;
					char confirms;
					cout << "\t\t\tAre you confirm delete row " << row << " and " << "column " << column << " <Y>es <N>o  >>";
					cin >> confirms;
					confirms = toupper(confirms);
					if (confirms == 'Y')
					{
						for (int j = i; j < unavailable[number - 1].data; j++)//delete the selected seats
						{
							unavailable[number - 1].row[j] = unavailable[number - 1].row[j + 1];
							unavailable[number - 1].column[j] = unavailable[number - 1].column[j + 1];
						}
						unavailable[number - 1].data -= 1;//data reduce by 1
						LoadCinemaHallRecord(record);
					}
					else
					{
						cout << "\t\t\t\033[1;31mConfirmation Unsuccessful\033[0m" << endl;
						cout << "\t\t\tPlease reinput the row and column" << endl;
					}
					break;
				}
			}
			if (found == 0)//no column and row found
				cout << "\t\t\t\033[1;31mNo data found in system\033[0m" << endl;
			cout << "\t\t\tDo you want to continue <Y>es <N>o >>";
			cin >> continued;
			continued = toupper(continued);
			if (continued == 'N')
				decision = false;
		} while (decision);
	}
	else
		cout << "\t\t\t\033[1;31mno cinema hall seat found\033[0m" << endl;
	cin.ignore();
}

void ConfirmAddCinemaSeat(int number, int row, int column) {
	char confirms;
	cout << "Are you confirm add row " << row << " and " << "column " << column << " <Y>es <N>o  >>";
	cin >> confirms;
	confirms = toupper(confirms);
	if (confirms == 'Y') {
		cout << "confirmation successful" << endl;
		unavailable[number - 1].data += 1;//add 1 seats
		unavailable[number - 1].row[unavailable[number - 1].data - 1] = row;
		unavailable[number - 1].column[unavailable[number - 1].data - 1] = column;
		cout << "succesfully added" << endl;
	}
	else {
		cout << "Confirmation Unsuccessful" << endl;
		cout << "Please reinput the row and column" << endl;
	}
}
void MovieManagement(int option)
{
	bool decision = true;
	string selection;
	do {
		int record = 0;
		cin.clear();
		system("cls");
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t" << text[4][i] << endl;
		}
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		ReadMovieRecord(record);
		MoviePrinting(record, 99);
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\n\t\t\t\t<1> Add Movie " << endl;
		cout << "\t\t\t\t<2> Modify Movie " << endl;
		cout << "\t\t\t\t<3> Delete Movie " << endl;
		cout << "\t\t\t\t<4> exit " << endl;
		cout << "\t\t\t\tInput your selection >>> ";
		getline(cin, selection);
		if (selection == "1")
			AddMovie(record);
		else if (selection == "2")
			ModifyMovie(record);
		else if (selection == "3")
			DeleteMovie(record);
		else if (selection == "4")
			decision = false;
		else
			cout << "\t\t\tInvalid input found" << endl;
	} while (decision);
}
void ReadMovieRecord(int& record)
{
	ifstream infile;
	infile.open("movie.txt");
	if (infile.fail())
		cout << "Please contact admin for further assistance..." << endl;
	else
	{
		while (!infile.eof())
		{
			getline(infile, movie[record].movie_id);
			getline(infile, movie[record].movie_name);
			getline(infile, movie[record].description);
			getline(infile, movie[record].movie_time);
			infile >> movie[record].movie_length;
			infile >> movie[record].movie_hall;
			infile >> movie[record].seats.data;
			if (movie[record].seats.data > 0)
			{
				for (int i = 0; i < movie[record].seats.data; i++)
					infile >> movie[record].seats.purchased_row[i];
				for (int i = 0; i < movie[record].seats.data; i++)
					infile >> movie[record].seats.purchased_column[i];
			}
			else
			{
				infile >> movie[record].seats.purchased_row[0];
				infile >> movie[record].seats.purchased_column[0];

			}
			infile >> movie[record].backup.data;
			if (movie[record].backup.data > 0)
			{
				for (int i = 0; i < movie[record].backup.data; i++)
					infile >> movie[record].backup.row[i];
				for (int i = 0; i < movie[record].backup.data; i++)
					infile >> movie[record].backup.column[i];
			}
			else
			{
				infile >> movie[record].backup.row[0];
				infile >> movie[record].backup.column[0];

			}
			infile.ignore();
			record++;
		}
	}
	infile.close();

}
void LoadMovieRecord(int& record)
{
	ofstream outfile;
	outfile.open("movie.txt");
	for (int i = 0; i < record; i++)
	{
		outfile << movie[i].movie_id << endl << movie[i].movie_name << endl << movie[i].description << endl;
		outfile << movie[i].movie_time << endl << movie[i].movie_length << endl << movie[i].movie_hall << endl;
		outfile << movie[i].seats.data << endl;
		if (movie[i].seats.data > 0)
		{
			for (int j = 0; j < movie[i].seats.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].seats.purchased_row[j];
			}
			outfile << endl;
			for (int j = 0; j < movie[i].seats.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].seats.purchased_column[j];
			}
			outfile << endl;
		}
		else
		{
			outfile << movie[i].seats.purchased_row[0] << endl;
			outfile << movie[i].seats.purchased_column[0] << endl;
		}
		outfile << movie[i].backup.data << endl;
		if (movie[i].backup.data > 0)
		{
			for (int j = 0; j < movie[i].backup.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].backup.row[j];
			}
			outfile << endl;
			for (int j = 0; j < movie[i].backup.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].backup.column[j];
			}
		}
		else
		{
			outfile << movie[i].backup.row[0] << endl;
			outfile << movie[i].backup.column[0];
		}
		if (!(i == record - 1))
			outfile << endl;
	}
	outfile.close();
}
void AddMovie(int& record)
{
	bool decision = true;
	do {
		int movie_hall;
		string movie_name, movie_id, description, movie_time, confirms;
		double movie_length;
		bool checking = true;
		do {
			int found = 0;
			cout << "\t\t\t\tInput the movie id >>> ";
			cin >> movie_id;
			movie_id = upper(movie_id);
			for (int i = 0; i < record; i++) {
				if (movie_id == movie[i].movie_id)//movie id found
					found++;
			}
			if (found == 0)//no movie id found
				checking = false;
			else
				cout << "\t\t\t\t\033[1;31mMovie id detected.\033[0m" << endl;
		} while (checking);
		cin.ignore();
		cout << "\t\t\t\tInput the movie name >>> "; //same name allowed(same name,diff. movie
		getline(cin, movie_name);
		movie_name = upper(movie_name);

		cout << "\t\t\t\tInput the movie description >>> ";
		getline(cin, description);

		checking = true;
		do {
			cout << "\t\t\t\tInput the movie_time (24 Hours format XXXX) >>> ";
			cin >> movie_time;
			bool result = MovieStartDetection(movie_time);//detect validation of time
			if (result)
				checking = false;
			else
				cout << "\t\t\t\t\033[1;31minvalid input\033[0m" << endl;
		} while (checking);

		checking = true;
		do {
			cout << "\t\t\t\tInput the movie_length in (Hours.minutes~~~ X.XX)>>> ";
			cin >> movie_length;								//2.60		2.50	(input)
			int hour = int(movie_length);						//2.00		2
			double minutes = (movie_length - hour) * 100;		//60		50
			if (minutes >= 60)
				cout << "\t\t\t\t\033[1;31minvalid input\033[0m" << endl;
			else
				checking = false;
		} while (checking);
		checking = true;
		do {
			int found = 0, hall = 0;
			cout << "\t\t\t\tInput the movie_hall >>>";
			cin >> movie_hall;
			if (movie_hall <= record || movie_hall > 0) {
				MovieEndDetection(movie_time, movie_hall, movie_length, found, record, 999);//ensure no movie in between start and end time
				if (found == 0)
					checking = false;
			}
			else
				cout << "\t\t\t\t\033[1;31mPlease input again the movie hall\033[0m" << endl;
			if (checking)
				cout << "\t\t\t\t\033[1;31mPlease input again the movie hall\033[0m" << endl;
		} while (checking);
		checking = true;
		do {//display all info
			cout << "\t\t\t\tMovie ID: " << movie_id << endl;
			cout << "\t\t\t\tMovie Name: " << movie_name << endl;
			cout << "\t\t\t\tMovie description: " << description << endl;
			cout << "\t\t\t\tMovie time: " << movie_time << endl;
			cout << "\t\t\t\tMovie length H.MM: " << movie_length << endl;
			cout << "\t\t\t\tMovie hall: " << movie_hall << endl;
			cout << "\t\t\t\tAre you confirm? <Y>es <N>o >>> ";
			cin >> confirms;
			confirms = upper(confirms);
			if (confirms == "Y" || confirms == "N")
			{
				checking = false;
			}
		} while (checking);

		if (confirms == "Y") {
			MovieIntoStruct(movie_id, movie_name, description, movie_time, movie_length, movie_hall, record);//record it
		}
		string cont;
		do {
			cout << "\t\t\t\tDO you want to continue <Y>es <N>o >>> ";
			cin >> cont;
			cont = upper(cont);
			if (!(cont == "Y" || cont == "N"))
				cout << "\t\t\tInvalid input" << endl;
		} while (!(cont == "Y" || cont == "N"));
		if (cont == "N")
			decision = false;
	} while (decision);

}
void ModifyMovie(int& record)
{
	bool decision = true;
	do {
		string movie_name, movie_id, description, movie_time;
		double movie_length;
		int movie_hall, trace = 0;
		int found = 0, selection, storage;
		cout << "\t\t\t\tInput the Movie ID <E>xit: ";
		cin >> movie_id;
		movie_id = upper(movie_id);
		for (int i = 0; i < record; i++) {
			if (movie_id == movie[i].movie_id) {
				found++;
				storage = i;
			}
		}
		if (found > 0) {
			cout << "\n\t\t\t\tWhich section you want to modify???" << endl;
			cout << "\t\t\t\t<1> Movie ID " << endl;
			cout << "\t\t\t\t<2> Movie Name" << endl;
			cout << "\t\t\t\t<3> Movie Description" << endl;
			cout << "\t\t\t\t<4> Movie Start time" << endl;
			cout << "\t\t\t\t<5> Movie length" << endl;
			cout << "\t\t\t\t<6> Cinema Hall of movie" << endl;
			cout << "\t\t\t\t<7> Exit" << endl;
			cout << "\t\t\t\tInput your selection";
			cin >> selection;
			switch (selection)
			{
			case(1):
			{
				int check = 0;
				cout << "\t\t\t\tInput new movie id >>> ";
				cin >> movie_id;
				for (int i = 0; i < record; i++) {
					if (movie_id == movie[i].movie_id) {
						cout << "\t\t\t\t\033[1;31mMovie ID was found inside the system.\033[0m" << endl;
						check++;
					}
				}
				if (check == 0) {//movie id not found
					movie[storage].movie_id = movie_id;
				}
				break;
			}
			case(2):
			{
				//assume that movie can have the same name !!!
				cout << "\t\t\t\tInput new movie name >>> ";
				getline(cin, movie_name);
				movie[storage].movie_name = movie_name;
				break;
			}
			case(3):
			{
				//assume that description can have the same !!!
				cout << "\t\t\t\tInput new movie description >>> ";
				getline(cin, description);
				movie[storage].description = description;
				break;
			}
			case(4):
			{

				cout << "\t\t\t\tInput the new start time in 24 Hours format (XXXX)>>> ";
				cin >> movie_time;
				bool result = MovieStartDetection(movie_time);
				if (result) {
					MovieEndDetection(movie_time, movie[storage].movie_hall, movie[storage].movie_length, trace, record, storage);
					cout << trace << endl;
					if (trace == 0) {
						movie[storage].movie_time = movie_time;
					}
				}
				break;
			}
			case(5)://enter length (start time,movie hall)
			{
				cout << "\t\t\t\tEnter the new movie length in Hours.Minutes(X.XX) >>>";
				cin >> movie_length;
				MovieEndDetection(movie[storage].movie_time, movie[storage].movie_hall, movie_length, trace, record, storage);
				if (trace == 0) {
					movie[storage].movie_length = movie_length;
				}
				break;
			}
			case(6)://movie hall( start time, end time)
			{
				cout << "\t\t\t\tEnter the new movie hall >>>";
				cin >> movie_hall;
				MovieEndDetection(movie[storage].movie_time, movie_hall, movie[storage].movie_length, trace, record, storage);
				if (trace == 0) {
					movie[storage].movie_hall = movie_hall;
					movie[storage].seats.data = 0;
					movie[storage].seats.purchased_row[0] = 0;
					movie[storage].seats.purchased_column[0] = 0;
					movie[storage].backup.data = unavailable[storage].data;
					for (int i = 0; i < movie[storage].backup.data; i++) {
						movie[storage].backup.row[i] = unavailable[storage].row[i];
						movie[storage].backup.column[i] = unavailable[storage].column[i];
					}
				}
				break;
			}
			case(7):
			{
				decision = false;
				break;
			}
			default:
			{
				cout << "\t\t\t\tPlease reinput again!!!" << endl;
			}
			}

		}
		else if (movie_id == "E")
			decision = false;
		else {
			cout << "\t\t\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
			Sleep(600);
		}
	} while (decision);
}
void DeleteMovie(int& record)
{
	int found = 0, index;
	string movie_id, confirm = "w";
	bool decision = true;
	do {
		cout << "\t\t\t\tInput the movie id you want to delete <E>xit >>>>";
		cin >> movie_id;
		movie_id = upper(movie_id);
		if (!(movie_id == "E"))
		{
			for (int i = 0; i < record; i++)
			{
				if (movie_id == movie[i].movie_id)
				{
					found++;
					index = i;
				}

			}
			if (found == 1)
			{
				cout << "\t\t\t\tMovie ID found in system" << endl;
				while (!(confirm == "Y" || confirm == "N"))
				{
					cout << "\t\t\t\tFinal confirmation <Y>es <N>o >>>";
					cin >> confirm;
					confirm = upper(confirm);
					if (!(confirm == "Y" || confirm == "N"))
						cout << "\t\t\t\tInvalid input" << endl;
				}
				if (confirm == "Y")
				{
					cout << "\t\t\t\tLoading..." << endl;
					Sleep(3500);
					for (int j = index; j < record; j++)
					{
						movie[j].movie_id = movie[j + 1].movie_id;
						movie[j].movie_name = movie[j + 1].movie_name;
						movie[j].description = movie[j + 1].description;
						movie[j].movie_time = movie[j + 1].movie_time;
						movie[j].movie_length = movie[j + 1].movie_length;
						movie[j].movie_hall = movie[j + 1].movie_hall;
						movie[j].seats.data = movie[j + 1].seats.data;
						if (movie[j].seats.data > 0) {
							for (int z = 0; z < movie[j].seats.data; z++)
							{
								movie[j].seats.purchased_row[z] = movie[j + 1].seats.purchased_row[z];
								movie[j].seats.purchased_column[z] = movie[j + 1].seats.purchased_column[z];
							}
						}
						else {
							movie[j].seats.purchased_row[0] = movie[j + 1].seats.purchased_row[0];
							movie[j].seats.purchased_column[0] = movie[j + 1].seats.purchased_column[0];
						}
						movie[j].backup.data = movie[j + 1].backup.data;
						if (movie[j].backup.data > 0)
						{
							for (int z = 0; z < movie[j].backup.data; z++)
							{
								movie[j].backup.row[z] = movie[j + 1].backup.row[z];
								movie[j].backup.column[z] = movie[j + 1].backup.column[z];
							}
						}
						else {
							movie[j].backup.row[0] = movie[j + 1].backup.row[0];
							movie[j].backup.column[0] = movie[j + 1].backup.column[0];

						}
						decision = false;
						record--;
						LoadMovieRecord(record);

					}
				}
				else if (confirm == "N")
					decision = false;
			}
			else if (found == 0)
				cout << "\t\t\tInvalid movie id" << endl;
		}
		else
			decision = false;
	} while (decision);

}
void MoviePrinting(int& record, int w) {
	for (int i = 0; i < record; i++) {
		cout << "\n\t\t\tNo. " << i + 1 << endl;
		if (w == 99) //only print for admin
			cout << "\t\t\tMovie Id: " << movie[i].movie_id << endl;
		cout << "\t\t\tMovie Name: " << movie[i].movie_name << endl;
		cout << "\t\t\tMovie Description: " << movie[i].description << endl;
		cout << "\t\t\tMovie Time: " << movie[i].movie_time << endl;
		cout << "\t\t\tMovie Length H.MM: " << fixed << setprecision(2) << movie[i].movie_length << endl;
		cout << "\t\t\tMovie Hall: " << movie[i].movie_hall << endl;
	}
}
bool MovieStartDetection(string movie_time)   //detect start time of movie
{													//sample output

	int checking = stoi(movie_time);				//2401      2061
	int integer_hours = checking / 100 * 100;		//2400		2000
	int remain = checking % integer_hours;			//1			61
	int size = int(movie_time.length());
	if (size > 4 || size < 4)
		return false;
	else if (integer_hours > 2400)		//if more than 24 hours (a day)
		return false;
	else if (remain > 60)		//if minutes more than 60
		return false;
	else
		return true;
}
void MovieIntoStruct(string id, string name, string description, string time, double length, int hall, int& record)
{
	record++;//add one movie
	movie[record - 1].movie_id = id;
	movie[record - 1].movie_name = name;
	movie[record - 1].description = description;
	movie[record - 1].movie_time = time;
	movie[record - 1].movie_length = length;
	movie[record - 1].movie_hall = hall;
	movie[record - 1].seats.data = 0;
	movie[record - 1].seats.purchased_row[0] = 0;
	movie[record - 1].seats.purchased_column[0] = 0;
	movie[record - 1].backup.data = unavailable[hall - 1].data;
	if (movie[record - 1].backup.data > 0)
	{
		for (int i = 0; i < movie[record - 1].backup.data; i++)
		{
			movie[record - 1].backup.row[i] = unavailable[hall - 1].row[i];
			movie[record - 1].backup.column[i] = unavailable[hall - 1].column[i];
		}
	}
	else
	{
		movie[record - 1].backup.row[0] = unavailable[hall - 1].row[0];
		movie[record - 1].backup.column[0] = unavailable[hall - 1].column[0];
	}
	LoadMovieRecord(record);
}
void MovieEndDetection(string movie_time, int movie_hall, double movie_length, int& found, int& record, int storage)
{//storage is i value from modication section
	double movie_end = stoi(movie_time) + (int(movie_length) * 100 + (movie_length - int(movie_length)) * 100);
	movie_end = int(movie_end);
	if (movie_end - movie_end / 100 * 100 > 60) {//minutes exist 60
		movie_end = movie_end - 60 + 100;
	}
	for (int i = 0; i < record; i++)
	{
		int detection = 0, timing, hour, minutes, ending, overflow;
		if (i == storage) {
			detection++;
			continue;
		}
		else if (movie_hall == movie[i].movie_hall) {		//take other record than that movie hall(if 99)  ===
			string time = movie[i].movie_time;				//1200
			timing = stoi(time);
			detection++;
		}
		if (detection == 1) {
			hour = int(movie_length);						//2.40=2
			minutes = int((movie_length - hour) * 100);		//40
			ending = timing + hour * 100 + minutes;			//1200+2*100+40
			overflow = ending - int(ending / 100 * 100);	//minutes
			if (overflow >= 60)
				ending = ending - 60 + 100;

			if (stoi(movie_time) >= timing && stoi(movie_time) <= ending)
			{
				found++;
			}
			else if (movie_end >= timing && movie_end <= ending)
			{
				found++;
			}
		}
	}
}

void EmployeeManagement(int)
{
	bool decision = true;
	do {
		system("cls");
		for (int i = 0; i < 7; i++) {
			cout << "\t\t\t\t" << text[6][i] << endl;
		}
		int record = 0;
		string selection;
		ReadEmployeeRecord(record);
		cout << "\n\n\n\t\t\t" << string(161, char(61)) << endl;
		cout << "\t\t\t=" << setw(15) << "Employee ID" << setw(35) << "Employee Name" << setw(45) << "Department" << setw(40) << "Position" << setw(20) << "Password" << setw(5) << "=" << endl;
		cout << "\t\t\t" << string(161, char(61)) << endl;
		for (int i = 0; i < record; i++)
		{
			cout << "\t\t\t=" << setw(15) << employee[i].id << setw(35) << employee[i].name << setw(45) << employee[i].department << setw(40) << employee[i].position << setw(20) << employee[i].password << setw(5) << "=" << endl;
		}
		cout << "\t\t\t" << string(161, char(61)) << endl;
		cout << "\t\t\t<1> Add Employee " << endl;
		cout << "\t\t\t<2> Modify Employee" << endl;
		cout << "\t\t\t<3> Delete Employee" << endl;
		cout << "\t\t\t<4> Exit" << endl;
		cout << "\t\t\tInput your selection >>>";
		getline(cin, selection);
		if (selection == "1")
			AddEmployee(record);
		else if (selection == "2")
			ModifyEmployee(record);
		else if (selection == "3")
			DeleteEmployee(record);
		else if (selection == "4")
			decision = false;
		else
			cout << "\n\t\t\tinvalid input" << endl;
	} while (decision);
}
void ReadEmployeeRecord(int& record) {//read employee info
	ifstream details;
	details.open("employee.txt");
	if (details.fail())
		cout << "unable to open the file" << endl;
	else
	{
		while (!details.eof())
		{
			getline(details, employee[record].id);
			getline(details, employee[record].name);
			getline(details, employee[record].department);
			getline(details, employee[record].position);
			details >> employee[record].password;
			details.ignore();
			record++;
		}
	}
	details.close();
}
void LoadEmployeeRecord(int& record) {//write employee info
	ofstream details;
	details.open("employee.txt");
	if (details.fail())
		cout << "Please contact admin for further assistance..." << endl;
	else
	{
		for (int i = 0; i < record; i++)
		{
			details << employee[i].id << endl;
			details << employee[i].name << endl;
			details << employee[i].department << endl;
			details << employee[i].position << endl;
			if (i == record - 1)
				details << employee[i].password;
			else
				details << employee[i].password << endl;
		}
	}
	details.close();
}
void AddEmployee(int& record) {
	bool decision = true;
	do {
		char confirms;
		bool checking = true, result;
		int password;
		string employee_id, employee_department, employee_name, employee_position;
		do {
			cout << "\t\t\tInput employee id ('EW' and 3 numeric numbers)>>>";
			cin >> employee_id;
			employee_id = upper(employee_id);
			result = EmployeeID(employee_id, record);
			if (result)//no employee tracked
				checking = false;
			else
				cout << "\t\t\tPlease reinput again employee id" << endl;
		} while (checking);
		char cont;
		do {
			cin.ignore();
			cout << "\t\t\tInput employee name >>>";
			getline(cin, employee_name);
			employee_name = upper(employee_name);
			cout << "\t\t\tEmployee name, " << employee_name << "\n\t\t\tIf confirms <Y>es >>> ";
			cin >> cont;
			cont = toupper(cont);
		} while (!(cont == 'Y'));

		char conts;
		do {
			int number;
			for (int i = 0; i < sizeof(department) / sizeof(string); i++) {//display department
				cout << "\t\t\t<" << i + 1 << "> " << department[i] << endl;
			}
			cout << "\t\t\tinput your selection >>>";
			cin >> number;
			employee_department = department[number - 1];
			cout << "\t\t\tThis employee under deparment of " << employee_department << endl;
			cout << "\t\t\tEmployee department confirmation <Y>es to continue... >>> ";
			cin >> conts;
			conts = toupper(conts);
		} while (!(conts == 'Y'));

		char resume;
		do {
			cin.ignore();
			cout << "\t\t\tInput the position of employee >>> ";
			getline(cin, employee_position);
			employee_position = upper(employee_position);
			cout << "\t\t\tHer/His position is " << employee_position << endl;
			cout << "\t\t\tEmployee position confirmation <Y>es to continue... >>> ";
			cin >> resume;
			resume = toupper(resume);
		} while (!(resume == 'Y'));
		bool check = true;
		do {
			int found = 0;
			int number[4] = { 10000,20000,30000,40000 };
			int index = rand() % 4;							//index=(0,1,2,3)
			int value = number[index] + rand() % 10000;		//10000+XXXX
			for (int i = 0; i < record; i++) {
				if (value == employee[i].password)
					found++;
			}
			if (found == 0) {
				password = value;//password will be assigned automatically
				check = false;
			}
		} while (check);

		do {
			cout << "\t\t\tFinal confirmation <Y>es <N>o >>>";
			cin >> confirms;
			confirms = toupper(confirms);
			if (confirms == 'Y') {//record all employee info
				cout << "\t\t\tSuccessfully added employee named " << employee_name << "," << employee_id << endl;
				employee[record].id = employee_id;
				employee[record].name = employee_name;
				employee[record].department = employee_department;
				employee[record].position = employee_position;
				employee[record].password = password;
				record++;
				LoadEmployeeRecord(record);
				decision = false;
			}
			else if (confirms == 'N') {
				cout << "\t\t\tPending exit to employee page." << endl;
				Sleep(500);
				decision = false;
			}
		} while (!(confirms == 'Y' || confirms == 'N'));
	} while (decision);
}
void DeleteEmployee(int& record)
{
	string employee_id, cont;
	do {
		int found = 0;
		cout << "\n\t\t\tInput the employee ID that want to delete >>>";
		cin >> employee_id;
		employee_id = upper(employee_id);
		for (int i = 0; i < record; i++)
		{
			if (employee_id == employee[i].id)//tracked id
			{
				for (int j = i; j < record; j++)
				{
					found++;//delete it
					record--;
					employee[j].id = employee[j + 1].id;
					employee[j].name = employee[j + 1].name;
					employee[j].department = employee[j + 1].department;
					employee[j].position = employee[j + 1].position;
					employee[j].password = employee[j + 1].password;
					LoadEmployeeRecord(record);
				}
				break;
			}
		}
		if (found == 0)
			cout << "\t\t\t\033[1;31mThe employee id did not found in the system\033[0m" << endl;
		do {
			cout << "\t\t\tDo you want to continue <Y>es <N>o >> >";
			cin >> cont;
			cont = upper(cont);
			if (!(cont == "N" || cont == "Y"))
				cout << "\t\t\tPlease input 'Y' or 'N' " << endl;
		} while (!(cont == "N" || cont == "Y"));
	} while (cont == "Y");
}
void ModifyEmployee(int& record)
{
	bool checking = true;
	do {
		bool result;
		int index, found = 0, selection, number = 0;
		string id, employee_id, employee_name, employee_position;
		cout << "\t\t\tInput the employee id to modify >>> ";
		cin >> id;
		id = upper(id);
		for (int i = 0; i < record; i++) {
			if (id == employee[i].id) {
				index = i;
				found++;
			}
		}
		if (found == 1) {//tracked id
			cout << "\t\t\tEmployee id, " << id << " found in system " << endl;
			cout << "\t\t\t<1> Employee id" << endl;
			cout << "\t\t\t<2> Employee name" << endl;
			cout << "\t\t\t<3> employee department" << endl;
			cout << "\t\t\t<4> employee position" << endl;
			cout << "\t\t\t<5> Exit" << endl;
			cout << "\t\t\tinput your selection to modify >>> ";
			cin >> selection;
			switch (selection)
			{
			case(1):
			{
				cout << "\t\t\tinput new employee id ('EW' and 3 numerial numbers)>>>";
				cin >> employee_id;
				employee_id = upper(employee_id);
				result = EmployeeID(employee_id, record);
				if (result)
					employee[index].id = employee_id;
				else
					cout << "\t\t\tInvalid employee id" << endl;
				checking = false;
				break;
			case(2):
			{
				cin.ignore();
				cout << "\t\t\tInput new employee name: ";
				getline(cin, employee_name);
				employee_name = upper(employee_name);
				employee[index].name = employee_name;
				checking = false;
				break;
			}
			case(3):
			{
				for (int i = 0; i < 5; i++)
				{
					cout << "\t\t\t< " << i + 1 << " > " << department[i] << endl;
				}
				cout << "\t\t\tInput the department number >>>";
				cin >> number;
				employee[index].department = department[number - 1];
				checking = false;
				break;
			}
			case(4):
			{
				cin.ignore();
				cout << "\t\t\tInput new position of employee >>> ";
				getline(cin, employee_position);
				employee_position = upper(employee_position);
				cout << "\t\t\tPosition is " << employee_position;
				employee[index].position = employee_position;
			}
			}case(5):
			{
				checking = false;
				break;
			}
			default:
			{
				cout << "\t\t\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
			}
			}
			LoadEmployeeRecord(record);
		}
		else {
			cout << "\t\t\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
			Sleep(600);
		}
	} while (checking);
}
bool EmployeeID(string employee_id, int& record)
{//employee id must start with EW and end with three numeric numbers
	int found = 0, size;
	size = signed(employee_id.size());
	for (int i = 0; i < record; i++)
	{
		if (employee_id == employee[i].id)
			found++;
	}
	if (found == 0 && size == 5)
	{
		if ((employee_id[0] == 'E' && employee_id[1] == 'W') && (isdigit(employee_id[3]) && (isdigit(employee_id[3]) && isdigit(employee_id[3]))))
			return true;//&& is binary operator(only can compare two items)
		else
			return false;
	}
	else
		return false;
}

void MovieDetails(int option) {//print movie info
	system("cls");
	cout << "\n\n" << endl;
	for (int i = 0; i < 7; i++) {
		cout << "\t\t\t\t\t\t" << text[10][i] << endl;
	}
	int record = 0;
	string leave;
	GetSystemTime(&systemTime);
	ReadMovieRecord(record);
	cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" << systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	MoviePrinting(record, 0);
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t";
	system("pause");
}
void PurchaseNow(int option) {
	string selection;
	bool decision = true;
	do {
		cin.clear();
		system("cls");
		cout << "\n\n" << endl;
		for (int i = 0; i < 7; i++) {
			cout << "\t\t\t\t\t" << text[7][i] << endl;
		}
		cout << "\n\t\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\t\t\t<1> Book a movie UwU " << endl;
		cout << "\t\t\t\t\t\t<2> Food & Beverages UnU" << endl;
		cout << "\t\t\t\t\t\t<3> Exit " << "\n\n\t\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\t\t\tInput your selection >>> ";
		getline(cin, selection);
		if (selection == "1")//book  movie
			BookMovie(1);
		else if (selection == "2")//purchase FB
			purchaseFB(2);
		else if (selection == "3")
			decision = false;
		else {
			cout << "\t\t\t\t\t\033[1;31mInvalid input detected\033[0m" << endl;
			Sleep(600);
		}
	} while (decision);

}
void BookMovie(int option)
{
	bool decision = true, validated = true;
	do {
		int record = 0, result = 0, time_validate = 0, inner = 0, movie_hall[30] = {}, date = 0, month = 0, year = 0, dd, mm, yyyy, moviefound[30] = {};
		string keyword, movie_time, currentdate;
		system("cls");
		cout << "\033[1;96m";
		for (int i = 0; i < 7; i++) {
			cout << "\t\t\t\t\t\t" << text[10][i] << endl;
		}
		cout << "\033[0m";
		ReadMovieRecord(record);
		GetSystemTime(&systemTime);
		cout << "\n\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" << systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
		cout << "\t\t\t" << string(150, char(95)) << endl;
		MoviePrinting(record, 0);
		cout << "\t\t\t" << string(150, char(95)) << endl;
		do {
			cin.clear();
			cout << "\033[1;33m";
			cout << "\t\t\tDear customer, please input current date (refer to upper right)" << endl;
			cout << "\033[0m";
			cout << "\t\t\tcurrent date in DD MM YYYY form >>>";
			cin >> dd >> mm >> yyyy;
			TimeChecking(dd, mm, yyyy, date, month, year, time_validate);
			if (time_validate > 0) {
				validated = false;
				currentdate = to_string(dd) + " " + to_string(mm) + " " + to_string(yyyy);
			}
			else
				cout << "\t\t\t\033[1;31m Invalid input detected\033[0m" << endl;
		} while (validated);
		cin.ignore();
		cout << "\t\t\tInput the keyword to search the movie <E>xit >>>";
		getline(cin, keyword);
		Sleep(400);
		keyword = upper(keyword);
		for (int i = 0; i < record; i++) {
			if (movie[i].movie_name.find(keyword) != string::npos) {//keyword checking process
				moviefound[inner] = i;
				inner++;
				if (inner == 1) {
					system("cls");
					cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
					cout << "\t\t\t" << setw(135) << systemTime.wDay << "/" << systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
					cout << "\t\t\t" << string(150, char(95)) << endl;
				}
				cout << "\n\t\t\tNo. " << inner << endl;//yellow
				cout << "\t\t\tMovie Name: " << movie[i].movie_name << endl;//blue
				cout << "\t\t\tMovie Description: " << movie[i].description << endl;
				cout << "\t\t\tMovie Time: " << movie[i].movie_time << endl;
				cout << "\t\t\tMovie Length H.MM: " << fixed << setprecision(2) << movie[i].movie_length << endl;
				cout << "\t\t\tMovie Hall: " << movie[i].movie_hall << endl;
			}
		}
		if (keyword == "E")
			decision = false;
		else if (inner == 0) {
			cout << "\t\t\t\033[1;31m no result found...\n\t\t\tReturn to booking page\033[0m" << endl;
			Sleep(1000);
		}
		else {
			cout << "\t\t\t" << string(150, char(95)) << endl;
			bool confirms = true;
			int found = 0, adult, child, total_people = 0, digit;
			string people[25] = {};
			string booking = "w";
			while (confirms) {
				cout << "\t\t\t\033[1;33mInput the showtime of the movie>>>";
				getline(cin, movie_time);
				cout << "\033[0m";
				digit = 0;
				for (int i = 0; i < movie_time.length(); i++) {
					if (isdigit(movie_time[i]))
						digit++;
				}
				if (movie_time == "E" || movie_time == "e") {
					confirms = false;
					decision = false;
				}
				else if (digit != movie_time.length())
				{
					confirms = false;
					cout << "\t\t\t\033[1;31mError detected....Leaving to booking page\033[0m" << endl;
					Sleep(1000);
				}
				else {
					int noMovie[10] = {}, index = 0, number = 0;
					bool result = MovieStartDetection(movie_time);

					for (int i = 0; i < record; i++) {
						if (movie_time == movie[moviefound[i]].movie_time) {
							noMovie[found] = moviefound[i];
							found++;
						}
					}
					if (result && found > 0) {
						do {
							string booking;
							cin.clear();
							index = noMovie[number];
							cout << "\t\t\tMovie Name: " << movie[index].movie_name << endl;
							cout << "\t\t\tMovie Description: " << movie[index].description << endl;
							cout << "\t\t\tMovie Time: " << movie[index].movie_time << endl;
							cout << "\t\t\tMovie Length H.MM: " << fixed << setprecision(2) << movie[index].movie_length << endl;
							cout << "\t\t\tMovie Hall: " << movie[index].movie_hall << endl;
							cout << "\t\t\t\033[1;32mAre this movie you want to book <Y>es <N>o>> >";
							getline(cin, booking);
							cout << "\033[0m";
							booking = upper(booking);
							string final;
							int row[25];
							int column[25];
							bool payment = true;
							if (booking == "Y") {
								NumberTicket(index, child, adult, row, column);
								cin.ignore();
								do {
									cin.clear();
									cout << "\t\t\tAre you confirms with this booking <Y>es <N>o>>>";
									getline(cin, final);
									final = upper(final);
									if (final == "Y")
										payment = false;
									else if (final == "N") {
										cout << "\t\t\t\033[1;31mPayment declined\033[0m" << endl;
										payment = false;
										confirms = false;
										decision = false;
										booking = "N";
									}
									else
										cout << "\t\t\t\033[1;31mInvalid input detected.\033[0m" << endl;
								} while (payment);
								if (final == "Y") {
									double price_child, price_adult, total_price, points;
									int nomember = 0, record = 0;
									OpenMemberDetails(nomember);
									ReadMovieRecord(record);
									string checking = "9999";
									MemberChecking(checking, nomember);
									price_child = child * child_price;
									price_adult = adult * adult_price;
									total_price = price_adult + price_child;
									points = int(total_price);
									system("cls");
									cout << "\t\t\t" << string(60, char(32)) << " PAYMENT SUMMARY " << string(60, CHAR(32)) << endl;
									cout << "\n\t\t\t" << string(150, char(95)) << endl;
									cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" << systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
									cout << "\t\t\t" << string(150, char(95)) << endl;
									cout << "\t\t\t\tMovie Name\t" << movie[index].movie_name << endl;
									cout << "\t\t\t\tMovie Time\t" << movie[index].movie_time << endl;
									cout << "\t\t\t\tMovie Hall\t" << movie[index].movie_hall << endl;
									cout << "\t\t\t" << string(150, char(95)) << endl;
									if (!(checking == "9999" || checking == "9998"))
										cout << "\t\t\t Member Name >>" << Member[stoi(checking)].Details_name << endl;
									cout << "\t\t\t" << string(150, char(95)) << endl;
									cout << fixed << setprecision(2) << endl;
									cout << "\t\t\t\t\tChild" << "\t\t\t\t\t\t\t\t\t" << child << "\t\t\t\t\t\t\t" << price_child << endl;;
									cout << "\t\t\t\t\tAdult" << "\t\t\t\t\t\t\t\t\t" << adult << "\t\t\t\t\t\t\t" << price_adult << endl;
									cout << "\t\t\t" << string(150, char(95)) << endl;
									cout << "\t\t\t\t   Seat Number" << endl;
									cout << "\t\t\t\t row" << "\t column " << endl;
									for (int i = 0; i < child + adult; i++) {
										cout << "\t\t\t\t  " << row[i] << "\t  " << column[i] << endl;
									}
									cout << "\t\t\t" << string(150, char(95)) << endl;
									cout << "\t\t\t\tTotal price \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << total_price << endl;
									cout << "\t\t\t\tservice tax \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << total_price * service_tax << endl;
									cout << "\t\t\t\tPrice After Tax \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\033[1;92m" << total_price * service_tax + total_price << "\033[0m" << endl;
									cout << fixed << setprecision(0) << endl;
									if (!(checking == "9999" || checking == "9998"))
										cout << "\t\t\t\tTotal point \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << points << endl;
									cout << "\t\t\t" << string(150, char(95)) << endl;
									cout << "\t\t\t" << string(60, char(32)) << " END OF PAGE " << string(60, CHAR(32)) << endl;
									cout << "\t\t\t" << string(150, char(95)) << endl;
									if (!(checking == "9999" || checking == "9998")) {
										OpenPurchaseHistory();
										int trace_member, tracked = 0, largest = 0;
										trace_member = stoi(checking);
										int number = 0;
										UpdateHistory(trace_member, number);
										Purchase[trace_member].Purchase_date[number] = currentdate;
										Purchase[trace_member].Purchase_movie[number] = movie[index].movie_name;
										Purchase[trace_member].Purchase_pax[number] = to_string(child) + " " + to_string(adult);
										Purchase[trace_member].Purchase_food[number] = "N/A";
										Member[trace_member].Details_point = to_string(int(stoi(Member[trace_member].Details_point) + points));
									}
									int j = 0;
									for (int i = movie[index].seats.data; i < movie[index].seats.data + adult + child; i++) {
										movie[index].seats.purchased_row[i] = row[j];
										movie[index].seats.purchased_column[i] = column[j];
										j++;
									}
									movie[index].seats.data += adult + child;
									LoadMemberDetail(nomember);
									LoadPurchaseHistory(nomember);
									LoadMovieRecord(record);
									confirms = false;
									decision = false;
									system("pause");
									break;
								}
							}
							else if (booking == "N") {
								number++;
								if (number == found) {
									cout << "\t\t\t\033[1;31mNo other movie found. Back to movie page\033[0m" << endl;
									cout << "\t\t\t";
									system("pause");
									return BookMovie(0);
								}
							}
							else
								cout << "\t\t\t\033[1;31mInvalid input detected.\033[0m" << endl;
						} while (booking == "N" || booking != "Y");
					}
					else
						cout << "\t\t\t\033[1;31mInvalid showtime detected...\033[0m" << endl;
				}
			}
		}
	} while (decision);
}
void NumberTicket(int index, int& child, int& adult, int row[], int column[]) {
	int input = 0, rows, columns, detected;
	CinemaSeatPrinting(index, 0);
	cout << "\t\t\tInput the number of children you want to book for >>>";
	cin >> child;
	cout << "\t\t\tInput the number of adult you want to book for >>>";
	cin >> adult;
	for (int i = 0; i < child + adult; i++) {
		cout << "\t\t\tNo. " << i + 1 << endl;
		do {
			detected = 0;
			cout << "\t\t\tInput the row you want >>>>";
			cin >> rows;
			cout << "\t\t\tInput the colomn you want >>>>";
			cin >> columns;
			if (rows > 9 || columns > 14)
				detected++;
			for (int j = 0; j < movie[index].seats.data; j++) {
				if (rows == movie[index].seats.purchased_row[i] && columns == movie[index].seats.purchased_column[i])
					detected++;
			}
			for (int j = 0; j < movie[index].backup.data; j++) {
				if (rows == movie[index].backup.row[i] && columns == movie[index].backup.column[j])
					detected++;
			}
			for (int i = 0; i < input; i++) {
				if (rows == row[i] && columns == column[i])
					detected++;
			}
			if (detected > 0)
				cout << "\t\t\t\033[1;31mcolumn of seat is not available.\033[0m" << endl;
		} while (detected != 0);
		if (detected == 0) {
			row[i] = rows;
			column[i] = columns;
			input++;
		}
	}
	cout << "\t\t\tSuccessfully booked the seats with " << endl;;
	for (int i = 0; i < child + adult; i++) {
		cout << "\t\t\tRow " << row[i] << " Column " << column[i] << endl;
	}
}
void MemberChecking(string& checking, int& nomember)
{
	string members, phone_number;
	do {
		cin.clear();
		cout << "\t\t\tAre you a member of our cinema <Y>es <N>o  >>";
		getline(cin, members);
		members = upper(members);
		if (members == "Y") {
			do {
				cout << "\t\t\tInput your phone number to record the points <E>xit >>>";
				getline(cin, phone_number);
				for (int i = 0; i < nomember; i++) {
					if (phone_number == Member[i].Details_phone)
						checking = to_string(i);
				}
				if (phone_number == "E")
					checking = "9998";
				else if (checking == "9999")
					cout << "\t\t\t\033[1;31mInvalid input detected.\033[0m" << endl;
			} while (checking == "9999");
		}
		else if (members == "N")
			checking = "9999";
		else
			cout << "\t\t\t\033[1;31mInvalid input detected.\033[0m" << endl;
	} while (!(members == "N" || members == "Y"));
}

void TimeChecking(int dd, int mm, int yyyy, int date, int month, int year, int& result) {
	if (mm >= 1 && mm <= 12) {
		if (to_string(yyyy).size() == 4) {//check year
			if (mm >= 1 && mm <= 7) {//check month
				if (mm == 2) {
					if ((dd >= 1 && dd <= 29) && (yyyy % 4 == 0))
						DateRecord(dd, mm, yyyy, date, month, year, result);
					else if ((dd >= 1 && dd <= 28) && (yyyy % 4 != 0))
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else if (mm % 2 == 0) {//check date
					if (dd >= 1 && dd <= 30)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else {
					if (dd >= 1 && dd <= 31)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
			}
			else {
				if (mm % 2 == 1) {
					if (dd >= 1 || dd <= 30)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else {
					if (dd >= 1 && dd <= 31)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
			}
		}
	}
}
void DateRecord(int dd, int mm, int yyyy, int date, int month, int year, int& result) {
	result++;
	date = dd, month = mm, year = yyyy;
}
void BookSeatPrinting(int w, int i, int j) {
	int checking = 1;
	if (movie[w].backup.data != 0) {
		for (int z = 0; z < movie[w].backup.data; z++) {
			if (i == movie[w].backup.row[z] && j == movie[w].backup.column[z]) {
				cout << setw(2) << " ";
				checking = 0;
			}
		}
	}
	else if (movie[w].seats.data != 0) {
		for (int z = 0; z < movie[w].seats.data; z++) {
			if (i == movie[w].seats.purchased_row[z] && j == movie[w].seats.purchased_column[z]) {
				cout << setw(2) << "X";
				checking = 0;
			}
		}
	}
	if (checking)
		cout << setw(2) << "A";
}
void CinemaRefresh(int option)
{
	string confirms;
	bool decision = true;
	int movie_record = 0, hall_record = 0, notfound;
	while (decision) {
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n" << endl;
		for (int i = 0; i < 7; i++)
			cout << "\t\t\t\t\t\t" << text[20][i] << endl;
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\tRefresh Cinema terms and conditions!!!" << endl;
		cout << "\t\t\t\tOnce you confirm to refresh the cinema, the available seats and the cinema hall record of each movie will be refreshed " << endl;
		cout << "\t\t\t\tTo the latest updated from the cinema hall record" << endl;
		cout << "\t\t\t\tThe system is not reversable after confirmation have made" << endl;
		cout << "\t\t\t\tRefreshing Cinema Confirmation" << endl;
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\t if Confirms <Y>es, else <N>o  >>>";
		getline(cin, confirms);
		confirms = upper(confirms);
		if (confirms == "Y") {
			ReadMovieRecord(movie_record);
			ReadCinemaHallRecord(hall_record);
			for (int i = 0; i < movie_record; i++) {
				notfound = 0;
				for (int j = 0; j < hall_record; j++) {//check if cinema hall not in the seatcontrol.txt
					if (movie[i].movie_hall == unavailable[j].hall) {
						notfound++;
					}
				}
				if (notfound != 1) {
					for (int j = i; j < movie_record; j++) {
						movie[j].movie_id = movie[j + 1].movie_id;
						movie[j].movie_name = movie[j + 1].movie_name;
						movie[j].description = movie[j + 1].description;
						movie[j].movie_time = movie[j + 1].movie_time;
						movie[j].movie_length = movie[j + 1].movie_length;
						movie[j].movie_hall = movie[j + 1].movie_hall;
						movie[j].seats.data = movie[j + 1].seats.data;
					}
					movie_record--;
				}
				movie[i].seats.data = 0;				//update seats data
				movie[i].seats.purchased_row[0] = 0;
				movie[i].seats.purchased_column[0] = 0;
				if (movie[i].movie_hall <= hall_record && movie[i].movie_hall > 0) {//refresh the data of cinema hall
					movie[i].backup.data = unavailable[movie[i].movie_hall - 1].data;
					if (movie[i].backup.data > 0) {
						for (int j = 0; j < movie[i].backup.data; j++) {
							movie[i].backup.row[j] = unavailable[movie[i].movie_hall - 1].row[j];
							movie[i].backup.column[j] = unavailable[movie[i].movie_hall - 1].column[j];
						}
					}
					else {
						movie[i].backup.row[0] = 0;
						movie[i].backup.column[0] = 0;
					}
				}
			}
			LoadMovieRecord(movie_record);
			decision = false;
		}
		else if (confirms == "N")
			decision = false;
		else
			cout << "\t\t\tInvalid Input found" << endl;
	}
}
void UpdateHistory(int& trace_member, int& number) {
	int tracked = 0, largest_date, largest_month, largest_year;
	string large;
	for (int i = 0; i < 5; i++) {
		string selected_date = Purchase[trace_member].Purchase_date[i];
		if (selected_date == "N/A") {//check if both are "N/A"
			number = i;
			tracked++;
			break;
		}
	}
	if (tracked == 0) {
		for (int i = 0; i < 5; i++) {
			large = Purchase[trace_member].Purchase_date[i];
			int date = stoi(large.substr(0, 2));
			int month = stoi(large.substr(3, 2));
			int year = stoi(large.substr(6, 4));
			if (i == 0) {
				largest_date = date;
				largest_month = month;
				largest_year = year;
			}
			if (largest_year == year) {
				if (largest_month > month) {
					largest_month = month;
					number = i;
				}
				else if (largest_month = month) {
					if (largest_date > date) {
						largest_date = date;
						number = i;
					}
				}
			}
			else if (largest_year > year) {
				largest_year = year;
				number = i;
			}
		}
	}
}
void LoadMemberDetail(int& nomember) {
	ofstream outfile;
	outfile.open("Admin_memberlist.txt");
	for (int i = 0; i < nomember - 1; i++) {
		outfile << Member[i].Details_user << endl;
		outfile << Member[i].Details_password << endl;
		outfile << Member[i].Details_name << endl;
		outfile << Member[i].Details_status << endl;
		outfile << Member[i].Details_join << endl;
		outfile << Member[i].Details_point << endl;
		outfile << Member[i].Details_phone << endl;
		outfile << Member[i].Details_email << endl;
	}
	outfile.close();
}
void LoadPurchaseHistory(int& nomember) {
	ofstream outfile;
	outfile.open("Admin_purchase.txt");
	for (int i = 0; i < nomember - 1; i++) {
		outfile << Purchase[i].Purchase_user << endl;
		outfile << Purchase[i].Purchase_name << endl;
		for (int j = 0; j < 5; j++) {
			outfile << Purchase[i].Purchase_date[j] << endl;
			outfile << Purchase[i].Purchase_pax[j] << endl;
			outfile << Purchase[i].Purchase_movie[j] << endl;
			outfile << Purchase[i].Purchase_food[j] << endl;
		}
	}
	outfile.close();
}
void MenuList() {
	system("cls");
	for (int i = 0; i < 7; i++) {
		cout << "\t\t\t\t\t\t\t" << text[9][i] << endl;
	}
	ifstream infile;
	infile.open("foodAndBeverage.txt");
	int i = 0;
	if (infile.is_open()) {
		cout << "\n\t\t\t\033[5;93m" << string(130, char(95)) << "\033[0m" << endl;
		cout << right << setw(100) << "Regular (RM)" << "\t\t" << "Large (RM)" << endl;
		while (!infile.eof()) {
			getline(infile, FNB[i].foodcode);
			getline(infile, FNB[i].foodname);
			infile >> FNB[i].regular_price >> FNB[i].large_price;
			infile.ignore();
			infile >> FNB[i].stock;
			infile.ignore();
			cout << showpoint << fixed << setprecision(2);
			cout << "\t\t\t\t\t" << setw(10) << FNB[i].foodcode << setw(30) << FNB[i].foodname << "\t" << setw(10) << FNB[i].regular_price << "\t\t" << setw(8) << FNB[i].large_price << endl;
			i++;
		}
		cout << "\n\n\t\t\t\033[5;93m" << string(130, char(95)) << "\033[0m" << endl;
		infile.close();
	}
	else {
		cout << "\t\t\t\033[1;31mPlease contact Cinema Admin for further assistance...\033[0m" << endl;;
	}
	cout << "\t\t\t";
	system("pause");
}
void inventoryMenu(int option)
{
	ReadTextRecord(0);
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[9][i] << endl;
	}
	cout << "\n\n\t\t\t\033[5;93m" << string(150, char(95)) << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	int fbrecord = 0;
	ReadFBRecord(fbrecord);
	cout << "\t\t\t" << right << setw(55) << "Regular (RM)" << "\t\t" << "Large (RM)" << "\t\t" << "Available Stock" << endl;
	for (int i = 0; i < fbrecord; i++)
	{
		cout << showpoint << fixed << setprecision(2);
		cout << "\t\t\t" << setw(10) << FNB[i].foodcode << setw(30) << FNB[i].foodname << "\t" << setw(10) << FNB[i].regular_price << "\t\t" << setw(8) << FNB[i].large_price << setw(15) << FNB[i].stock << endl;
	}
}
void addFB()
{

	char more = 'N';
	int i = 0;
	ofstream outfile;
	outfile.open("foodAndBeverage.txt", ios::app);
	if (outfile.is_open())
	{
		inventoryMenu(0);
		do {
			cout << right << setw(15);
			cout << " Code: ";
			cin.ignore();
			getline(cin, FNB[i].foodcode);
			cout << right << setw(15) << "Food Name: ";
			getline(cin, FNB[i].foodname);
			cout << right << setw(15) << "Regular Price: ";
			cin >> FNB[i].regular_price;
			cout << right << setw(15) << "Large Price: ";
			cin >> FNB[i].large_price;
			cout << right << setw(15) << "Available stock: ";
			cin >> FNB[i].stock;
			outfile << showpoint << fixed << setprecision(2);
			outfile << endl;
			outfile << FNB[i].foodcode << endl;
			outfile << FNB[i].foodname << endl;
			outfile << FNB[i].regular_price << " " << FNB[i].large_price << endl;
			outfile << FNB[i].stock;
			cout << "\t\t\tDo you wish to add more? Enter 'Y' to add more...";
			cin >> more;
		} while (toupper(more) == 'Y');

		outfile.close();
		system("cls");
		inventoryMenu(0);
	}
	else
	{
		cout << "\t\t\t\033[1;31mProblem occur!!! Please contact cinema admin for further assistance...\033[0m" << endl;
	}



}
void deleteFB(int option)
{
	bool found = true;
	int fbrecord = 0, detect = 0;
	do {
		string keyword;
		ReadFBRecord(fbrecord);
		system("cls");
		inventoryMenu(0);
		cout << "\t\t\tFood Code: ";
		cin >> keyword;
		keyword = upper(keyword);
		for (int i = 0; i < fbrecord; i++)
		{
			if (keyword == FNB[i].foodcode)
			{
				detect++;
				for (int j = i; j < fbrecord; j++)
				{
					FNB[j].foodcode = FNB[j + 1].foodcode;
					FNB[j].foodname = FNB[j + 1].foodname;
					FNB[j].regular_price = FNB[j + 1].regular_price;
					FNB[j].large_price = FNB[j + 1].large_price;
					FNB[j].stock = FNB[j + 1].stock;
				}
				fbrecord--;
			}
		}
		if (detect == 0)
			cout << "\t\t\t\033[1;31mInvalid Food Code found!!!\033[0m" << endl;
		else
			found = false;
		LoadFBRecord(fbrecord);
	} while (found);
	system("cls");
	inventoryMenu(0);
	system("pause");
	system("cls");
	FBManagement();
}
void inventoryFB(int option)
{
	ReadTextRecord(0);
	cout << "\033[1;96m";
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[8][i] << endl;
	}
	cout << "\033[0m\n\n\t\t\t/033[5;93m" << string(150, char(95)) << "\033[0m" << endl;
	int fbrecord = 0;
	ReadFBRecord(fbrecord);
	//let users to select whether to add or delete stock
	string keyword, line;
	int action, quantity, i = 0, size, index;
	bool decision = true, found = 0;
	do {
		system("cls");
		inventoryMenu(0);
		cout << "\n\n\n\t\t\t<1> Add Stock " << endl;
		cout << "\t\t\t<2> Reduce Stock " << endl;
		cout << "\t\t\t<3> Exit" << endl;
		cout << "\t\t\tEnter your action: ";
		cin >> action;
		if (action == 1 || action == 2)
		{
			cout << "\t\t\tFood Code: ";
			cin >> keyword;
			keyword = upper(keyword);
			size = keyword.length();
			for (int i = 0; i < fbrecord; i++)
			{
				if (keyword == FNB[i].foodcode)
					index = i;//record the location of code
			}
			if (size == 4 && keyword == FNB[index].foodcode)
			{
				cout << "\t\t\tQuantity: ";
				cin >> quantity;
				cout << FNB[index].stock << endl;
				if (action == 1)
					FNB[index].stock += quantity;
				else if (action == 2)
					FNB[index].stock -= quantity;
				cout << FNB[index].stock << endl;
				LoadFBRecord(fbrecord);


				cout << "\t\t\t\033[1;92mStock Updated.\033[0m" << endl;

			}
			else
				cout << "\t\t\t\033[1;31mInvalid id detected!!!\033[0m" << endl;
		}
		else if (action == 3)
			decision = false;
		else
		{
			cout << "\t\t\t\033[1;31mInvalid Action!!! Please enter <1> <2> <3>\033[0m" << endl;

		}
	} while (decision);
}
void FBManagement()
{
	system("cls");
	ReadTextRecord(0);
	cout << "\033[1;96m";
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[8][i] << endl;
	}
	cout << "\033[0m\n\n\t\t\t\033[5;93m" << string(150, char(95)) << endl;
	cout << "\t\t\t" << string(150, char(95)) << "\033[0m" << endl;
	bool con = true;
	do {
		int selection;
		cout << "\t\t\t<1> Add New Food and Beverage" << endl;
		cout << "\t\t\t<2> Delete Existing Food and Beverage" << endl;
		cout << "\t\t\t<3> Inventory Management" << endl;
		cout << "\t\t\t<4> Return to Administrator Menu" << endl;
		cout << "\t\t\tPlease enter your selection: ";
		cin >> selection;
		if (selection == 1)
		{
			system("cls");
			addFB();
		}
		else if (selection == 2)
		{
			system("cls");
			deleteFB(selection);
		}
		else if (selection == 3)
		{
			system("cls");
			inventoryFB(selection);
		}
		else if (selection == 4)
		{
			system("cls");
			con = false;
		}
		else
			cout << "\t\t\t\033[1;31mWrong Input!!! Please enter <1> <2> <3>\033[0m" << endl;
	} while (con);
}
void ReadFBRecord(int& fbrecord)
{
	ifstream infile;
	infile.open("foodAndBeverage.txt");
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			getline(infile, FNB[fbrecord].foodcode);
			getline(infile, FNB[fbrecord].foodname);
			infile >> FNB[fbrecord].regular_price >> FNB[fbrecord].large_price;
			infile >> FNB[fbrecord].stock;
			infile.ignore();
			fbrecord++;
		}
		infile.close();
	}
	else
		cout << "\t\t\t\033[1;31mPlease contact Cinema Admin for further assistance...\033[0m";
}
void LoadFBRecord(int& fbrecord)
{
	ofstream outfile;
	outfile.open("foodAndBeverage.txt");
	for (int i = 0; i < fbrecord; i++)
	{
		outfile << FNB[i].foodcode << endl;
		outfile << FNB[i].foodname << endl;
		outfile << FNB[i].regular_price << " " << FNB[i].large_price << endl;
		outfile << FNB[i].stock;
		if (i != fbrecord - 1)
			outfile << endl;
	}
}
void purchaseFB(int option)
{
	system("cls");
	ReadTextRecord(0);
	cout << "\033[1;96m";
	for (int i = 0; i < 7; i++)
	{
		cout << "\t\t\t\t\t\t\t\t" << text[11][i] << endl;
	}
	cout << "\033[0m\n\n\t\t\t\033[5;93m" << string(150, char(95)) << endl;
	cout << "\t\t\t" << string(150, char(95)) << "\033[0m" << endl;
	int fbrecord = 0;
	ReadFBRecord(fbrecord);
	string checking = "9999";
	int nomember = 0;
	GetSystemTime(&systemTime);
	cout << "\n\n\n\n\t\t\t\033[5;93m" << string(150, char(95)) << "\033[0m" << endl;
	cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" << systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
	cout << "\t\t\t\033[5;93m" << string(150, char(95)) << "\033[0m" << endl;
	for (int i = 0; i < fbrecord; i++)
	{
		cout << showpoint << fixed << setprecision(2);
		cout << "\t\t\t" << setw(5) << "<" << i + 1 << ">" << setw(30) << FNB[i].foodname << "\t" << setw(10) << FNB[i].regular_price << "\t" << setw(6) << FNB[i].large_price << endl;
	}
	int choice, size, time_validate = 0, date = 0, month = 0, year = 0, dd, mm, yyyy;
	string currentdate;
	double price, total = 0;
	int quantity, point;
	bool correct = 0, validated;
	string cont;
	string foodname[30] = {};
	int total_quantity[30] = {};
	double unit_price[30] = {};
	int checker = 0, trace_member, tracked = 0, largest = 0, number;
	do {
		cin.clear();
		cout << "\t\t\tDear customer, please input current date (refer to upper right)" << endl;
		cout << "\t\t\tcurrent date in DD MM YYYY form >>>";
		cin >> dd >> mm >> yyyy;
		TimeChecking(dd, mm, yyyy, date, month, year, time_validate);
		if (time_validate > 0)
		{
			validated = false;
			if (mm < 10)
				currentdate = to_string(dd) + " " + to_string(0) + to_string(mm) + " " + to_string(yyyy);
			else
				currentdate = to_string(dd) + " " + to_string(mm) + " " + to_string(yyyy);
		}
		else
			cout << "\t\t\t\033[1;31mInvalid input detected.\033[0m" << endl;
	} while (validated);
	do {

		do {
			cout << "\n\n\n\t\t\tEnter your choice: ";
			cin >> choice;
			if (choice <1 || choice>fbrecord)
				cout << "\t\t\t\033[1;31mInvalid Input!!!\033[0m" << endl;

			else
				correct = 1;

		} while (correct == 0);
		correct = 0;
		do {
			cout << "\t\t\tSize: <1> Regular <2> Large: ";
			cin >> size;
			if (size < 1 || size>2)
				cout << "\t\t\t\033[1;31mInvalid Input!!!\033[0m" << endl;
			else
				correct = 1;
		} while (correct == 0);
		correct = 0;
		do {
			cout << "\t\t\tQuantity: ";
			cin >> quantity;
			if (quantity < 0)
				cout << "\t\t\t\033[1;31mInvalid Input!!!\033[0m";
			else if (quantity > FNB[choice - 1].stock)
				cout << "\t\t\t\033[1;31mOut of Stock!!!\033[0m" << endl;
			else
				correct = 1;
		} while (correct == 0);

		if (size == 1)
		{
			price = FNB[choice - 1].regular_price * quantity;
			unit_price[checker] = FNB[choice - 1].regular_price;
		}
		else
		{
			price = FNB[choice - 1].large_price * quantity;
			unit_price[checker] = FNB[choice - 1].large_price;
		}
		foodname[checker] = FNB[choice - 1].foodname;
		total_quantity[checker] = quantity;
		total += price;
		point = int(total);

		FNB[choice - 1].stock -= quantity;
		LoadFBRecord(fbrecord);

		cout << "\t\t\tDo you want to add another F&B? <Y> to continue...";
		cin >> cont;
		checker++;
	} while (upper(cont) == "Y");
	cin.ignore();
	system("cls");
	OpenMemberDetails(nomember);
	MemberChecking(checking, nomember);
	cout << "\t\t\t" << string(60, char(32)) << " PAYMENT SUMMARY " << string(60, char(32)) << endl;
	cout << "\n\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" << systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	if (!(checking == "9999" || checking == "9998"))
		cout << "\t\t\t Member Name >>" << Member[stoi(checking)].Details_name << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << fixed << setprecision(2) << endl;
	cout << "\t\t\t\t" << setw(20) << "F & B name\t\t\t\t Unit Price\t\t\t\tQuantity\t\t\t\tTotal Price" << endl;
	for (int i = 1; i <= checker; i++)
	{
		cout << "\t\t\t" << setw(20) << foodname[i - 1] << "\t\t\t\t" << unit_price[i - 1] << "\t\t\t\t\t" << total_quantity[i - 1] << "\t\t\t\t\t" << unit_price[i - 1] * total_quantity[i - 1] << endl;
	}
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t\tTotal price \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << total << endl;
	cout << "\t\t\t\tservice tax \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << total * service_tax << endl;
	cout << "\t\t\t\tPrice After Tax \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\033[1;92m" << total * service_tax + total << "\033[0m" << endl;
	cout << fixed << setprecision(0) << endl;
	if (!(checking == "9999" || checking == "9998"))
		cout << "\t\t\t\tTotal point \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << point << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t" << string(60, char(32)) << " END OF PAGE " << string(60, CHAR(32)) << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	system("pause");
	if (!(checking == "9999" || checking == "9998"))
	{
		trace_member = stoi(checking);
		OpenPurchaseHistory();
		number = 0;
		UpdateHistory(trace_member, number);
		Purchase[trace_member].Purchase_date[number] = currentdate;
		Purchase[trace_member].Purchase_movie[number] = "N/A";
		Purchase[trace_member].Purchase_pax[number] = "N/A";
		string food;
		for (int i = 1; i <= checker; i++)
		{
			food += foodname[i - 1];
			if (i < checker) {
				food += ", ";
			}
		}
		Purchase[trace_member].Purchase_food[number] = food;
		Member[trace_member].Details_point = to_string(int(stoi(Member[trace_member].Details_point) + point));
		LoadPurchaseHistory(nomember);
		LoadMemberDetail(nomember);
	}
}
void ReadTextRecord(int record) {
	ifstream infile;
	infile.open("Title.txt");
	if (infile.fail())
		cout << "unable to open the file" << endl;
	else {
		while (!infile.eof()) {
			for (int i = 0; i < 26; i++) {
				for (int j = 0; j < 7; j++) {
					getline(infile, text[i][j]);
				}
			}
		}
	}
}
void Main_Menu(string Name) {
	for (int i = 0; i < 7; i++) {
		SetConsoleTextAttribute(console, 14);
		cout << "\t\t\t\t\t" << text[21][i] << endl;
		SetConsoleTextAttribute(console, 7);
	}
	int i = 126;
	cout << "\n\t\t\t" << string(122, char(61)) << "\n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << string(4, ' ') << "." << string(18, char(i)) << "." << string(22, ' ') << "." << string(21, char(i)) << "." << string(25, ' ') << "." << string(17, char(i)) << "." << string(5, ' ') << "|| \n";
	cout << "\t\t\t||" << string(4, ' ') << "[ 1| Movie Details ]" << string(22, ' ') << "[ 2| Food & Beverages ]" << string(25, ' ') << "[ 3. Purchase Now ]" << string(5, ' ') << "|| \n";
	cout << "\t\t\t||" << string(4, ' ') << "." << string(18, char(i)) << "." << string(22, ' ') << "." << string(21, char(i)) << "." << string(25, ' ') << "." << string(17, char(i)) << "." << string(5, ' ') << "|| \n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << string(24, ' ') << "." << string(20, char(i)) << "." << string(23, ' ') << "." << string(23, char(i)) << "." << string(24, ' ') << "|| \n";
	cout << "\t\t\t||" << string(24, ' ') << "[ 4| Membership Page ]" << string(23, ' ') << "[ 5| Administrator Page ]" << string(24, ' ') << "|| \n";
	cout << "\t\t\t||" << string(24, ' ') << "." << string(20, char(i)) << "." << string(23, ' ') << "." << string(23, char(i)) << "." << string(24, ' ') << "|| \n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << string(45, ' ') << "." << string(23, char(i)) << "." << string(48, ' ') << "|| \n";
	cout << "\t\t\t||" << string(45, ' ') << "| 6| Customer Feedback  |" << string(48, ' ') << "|| \n";
	cout << "\t\t\t||" << string(45, ' ') << "." << string(23, char(i)) << "." << string(48, ' ') << "|| \n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << string(51, ' ') << "." << string(11, char(i)) << "." << string(54, ' ') << "|| \n";
	cout << "\t\t\t||" << string(51, ' ') << "[ 7|  EXIT  ]" << string(54, ' ') << "|| \n";
	cout << "\t\t\t||" << string(51, ' ') << "." << string(11, char(i)) << "." << string(54, ' ') << "|| \n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t||" << right << setw(121) << "||\n";
	cout << "\t\t\t" << string(122, char(61)) << "\n";
}