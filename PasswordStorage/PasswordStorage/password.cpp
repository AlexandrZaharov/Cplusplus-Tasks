#include <istream>
#include <ostream>
#include <iostream>
#include "HashTable.h"
#include "password.h"


PasswordStorage::PasswordStorage(const int size) : storage_(size)
{}


void PasswordStorage::Add(const std::pair<std::string, std::string>& new_pair)
{
    storage_.Add(new_pair);
}


bool PasswordStorage::Has(const std::string& try_nickname) const
{
    return storage_.Has(try_nickname);
}


int PasswordStorage::GetPasswordHash()
{
    return password_hash;
}


void PasswordStorage::GetNicknamePassword(const std::string& nickname)
{
    if (storage_.Has(nickname) == false)
    {
        std::cout << "Such nickname wasn't found. Try again." << std::endl;
    }

    for (int i = 0; i < storage_.GetData()[storage_.GetHash(EncodeString(nickname))].size(); i++)
    {
        if (storage_.GetData()[storage_.GetHash(EncodeString(nickname))][i].first == EncodeString(nickname))
        {
            std::cout << "User: " << nickname << ", " << 
                "Password:" << DecodeString(storage_.GetData()[storage_.GetHash(EncodeString(nickname))][i].second) << std::endl;
        }
    }
}


void PasswordStorage::ChangePassword(const std::string& new_password)
{
    (*this).password_hash = GetHashFromString(new_password);
}


std::ostream& operator<<(std::ostream& out_stream, const PasswordStorage& storage)
{
    for (int i = 0; i < storage.storage_.GetData().size(); i++)
    {
        if (!storage.storage_.GetData()[i].empty())
        {
            for (int j = 0; j < storage.storage_.GetData()[i].size(); j++)
            {
                out_stream << "User: " << DecodeString(storage.storage_.GetData()[i][j].first) << "," 
                    << " Password: " << DecodeString(storage.storage_.GetData()[i][j].second) << "\n";
            }
        }
    }
    return out_stream;
}