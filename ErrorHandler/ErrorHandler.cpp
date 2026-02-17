#include "ErrorHandler.h"

string choiceChecker( const string & input, int start, int end )
{
  for (int i = start; i <= end; ++i) 
  {
    if( input == to_string(i) )
      return to_string(i);
  }
  return "ERROR";
}