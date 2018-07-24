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

#ifndef __WEBSOCKET_CIVET_HANDLER_WEBSERVER_H__
#define __WEBSOCKET_CIVET_HANDLER_WEBSERVER_H__

#include "CivetServer.h"
#include <memory>
#include <CircularBuffer.h>
#include <SharedData.h>
#include <Request.h>

#include <eigen_conversions/eigen_msg.h>

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointField.h>

class SharedData;

class WebSocketHandler : public CivetWebSocketHandler {

  public:
    std::shared_ptr<ros::NodeHandle> _nh;
    ros::Publisher _pubJoint;
    
    ros::Subscriber pointCloud;
    
    std::shared_ptr<Buffer<std::vector<uint8_t>>> pointBuffer;
    
    
    WebSocketHandler(std::shared_ptr<SharedData> sharedData){
      
     
      this->sharedData = sharedData;    
      

      //Type: geometry_msgs/PoseStamped
    int argc = 1;
    const char *arg = "dummy_arg";
    char* argg = const_cast<char*>(arg);
    char** argv = &argg;

     // ROS init
    ros::init(argc, argv, "webpc");    
    _nh = std::make_shared<ros::NodeHandle>();  
    
    pointCloud = _nh->subscribe<sensor_msgs::PointCloud2>("/kinect2/qhd/points", 1,  boost::bind(&WebSocketHandler::CloudCallback,this,_1));
    
    pointBuffer = std::make_shared<Buffer<std::vector<uint8_t>>>(1);
    
    }
    
    void CloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg);
           
    virtual bool handleConnection(CivetServer *server, const struct mg_connection *conn);

    virtual void handleReadyState(CivetServer *server, struct mg_connection *conn);

    virtual bool handleData(CivetServer *server,
                            struct mg_connection *conn,
                            int bits,
                            char *data,
                            size_t data_len);

    virtual void handleClose(CivetServer *server, const struct mg_connection *conn);

  private:
    std::shared_ptr<Buffer<WebRobotStateTX>> buffer;
    std::shared_ptr<SharedData> sharedData;

};

#endif //__WEBSOCKET_CIVET_HANDLER_WEBSERVER_H__
