/*!	

	\file   table.cpp
	\brief   Code of some functions of Table class
	\author  
	\date    2017-12-13
	\version 1.0
*/

#include <map>

#include <cassert>

#include <iostream>

#include "table.hpp"

#include "../includes/utils.hpp"


bool lp::Table::lookupSymbol(const std::string & name) const 
{		
	return this->_table.find(toLower(name)) != this->_table.end();
}


lp::Symbol * lp::Table::getSymbol(const std::string & name)
{
 #ifndef NDEBUG
   // Precondition
   assert (this->lookupSymbol(name) == true);
 #endif //NDEBUG

 return	this->_table[toLower(name)];
}



void lp::Table::installSymbol(Symbol * s)
{
  assert(this->lookupSymbol(s->getName()) == false);
  this->_table[toLower(s->getName())] = s;
  assert(this->lookupSymbol(s->getName()) == true);
}



void lp::Table::eraseSymbol(const std::string & name)
{
 #ifndef NDEBUG
  // Precondition
   assert (this->lookupSymbol(name) == true);
 #endif //NDEBUG

   // The symbol "name" is deleted from the map
   this->_table.erase(toLower(name));

 #ifndef NDEBUG
  // Postcondition
   assert (this->lookupSymbol(name) == false);
 #endif //NDEBUG
}


void lp::Table::printTable()
{
	for(std::map<std::string, lp::Symbol *>::const_iterator it = this->_table.begin();
        it != this->_table.end();
        ++it)
    {
		std::cout<<it->first<<", "<<getSymbol(it->first)->getToken()<< std::endl;
	}
}
