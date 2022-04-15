#include <iostream>
#include <functional>
#include "RedBlackTree.h"
#include "RedBlackTree.cpp"

#ifndef PHONEBOOK_PHONEBOOK_H
#define PHONEBOOK_PHONEBOOK_H

struct Contact {
    std::string phoneNumber;
    std::string email;
    std::string name;
};

class phoneBook {
private:
    RedBlackTree<size_t, Contact> *phoneNumbersBook;
    RedBlackTree<size_t, Contact> *emailsBook;
    RedBlackTree<size_t, Contact> *namesBook;
public:
    phoneBook();

    void addContact(Contact contact);

    void removeContact(Contact contact);

    void updateContact(Contact newContact);
};


#endif //PHONEBOOK_PHONEBOOK_H
