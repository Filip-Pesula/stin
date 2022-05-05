#pragma once
#include <string>
#include <memory>
#include <Request.h>
namespace STIN_Bot{
    class Bot
	{
		std::vector<std::unique_ptr<Request>> requests;
		Res& res;
	public:
		Bot(std::vector<std::unique_ptr<Request>> requests,Res& res);
		std::u32string processMessage(const std::u32string &);
		Bot(const Bot&) = delete;
		Bot& operator=(const Bot&) = delete;
		
	};
}