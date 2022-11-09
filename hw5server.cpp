
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "IOT_Thing.h"
#include "Person.h"
#include "Thing.h"
#include <time.h>
#include "Shadow_Thing.h"

using namespace jsonrpc;
using namespace std;

// std::map (key, value pairs)
std::map<std::string, Person *> Person_Map;

class Myhw5Server : public hw5Server
{
public:
  Myhw5Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value dump2JSON(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id);
};

Myhw5Server::Myhw5Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Server(connector, type)
{
  std::cout << "Myhw5Server Object created" << std::endl;
}

// member functions

Json::Value
Myhw5Server::dump2JSON
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id)
{
  // a pointer to Person
  Person *person_ptr; // now a local variable

  Json::Value result;
  std::cout << action << " " << arguments << std::endl;
  std::string strJson;

  if (class_id != "Person")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
    }
  else
    {
      if (Person_Map.find(object_id) != Person_Map.end())
	{
	  // existing person
	  person_ptr = Person_Map[object_id];
	  result = person_ptr->dump2JSON();
	  result["status"] = "successful";
	}
      else
	{
	  // new person
	  result["status"] = "new student";
	  person_ptr = new Person {};
	  person_ptr->SSN = object_id;
	  person_ptr->name = arguments;
	  person_ptr->location = GPS_DD {38.53888138735077, -121.75446251026008};
	  person_ptr->home = GPS_DD {38.53617254217249, -121.75750539507422};
	  Person_Map[object_id] = person_ptr;

	  // save it to the file
	  int rc;
	  JvTime *t_now = getNowJvTime();
	  person_ptr->since_when = (*t_now);
	  
	  char name_buf[256];
	  bzero(name_buf, 256);
	  sprintf(name_buf, "./json_objects/%s_%s_%s.json",
		  object_id.c_str(), arguments.c_str(), (t_now->getTimeString())->c_str());
	  Json::Value jv_p = person_ptr->dump2JSON();
	  rc = myJSON2File(name_buf, &jv_p);
	  if (rc != 0)
	    {
	      std::cout << "myJSON2File error " << rc << std::endl;
	      exit(-1);
	    }
	  delete t_now;
	}

      for (const auto& [key, value] : Person_Map)
	std::cout << '[' << key << "] = " << value << ";\n ";
    }

  return result;
}

int main()
{
  HttpServer httpserver(8384);
  Myhw5Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
