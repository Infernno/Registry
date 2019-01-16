#ifndef AUTHMANAGER_HPP
#define AUTHMANAGER_HPP

#include <QString>

#include "Core/Data/database.hpp"
#include "Core/Data/Entities/identity.hpp"
#include "Core/Data/Entities/user.hpp"

#define ADMIN_GROUP 0
#define REGISTRATOR_GROUP 1
#define DOCTOR_GROUP 2
#define PATIENT_GROUP 3

class AuthManager
{
public:
    bool Authenticate(const QString & username, const QString & passwordHash);
    bool isAuthenticated() const;

    void changePassword(const QString & newPassword);

    QString getFullName() const;
    QString getUsername() const;
    int getUserGroup() const;

    const User * getCurrentProfile() const;

    static AuthManager * Instance();

private:
    AuthManager();

    User * mCurrentUser;
};

#endif // AUTHMANAGER_HPP
