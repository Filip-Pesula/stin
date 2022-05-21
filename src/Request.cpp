#include "Request.h"
#include <algorithm>
#include <numeric>
#include <utils.h>
#include <resources/MoneyCash.h>
#include <string>
#include <Logger.h>

namespace STIN_Bot
{
    float getDifference(const std::vector<std::pair<boost::gregorian::date,Money<>>>& moneyh){
        std::vector<float> centdiff(2);
        std::fill(centdiff.begin(),centdiff.end(),0.f);
        {
            auto itr = centdiff.begin();
            for(auto it = moneyh.end()-1; it <= moneyh.begin(), itr < centdiff.end(); it--,itr++){
                while (it->second.getCents()==0 && it >= moneyh.begin())
                {
                    Logger::log("skipF",it->second.getCents());
                    it--;
                }
                Logger::log("prev",(it-1)->second.getCents());
                Logger::log("curent",it->second.getCents());
                *itr = float(it->second.getCents() -(it-1)->second.getCents()) / float(it->second.getCents());
            }
        }
        Logger::log("firstdif",centdiff[0]);
        Logger::log("firstdif",centdiff[1]);
        return(std::accumulate(centdiff.begin(),centdiff.end(),0.f));
    };


    KeySet::KeySet(std::vector<std::u32string> keySet):
        keySet(keySet)
    {
    }
    bool KeySet::contains(const std::u32string& key)
    {
        return std::any_of(keySet.begin(),keySet.end(),[&key](const std::u32string &s){
            return s == key;
        });
    }
    bool KeySet::contains(std::u32string_view key)
    {
        return std::any_of(keySet.begin(),keySet.end(),[&key](const std::u32string &s){
            return s == key;
        });
    }

    std::vector<KeySet> GetNameRequestEN::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"what",U"what's"}),
            KeySet({U"name"})
        });
    }
    std::u32string GetNameRequestEN::getResponse(Res& res) const{
        return U"My name is Chatbot";
    }

    std::vector<KeySet> GetNameRequestCZ::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"jak",U"jaké"}),
            KeySet({U"jmenuješ",U"jeméno",U"nazýváš"})
        });
    }
    std::u32string GetNameRequestCZ::getResponse(Res& res) const{
        return U"Jmenuji se ChatBot";
    }

    std::vector<KeySet> GetTimeRequestEN::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"what"}),
            KeySet({U"time"})
        });
    }

    std::u32string GetTimeRequestEN::getResponse(Res& res) const{
        std::string timenow = now_s();
        return U"It's " + std::u32string(timenow.begin(),timenow.end());
    }

    std::vector<KeySet> GetTimeRequestCZ::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"jaký",U"kolik"}),
            KeySet({U"čas",U"hodin"})
        });
    }
    std::u32string GetTimeRequestCZ::getResponse(Res& res) const{
        std::string timenow = now_s();
        return U"Je " + std::u32string(timenow.begin(),timenow.end());
    }

    std::vector<KeySet> GetEuroRequestCZ::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"jaká",U"kolik"}),
            KeySet({U"cena",U"stojí"}),
            KeySet({U"eura",U"euro"})
        });
    }
    std::u32string GetEuroRequestCZ::getResponse(Res& res) const{
        MoneyCash* moneyCash = dynamic_cast<MoneyCash*>(res[MoneyCash::name]);
        return U"Euro Stojí: " + moneyCash->latest().to_string<char32_t>(U",") + U"Kč";
    }

    std::vector<KeySet> GetEuroRequestEN::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"much",U"price"}),
            KeySet({U"euro"})
        });
    }
    std::u32string GetEuroRequestEN::getResponse(Res& res) const{
        MoneyCash* moneyCash = dynamic_cast<MoneyCash*>(res[MoneyCash::name]);
        return U"Euro costs: " + moneyCash->latest().to_string<char32_t>(U",") + U"Kč";
    }
    std::vector<KeySet> GetHelpRequestEN::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"help"})
        });
    }
    std::u32string GetHelpRequestEN::getResponse(Res& res) const{
        return U"Bot can aswer you in Czech or Engish\n\n\
Request can be:\n\
1. what is your name\n\
2. what time is it\n\
3. how much euro costs\n\
4. euro history\n\
5. recommend euro purchase\n\
\n!!Be aweare Bot is case sensitive :)";
    }
    std::vector<KeySet> GetHelpRequestCZ::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"pomoc"})
        });
    }
    std::u32string GetHelpRequestCZ::getResponse(Res& res) const{
        return U"Bot umí odpovídat v češtině a angličtině\n\n\
Příkazy:\n\
1. jak se jmenuješ\n\
2. kolik je hodin\n\
3. kolik stojí euro\n\
4. historie eura\n\
5. doporuč nákup eura\n\
\n!!Pozor bot je case sensitive :)";
    }

    std::vector<KeySet> GetEuroHystoryRequestCZ::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"historie"}),
            KeySet({U"eura"}),
        });
    }
    std::u32string GetEuroHystoryRequestCZ::getResponse(Res& res) const{
        MoneyCash* moneyCash = dynamic_cast<MoneyCash*>(res[MoneyCash::name]);
        std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh = moneyCash->history();
        std::reverse(moneyh.begin(),moneyh.end());
        std::basic_stringstream<char32_t> history;
        for (std::pair<boost::gregorian::date,Money<>> m : moneyh)
        {
            std::string d = boost::gregorian::to_iso_extended_string(m.first);
            history << std::u32string(d.begin(),d.end()) << U":" << m.second.to_string<char32_t>(U",") << U"Kč\n";
        }
        return U"Hytorie Eura: \n" + history.str();
    }

    std::vector<KeySet> GetEuroHystoryRequestEN::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"euro"}),
            KeySet({U"history"})
        });
    }
    std::u32string GetEuroHystoryRequestEN::getResponse(Res& res) const{
        MoneyCash* moneyCash = dynamic_cast<MoneyCash*>(res[MoneyCash::name]);
        std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh = moneyCash->history();
        std::reverse(moneyh.begin(),moneyh.end());
        std::basic_stringstream<char32_t> history;
        for (std::pair<boost::gregorian::date,Money<>> m : moneyh)
        {
            std::string d = boost::gregorian::to_iso_extended_string(m.first);
            history << std::u32string(d.begin(),d.end()) << U":" << m.second.to_string<char32_t>(U",") << U"Kč\n";
        }
        return U"Euro history: \n" + history.str();
    }


    std::vector<KeySet> GetEuroRecomandationRequestCZ::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"doporuč",U"doporučit"}),
            KeySet({U"nákup",U"koupit"}),
            KeySet({U"eura",U"euro"})
        });
    }
    std::u32string GetEuroRecomandationRequestCZ::getResponse(Res& res) const{
        MoneyCash* moneyCash = dynamic_cast<MoneyCash*>(res[MoneyCash::name]);
        std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh = moneyCash->history();
        if(moneyh.size()<3){
            return U"Nedostatek dat pro doporučení nákupu Eura.";
        }
        float dist = getDifference(moneyh);
        
        std::stringstream dist_ss;
        dist_ss << std::fixed << std::setprecision(4) << dist;
        std::string dist_s = dist_ss.str();

        if(dist < -0.1){
            return U"Nedopuručuji nakoupit: \neuro klesá o více jak 10%\nzměna:" + std::basic_string<char32_t>( dist_s.begin(),dist_s.end());
        }
        if(dist <= 0.0){
            return U"Dopuručuji nakoupit: \neuro neklesá o více jak 10%\nzměna:" + std::basic_string<char32_t>( dist_s.begin(),dist_s.end());
        }
        else{
            return U"Dopuručuji nakoupit: \neuro stoupá\nzměna:" + std::basic_string<char32_t>( dist_s.begin(),dist_s.end());
        }
    }

    std::vector<KeySet> GetEuroRecomandationRequestEN::getKeysets() const{
        return std::vector<KeySet>({
            KeySet({U"recommend"}),
            KeySet({U"euro"}),
            KeySet({U"purchese"})
        });
    }
    std::u32string GetEuroRecomandationRequestEN::getResponse(Res& res) const{
        MoneyCash* moneyCash = dynamic_cast<MoneyCash*>(res[MoneyCash::name]);
        std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh = moneyCash->history();
        if(moneyh.size()<3){
            return U"Not enough data to recommend.";
        }
        float dist = getDifference(moneyh);
        
        std::stringstream dist_ss;
        dist_ss << std::fixed << std::setprecision(4) << dist;
        std::string dist_s = dist_ss.str();

        if(dist < -0.1){
            return U"Not Recommending purchase: \neuro is descending over 10%\ndifference:" + std::basic_string<char32_t>( dist_s.begin(),dist_s.end());
        }
        if(dist <= 0.0){
            return U"Recommending purchase: \neuro is not descending over 10%\ndifference:" + std::basic_string<char32_t>( dist_s.begin(),dist_s.end());
        }
        else{
            return U"Recommending purchase: \neuro is ascending\ndifference:" + std::basic_string<char32_t>( dist_s.begin(),dist_s.end());
        }
    }



} // namespace STIN_Bot
