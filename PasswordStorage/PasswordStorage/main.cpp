#include <iostream>
#include <utility>
#include "password.h"
#include "HashTable.h"

std::string EncodeString(const std::string& string_to_encode)
{
    std::string encoded_string = string_to_encode;
    for (size_t i = 0; i < encoded_string.size(); i++)
    {
        encoded_string[i] += (i + 1);
    }
    return encoded_string;
}


std::string DecodeString(const std::string& string_to_decode)
{
    std::string decoded_string = string_to_decode;
    for (size_t i = 0; i < decoded_string.size(); i++)
    {
        decoded_string[i] -= (i + 1);
    }
    return decoded_string;
}


int GetHashFromString(const std::string& value)
{
    if (value.size() == 0)
    {
        return 1;
    }

    int hash = value[0];
    for (size_t i = 1; i < value.size(); i++)
    {
        hash = (hash << 1) ^ value[i];
    }
    return hash;
}


void PasswordStorageBeginning()
{
    std::cout << "Hello! It's Password Storage!" << "\n";
    std::cout << "------------------------------------" << "\n";
    std::cout << "What would you like to do?" "\n";
    std::cout << "------------------------------------" << "\n";
    std::cout << "If you want to:" << "\n"
        << " - print all password database, press 1" << "\n"
        << " - get individual nickname password, press 2" << "\n"
        << " - change password, press 3" << "\n";

}


bool CheckUserPassword(PasswordStorage storage)
{
    std::cout << "Input password" << std::endl;
    std::string user_input;
    std::getline(std::cin, user_input);

    if (GetHashFromString(user_input) == storage.GetPasswordHash())
    {
        if (GetHashFromString(user_input) != storage.GetPasswordHash())
        {
            std::cout << "It seems that somebody tried this program.\n";
            std::cout << "That patch doesn't work! Ha-ha-ha!" << std::endl;
        }
        PasswordStorageBeginning();
        return 1;
    }
    else
    {
        std::cout << "Incorrect password" << std::endl;
        exit(0);
    }
}

   
int main()
{
    const int pairs_number = 5;
    PasswordStorage pairs(pairs_number);

    PasswordStorageEntry pair_1;
    pair_1.nickname = "Christopher";
    pair_1.password = "TheDarkKnight";
    pairs.Add(pair_1);

    PasswordStorageEntry pair_2;
    pair_2.nickname = "David";
    pair_2.password = "GoneGirl";
    pairs.Add(pair_2);

    PasswordStorageEntry pair_3;
    pair_3.nickname = "Yuriy";
    pair_3.password = "Durak";
    pairs.Add(pair_3);

    PasswordStorageEntry pair_4;
    pair_4.nickname = "Quentin";
    pair_4.password = "IngloriousBastards";
    pairs.Add(pair_4);

    PasswordStorageEntry pair_5;
    pair_5.nickname = "Roman";
    pair_5.password = "InadequatePeople";
    pairs.Add(pair_5);


    CheckUserPassword(pairs);


    while (1)
    {

        std::string user_input;
        std::getline(std::cin, user_input);


        if (user_input == "1")
        {
            std::cout << pairs;
        }


        if (user_input == "2")
        {
            std::cout << "Please, input nickname: ";
            std::string user_nickname;
            std::getline(std::cin, user_nickname);

            if (pairs.Has(user_nickname))
            {
                pairs.GetNicknamePassword(user_nickname);
            }
            else
            {
                std::cout << "Such nickname wasn't found. Try again." << "\n";
            }
        }


        if (user_input == "3")
        {
            std::cout << "Please, input previous password: " << std::endl;
            std::string previous_password;
            std::getline(std::cin, previous_password);

            if (GetHashFromString(previous_password) == pairs.GetPasswordHash())
            {
                std::cout << "Input new password: " << std::endl;
                std::string new_password;
                std::getline(std::cin, new_password);
                pairs.ChangePassword(new_password);
            }
            else
            {
                std::cout << "Incorrect password" << std::endl;
            }
        }
    }

    return 0;
}