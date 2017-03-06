#ifndef SOCIETY_HPP_INCLUDED
#define SOCIETY_HPP_INCLUDED

#include <cstring>
#include "govt.hpp"
#include "rlutil.h"

typedef unsigned long long ull;



class address{
public:
    unsigned short number;                  // House number
    unsigned short region;                  // Region code
    int operator =(address & a){            // Standard copy constructor
        this->number = a.number;
        this->region = a.region;
    }
};

class house{
    public:
	house(address, ull);		    // Constructor
        void purchase(ull);	 	    // Purchase of house
                                            // true on success, false on failure
        ull getown(void);                   // Returns owner UID
	ull getHID(void);		    // Returns HID or House Identification Number
        address getadr(void);               // Returns house address
        ull getprice(void);		    // Returns price of house
        friend bool occupy(ull, ull);	    // Refer to occupy(ull id, ull hid) after class definitions
	friend house ::govt::matchhouse(ull); // Refer to govt.hpp

    private:
	ull HID;			    // House Identification Number
        ull owner;      	            // Owner UID
	ull renter;			    // If house is rented, to whom
        bool isrented;                      // Is the house currently out on rent
        bool isoccupied;                    // Does anyone currently live in the house
        address adr;                        // Location of the house
        ull price;           		    // Market sale price of house
//      Rent of house = price/100           // Will be calculated later as per price

};

class human{

    public:
        human(std::string, unsigned short,	    // Constructor
              unsigned int, ull,	    // Takes name, age, year of birth,
              bool);      	            // parent's UID (either) and sex
	
	human(void){ ;}			    // Default constructor

        std::string getname(void);               // Returns name of person
        unsigned short getage(void);        // Returns age of person
        ull getUID(void);                   // Returns UID of person
        ull getparent(bool = false);        // Returns parent's UID; false for 1st, true for 2nd
        house getres(void);                 // Returns residence of person
        ull getcash(bool = false);	    // Returns balance; cash on hand for false, bank balance for true
        bool isadult(void);                 // Is the person an adult
        ull getacc(void);        	    // Returns bank account number of person
        ull getspouse(void);                // Returns spouse UID, NULL if unmarried
        ::govt::bank::loan getloan(void);     // Returns load ID, NULL if no loan taken
        void adulthood(void);               // Changes person into adult, generates empty bank account
        friend bool house::purchase(ull);   // Refer to class house
        friend bool occupy(ull, ull);	    // Refer to occupy(ull id, ull hid) after class definitions
	friend bool govt::bank::trans(ull,  // Refer to govt.hpp
				      ull,
				      bool);
	friend human govt::matchhuman(ull); // Refer to govt.hpp

    private:
        std::string name;                        // Name of person
        unsigned short age;                 // Age of person
        unsigned int year;                  // Year of birth
        ull UID;                            // Unique Identification Number (UID number)  -- 12 digits
        ull residence;        	            // HID of residence of person
        ull parent_UID[2];                  // UID of person's parents
        bool sex;                           // Sex of person; False for male, true for female
        ull cash;         		    // Cash on hand, valid for children as well

        //////////////////////////
        // Adult Criteria
        //////////////////////////

        bool adult;                         // Is person an adult
        ull acc; 		            // Bank account number, corresponds to World Bank
        ull loan;                           // Loan ID, if any; 0 by default i.e. no loan
        ull spouse; 	                    // Spouse UID

        //////////////////////////
        // Election Criteria
        //////////////////////////

        bool prez_cand;                     // Is the person participating in presidential elections
        unsigned short vote;                // Candidate number to whom vote is cast; reset to 0 after election

        //////////////////////////
};




///////////////////////////////////////////////////
///     Function definitions for class human

human::human(std::string inp_name, unsigned short inp_age,
	     unsigned int inp_year, ull inp_par_uid,
	     bool inp_sex){

	this->name = inp_name;
	this->age = inp_age;
	this->year = inp_year;
	this->sex = inp_sex;

	human temp (govt::matchhuman(inp_par_uid));

	this->parent_UID[0] = inp_par_uid);
	this->parent_UID[1] = temp.getspouse());

	this->adulthood(void);
	
	this->loan = 0;
	this->spouse = 0;
	this->prez_cand = false;
	this->vote = 0;

	govt::addUID(void);
	this->UID = govt::getmaxUID(void);
}

std::string human::getname(void){
	return this->name;
}

unsigned short human::getage(void){
	return this->age;
}

ull human::getUID(void){
	return this->UID;
}

ull human::getparent(bool a){
	return this->parent_UID[a];
}

house human::getres(void){
	return govt::matchhouse(this->residence);
}

ull human::getcash(bool a){
	if(a){
		return govt::bank::getbal(this->acc);
	}
	else{
		return this->cash;
	}
}

ull human:getspouse(void){
	return this->spouse;
}

govt::bank::loan human::getloan(void){
	return govt::bank::matchloan(this->loan);
}

void human::adulthood(void){
	if(this->isadult(void)){
		return;
	}
	if(this->age >=18){
		this->adult = true;
		this->acc = govt::bank::newacc(this->UID);
	}

	else{
		this->adult = false;
		this->acc = 0;
	}
}

bool human::isadult(void){
	if(this->adult){
		return true;
	}
	else{
		return false;
	}
}

///////////////////////////////////////////////////
///  Function defenitions for class house

house::house(address inp_addr, ull inp_pr, ull inp_id){
	this->adr = inp_addr;
	this->price = inp_pr;

	this->HID = inp_id;

	this->owner = 0;
	this->renter = 0;
	this->isrented = false;
	this->isoccupied = false;
}

address house::getadr(void){
	return this->adr;
}

ull house::getprice(void){
	return this->price;
}

ull house::getown(void){
	return this->owner;
}

ull house::getHID(void){
	return this->HID;
}

void house::purchase(ull id){
	human temp;
	temp = govt::matchhuman(this->owner);

	std::cout << "\n\nAre you sure you wish to purchase house number "
		<< this->adr.number << " in " << govt::getRegionName(this->adr)
		<< "?\n" << "You must pay " << CURRENCY << this->getprice(void)
		<< " to " << temp.name << ".";

	
	
	bool a = false;	
	do{	
		char inp; std::cin.ignore(1000, '\n');
		inp = getch();
	
		switch (inp){
			case 'y': case 'Y':
				human buyer = govt::matchhuman(id);
				if(this->isoccupied(void)){
					rlutil::setColor(rlutil::RED);
					std::cout << "\nPurchase fail! House is occupied!";
					rlutil::setColor(rlutil::WHITE);
				}
				if(this->isrented(void)){
					rlutil::setColor(rlutil::RED);
					std::cout << "\nPurchase fail! House is rented!";
					rlutil::setColor(rlutil::WHITE);
				}
				if(temp2.getcash(true) >= this->getprice(void)){
					govt::bank::trans(buyer.acc, this->getprice(void), false);
					govt::bank::trans(temp.acc, this->getprice(void), true);
					this->owner = buyer.getUID(void);
					rlutil::setColor(rlutil::GREEN);
					std::cout << "\nPurchase successful!";
					rlutil::setColor(rlutil::WHITE);					
				}	
				else{
					rlutil::setColor(rlutil::RED);
					std::cout << "\nYou do not have enough money in bank!";
					rlutil::setColor(rlutil::WHITE);
				}			
				a = true;
				break;
			case 'n': case 'N':
				a = true;
				break;
			default:
				rlutil::setColor(rlutil::RED);
				std::cout << "Invalid input!";
				rlutil::setColor(rlutil::WHITE);
		}
	}while(!a)
}

///////////////////////////////////////////////////

bool occupy(ull id, ull hid){
	human temp;
	temp = govt::matchhuman(id);

	house temph;
	temph = govt::matchhouse(hid);

	if(temph.owner == temp.getUID(void) || temph.owner == temp.getspouse(void) ||
	   temph.owner == temp.getparent(false) || temph.owner == temp.getparent(true))
	{
		if(!temph.isrented){
			temp.residence = temph.getHID(void);
			temph.isoccupied = true;
			return true;
		}
		else{
			return false;
		}
	}
	else if(temph.isrented(void)){
		if(temph.renter == temp.getUID(void) || temph.renter == temp.getspouse(void) ||
		   temph.renter == temp.getparent(false) || temph.renter == temp.getparent(true))
		{
			temp.residence = temph.getHID(void);
			temph.isoccupied = true;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
		
}

#endif // SOCIETY_HPP_INCLUDED
