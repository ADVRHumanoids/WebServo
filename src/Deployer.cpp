/*
 * Copyright (C) 2017 IIT-ADVR
 * Author:  Giuseppe Rigano
 * email:   giuseppe.rigano@iit.it
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
*/


#include <iostream>
#include <unistd.h>
#include <cstring>
#include <signal.h>
#include <cstdlib>
#include <Deployer.h>
     
bool exitNow = false;

Deployer::Deployer(std::string address)
{
    //_path_to_cfg(robot->getPathToConfig())
    std::string aport = PORT;
    /*YAML::Node root_cfg = YAML::LoadFile(_path_to_cfg);
    const YAML::Node &web_server = root_cfg["WebServer"]; 
    if(web_server){
       address = web_server["address"].as<std::string>();
       port = web_server["port"].as<std::string>();
       aport = address +":"+port;
    } */
    
    if (address != "")
     aport = address;
    
    std::string droot = "";
    /*const char* env_p = std::getenv("XBOT_ROOT");
    if( env_p != nullptr && !(strcmp(env_p,"") == 0))
       droot = std::string(env_p) + std::string(DOCUMENT_ROOT);
    */
    const char *options[] = {
            "document_root", droot.c_str(), "listening_ports", aport.c_str(), 0};
    
    std::vector<std::string> cpp_options;
    for (int i=0; i<(sizeof(options)/sizeof(options[0])-1); i++) {
        cpp_options.push_back(options[i]);
    }      
    
    sharedData = std::make_shared<SharedData>();
    

    try{
      server = std::make_shared<CivetServer>(cpp_options);  
    }catch( CivetException e ){ std::cout<<"Port "<< aport <<" already in use from another process"<<std::endl; std::cout<<e.what()<<std::endl; exit(1);}
    ws_civet_handler = std::make_shared<WebSocketHandler>(sharedData);   
    
    server->addWebSocketHandler("/pointcloud", *ws_civet_handler);

    http_handler = std::make_shared<HttpHandler>(sharedData);
    http_civet_handler = std::make_shared<HttpCivetHandler>(http_handler);
    server->addHandler(HOME_URI, *http_civet_handler);
   
    std::cout << "WebServo running at http://" << aport << std::endl;

}

void exit_handler(int s){
    
   std::cout<<"signal "<<s <<std::endl;
  exitNow = true;
 

}
 
int main(int argc, char *argv[])
{
   
    signal(SIGINT, exit_handler); 
      
    Deployer deployer("10.255.32.103:8090");

    while (!exitNow) {

            sleep(1);
    }

    std::cout <<"Bye!"<<std::endl;

    return 0;
}

