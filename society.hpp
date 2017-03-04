#ifndef SOCIETY_HPP_INCLUDED
#define SOCIETY_HPP_INCLUDED

#include <string>
#include "govt.hpp"

typedef unsigned long long ull;

class human{

    public:
        human(string, unsigned short,	    // Constructor
              unsigned int, ull,	    // Takes name, age, year of birth,
              bool);      	            // parent's UID (either) and sex

        string getname(void);               // Returns name of person
        unsigned short getage(void);        // Returns age of person
        ull getUID(void);                   // Returns UID of person
        ull getparent(bool = false);        // Returns parent's UID; false for 1st, true for 2nd
        house getres(void);                 // Returns residence of person
        ull getcash(bool = false);	    // Returns balance; cash on hand for false, bank balance for true
        bool isadult(void);                 // Is the person an adult
        ull getacc(void);        	    // Returns bank account number of person
        ull getspouse(void);                // Returns spouse UID, NULL if unmarried
        govt::bank::loan getloan(void);     // Returns load ID, NULL if no loan taken
        void adulthood(void);               // Changes person into adult, generates empty bank account
        friend bool house::purchase(ull,    // Refer to class house
                                    ull);
	friend bool house::occupy(ull);	    // Refer to class house
	friend human matchhuman(ull);       // Refer to matchhuman(ull id)

    private:
        string name;                        // Name of person
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

class house{
    public:
	house(address, ull);		    // Constructor
	house(void);			    // Default Constructor
        void purchase(ull, ull);	    // Sale/purchase of house
                                            // purchase(a, b)
                                            // ownership transfers from a to b
                                            // true on success, false on failure
        ull getown(void);                   // Returns owner UID
        address getadr(void);               // Returns house address
        ull getprice(void);		    // Returns price of house
        friend bool occupy(ull);	    // Change occupancy status of house
	friend house matchhouse(ull)	    // Refer to matchhouse(ull id) after class definitions 

    private:
	ull HID;			    // House Identification Number
        ull owner;      	            // Owner UID
        bool isrented;                      // Is the house currently out on rent
        bool isoccupied;                    // Does anyone currently live in the house
        address adr;                        // Location of the house
        ull price;           		    // Market sale price of house
//      Rent of house = price/100           // Will be calculated later as per price

};

struct address{
    unsigned short number;                  // House number
    unsigned short region;                  // Region code
    operator =(address & a){                // Standard copy constructor
        this->number = a.number;
        this->region = a.region;
    }
};




///////////////////////////////////////////////////
///     Function definitions for class human

human::human(string inp_name, unsigned short inp_age,
	     unsigned int inp_year, ull inp_par_uid,
	     bool inp_sex){

	this->name = inp_name;
	this->age = inp_age;
	this->year = inp_year;
	this->sex = inp_sex;

	human temp (matchhuman(inp_par_uid));

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

string human::getname(void){
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
	return matchhouse(this->residence);
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


///////////////////////////////////////////////////

human matchhuman(ull id){
	; // stuff
}

house matchhouse(ull id){
	; // stuff
}

#endif // SOCIETY_HPP_INCLUDED
