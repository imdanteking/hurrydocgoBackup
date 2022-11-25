#pragma once
#include "../common/util.hpp"
#include "../third_party/cppjieba/include/cppjieba/Jieba.hpp"

namespace hurrydocgo
{
    class Index
    {

    public:
        Index();

        // 1. Forward searcher func, return pointer to use NULL to indicate invalid situation
        const DocInfo *GetDocInfo(int64_t doc_id);

        // 2. Inverted searcher func
        const InvertedList *GetInvertedList(const std::string &key);

        // 3. Build the Index
        bool Build(const std::string &input_path);

        // 4.WordCut Function
        void CutWord(const std::string &input, std::vector<std::string> *output);

    private:
        DocInfo *BuildForward(const std::string &line);

        void BuildInverted(const DocInfo &doc_info);

    private:
        std::vector<DocInfo> m_forward_index;

        std::unordered_map<std::string, InvertedList> m_inverted_index;

        cppjieba::Jieba m_jieba;


    };
} // namespace end