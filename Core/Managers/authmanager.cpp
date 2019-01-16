#include "authmanager.hpp"

AuthManager::AuthManager() : mCurrentUser(nullptr)
{

}

bool AuthManager::Authenticate(const QString &username, const QString &passwordHash)
{
    auto admin = Database::Instance()->adminTable()->find([&username, &passwordHash](const auto & item)
    {
        return item.Username == username && item.PasswordHash == passwordHash;
    });

    auto registrator = Database::Instance()->registratorTable()->find([&username, &passwordHash](const auto & item)
    {
        return item.Username == username && item.PasswordHash == passwordHash;
    });

    auto doctor = Database::Instance()->doctorTable()->find([&username, &passwordHash](const auto & item)
    {
        return item.Username == username && item.PasswordHash == passwordHash;
    });

    auto patient = Database::Instance()->patientTable()->find([&username, &passwordHash](const auto & item)
    {
        return item.Username == username && item.PasswordHash == passwordHash;
    });

    if(admin != nullptr)
    {
        mCurrentUser = admin;
        return true;
    }

    if(registrator != nullptr)
    {
        mCurrentUser = registrator;
        return true;
    }

    if(doctor != nullptr)
    {
        mCurrentUser = doctor;
        return true;
    }

    if(patient != nullptr)
    {
        mCurrentUser = patient;
        return true;
    }

    return false;
}

bool AuthManager::isAuthenticated() const
{
    if(mCurrentUser == nullptr)
    {
        return false;
    }

    return true;
}

void AuthManager::changePassword(const QString &newPassword)
{
    mCurrentUser->PasswordHash = newPassword;
}

QString AuthManager::getFullName() const
{
    if(isAuthenticated())
    {
        return mCurrentUser->getFullName();
    }

    return "None";
}

QString AuthManager::getUsername() const
{
    if(isAuthenticated())
        return mCurrentUser->Username;

    return "None";
}

int AuthManager::getUserGroup() const
{
    if(isAuthenticated())
        return mCurrentUser->GroupID;

    return -1;
}

const User *AuthManager::getCurrentProfile() const
{
    return mCurrentUser;
}

AuthManager * AuthManager::Instance()
{
    static AuthManager instance;
    return &instance;
}

