#include <gtest/gtest.h>
#include "StringUtils.h"


// Test for Slice function of StringUtils
TEST(StringUtilsTest, Slice){
        std::string base = "Hello";
        std::string empty = "";

        EXPECT_EQ(StringUtils::Slice(base,0,5), "Hello");

        EXPECT_EQ(StringUtils::Slice(base,0,3),"Hel");

        EXPECT_EQ(StringUtils::Slice(base,1,4),"ell");

        EXPECT_EQ(StringUtils::Slice(empty,0,5), empty);
    
}

// Test for Capitalize function of StringUtils
TEST(StringUtilsTest, Capitalize){ 
    std::string base = "hello";
    std::string empty = "";

    EXPECT_EQ(StringUtils::Capitalize(base),"Hello");

    EXPECT_EQ(StringUtils::Capitalize("HELLO"),"HELLO");

    EXPECT_EQ(StringUtils::Capitalize(empty),empty);
}

// Test for Upper function of StringUtils
TEST(StringUtilsTest, Upper){
    std::string base = "hello";
    std::string empty = "";
    EXPECT_EQ(StringUtils::Upper(base),"HELLO");
    EXPECT_EQ(StringUtils::Upper(empty),empty);
}

// Test for Lower function of StringUtils
TEST(StringUtilsTest, Lower){ 
    std::string base = "HELLO";
    std::string empty = "";
    EXPECT_EQ(StringUtils::Lower(base),"hello");
    EXPECT_EQ(StringUtils::Lower(empty),empty);
}

// Test for LStrip function of StringUtils
TEST(StringUtilsTest, LStrip){
    std::string base = "   hello ";
    std::string empty = "";
    EXPECT_EQ(StringUtils::LStrip(base),"hello ");
    EXPECT_EQ(StringUtils::LStrip(empty),empty);
    
}

// Test for RStrip function of StringUtils
TEST(StringUtilsTest, RStrip){ 
    std::string base = "hello   ";
    std::string empty = "";
    EXPECT_EQ(StringUtils::RStrip(base),"hello");
    EXPECT_EQ(StringUtils::RStrip(empty),empty);
}

// Test for Strip function of StringUtils
TEST(StringUtilsTest, Strip){
    std::string base = " hello   ";
    std::string empty = "";

    EXPECT_EQ(StringUtils::Strip(base),"hello");
    EXPECT_EQ(StringUtils::Strip(empty),empty);
}

// Test for Center function of StringUtils
TEST(StringUtilsTest, Center){ 
    std::string base = "hello";
    std::string empty = "";


    EXPECT_EQ(StringUtils::Center(base, 11, '0'),"000hello000");
    EXPECT_EQ(StringUtils::Center(base, 8, ' '),"  hello ");
    EXPECT_EQ(StringUtils::Center(base, 8, ' '),"  hello ");  
    EXPECT_EQ(StringUtils::Center(empty, 8, ' '),"        ");  
     
}

// Test for LJust function of StringUtils
TEST(StringUtilsTest, LJust){ 
    std::string base = "hello";
    std::string empty = "";


     EXPECT_EQ(StringUtils::LJust(base, 10, ' '),"hello     ");
     EXPECT_EQ(StringUtils::LJust(base, 5, '_'),"hello");
     EXPECT_EQ(StringUtils::LJust(base, 2, ' '),"hello");
     EXPECT_EQ(StringUtils::LJust(empty, 8, ' '),"        ");  

}

// Test for RJust function of StringUtils
TEST(StringUtilsTest, RJust){ 
    std::string base = "hello";
    std::string empty = "";

     EXPECT_EQ(StringUtils::RJust(base, 9, '_'),"____hello");
     EXPECT_EQ(StringUtils::RJust(base, 5, '_'),"hello");
     EXPECT_EQ(StringUtils::RJust(base, 2, ' '),"hello");
     EXPECT_EQ(StringUtils::RJust(empty, 8, ' '),"        ");  
    
}

// Test for Replace function of StringUtils
TEST(StringUtilsTest, Replace){ 
    std::string base = "hello";
    std::string empty = "";

     EXPECT_EQ(StringUtils::Replace(base, "l", "k"),"hekko");
     EXPECT_EQ(StringUtils::Replace(base, "hello", "greetings!"),"greetings!");
     EXPECT_EQ(StringUtils::Replace(empty, "l", "k"),empty);

}

// Test for Split function of StringUtils
TEST(StringUtilsTest, Split){ 
    std::string base = "hello, this is, a test, case";


    std::vector< std::string > expected = {"hello", " this is", " a test", " case"};

    EXPECT_EQ(StringUtils::Split(base, ","),expected);


    
}

// Test for Join function of StringUtils
TEST(StringUtilsTest, Join){ 
    std::vector< std::string > base = {"hello", "this is", "an awesome", "test case"};
    std::vector< std::string > empty = {};
    EXPECT_EQ(StringUtils::Join(" ",base),"hello this is an awesome test case");
    
}

// Test for ExpandTabs function of StringUtils
TEST(StringUtilsTest, ExpandTabs){ 
    std::string base = "h\te\tl\tl\to";
    std::string base2 = "hello";
    std::string empty = "";


    EXPECT_EQ(StringUtils::ExpandTabs(base,5),"h    e    l    l    o");
    EXPECT_EQ(StringUtils::ExpandTabs(base2,5),"hello");
    EXPECT_EQ(StringUtils::ExpandTabs(empty,5),empty);

}

// Test for EditDistance function of StringUtils
TEST(StringUtilsTest, EditDistance){
    std::string base = "hello";
    std::string base2 = "Greetings";
    std::string empty = "";
    std::string base3 = "Hello";


    EXPECT_EQ(StringUtils::EditDistance(base,base,true),0);
    EXPECT_EQ(StringUtils::EditDistance(base,base,false),0);

    EXPECT_EQ(StringUtils::EditDistance(base,base2,false),8);
    EXPECT_EQ(StringUtils::EditDistance(base,base2,true),8);

    EXPECT_EQ(StringUtils::EditDistance(base,base3,false),1);
    EXPECT_EQ(StringUtils::EditDistance(base,base3,true),0);

    
}