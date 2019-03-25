#pragma once
#include <ostream>
#include "HashTable.h"


class PasswordStorage
{

    friend std::ostream& operator<<(std::ostream& out_stream, const PasswordStorage& storage);

public:

    PasswordStorage(const int size);
    void Add(const PasswordStorageEntry& new_pair);
    bool Has(const std::string& try_nickname) const;
    int GetPasswordHash();
    void GetNicknamePassword(const std::string& nickname);
    void ChangePassword(const std::string& new_password);
   

private:
    HashTable storage_;
    int password_hash = 103391;
};

std::ostream& operator<<(std::ostream& out_stream, const PasswordStorage& storage);
