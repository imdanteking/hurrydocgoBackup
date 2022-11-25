#include "index.h"
#include <algorithm>
namespace hurrydocgo{


  Index::Index()
    : m_jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH){}


  /*
  * @brief: get DocInfo by doc_id
  */
  const DocInfo* Index::GetDocInfo(int64_t doc_id) {

    if(doc_id < 0 || doc_id > m_forward_index.size()) {
      return nullptr;
    }
    return &m_forward_index[doc_id];

  }

  const InvertedList* Index::GetInvertedList(const std::string& key) {

    std::unordered_map<std::string, InvertedList>::iterator it = m_inverted_index.find(key);
    if(it == m_inverted_index.end()) {
      return nullptr;
    }
    return &it->second;

  }

  bool Index::Build(const std::string& input_path) {

    // 1. read raw_input file, which is a line txt that means each line stands for a html file 
    std::cout << "Start Build Index..." << std::endl; 

    std::ifstream file(input_path.c_str());
    if(!file.is_open()) {
      std::cout << "Read raw_input Failing..." << std::endl;
      return false;
    }

    // get number of lines in line 
    std::ifstream tmpfile(input_path.c_str());
    int64_t line_amount = std::count(std::istreambuf_iterator<char>(tmpfile), std::istreambuf_iterator<char>(), '\n');
    tmpfile.close();
    // build index from each page
    std::string line;
    while(std::getline(file, line)) {
      // 2. convert each line to  DocInfo , construct ForwardIndex
      DocInfo* doc_info = BuildForward(line);
      if(!doc_info) {
        std::cout << "Construct Failing..." << std::endl;
        continue;
      }
      // 3. using ForwardIndex to Build Inverted Index
      BuildInverted(*doc_info);
      // print process bar
      Util::ProcessBar(line_amount, (*doc_info).doc_id);
    }
    

    std::cout << "Finish Build Index..." << std::endl;
    file.close();
    return true;
  }


  // use '\3' to cut title, url, content and convert to DocInfo
  DocInfo* Index::BuildForward(const std::string& line) {
    std::vector<std::string> tokens;
    // 1.Split raw_input with "\3"
    Util::Split(line, "\3", &tokens);
    if(tokens.size() != 3) {
      // Split failed if string is not consisted of 3 strings
      return nullptr;
    }
    // 2.put token into DocInfo 
    DocInfo doc_info;
    doc_info.doc_id = m_forward_index.size();
    doc_info.title = tokens[0];
    doc_info.url = tokens[1];
    doc_info.content = tokens[2];
    m_forward_index.push_back(std::move(doc_info));
    return &m_forward_index.back();
  }

  void Index::BuildInverted(const DocInfo& doc_info) {
    struct WordCut{
      int title_cnt;
      int content_cnt;

      WordCut()
        :title_cnt(0)
        ,content_cnt(0){}
    };
    std::unordered_map<std::string, WordCut> word_cut_map;
    //1.title segment
    std::vector<std::string> title_token;
    CutWord(doc_info.title, &title_token);
    //2.traversal, count frequency of title words
    for(std::string word: title_token) {
      // boost::to_lower(word); // convert all character to lower
      // std::string lower_word;
      // std::transform(word.begin(), word.end(), lower_word.begin(), ::tolower);
      ++word_cut_map[word].title_cnt;
    }
    //3.content segment
    std::vector<std::string> content_token;
    CutWord(doc_info.content, &content_token);
    //4.traversal, count frequency of content words
    for(std::string word: content_token) {
      // std::string lower_word;
      // std::transform(word.begin(), word.end(), lower_word.begin(), ::tolower);
      // boost::to_lower(word);
      ++ word_cut_map[word].content_cnt;
    }

    //5.deal with weight
    for(const auto& word_pair: word_cut_map) {
      Weight weight;
      weight.doc_id = doc_info.doc_id;
      // weight = title_cnt * 10 + content_cnt * 1
      weight.weight = 10 * word_pair.second.title_cnt + word_pair.second.content_cnt;
      weight.word = word_pair.first;
      //insert word into inverted_index
      InvertedList& invert_list = m_inverted_index[word_pair.first];
      invert_list.push_back(weight);
    }

  }
  
  void Index::CutWord(const std::string& input, std::vector<std::string>* output) {
    m_jieba.CutForSearch(input, *output);
  }
 

} // namespace end