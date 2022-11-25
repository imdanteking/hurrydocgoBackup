#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <boost/algorithm/string.hpp>

namespace hurrydocgo
{

  struct DocInfo
  {
    int64_t doc_id;
    std::string title;
    std::string url;
    std::string content;
  };

  struct Weight
  {
    int64_t doc_id;
    int weight;
    std::string word;
  };

  // 构建索引进度条的长度
  const static size_t PROCESS_BAR_LENGTH = 102;

  // 待处理输入文件的路径
  const static std::string g_input_path = "../data/input";

  // 输出文件的路径
  const static std::string g_output_path = "../data/output/raw_input";

  // html后缀常量
  const static std::string HTML = ".html";

  // title起始标签
  const static std::string TITLE_BEGIN_LABEL = "<title>";

  // title结束标签
  const static std::string TITLE_END_LABEL = "</title>";

  // 倒排拉链
  typedef std::vector<Weight> InvertedList;



  const char *const DICT_PATH = "../third_party/cppjieba/dict/jieba.dict.utf8";
  const char *const HMM_PATH = "../third_party/cppjieba/dict/hmm_model.utf8";
  const char *const USER_DICT_PATH = "../third_party/cppjieba/dict/user.dict.utf8";
  const char *const IDF_PATH = "../third_party/cppjieba/dict/idf.utf8";
  const char *const STOP_WORD_PATH = "../third_party/cppjieba/dict/stop_words.utf8";

  class Util
  {
  public:
    static bool ReadFile(const std::string &input_path, std::string *output)
    {
      // 以输入文件流的方式打开文件
      std::ifstream file(input_path.c_str());
      // 判断文件是否打开成功并且与当前流对象相关联
      if (!file.is_open())
      {
        std::cout << "Open file " << input_path << " failing" << std::endl;
        return false;
      }
      // 按行读取一个文件并以\n作为行分隔符
      std::string line;
      while (std::getline(file, line))
      {
        *output += (line + '\n');
      }
      // 关闭文件流
      file.close();
      return true;
    }

    static void Split(const std::string& input, const std::string& delimiter, std::vector<std::string>* output) {
      boost::split(*output, input, boost::is_any_of(delimiter), boost::token_compress_off);
    }

    static void ProcessBar(int64_t line_amount, int64_t doc_id) {
      char pb[PROCESS_BAR_LENGTH] = {0};
      char state[4] = {'-', '\\', '|', '/'};
      pb[0] = '[';
      pb[PROCESS_BAR_LENGTH - 1] = ']';
      int64_t mark_amount = (doc_id + 2) * 100 / line_amount;
      for(int i = 1; i <= mark_amount; i++) {
        pb[i] = '#';
      }
      for(int i = 0; i < PROCESS_BAR_LENGTH; i++) {
        if(pb[i] != 0) {
          std::cout << pb[i];
        }
        else {
          std::cout << " ";
        }
      }
      std::cout << " [%" << mark_amount << "] [" << state[mark_amount % 4] << "]";
      if(mark_amount == 100) {
        sleep(1);
      }
      std::fflush(stdout);
      std::cout << '\r';
  }
  };
} // namespace end
