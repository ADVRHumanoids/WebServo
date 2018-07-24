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

#include <WebSocketCivetHandler.h>
#include <iostream>
#include <assert.h>
#include <cstdint>

bool WebSocketHandler::handleConnection(CivetServer *server, const struct mg_connection *conn) {
  
    std::cout<<"WS connected\n";
    return true;  
}

void WebSocketHandler::handleReadyState(CivetServer *server, struct mg_connection *conn) {
   
    std::cout<<"WS ready\n";
    const char *text = "{ \"msg\": \"Hello from XBotCore\"} ";
    mg_websocket_write(conn, WEBSOCKET_OPCODE_TEXT, text, strlen(text));    
    sharedData->increaseNumClient();    
} 

void WebSocketHandler::CloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg){
  
  //std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
  //Logger::error(Logger::Severity::FATAL)<<"AOOOO"<<Logger::endl;
  /*std::cout<<"height "<<msg->height<<" width "<<msg->width<<std::endl;
  std::cout<<"row step "<<msg->row_step<<std::endl;
  std::cout<<"point step "<<msg->point_step<<std::endl;*/
  
  int offset[4];
  
  int num_points = msg->height * msg->width;
  int pointIndex = 0;
  int i = 0;
  
  std::vector<uint8_t> dt = msg->data;
  
  float maxx =0, maxy=0, maxz=0;
  
  pointBuffer->add(dt);
  
  /*
  for (sensor_msgs::PointField var : msg->fields){
    
    std::cout<<"NAME "<<var.name<<std::endl;
    std::cout<<"OFFSET "<< var.offset<<std::endl;
    offset[i] = var.offset;
    
    switch (var.datatype){
      case sensor_msgs::PointField::INT32 :
         std::cout<<"INT32 "<<std::endl;
         break;
      case sensor_msgs::PointField::UINT32 :
         std::cout<<"UINT32 "<<std::endl;
         break;
      case sensor_msgs::PointField::FLOAT32 :
         std::cout<<"FLOAT32 "<<std::endl;
         break;
      case sensor_msgs::PointField::FLOAT64 :
         std::cout<<"FLOAT64 "<<std::endl;
         break;  
      case sensor_msgs::PointField::INT16 :
         std::cout<<"INT16 "<<std::endl;
         break;  
      case sensor_msgs::PointField::UINT16 :
         std::cout<<"UINT16 "<<std::endl;
         break;  
      case sensor_msgs::PointField::INT8 :
         std::cout<<"INT8 "<<std::endl;
         break;
      case sensor_msgs::PointField::UINT8 :
         std::cout<<"UINT8 "<<std::endl;
         break;
      
    } 
    std::cout<<"COUNT "<<var.count<<std::endl;
    
    i++;
  }
  
  
   for (;pointIndex<num_points; pointIndex = pointIndex + 32){
   
     //  std::cout<<" READ at"<<pointIndex+offset[0]<<std::endl;
      float x = 0;
      //std::cout<<" READ at"<<pointIndex+offset[1]<<std::endl;
      float y = 0;
      //std::cout<<" READ at"<<pointIndex+offset[2]<<std::endl;
      float z = 0;
      //std::cout<<" READ at"<<pointIndex+offset[3]<<std::endl;
      float rgb = 0;
          
      memcpy(&x, &dt[pointIndex+offset[0]], sizeof(float));
      memcpy(&y, &dt[pointIndex+offset[1]], sizeof(float));
      memcpy(&z, &dt[pointIndex+offset[2]], sizeof(float));
  
      //std::cout<<" x "<<x <<" y "<<y<<" z"<<z<<std::endl;
      
      uint8_t r,g,b;
      
      memcpy(&r, &dt[pointIndex+offset[3]], sizeof(uint8_t));
      memcpy(&g, &dt[pointIndex+offset[3]+1], sizeof(uint8_t));
      memcpy(&b, &dt[pointIndex+offset[3]+2], sizeof(uint8_t));
      
      //std::cout<<" r "<<(int)r <<" g "<<(int)g<<" b"<<(int)b<<std::endl;
      
      
      if (x> maxx) maxx = x;
      if (y> maxy) maxy = y;
      if (z> maxz) maxz = z;
      
   }
  
  std::cout<<" maxx "<<maxx <<" maxy "<<maxy<<" maxz"<<maxz<<std::endl;
  */
}
        
bool WebSocketHandler::handleData(CivetServer *server,
                                struct mg_connection *conn,
                                int bits,
                                char *data,
                                size_t data_len) {
  
    data[data_len] = 0;
    //std::shared_ptr<RequestObject> req = std::make_shared<RequestObject>();
    //req->SetData(data);
    
    //TODO move in abstraction interface
    //void * buff;
    //buff = req->GetData();     
    //StringStream stream((char*)buff);
    //std::cout<<"pos"<<std::string((char*)buff)<<std::endl;
    //Document d;
    //d.ParseStream(stream);
    
    ros::spinOnce();
    
    
    std::vector<uint8_t> tdata;
    //std::cout<<"SIZE BUFFER "<<pointBuffer->circular_buffer.size();
    pointBuffer->remove(tdata);
   
    
    int resp = mg_websocket_write(conn, WEBSOCKET_OPCODE_BINARY, (const char*)tdata.data(), tdata.size());
     //std::cout<<"WROTE BYTE "<<resp<<std::endl;
    
    return true;
}  

void WebSocketHandler::handleClose(CivetServer *server, const struct mg_connection *conn) {
       std::cout<<"WS closed\n";
       sharedData->decreaseNumClient();
}  