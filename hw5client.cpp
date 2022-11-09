

// ecs36b first program

#include <iostream>
#include "Shadow_Thing.h"
#include "Shadow_Person.h"
#include "Network.h"
#include "IOT_Thing.h"

using namespace std;

int
main()
{
  // first object
  // Shadow_Thing st_1 { "http://10.42.0.1:8384", "Thing", "00000001" };
  Shadow_Person me { "http://127.0.0.1:8384", "Person", "123456789", "Felix Wu" };
  // Shadow_Person me { "http://10.42.0.1:8384", "Person", "123456789", "Felix Wu" };

  Json::Value result;
  result = me.dump2JSON();
  cout << result.toStyledString() << endl;

  return 0;
}
