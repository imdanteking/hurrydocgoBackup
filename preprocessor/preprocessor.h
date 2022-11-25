/*
 * @Description: 
 * @version: 
 * @Author: @imdanteking
 * @Date: 2022-11-24 19:43:38
 * @LastEditTime: 2022-11-26 01:24:08
 */

#pragma once
// The model is to pretreat
// - read and analyse htmls from boost
// - get title. url and contents wuthout html labels
// - output is texts

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "../common/util.hpp"

//   core steps
// 1.get all the urls of html files
// 2.read contents of all html files following urls and analyse them
// 3.write contents into output files

namespace hurrydocgo
{
  /**
   * 
  */
  class PreProcessor
  {
  public:

    static bool EnumFile(const std::string &g_input_path, std::vector<std::string> *file_list); 
    static bool ParseTitle(const std::string &html, std::string *title);
    static bool ParseUrl(const std::string &file_path, std::string *url);
    static bool ParseContent(const std::string &html, std::string *content);
    static bool ParseFile(const std::string &file_path, DocInfo *doc_info);
    static void WriteOutput(const DocInfo &doc_info, std::ofstream &ofstream);

  };
} // namespace end
