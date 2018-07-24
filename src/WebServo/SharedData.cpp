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

#include <SharedData.h>

SharedData::SharedData(){ 
    num_client.store(0);
    external_command = std::make_shared<Buffer<std::vector<double>>>(5);
}    

void SharedData::increaseNumClient(){      
  num_client++;
  std::cout<<"Num_Client "<< num_client.load()<<std::endl;
}

void SharedData::decreaseNumClient(){     
  num_client--;
  std::cout<<"Num_Client "<< num_client.load()<<std::endl;      
}

std::atomic<int>& SharedData::getNumClient(){
  return num_client;
}