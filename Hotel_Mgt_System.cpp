//Rachit Jas       ---  13BCE0810
//Shashank Shankar --- 13BCE0838
//Data Structures And Algorithms Project
//Hotel Management System


//UPDATE Log: 26/10/2014
//1. Registration Queue has been converted into a Circular Queue
//2. Added Room Numbers For The Guests
//3. Authentication provided
//4. Better Documentation in the code

//Important Note : Use "pass12" as password for authentication

/////////////////////////////////////////////////HEADER Files/////////////////////////////////////////////////////////////////////
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//CONSTANT Used
#define SIZE 5
#define size 6

//COUNTER Variable 
int i=0;

//NAMESPACE Used
using namespace std;

//CLASS Prototype
class Guest;
class Registration;
class Restuarant;



///////////////////////////////////////////////////GUEST Class////////////////////////////////////////////////////////////////////
/*Description: The main guest class, which serves as the base class for may other declared classes. Crucial as it stores the 
               details of the class.*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
               
class Guest
{
	protected:
//-------------------------------->DATA Members 
	char name[20];
	char room_preference;
	int age;
	int days;
	long long int phone_number;
	int roomno;
	
	public:
        
//-------------------------------->MEMBER Functions
	
		//To input the details of the guest
		 void get()
		{		system("cls");
                int x;
                fflush(stdin);
			    cout<<"\n\n For the Guest "<<++i<<",";
			    cout<<"\n Enter the name: ";
				gets(name);
				cout<<" Enter the age: ";
				cin>>age;
				cout<<" Enter the phone number (the primary number): ";
				cin>>phone_number;
				cout<<" Enter the choice of room:\n\n a: Suite         (Rent = Rs.10000 per day)\n b: Luxury        (Rent = Rs.8000 per day)\n c: Super deluxe  (Rent = Rs.6000 per day)\n d: Deluxe        (Rent = Rs.3000 per day)"<<endl;
				x:
                cout<<"\n "; cin>>room_preference;
				if(isalpha(room_preference))
				{if((room_preference!='a')&&(room_preference!='b')&&(room_preference!='c')&&(room_preference!='d'))
				{
					cout<<"\n Please enter a valid choice from the list\n"; goto x;
				}
				cout<<"\n Enter the number of days of stay: ";
				cin>>days;
                } else { cout<<"\n Please enter a valid choice from the list\n";  goto x;}
		}
		
		//To display the details of the guest
		void display()
		{
			    cout<<endl;
                cout<<"\n Name of the guest: "<<name;
				cout<<"\n Age of the guest: "<<age;
				cout<<"\n Phone number: "<<phone_number;
				cout<<"\n Type of room allotted: "<<room_preference<<endl;
				//b.amt(a[i]);
		}
		
		//friends for this class
				friend class Registration;
				friend void room_allocate(Guest &x);
		};
////////////////////////////////////////////////////////////END OF GUEST CLASS////////////////////////////////////////////////////////////		






		
	
//////////////////////////////////////////////////////////REGISTRATION Class/////////////////////////////////////////////////////////////
/*Description: Registration class implements the concept of Circular Queues using arrays. A front and a rear variable has been declared 
			   outside the class, which will control the flow. */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////               

//FRONT AND REAR OF THE CIRCULAR QUEUE
int front = -1;
int rear  = -1;

//REVENUE Collected
int revenue = 0;

	class Registration: public Guest
{

//------------------------------>DATA Members
        int price;
		public:
			
//------------------------------>MEMBER Functions
		
			friend class Guest;
			friend void room_deallocate(Registration &x);
		    Registration()
		    {
		    	price=0;
		    }
			
			void copy(Guest p)
			{
				room_allocate(p);
				strcpy(name,p.name);
				room_preference = p.room_preference;
				age = p.age;
				days = p.days;
				phone_number = p.phone_number;
				roomno = p.roomno;
			}

			void amt()
			{  
				if(room_preference == 'a')
				price = 10000*(days);
				else if(room_preference == 'b')
				price = 8000*(days);
				else if(room_preference == 'c')
				price = 6000*(days);
				else if(room_preference == 'd')
				price = 3000*(days);
				else
				{
					price = 3000*(days);
					room_preference = 'd';
					//cout<<"\nThe guest has been allotted the Delux room";
				}
				revenue += price;
			}
             
			void show_amount()
			{
				cout<<" Room Alloted to the guest: "<<roomno<<endl;
				cout<<" Amount payable by the guest: Rs. "<<price<<endl;
			}
			
		  void Revenue()
			{
				cout<<"\n Revenue collected: Rs. "<<revenue;
			}
			
};

///////////////////////////////////////////////////////END OF REGISTRATION CLASS////////////////////////////////////////////////////////////		


//---------------->VARIABLES to govern the flow of the Registration
Registration b[SIZE];
int n = 0;   //Keeps track of the object counts
Guest guest[SIZE*2];

//---------------->ROOM Number Counter Variables		
int suite_counter = 100;
int luxury_counter = 200;
int sdeluxe_counter = 300;
int deluxe_counter = 400;


//ROOM Allocation Function
void room_allocate(Guest &x)
{
	switch(x.room_preference)
	{
		case 'a':
			x.roomno = suite_counter;
			suite_counter++;
			break;
		case 'b':
			x.roomno = luxury_counter;
			luxury_counter++;
			break;
		case 'c':
			x.roomno = sdeluxe_counter;
			sdeluxe_counter++;
			break;
		case 'd':
			x.roomno = deluxe_counter;
			deluxe_counter++;
			break;	
	}	
}	





//ROOM De-allocation Function
void room_deallocate(Registration &x)
{
	switch(x.room_preference)
	{
		case 'a':
			x.roomno = suite_counter;
			suite_counter--;
			break;
		case 'b':
			x.roomno = luxury_counter;
			luxury_counter--;
			break;
		case 'c':
			x.roomno = sdeluxe_counter;
			sdeluxe_counter--;
			break;
		case 'd':
			x.roomno = deluxe_counter;
			deluxe_counter--;
			break;	
	}	
}			

//---------------------------------------CIRCULAR QUEUE OPERATIONS------------------------------------------------


//***********************************>ENQUEUE OPERATION	

//Accomodating Guests Module
void Accomodate_Guests()
{ 		
		cout<<"\n Kindly enter the details of the guest: ";
		if((front == 0 && rear == SIZE-1) || (front == rear+1))
		{
			cout<<"\n Sorry, the registrations are full!! No seats available! Please try later ...";
			
		}
		else if(rear == -1)
		{
			guest[n].get();
			front = rear = 0;
			//system("cls");
			b[rear].copy(guest[n]);
        	b[rear].amt();
        	cout<<endl;
          	b[rear].show_amount();
          	n++;
		}
		else
		{
			if(rear == SIZE-1)
			rear=0;
			else
			++rear;
			guest[n].get();
			//system("cls"); n++;
			b[rear].copy(guest[n]);
        	b[rear].amt();
        	cout<<endl;
          	b[rear].show_amount();
          	n++;
	    }
        
    
}			


//*************************************>DEQUEUE OPERATION	

//Removing Guests Module
void Remove_Guests()
{
		int c;
		cout<<"\n The first guest details will be deleted permanently.\n Are you still sure you want to continue? (Yes = 1/ No = 0)\n";
		cout<<" "; cin>>c;
		if(c == 1)
		{
			if(front == -1)
			{
				cout<<"\nNo guests are currently residing in the hotel. Sorry ...";
	
			}
			else if(front == rear)
			{
				cout<<"\nThe following guest details have been deleted: \n";
				b[front].display();
				room_deallocate(b[front]);
				front = rear = -1;
				--n;
			}
			else
			{
				cout<<"\nThe following guest details have been deleted: \n";
				b[front].display();
				room_deallocate(b[front]);
				if(front==SIZE-1)
                front=0;
	   		    else
    		    ++front;
				--n;
			}
		}
		
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////END OF CIRCULAR QUEUE IMPLEMENTATION/////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////STACK Class////////////////////////////////////////////////////////////////////
/*Description: Stack class, as the name suggests, implements the Stack Data Structure. The Stack Class along with the function 
			   authentication() provide a high security authentication program. The entire program works only if the Activation code 
			   entered is correct */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////               

//ACTIVATION Code For The Program
char password[] = "pass12";

//STACK Class
class Stack
{
//------------------------------------->DATA Members	
	char word[size];
	int TOP;
	
	public:

//------------------------------------->MEMBER Functions	
		
	//CONSTRUCTOR Initializing TOP = -1 
	Stack()
	{
		TOP =-1 ;
	}
	
	//PUSH Function
	void push(char w)
	{
		if(TOP == size-1)
		{
			cout<<"\nStack Overflow! \n Aborting ...";
		}
		else 
		{
			TOP++;
			word[TOP] = w;
		}
	}
	
	//POP Function
	char pop()
	{
		char x=word[TOP];
		if(TOP == -1)
		{
			cout<<"\nStack Underflow! \n Aborting ...";
		}
		else 
		{
			TOP--;
			return x;
		}
	}
	
}r;


////////////////////////////////////////////END OF STACK CLASS/////////////////////////////////////////////////////



//AUTHENTICATION Function
void authentication()
{
	cout<<"\t\t----------------DISCLAIMER-----------------------";
	cout<<"\n\nThe following work belongs to the respective authors. Any kind of misuse or \ncopying of the personal work without the prior consent and permission of the authors is liable";
	cout<<" to Copyright Infringement. The password will not be shown to the user.The user should ensure to enter the password correctly without any mistakes. \nCorrecting the ";
	cout<<"mistakes is not allowed. In case of a wrong password, the user\ncan try again."<<endl<<endl;
	cout<<"Enter Passowrd : ";
	char x = getch();
	cout<<"*";
	r.push(x);
	for(int i=0;i<size-1; i++)
	{
		r.push(getch());
		cout<<"*";
	}
	for(int i=5; i>=0; i--)
	{
		if(password[i] != r.pop())
		{
		cout<<"\nAccess Denied! \nWrong Password. Please verify your access code and try again later ...";
		for(int i=0; i<10; i++) 
		cout<<"";
		getch();
		exit(0);
		}
	}
	cout<<"\n\nAccess Aprroved ...";
	getch();
	fflush(stdin);
	system("cls");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////END OF STACK IMPLEMENTATION////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////INTRO-SCREEN///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void intro_screen()
{
	cout<<"\n\n\n\n\t\ts\t\t  HOTEL";
	for(int i=0; i<200000000; i++);
	cout<<"\n\n\t\t\t\tMANAGEMENT";
	for(int i=0; i<200000000; i++);
	cout<<"\n\n\t\t\t\t  SYSTEM\n";
	for(int i=0; i<500000000; i++);
	
	cout<<"\n\n\n\t\tVersion Alpha 4.0";
	
	cout<<"\n\n\t\t__________________________________________";
	cout<<"\n\t\t|DEVELOPERS: Rachit Jas       [13BCE0810]|";
	cout<<"\n\t\t|            Shashank Shankar [13BCE0838]|";
	cout<<"\n\t\t|________________________________________|\n";
	//for(int i=0; i<1100000000; i++);
	cout<<endl<<"\t\t\t";
	system("pause");
	system("cls");
	for(int i=0; i<3; i++)
	{
		cout<<"\n\n\n\n\t\t\t    LOADING ...";     for(int i=0; i<150000000; i++); system("cls");
		cout<<"\n\n\n\n\t\t\t    LOADING  ...";    for(int i=0; i<150000000; i++); system("cls");
		cout<<"\n\n\n\n\t\t\t    LOADING   ...";   for(int i=0; i<150000000; i++); system("cls");
	}


}


//////////////////////////////////////////////////////////RESTUARANT Class/////////////////////////////////////////////////////////////
/*Description: Restuarant is a class which keeps a check on the orders placed by the customers. The class implements the Linked List Data
			   Structure  	 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////               

//COUNTER Variable
int restcounter = 0;

class Restuarant
{
	int tableno;
	int dishno;
	char dish[10][20];
	int bill;
		public:
    Restuarant *next;

	Restuarant()
	{
		for(int i=0; i<10; i++)
		strcpy(dish[i],"N/A");
		tableno = bill = 0;
		dishno = 0;
		next = NULL;
	}
	
	void getorder()
	{
		cout<<"\nEnter the following details: ";
		cout<<"\nTable No: "; cin>>tableno;
		cout<<"\nHow many dishes are to be ordered? \n"; cin>>dishno;
		cout<<"\nPlease place the order ";
		cout<<"\nMENU\n\n";
		cout<<"1. Veg Puff\n2. Chicken Puff\n3. Veg Paneer Roll\n4. Veg Aloo Roll\n5. Chicken Roll\n6. Chicken 65\n\n";  
		for(int i=0; i<dishno; i++)
		{
			cout<<endl; cin>>dish[i];
			if(checkorder(dish[i]) == 0)
			{
				again:
				cout<<"The dish you have ordered does not exist in the menu. Please Try Again!";
				system("pause");			
				goto again;
			}
		}
		cout<<"\nAmount Payable By the Customer: "<<bill;
	}
	
	void displayorder()
	{
		cout<<"\nTable No: "<<tableno;
		cout<<"\nNumber of dishes ordered: "<<dishno;
		cout<<"\nOrder Placed: ";
			for(int i=0; i<10; i++)
		{
			cout<<endl<<dish[i];
		}
		cout<<"\nAmount Payable By the Customer: "<<bill;
	}
	
	int checkorder(char *x)
	{
		if(strcmp(x,"Veg Puff")==0)
			bill += 50;
		else if(strcmp(x,"Chicken Puff")==0)
			bill += 98;
		else if(strcmp(x,"Veg Paneer Roll")==0)
			bill += 87;
	    else if(strcmp(x,"Veg Aloo Roll")==0)
			bill += 66;
		else if(strcmp(x,"Chicken Roll")==0)
			bill += 99;
		else if(strcmp(x,"Chicken 65")==0)
			bill += 55;
		else if(strcmp(x,"Paneer 65")==0)
			bill += 45;
		else if(strcmp(x,"Tomato Soup")==0)
			bill += 56;
		else if(strcmp(x,"Chicken Soup")==0)
			bill += 66;
		else if(strcmp(x,"French Fries")==0)
			bill += 70;
		else if(strcmp(x,"Veg Aloo Tikki")==0)
			bill += 77;
		else if(strcmp(x,"Chicken Tikki")==0)
			bill += 78;
		else if(strcmp(x,"Masala Dosa")==0)
			bill += 79;
		else if(strcmp(x,"Plain Dosa")==0)
			bill += 80;
		else if(strcmp(x,"Idli Sambar")==0)
			bill += 81;
		else if(strcmp(x,"Raj Kachori")==0)
			bill += 85;
		else if(strcmp(x,"Chicken Burger")==0)
			bill += 88;
		else if(strcmp(x,"Veg Cheese Burger")==0)
			bill += 11;
		else if(strcmp(x,"Finger Chips")==0)
			bill += 55;
		else if(strcmp(x,"Cholle Bhature")==0)
			bill += 88;
		else if(strcmp(x,"Ice Cream Mango")==0 || strcmp(x,"Ice Cream Vanilla")==0 || strcmp(x,"Ice Cream Strawberry")==0 || strcmp(x,"Ice Cream Chocolate")==0 || strcmp(x,"Ice Cream Blueberry")==0 || strcmp(x,"Pista")==0) 
			bill += 67;
		else if(strcmp(x,"Tea")==0 || strcmp(x,"Coffee")==0)
			bill += 76;
		else if(strcmp(x,"Mountain Dew")==0 || strcmp(x,"Pepsi")==0 || strcmp(x,"Sprite")==0 || strcmp(x,"7Up")==0 || strcmp(x,"Coca Cola")==0 || strcmp(x,"Thums Up"))
			bill += 60;
		else return 0;	
		return 1;
		
	}
	
	int returntableno()
	{
		return tableno;
	}
}*reaar=NULL, *froont=NULL;

void insertorder()
{
	Restuarant *p = new Restuarant;
	p->getorder();
	++restcounter;
	if(reaar == NULL)
	{
		reaar = p;
		froont = p;		
	}
	else
	{
	    reaar->next = p;
	    reaar = p;
	}
	delete p;
}

void deleteorder()
{
	int tablenu, n=1;
	if(reaar!=NULL)
	{
	
	cout<<"\nWhich order would you like to remove? Please provide the table number: ";
	cin>>tablenu;
	Restuarant *p = new Restuarant;
	p = froont;
	Restuarant *q = new Restuarant;
	while(p!=NULL)
	{
		if(p->returntableno() == tablenu)
		break;
		p=p->next;
		++n;
	}
	if(n == 1)
	{
		p=froont;
		froont=froont->next;
		p->displayorder();
		delete p;
		delete q;
	}
	else if(n == restcounter)
	{
		p = froont;
		for(int i = 1; i < n; i++)
		p = p->next;
		q = froont;
		for(int i = 1; i < n-1; i++)
		q = q->next;
		q->next = NULL;
		reaar = q;
		delete p;
		delete q;
	}
	else 
	{
		p = froont;
		for(int i = 1; i < n; i++)
		p = p->next;
		q = froont;
		for(int i = 1; i < n-1; i++)
		q = q->next;
		q = p->next;
		delete p;
		delete q;		
	}
	}
	else
	cout<<"\nNo Orders have been placed yet. Try Again Later!";
	
}


void showorder()
{
	if(restcounter != 0){
	cout<<"\nHere all the orders that have been placed: ";
	Restuarant *p = new Restuarant;
	p=froont;
	while(p!=NULL)
	{p->displayorder(); cout<<endl; p = p->next; }
	delete p;
	}
	else 
	cout<<"\nNo Orders have been placed yet.";
}








////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////------------>MAIN Method<---------------////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int main()
	{   
		authentication();
		char choice; char choiceR; char choiceRest;
		intro_screen();
		beg:
		while(1) {
		system("cls");	
		cout<<"------------------------->Hotel Management System<------------------------------";
		cout<<"\n 1. Registrations Desk";
		cout<<"\n 2. Restuarant Counter";
		cout<<"\n 3. Exit\n\n";
		cout<<" "; cin>>choice;
		if(isdigit(choice))
		{
		if(choice == '1')
		{
			while(1)
			{
			system("cls");
			cout<<"\n Welcome to the Registrations Desk !";
			cout<<"\n\n 1. Accomodate guests";
			cout<<"\n 2. Check out guests";
			cout<<"\n 3. Display residing guests";
			cout<<"\n 4. Total revenue collected in registration";
			cout<<"\n 5. Return to the menu\n\n";
			cout<<" "; cin>>choiceR;
			if(isdigit(choiceR))
			{if(choiceR == '1')
			Accomodate_Guests();
			else if(choiceR == '2')
			Remove_Guests();
			else if(choiceR == '3')
			{
				if(front != -1)
				{
				cout<<"\n Here are the following guest residing in the hotel.\n";	
				int i;
				for( i = front; i!= rear; i=(i+1)%SIZE)
				{ b[i].display(); b[i].show_amount(); }
				 b[i].display(); b[i].show_amount(); 
				
		        }
		        else
		        {
		        	cout<<" The hotel is empty! No details to be displayed ...";
		        }
			}
		    else if(choiceR == '4')
		    b[front].Revenue();
		    else if(choiceR == '5')
		    goto beg;
		    cout<<endl;
		    system("pause");
		    }
            else {cout<<"\n Please enter an option from the menu"; getch();}
            }
		}
		else if(choice == '2')
		{
			while(1)
			{
			system("cls");
			cout<<"\n Welcome to the Restuarant Counter!";
			cout<<"\n\n 1. Place the order of the guest";
			cout<<"\n 2. Delete the order of the guest";
			cout<<"\n 3. Display the order of the guest";
			cout<<"\n 4. Return to the main menu";
			cout<<"\n "; cin>>choiceRest;
			if(choiceRest == '1')
			insertorder();
			else if(choiceRest == '2')	
			deleteorder();
			else if(choiceRest == '3')
			showorder();
			else 
			goto beg;
			cout<<endl;
			system("pause");
			}
		}
		else if(choice == '3')
		exit(0);
        } else {cout<<"\n Please enter an option from the menu"; getch();}
		
			}
		
	}
//Deallocating room number
/*	//Accomodating Guests Module
	    cout<<"\nKindly enter number of guests: ";
		cin>>n;
		if(n>SIZE)
		{
			cout<<"\nMore than "<<SIZE<<" persons cannot be accomodated. "<<"\nWe are accomodating "<<SIZE<<" people only and not "<<n<<". Sorry\n";
			n=SIZE;
		}
        
		Guest a[10];
        
		for(i=0;i<n;i++)
        a[i].get();
        
		//system("cls");
        
		for(i=0;i<n;i++)
        {
        	if()
			b[i].copy(a[i]);
        	b[i].amt();
          	b[i].show_amount();
		}
		*/
		

