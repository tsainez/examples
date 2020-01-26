//
//  OperatorOverloading.cpp
//
//  Created by Anthony Sainez on 1 November 2019
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <iostream>
using namespace std;

class Distance {
private:
	int meter;
public:
	Distance(int m)								{ 		meter = m;			}

	bool operator < 	(const  Distance d ) 	{ return meter < d.meter;	}

	bool operator <= 	(const Distance d) 		{ return meter <= d.meter; 	}

	bool operator > 	(const Distance d)		{ return meter > d.meter; 	}

	bool operator >= 	(const Distance d)		{ return meter >= d.meter; 	}

	bool operator == 	(const Distance &d) 	{ return meter == d.meter; 	}

	bool operator !=	(const Distance &d) 	{ return meter != d.meter; 	}

	void operator = 	(const  Distance &d) 	{ meter = d.meter;			}

	Distance operator + (const Distance &d) {
		Distance dist(0);
		dist.meter = this->meter + d.meter; // this = d1; d = d2
		return dist;
	}

	Distance operator - (const Distance &d) {
		Distance dist(0);
		dist.meter = this->meter - d.meter; // this = d1, d = d2
		return dist;
	}

	Distance operator * (const Distance &d) {
		Distance dist(0);
		dist.meter = this->meter * d.meter;
		return dist;
	}

	Distance operator / (const Distance &d) {
		Distance dist(0);
		dist.meter = this->meter / d.meter; // this = d1; d = d2
		return dist;
	}

	friend ostream &operator << (ostream &output, const Distance &D) {
		output << D.meter << "m " << endl;
	}

	friend istream &operator >> (istream &input, Distance &D) {
		input >> D.meter;
		return input;
	}
};

int main() {
	Distance d1(4), d2(2), d3(0), d4(4);
	cout << "d1 = " << d1 ; //  << for d1, d2, d3 and d4
	cout << "d2 = " << d2 ;
	cout << "d3 = " << d3 ;
	cout << "d4 = " << d4 ;
	d4 = d1+d2;

	// simple operators
	cout << "d1 + d2 =  d4 = " 	<< d1 + d2;				// +
	cout << "d2 - d1 = " 		<< d2 - d1;
	cout << "d1 / d2 = "		<< d1 / d2;
	cout << "d2 * d1 = "		<< d2 * d1;

	// checking statements
	cout << "(d1 < d2) is " 	<< (d1 < d2) 	<< endl; 	// <
	cout << "(d3 < d1) is " 	<< (d3 < d1) 	<< endl;
	cout << "(d2 <= d1) is " 	<< (d2 <= d1) 	<< endl;
	cout << "(d2 >= d1) is "	<< (d2 >= d1)	<< endl;
	cout << "(d2 > d1) is " 	<< (d2 > d1) 	<< endl;
	cout << "(d4 == d1) is " 	<< (d4 == d1) 	<< endl; 	// ==
	cout << "(d4 != d1) is " 	<< (d4 != d1) 	<< endl; 	// !=

	cout << "Enter d4: ";
	cin >> d4;											// >>
	cout << "d4 = " << d4; 								// <<
}

/* test run
d1 = 4m 
d2 = 2m 
d3 = 0m 
d4 = 4m 
d1 + d2 =  d4 = 6m 
d2 - d1 = -2m 
d1 / d2 = 2m 
d2 * d1 = 8m 
(d1 < d2) is 0
(d3 < d1) is 1
(d2 <= d1) is 1
(d2 >= d1) is 0
(d2 > d1) is 0
(d4 == d1) is 0
(d4 != d1) is 1
Enter d4: 3
d4 = 3
Realtek 8821AE Wireless LAN 802.11ac PCI-E NIC
Realtek PCIe GBE Family Controller
*/
