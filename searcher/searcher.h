/*
 * @Description: 
 * @version: 
 * @Author: @imdanteking
 * @Date: 2022-11-25 12:17:36
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-11-26 01:23:56
 */
#pragma once
#include <iostream>                                           
#include <stdint.h>
#include <unistd.h>
#include <string>
#include <vector>                                  
#include <unordered_map>      
#include <algorithm>
#include <json/json.h>
#include "../index/index.h"
                                                     

namespace hurrydocgo{
  class Searcher {
    private:

      Index* m_index;

    public:

      Searcher() : m_index(new Index){}
      
      bool Init(const std::string& input_path);

      bool Search(const std::string& query, std::string* output);
 
    private:

      std::string GenerateDescription(const std::string& content, const std::string& word);

  };
} // namesapce end
