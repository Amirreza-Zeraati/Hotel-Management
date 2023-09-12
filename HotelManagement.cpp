
//----- Amirreza Zeraati -----


//libraries
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<cstring>
#include<conio.h>
#include<fstream>

//maximum number of rooms
#define max 100

using namespace std;

class Customer
{
	public:
		string name;
		string address;
		string phone;
		float payment_advance;
		string booking_id;
};

class Room
{
	public:
		string type;
		string roomNumber;
		string rent;
		int status;
		
	class Customer cust;
	class Room addRoom(string);
	void searchRoom(string);
	void displayRoom(Room);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//check the number .... numbers have to be integer
bool Numint(const string& str)
{
    for(char const &c : str) 
    {
        if(isdigit(c) == 0) return false;
    }
    return true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//save room data in HotelManage_rooms.txt
void SaveRoomData(string a, char b, string c)
{
	ofstream outputfile("HotelManage_rooms.txt" , ios::app);
	outputfile <<"Room Number : "<<a<<" | Type : "<<b<<" | Daily Rent : "<<c<<".000"<< endl;
}
//save customer data in HotelManage_customer.txt
void SaveCustomerData(string a, string b,string c, string d, float e)
{
	ofstream outputfile("HotelManage_customer.txt" , ios::app);
	outputfile <<"Booking ID : "<<a<<" | Name : "<<b<<" | Address : "<<c<<" | Phone : "<<d<<" | Advance Payment : "<<e<<endl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//show room data from HotelManage_rooms.txt
void ShowRoomData()
{
    ifstream MyFile("HotelManage_rooms.txt");
	char ch;
	while(!MyFile.eof())
	{
		MyFile.get(ch);
		cout<<ch;
	}
}
//show customer data from HotelManage_customer.txt
void ShowCustomerData()
{
    ifstream MyFile("HotelManage_customer.txt");
	char ch;
	while(!MyFile.eof())
	{
		MyFile.get(ch);
		cout<<ch;
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//class add rooms
class Room rooms[max];
int count = 0;

Room Room::addRoom(string r)
{
	class Room room;
	room.roomNumber = r;
	char Q;
	string dr;
	
	Qsw:
	cout<<"\nType Size (S-Single / D-Double / T-Triple): ";
	cin>>Q;
	Q = toupper(Q);
	switch(Q)
	{
		case 'S':
			room.type = Q;
			break;
		case 'D':	
			room.type = Q;
			break;
		case 'T':
			room.type = Q;
			break;
		default :
				cout<<"Error! Enter correct option";
				goto Qsw;
				break;
	}
	indr:
	cout<<"\nDaily Rent: ";
	cin>>dr;
	if(Numint(dr) == true)
	{
		room.rent = dr;
	}
	else
	{
		cout<<"Error! Enter Integer"<<endl;
		goto indr;
	}
	
	room.status = 0;
	
	cout<<"\nRoom Added Successfully!";
	SaveRoomData(r,Q,dr);
	getch();
	return room;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//search rooms
void Room::searchRoom(string r)
{
	int i,found=0;
	for(i=0 ; i<count ; i++)
	{
		if(rooms[i].roomNumber == r)
		{
			found = 1;
			break;
		}
	}
	if(found == 1)
	{
		if(rooms[i].status == 1)
		{
			cout<<"\nRoom is Reserved";
		}
		else
		{
			cout<<"\nRoom is available";
		}
		cout<<"\nRoom Details : \n";
		displayRoom(rooms[i]);
		getch();
	}
	else
	{
		cout<<"\nRoom Not Found";
		getch();
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//show room details
void Room::displayRoom(Room tempRoom)
{
	cout<<"\nRoom Number: "<<tempRoom.roomNumber;
	cout<<"\nType Size (S/D/T): "<<tempRoom.type;
	cout<<"\nDaily Rent: "<<tempRoom.rent<<".000";
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//class check-in
class Hotelmanage:protected Room
{
	public:
		void checkIn();
		void getAvailRoom();
		void searchCustomer(string);
};

void Hotelmanage::checkIn()
{
	class Room room;
	int i, found=0;
	string ph, r, id;
	
	inroomnum:
	cout<<"\nEnter Room number: ";
	cin>>r;
	if(Numint(r) == true)
	{
		for(i=0 ; i<count ; i++)
		{
			if(rooms[i].roomNumber == r)
			{
				found = 1;
				break;
			}
			else
			{
				cout<<"\nRoom Not Found";
				getch();
				return;
			}
		}
		if(found == 1)
		{
			if(rooms[i].status == 1)
			{
				cout<<"\nRoom is already Booked";
				getch();
				return;
			}
			
			inputid:
			cout<<"\nEnter booking id: ";
			cin>>id;
			if(Numint(id) == true)
			{
				rooms[i].cust.booking_id = id;
			}
			else
			{
				cout<<"Error! Enter Integer"<<endl;
				goto inputid;
			}
			
			cout<<"\nEnter Customer Name (First Name): ";
			cin>>rooms[i].cust.name;
			
			cout<<"\nEnter Address (only city): ";
			cin>>rooms[i].cust.address;
			
			inphone:
			cout<<"\nEnter Phone: ";
			cin>>ph;
			if(ph.length()==11 && Numint(ph) == true)
			{
				rooms[i].cust.phone = ph;
			}
			else
			{
				cout<<"Error! Your number is not correct "<<endl;
				goto inphone;
			}
			
			cout<<"\nEnter Advance Payment: ";
			cin>>rooms[i].cust.payment_advance;
			
			rooms[i].status=1;
			
			cout<<"\nCustomer Checked-in Successfully!";
			
			SaveCustomerData(rooms[i].cust.booking_id,rooms[i].cust.name,rooms[i].cust.address,rooms[i].cust.phone,rooms[i].cust.payment_advance);
			getch();
		}
	}
	else
	{
			cout<<"Error! Enter Integer"<<endl;
			goto inroomnum;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void manageRooms()
{
	class Room room;
	int opt, i, flag=0;
	string r;
	do
	{
		system("cls");
		cout<<"\n  ================ \n||  Manage Rooms  ||\n  ================  \n";
		cout<<"\n| 1. Add Room";
		cout<<"\n| 2. Search Room";
		cout<<"\n| 3. Show All Rooms";
		cout<<"\n| 4. Back to Main Menu";
		cout<<"\n\nEnter Option: ";
		cin>>opt;
		switch(opt)
		{
			case 1:
				inputroomnum:
				cout<<"\nEnter Room Number: ";
				cin>>r;
				if(Numint(r) == true)
				{
					i=0;
					for(i=0 ; i<count ; i++)
					{
						if(rooms[i].roomNumber == r)
						{
							flag = 1;
						}
					}
					if(flag == 1)
					{
						cout<<"\nRoom Number is Present.\nPlease Enter Unique Number";
						flag = 0;
						getch();
					}
					else
					{
						rooms[count] = room.addRoom(r);
						count++;
					}
				}
				else
				{
					cout<<"Error! Enter Integer"<<endl;
					goto inputroomnum;
				}
				break;
				
			case 2:
				cout<<"\nEnter room number: ";
				cin>>r;
				room.searchRoom(r);
				break;
				
			case 3:
				ShowRoomData();
				getch();
				break;
				
			case 4:
				//nothing to do
				break;
				
			default:
				cout<<"\nPlease Enter correct option";
				break;
		}
	}while(opt!=4);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Hotelmanage::getAvailRoom()
{
	int i, found = 0;
	for(i=0 ; i<count ; i++)
	{
		if(rooms[i].status == 0)
		{
			displayRoom(rooms[i]);
			cout<<"\n\nPress enter for next room";
			found = 1;
			getch();
		}
	}
	if(found==0)
	{
		cout<<"\nAll rooms are reserved";
		getch();
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Hotelmanage::searchCustomer(string pname)
{
	int i, found=0;
	for(i=0 ; i<count ; i++)
	{
		if(rooms[i].status == 1 && rooms[i].cust.name == pname)
		{
			cout<<"\nCustomer Name: "<<rooms[i].cust.name;
			cout<<"\nRoom Number: "<<rooms[i].roomNumber;
			
			cout<<"\n\nPress enter for next record";
			found = 1;
			getch();
		}
	}
	if(found == 0)
	{
		cout<<"\nPerson not found.";
		getch();
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void managecustomer()
{
	class Hotelmanage H;
	int opt;
	string pname;
	do
	{
		system("cls");
		cout<<"\n  ==================== \n||  Manage Customers  ||\n  ====================  \n";
		cout<<"\n| 1. Search Customer";
		cout<<"\n| 2. Show All Customers";
		cout<<"\n| 3. Back to Main Menu";
		cout<<"\n\nEnter Option: ";
		cin>>opt;
		switch(opt)
		{
			case 1:
				if(count == 0)
				{
					cout<<"\nRooms are not available.\nPlease add the rooms first.";
					getch();
				}
				else
				{
					cout<<"Enter Customer Name: ";
					cin>>pname;
					H.searchCustomer(pname);
				}
				break;
				
			case 2:
				ShowCustomerData();
				getch();
				break;

			case 3:
				//nothing to do
				break;
			default:
				cout<<"\nPlease Enter correct option";
				break;
		}
	}while(opt!=3);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main()
{
	class Hotelmanage H;
	int i, j, opt, r;
	char ch;
	system("cls");
	
	do
	{
		system("cls");
			cout<<" "
			<<"\n	###       ###        ########      ####################   ##############    ###"
			<<"\n	###       ###      ############    ####################   ##############    ###"
			<<"\n	###       ###     ###        ###           ###            ###               ###"
			<<"\n	###       ###    ###          ###          ###            ###               ###"
			<<"\n	#############   ###            ###         ###            ##############    ###"
			<<"\n	#############   ###            ###         ###            ##############    ###"  
			<<"\n	###       ###    ###          ###          ###            ###               ###"
			<<"\n	###       ###     ###        ###           ###            ###               ###"
			<<"\n	###       ###      ############            ###            ##############    ###############"
			<<"\n	###       ###        ########              ###            ##############    ###############";

		cout<<"\n\n\n  ==================== \n||  Hotel Management  ||\n  ====================  \n";
		cout<<"\n| 1. Manage Rooms";
		cout<<"\n| 2. Check-In Room";
		cout<<"\n| 3. Available Rooms";
		cout<<"\n| 4. Manage Customers";
		cout<<"\n| 5. Exit";
		cout<<"\n\nEnter Option: ";
		cin>>opt;
		
		switch(opt)
		{
		case 1:
			manageRooms();
			break;
			
		case 2:
			if(count == 0)
			{
				cout<<"\nRooms data is not available.\nPlease add the rooms first.";
				getch();
			}
			else
			H.checkIn();
			break;
			
		case 3:
			if(count == 0)
			{
				cout<<"\nRooms data is not available.\nPlease add the rooms first.";
				getch();
			}
			else
			H.getAvailRoom();
			break;
			
		case 4:
			managecustomer();
			break;
			
		//exit	
		case 5:
			break;
			
		default:
			cout<<"\nPlease Enter correct option";
			break;
		}
	}while(opt != 5);
	getch();
}
