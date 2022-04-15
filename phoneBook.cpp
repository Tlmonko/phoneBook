//
// Created by Timonko on 15.04.2022.
//

#include "phoneBook.h"

phoneBook::phoneBook() {
    phoneNumbersBook = new RedBlackTree<size_t, Contact>;
    emailsBook = new RedBlackTree<size_t, Contact>;
    namesBook = new RedBlackTree<size_t, Contact>;
}

void phoneBook::addContact(Contact contact) {
    size_t hashedPhone = std::hash<std::string>{}(contact.phoneNumber);
    size_t hashedEmail = std::hash<std::string>{}(contact.email);
    size_t hashedName = std::hash<std::string>{}(contact.name);

    phoneNumbersBook->add(hashedPhone, contact);
    emailsBook->add(hashedPhone, contact);
    namesBook->add(hashedPhone, contact);
}


