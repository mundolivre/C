///////////////////////////////////////////////////////////
//  HTTP.h
//  Implementation of the Class HTTP
//  Created on:      15-dez-2011 23:01:27
//  Original author: neriberto
///////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

using namespace std;

class HTTP
{

public:
	HTTP();
	virtual ~HTTP();

	void getFile(string URL);
	void getHeader();

};
