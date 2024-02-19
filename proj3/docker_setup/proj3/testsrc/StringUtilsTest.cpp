#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, Slice){ //done
        std::string base = "Hello";
        std::string empty = "";

        EXPECT_EQ(StringUtils::Slice(base,0,5), "Hello");

        EXPECT_EQ(StringUtils::Slice(base,0,3),"Hel");

        EXPECT_EQ(StringUtils::Slice(base,1,4),"ell");

        EXPECT_EQ(StringUtils::Slice(empty,0,5), empty);
    
}

TEST(StringUtilsTest, Capitalize){ //done
    std::string base = "hello";
    std::string empty = "";

    EXPECT_EQ(StringUtils::Capitalize(base),"Hello");

    EXPECT_EQ(StringUtils::Capitalize("HELLO"),"HELLO");

    EXPECT_EQ(StringUtils::Capitalize(empty),empty);
}

TEST(StringUtilsTest, Upper){ //done
    std::string base = "hello";
    std::string empty = "";
    EXPECT_EQ(StringUtils::Upper(base),"HELLO");
    EXPECT_EQ(StringUtils::Upper(empty),empty);
}

TEST(StringUtilsTest, Lower){ //done
    std::string base = "HELLO";
    std::string empty = "";
    EXPECT_EQ(StringUtils::Lower(base),"hello");
    EXPECT_EQ(StringUtils::Lower(empty),empty);
}

TEST(StringUtilsTest, LStrip){ //done
    std::string base = "   hello ";
    std::string empty = "";
    EXPECT_EQ(StringUtils::LStrip(base),"hello ");
    EXPECT_EQ(StringUtils::LStrip(empty),empty);
    
}

TEST(StringUtilsTest, RStrip){ //done
    std::string base = "hello   ";
    std::string empty = "";
    EXPECT_EQ(StringUtils::RStrip(base),"hello");
    EXPECT_EQ(StringUtils::RStrip(empty),empty);
}

TEST(StringUtilsTest, Strip){ //done
    std::string base = " hello   ";
    std::string empty = "";

    EXPECT_EQ(StringUtils::Strip(base),"hello");
    EXPECT_EQ(StringUtils::Strip(empty),empty);
}

TEST(StringUtilsTest, Center){ //done
    std::string base = "hello";
    std::string empty = "";


    EXPECT_EQ(StringUtils::Center(base, 11, '0'),"000hello000");
    EXPECT_EQ(StringUtils::Center(base, 8, ' '),"  hello ");
    EXPECT_EQ(StringUtils::Center(base, 8, ' '),"  hello ");  
    EXPECT_EQ(StringUtils::Center(empty, 8, ' '),"        ");  
     
}

TEST(StringUtilsTest, LJust){ //done
    std::string base = "hello";
    std::string empty = "";


     EXPECT_EQ(StringUtils::LJust(base, 10, ' '),"hello     ");
     EXPECT_EQ(StringUtils::LJust(base, 5, '_'),"hello");
     EXPECT_EQ(StringUtils::LJust(base, 2, ' '),"hello");
     EXPECT_EQ(StringUtils::LJust(empty, 8, ' '),"        ");  

}

TEST(StringUtilsTest, RJust){ //done
    std::string base = "hello";
    std::string empty = "";

     EXPECT_EQ(StringUtils::RJust(base, 9, '_'),"____hello");
     EXPECT_EQ(StringUtils::RJust(base, 5, '_'),"hello");
     EXPECT_EQ(StringUtils::RJust(base, 2, ' '),"hello");
     EXPECT_EQ(StringUtils::RJust(empty, 8, ' '),"        ");  
    
}

TEST(StringUtilsTest, Replace){ //done
    std::string base = "hello";
    std::string empty = "";

     EXPECT_EQ(StringUtils::Replace(base, "l", "k"),"hekko");
     EXPECT_EQ(StringUtils::Replace(base, "hello", "greetings!"),"greetings!");
     EXPECT_EQ(StringUtils::Replace(empty, "l", "k"),empty);

}

TEST(StringUtilsTest, Split){ //done!!
    std::string base = "hello, this is, a test, case";


    std::vector< std::string > expected = {"hello", " this is", " a test", " case"};

    EXPECT_EQ(StringUtils::Split(base, ","),expected);


    
}

TEST(StringUtilsTest, Join){ //done
    std::vector< std::string > base = {"hello", "this is", "an awesome", "test case"};
    std::vector< std::string > empty = {};
    EXPECT_EQ(StringUtils::Join(" ",base),"hello this is an awesome test case");
    
}

TEST(StringUtilsTest, ExpandTabs){ //done
    std::string base = "h\te\tl\tl\to";
    std::string base2 = "hello";
    std::string empty = "";


    EXPECT_EQ(StringUtils::ExpandTabs(base,5),"h    e    l    l    o");
    EXPECT_EQ(StringUtils::ExpandTabs(base2,5),"hello");
    EXPECT_EQ(StringUtils::ExpandTabs(empty,5),empty);

}

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