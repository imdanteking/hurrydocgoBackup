#include "searcher.h"
#include <algorithm>
namespace hurrydocgo{

  bool Searcher::Init(const std::string& input_path) {
    return m_index->Build(input_path);
  }

  bool Searcher::Search(const std::string& query, std::string* output) {
    // 1.word segment
    std::vector<std::string> tokens;
    m_index->CutWord(query, &tokens);
    // 2.trigger
    std::vector<Weight> all_token_result;
    for(const std::string& word : tokens) {
      // std::string lower_word;
      // std::transform(word.begin(), word.end(), lower_word.begin(), ::tolower);
      // boost::to_lower(word);
      auto* inverted_list = m_index->GetInvertedList(word);
      if(!inverted_list) {
        // the word is not found
        continue;
      }
      all_token_result.insert(all_token_result.end(), inverted_list->begin(), inverted_list->end());
    }
    // 3.descending sort 
    std::sort(all_token_result.begin(), all_token_result.end(), [](const Weight& w1, const Weight& w2){return w1.weight > w2.weight;});
    // 4.pack
    Json::Value results;
    for(const auto& weight: all_token_result) {
      const DocInfo* doc_info = m_index->GetDocInfo(weight.doc_id);
      Json::Value result;
      result["title"] = doc_info->title;
      result["url"] = doc_info->url;
      result["description"] = GenerateDescription(doc_info->content, weight.word); 
      results.append(result);
    }

    Json::FastWriter writer;
    *output = writer.write(results);
    return true;
  }

  std::string Searcher::GenerateDescription(const std::string& content, const std::string& word) {
    // word as center ,find 60(or other) bytes before and 160(or other) bytes after
    // if less than 60 bytes before, start from 0
    // less than 160 bytes after, to the end
    
    size_t first_pos = content.find(word);
    size_t begin = 0;
    if(begin == std::string::npos) {
      // word not found
      if(content.size() < 160) {
        return content;
      }
      std::string description =  content.substr(0, 160);
      description[description.size() - 1] = '.';
      description[description.size() - 2] = '.';
      description[description.size() - 3] = '.';
      return content.substr(0, 160);
    }

    begin = first_pos < 60 ? 0 : first_pos - 60;
    if(begin + 160 > content.size()) {
      return content.substr(begin);
    }
    else {
      std::string description =  content.substr(begin, 160);
      description[description.size() - 1] = '.';
      description[description.size() - 2] = '.';
      description[description.size() - 3] = '.';
      return description;
    }
  }

} // namespace end
