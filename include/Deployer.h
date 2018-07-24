/*
 * Copyright (C) 2017 IIT-ADVR
 * Author: Giuseppe Rigano
 * email:  giuseppe.rigano@iit.it
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


#ifndef _DEPLOYER_
#define _DEPLOYER_

#include <HttpCivetHandler.h>
#include <WebSocketCivetHandler.h>

#define DOCUMENT_ROOT "./root"
#define PORT "127.0.0.1:8081"
#define HOME_URI "/home"

class Deployer {

  public:

      Deployer(std::string address);
      virtual ~Deployer(){};

      
  private:

      std::shared_ptr<CivetServer> server;
      std::shared_ptr<HttpCivetHandler> http_civet_handler;
      std::shared_ptr<WebSocketHandler> ws_civet_handler;    
      std::shared_ptr<HttpHandler> http_handler;     
      
      std::shared_ptr<SharedData> sharedData;
      std::string address;
      std::string port; 
};

#endif 
