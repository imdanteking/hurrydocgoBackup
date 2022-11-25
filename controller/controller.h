/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-11-24 19:43:38
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-11-26 01:24:21
 * @FilePath: /hurrydocgo/controller/controller.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "../preprocessor/preprocessor.h"
#include "../searcher/searcher.h"
#include "../third_party/cpp-httplib/httplib.h"
#include <memory>

namespace hurrydocgo
{
    class Controller
    {
    public:
        Controller();
        ~Controller();
        void Init();
    private:
        void BuildPreProcessor(); 
        void BuildSearcher();
        void BuildQueryService();
    public:
        Searcher* m_searcher;
    };
} // namespace end