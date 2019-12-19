#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <fstream>
#include "piFile.cpp"

unsigned int TIME_UNIT = 100;

std::string alphabet[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
                            "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
                            "--.."};

std::string numbers[10] = {".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

int BUFFER = 3 * TIME_UNIT;
int SPACE = 7 * TIME_UNIT;


std::string toLower(std::string str);

void str2char_arr(char *dst_char, std::string *str) {
    //int n = str->length();
    strcpy(dst_char, str->c_str());
}

std::string char2morse(char c) {

    if (48 <= +c && +c <= 57) {
        std::cout << c << "->" << +c << "->" << alphabet[+c - 48] << std::endl;
        return numbers[+c - 48] + " ";
    } else if (97 <= +c && +c <= 122) {
        std::cout << c << "->" << +c << "->" << alphabet[+c - 97] << std::endl;
        return alphabet[+c - 97] + " ";
    } else { return "\t"; }
}

std::string str_arr2str(std::string arr[], int length) {
    std::string str;
    for (int i = 0; i < length; i++) {
        str += arr[i];
    }
    return str;
}

std::string str2morse(std::string str) {
    str = toLower(str);
    //std::cout << str << std::endl;
    int n = str.length();
    char charArray[n];
    std::string morse[n];
    str2char_arr(charArray, &str);

    for (int i = 0; i < n; i++) {
        morse[i] = char2morse(charArray[i]);
    }
    return str_arr2str(morse, n);
}

std::string toLower(std::string str) {
    std::for_each(str.begin(), str.end(), [](char &c) {
        c = ::tolower(c);
    });
    return str;
}

std::string f2str(std::string src) {
    std::ifstream t(src);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return str;
}

void str2f(const std::string &str, const std::string &dst) {
    std::ofstream outf(dst);
    outf << str;
    outf.close();
}

void f2mf(std::string src, const std::string &dst) {
    str2f(str2morse(f2str(std::move(src))), dst);
}

void transmitToPi(std::string mes) {
    char arr[mes.length()];
    str2char_arr(arr, &mes);
    //cout << "Morse => "<< arr <<endl;
    Pi pi;

    //cout<<"pi.transmit(TIME_UNIT, 1);";
    //pi.transmit(TIME_UNIT, 1);

    for (char c : arr) {
        switch (c) {
            case '.' :
                pi.transmit(TIME_UNIT, 1);
                break;
            case '-':
                pi.transmit(BUFFER, 1);
                break;
            case ' ':
                pi.transmit(TIME_UNIT * 3, 0);
                break;

            case '\t':
                pi.transmit(TIME_UNIT * 7, 0);
                break;
        }
    }

}

void testf2mf() {
    std::string src, dst;
    std::cout << "Enter source file for text: ";
    std::cin >> src;
    std::cout << "\nEnter destination file for morse text: ";
    std::cin >> dst;
    f2mf(src, dst);
    //transmitToPi(str2morse(f2str(dst)));

}

void message2morse_intrf() {
    std::string message;
    std::cout << "Enter message: ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, message);
    message = toLower(message);
    char arr[message.length()];
    str2char_arr(arr, &message);

    std::cout << message << ": " << std::endl << str2morse(message) << std::endl;
    //transmitToPi(str2morse(message));
}

int main() {
    while (true) {
        char o;
        std::cout << "\nConvert text or file? \n1. Text\n2. File\n>>";
        std::cin >> o;
        switch (o) {
            case '1': {
                message2morse_intrf();
                break;
            }
            case '2': {
                testf2mf();
                break;
            }
            default:
                break;
        }
        if (o == 'q') {
            break;
        }
    }
    return 0;
}
