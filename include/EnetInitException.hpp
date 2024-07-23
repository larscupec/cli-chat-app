#pragma once

#include <exception>

class EnetInitException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "An error occurred while initializing ENet.";
  }
};
