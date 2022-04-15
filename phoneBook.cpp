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

void phoneBook::removeContact(ContactField key) {
    size_t hashedKey = std::hash<std::string>{}(key.value);
    switch (key.field) {
        case ContactField::PHONE:
            phoneNumbersBook->remove(hashedKey);
            break;
        case ContactField::EMAIL:
            emailsBook->remove(hashedKey);
            break;
        case ContactField::NAME:
            namesBook->remove(hashedKey);
            break;
    }
}

Contact phoneBook::getContact(ContactField key) {
    Contact contact;
    size_t hashedKey = std::hash<std::string>{}(key.value);
    switch (key.field) {
        case ContactField::PHONE:
            contact = phoneNumbersBook->get(hashedKey);
            break;
        case ContactField::EMAIL:
            contact = emailsBook->get(hashedKey);
            break;
        case ContactField::NAME:
            contact = namesBook->get(hashedKey);
            break;
    }
    return contact;
}

void phoneBook::updateContact(ContactField key, ContactField updateField) {
    Contact contact = getContact(key);
    removeContact(key);

    switch (updateField.field) {
        case ContactField::PHONE:
            contact.phoneNumber = updateField.value;
            break;
        case ContactField::EMAIL:
            contact.email = updateField.value;
            break;
        case ContactField::NAME:
            contact.name = updateField.value;
            break;
    }

    addContact(contact);
}



