#pragma once
#include <string>
#include <memory>
#include <Request.h>
namespace STIN_Bot{
    class Bot
	{
		std::vector<std::unique_ptr<Request>> requests;
	public:
		Bot(std::vector<std::unique_ptr<Request>> requests);
		std::u32string processMessage(const std::u32string &);
	protected:
		
	};
}