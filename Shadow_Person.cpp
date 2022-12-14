
#include "Shadow_Person.h"
#include "ecs36b_Exception.h"

// JSON RPC part
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

Shadow_Person::Shadow_Person
(std::string arg_host_url, std::string arg_class_id, std::string arg_object_id, std::string arg_name)
{
  this->host_url = arg_host_url;
  this->class_id = arg_class_id;
  this->object_id = arg_object_id;
  this->name = arg_name;
  std::cout << "Shadow_Person Object created" << std::endl;
}

Json::Value
Shadow_Person::dump2JSON()
{
  HttpClient httpclient((this->host_url).c_str());
  hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  try {
    myv = myClient.dump2JSON("dump2JSON", "Felix Wu",
			     (this->class_id).c_str(), (this->host_url).c_str(),
			     (this->object_id).c_str());

    // throw ecs36b_Exception {};
    // cout << myv.toStyledString() << endl;
    } catch (JsonRpcException &e) {
    // } catch (ecs36b_Exception &e) {
    std::cout << "Here\n";
    cerr << e.what() << endl;
  }
  
  return myv;
}

