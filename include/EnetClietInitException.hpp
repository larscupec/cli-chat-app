#pragma once

#include <exception>

class EnetClientInitException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "An error occurred while trying to create an ENet client host.";
  }
};
