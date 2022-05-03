#define BOOST_TEST_MODULE DummyTest
#include <boost/test/included/unit_test.hpp>

#include <WebReader.h>
#include <Logger.h>
BOOST_AUTO_TEST_CASE(test_Log_string){
    std::string data = getEuro("01.05.2022");
    Logger::log(data);
    BOOST_WARN(data.size()>0); 
}


BOOST_AUTO_TEST_CASE(test_getEuro_Nominal){
    std::string data = 
R"(02.05.2022 #84
země|měna|množství|kód|kurz
Austrálie|dolar|1|AUD|16,548
Brazílie|real|1|BRL|4,702
Bulharsko|lev|1|BGN|12,613
Čína|žen-min-pi|1|CNY|3,548
Dánsko|koruna|1|DKK|3,316
EMU|euro|1|EUR|24,670
Filipíny|peso|100|PHP|44,671
Hongkong|dolar|1|HKD|2,988
Chorvatsko|kuna|1|HRK|3,263
Indie|rupie|100|INR|30,647
Indonesie|rupie|1000|IDR|1,617
Island|koruna|100|ISK|17,981
Izrael|nový šekel|1|ILS|6,993
Japonsko|jen|100|JPY|18,057
Jižní Afrika|rand|1|ZAR|1,474
Kanada|dolar|1|CAD|18,194
Korejská republika|won|100|KRW|1,850
Maďarsko|forint|100|HUF|6,517
Malajsie|ringgit|1|MYR|5,385
Mexiko|peso|1|MXN|1,148
MMF|ZPČ|1|XDR|31,514
Norsko|koruna|1|NOK|2,485
Nový Zéland|dolar|1|NZD|15,081
Polsko|zlotý|1|PLN|5,266
Rumunsko|leu|1|RON|4,987
Singapur|dolar|1|SGD|16,916
Švédsko|koruna|1|SEK|2,371
Švýcarsko|frank|1|CHF|24,060
Thajsko|baht|100|THB|68,136
Turecko|lira|1|TRY|1,574
USA|dolar|1|USD|23,443
Velká Británie|libra|1|GBP|29,439
)";
    std::string euro = extractEuro(data);
    Logger::log(data);
    BOOST_CHECK_EQUAL(euro,"24,670"); 
}
BOOST_AUTO_TEST_CASE(test_getEuro_Empty){
    std::string euro = extractEuro("");
    BOOST_CHECK_EQUAL(euro,""); 
}

BOOST_AUTO_TEST_CASE(test_getEuro_NotFound){
    std::string euro = extractEuro("Singapur|dolar|1|SGD|16,916\
Švédsko|koruna|1|SEK|2,371\
Švýcarsko|frank|1|CHF|24,060\
Thajsko|baht|100|THB|68,136\
Turecko|lira|1|TRY|1,574\
USA|dolar|1|USD|23,443\
Velká Británie|libra|1|GBP|29,439");
    BOOST_CHECK_EQUAL(euro,""); 
}

BOOST_AUTO_TEST_CASE(test_getEuro_EndOfFile){
    std::string euro = extractEuro("Bulharsko|lev|1|BGN|12,613\
Čína|žen-min-pi|1|CNY|3,548\
Dánsko|koruna|1|DKK|3,316\
EMU|euro|1|EUR|24,670");
    BOOST_CHECK_EQUAL(euro,"24,670"); 
}
