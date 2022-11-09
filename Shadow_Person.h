
#ifndef _SHADOW_PERSON_H_
#define _SHADOW_PERSON_H_

#include "Person.h"

class Shadow_Person: public Person
{
 private:
 public:
  
  std::string host_url;
  std::string class_id;
  std::string object_id;

  Shadow_Person(std::string, std::string, std::string, std::string);
  virtual Json::Value dump2JSON(); // print the content of the object
};

#endif // _SHADOW_PERSON_H_
