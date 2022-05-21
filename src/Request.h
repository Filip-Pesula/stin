#pragma once
#include <vector>
#include <string>
#include <resources/Res.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <Money.h>
namespace STIN_Bot{
    float getDifference(const std::vector<std::pair<boost::gregorian::date,Money<>>>& moneyh);
    

    class KeySet{
        std::vector<std::u32string> keySet;
    public:
        KeySet(std::vector<std::u32string> keySet);
        bool contains(const std::u32string&);
        bool contains(std::u32string_view);
    };
    class Request{
    public:
        virtual std::vector<KeySet> getKeysets() const = 0;
        virtual std::u32string getResponse(Res& res) const = 0;
    };

    class GetNameRequestEN : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };
    class GetNameRequestCZ : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };
    class GetTimeRequestEN : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };
    class GetTimeRequestCZ : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };

    class GetEuroRequestEN : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };
    class GetEuroRequestCZ : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };

    class GetHelpRequestEN : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };
    class GetHelpRequestCZ : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };

    class GetEuroHystoryRequestEN : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };
    class GetEuroHystoryRequestCZ : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };

    class GetEuroRecomandationRequestEN : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };
    class GetEuroRecomandationRequestCZ : public Request{
        public:
        std::vector<KeySet> getKeysets() const override;
        std::u32string getResponse(Res& res) const override;
    };

}