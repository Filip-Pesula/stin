#define BOOST_TEST_MODULE ResourcesTest
#include <boost/test/included/unit_test.hpp>
#include <filesystem>
#include <Resources.h>
#include <boost/filesystem/path.hpp>
#include <Logger.h>
BOOST_AUTO_TEST_CASE(test_ReadResource_Nominal){
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::filesystem::path p = ".";
    p = p / "testRes" / "testReadable.txt";
    std::string resFile = "/testReadable.txt";
    STIN_Bot::Resources res({ {resFile, STIN_Bot::HtmlType::plain, p} });
    BOOST_CHECK_EQUAL(res.files.size(),1);
    std::u32string expected = U"test Line1: Text Line\ntest Line2: Test Line ó +ěščřžýá";
    BOOST_CHECK(res.files[resFile] == expected);
    BOOST_CHECK_EQUAL(res.exists(resFile),true);
    Logger::log(res.files[resFile]);
}

BOOST_AUTO_TEST_CASE(test_Exist_Nominal){
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::filesystem::path p = ".";
    p = p / "testRes" / "testReadable.txt";
    STIN_Bot::Resources res({ {std::string("/testReadable.txt"), STIN_Bot::HtmlType::plain, p} });
    BOOST_CHECK_EQUAL(res.exists("/testReadable.txt") , true);
}
BOOST_AUTO_TEST_CASE(test_Exist_Non){
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::filesystem::path p = ".";
    p = p / "testRes" / "testReadable.txt";
    STIN_Bot::Resources res({ {std::string("/testReadable.txt"), STIN_Bot::HtmlType::plain, p} });
    BOOST_CHECK_EQUAL(res.exists("/InvalidFile.txt") , false);
}