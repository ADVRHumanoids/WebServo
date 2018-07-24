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

#include <HttpHandler.h>


HttpHandler::HttpHandler (std::shared_ptr<SharedData>& sharedData){
      
      this->sharedData = sharedData;
}
 
void HttpHandler::handleGet(std::shared_ptr<ResponseInterface>& response){      
         
      std::shared_ptr<StringBuffer> jsonresp = std::make_shared<StringBuffer>();
      jsonresp->Clear();
      Writer<StringBuffer> writer(*jsonresp);
  
      if(uri.compare("/home")==0){
        
        writer.StartObject();  
        writer.Key("Response");
        writer.String("OK");
        writer.EndObject();
      }
      
      response = std::make_shared<JsonResponse>(jsonresp);
}
  
void HttpHandler::handlePost(std::shared_ptr<RequestObject>& binary_request){
    
      std::unique_ptr<JsonRequest> getter = std::unique_ptr<JsonRequest>(new JsonRequest(binary_request));
       void* buff = binary_request->GetData();     
       std::cout<<"pos"<<std::string((char*)buff)<<std::endl;
      
      if(uri.compare("/cmd")==0) {
          std::string mess = getter->GetDocument().GetObject()["cmd"].GetString();
          std::string key = getter->GetDocument().GetObject()["Name"].GetString();
      }   
    
}
  