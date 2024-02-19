#include "StringUtils.h"
#include <string>
#include <cctype>
#include <vector>
namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{ //done

    //Edge Cases
    if (start < 0 || end < 0 || start > end || start >= str.size() || end > str.size()) {
        return "";
    }
    std::string result = str.substr(start, end-start);
    return result;
}

std::string Capitalize(const std::string &str) noexcept{ //done

    if (str.empty()) {
        return "";
    }

    std::string result = str;
    result[0] = std::toupper(result[0]);
    return result;
}

std::string Upper(const std::string &str) noexcept{ //done

    if (str.empty()) {
        return "";
    }

    std::string result = str;
    for (ssize_t i=0;i<result.size();i++) {
        result[i] = std::toupper(result[i]);
    }
    return result;
}

std::string Lower(const std::string &str) noexcept{ //done
    if (str.empty()) {
        return "";
    }

    std::string result = str;
    for (ssize_t i=0;i<result.size();i++) {
        result[i] = std::tolower(result[i]);
    }
    return result;
}

std::string LStrip(const std::string &str) noexcept{ //done
    if (str.empty()) {
        return "";
    }

    size_t i = 0;
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    
    return str.substr(i);
}

std::string RStrip(const std::string &str) noexcept{ //done
    if (str.empty()) {
        return "";
    }

    size_t i = str.size() - 1;
    while (i > 0 && std::isspace(str[i])) {
        i--;
    }

    return str.substr(0,i+1);
}

std::string Strip(const std::string &str) noexcept{ //done
    if (str.empty()) {
        return "";
    }
    std::string retval = str;
    size_t i = 0;
    while (i < str.size()) {
        if (std::isspace(retval[i])) {
            retval.erase(i, 1);
        }
        else {i++;}
    }
    return retval;
}

std::string Center(const std::string &str, int width, char fill) noexcept{ //done

    if (width < str.size()) {return str;}


    int fillers = width - str.size();
    int leftFill;
    if (fillers%2==1) {
        leftFill = (fillers/2)+1 ;
    } else { 
        leftFill = fillers/2;}

    int rightFill = fillers/2;

    return std::string(leftFill, fill) + str + std::string(rightFill,fill);
}

std::string LJust(const std::string &str, int width, char fill) noexcept{ //done
    if (width < str.size()) {
        return str;
    }
    int rightFill = width-str.size();
    return str + std::string(rightFill,fill);

}

std::string RJust(const std::string &str, int width, char fill) noexcept{ //done
    if (width < str.size()) {
        return str;
    }
    int leftFill = width-str.size();
    return std::string(leftFill,fill) + str;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{ //done
    if (str.empty()) {
        return "";
    }

    std::string retval = str;
    size_t i = str.find(old);
    int pos = 0;
    while ((pos = retval.find(old, pos)) != std::string::npos) {
        retval.replace(pos, old.length(), rep);
        pos += rep.length(); 
    }
    return retval;

}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{ //done
    if (str.empty()) {
        return {""};
    }
    if (splt.empty()) {
        return {str};
    }
    std::vector<std::string> list;

    size_t startpos = 0;
    size_t endpos;
    while ((endpos = str.find(splt, startpos)) != std::string::npos) {

        list.push_back(str.substr(startpos, endpos - startpos));
        

        startpos = endpos + splt.length();
    }
    list.push_back(str.substr(startpos));
    return list;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{ //done

    if (vect.empty()) {
        return "";
    }
    std::string retval;
    int i = 0;
    while(i<vect.size()) {
        retval = retval+vect[i]+str;
        i++;
    }
    retval.pop_back();
    return retval;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept { //done
    if (str.empty()) {
        return str;
    }

    std::string retval;
    size_t pos= 0;

    for (char ch : str) {
        if (ch == '\t') {

            size_t spacesToAdd = tabsize - (pos % tabsize);
            retval.append(spacesToAdd, ' ');
            pos += spacesToAdd;
        } else {

            retval.push_back(ch);

            if (ch == '\n' || ch == '\r') {
                pos = 0;
            } else {
                pos++;
            }
        }
    }

    return retval;
}


int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept { //DONE!!!
    std::string l = left;
    std::string r = right;
    if (ignorecase) {
    l = Lower(left);
    r = Lower(right);
    }

    std::vector<std::vector<int>> matrix(l.size() + 1, std::vector<int>(r.size() + 1, 0));

   for(int i = 0; i <= l.size(); ++i) {
        matrix[i][0] = i;
    }
    for (int j = 0; j <= r.size(); ++j) {
       matrix[0][j] = j;
    }


    for (int i = 1; i <= l.size(); ++i) {
        for (int j = 1; j <= r.size(); ++j) {
            int cost;
            if (l[i - 1] == r[j - 1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            //find min cost between substituion, deletion, and insertion (not in that order)
           matrix[i][j] = std::min({matrix[i - 1][j] + 1,matrix[i][j - 1] + 1,matrix[i - 1][j - 1] + cost });
        }
    }
    return matrix[l.size()][r.size()];
} 

    
};