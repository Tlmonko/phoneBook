#include "phoneBook.h"

int main() {
    phoneBook book;
    book.addContact({"89222222222", "me@ya.ru", "yandex"});
    book.addContact({"88005553535", "me@gmail.com", "google"});
    book.addContact({"88881122334", "me@outlook.com", "microsoft"});
    book.print();

    std::cout << book.getContact({ContactField::PHONE, "89222222222"}) << std::endl;
    std::cout << book.getContact({ContactField::EMAIL, "me@gmail.com"}) << std::endl;
    std::cout << book.getContact({ContactField::NAME, "microsoft"}) << std::endl;

    book.removeContact({ContactField::NAME, "yandex"});
    book.print();

    book.updateContact({ContactField::EMAIL, "me@gmail.com"}, {ContactField::PHONE, "89999999999"});
    std::cout << book.getContact({ContactField::EMAIL, "me@gmail.com"}) << std::endl;
}
