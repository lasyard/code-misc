#ifndef _USER_AND_GROUP_
#define _USER_AND_GROUP_

#include <comutil.h>
#include <wbemidl.h>

#include <map>
#include <string>
#include <vector>

typedef std::wstring MyString;

// Retrieve user and group using WMI
class UserAndGroup
{
public:
    const _bstr_t COMPUTER_SYSTEM_CLASS = L"Win32_ComputerSystem";
    const _bstr_t USER_ACCOUNT_CLASS = L"Win32_UserAccount";
    const _bstr_t SYSTEM_ACCOUNT_CLASS = L"Win32_SystemAccount";
    const _bstr_t GROUP_CLASS = L"Win32_Group";
    const _bstr_t GROUP_USER_CLASS = L"Win32_GroupUser";

    UserAndGroup();
    ~UserAndGroup();

    struct Account {
        Account(const _bstr_t &d, const _bstr_t &n)
        {
            domain = d;
            name = n;
        }

        MyString domain;
        MyString name;
    };

    const MyString &computerName() const
    {
        return m_computerName;
    }

    const std::vector<struct Account> &userAccounts() const
    {
        return m_userAccounts;
    }

    const std::vector<struct Account> &systemAccounts() const
    {
        return m_systemAccounts;
    }

    const std::vector<struct Account> &groups() const
    {
        return m_groups;
    }

    const std::map<struct Account, std::vector<struct Account>> &userGroups() const
    {
        return m_userGroups;
    }

    bool cacheUserGroupInfo()
    {
        if (m_userGroupInfoCached)
            return true;
        if (m_pWbemServices == NULL)
            return false;
        if (SUCCEEDED(cacheComputerName()) && SUCCEEDED(cacheUserAccount()) && SUCCEEDED(cacheSystemAccount()) &&
            SUCCEEDED(cacheGroup()) && SUCCEEDED(cacheUserGroup())) {
            m_userGroupInfoCached = true;
            return true;
        }
        return false;
    }

    bool hasUser(const MyString &domain, const MyString &name) const
    {
        for (auto i : m_userAccounts) {
            if (i.domain == domain && i.name == name)
                return true;
        }
        for (auto i : m_systemAccounts) {
            if (i.domain == domain && i.name == name)
                return true;
        }
        return false;
    }

    bool hasGroup(const MyString &domain, const MyString &name) const
    {
        for (auto i : m_groups) {
            if (i.domain == domain && i.name == name)
                return true;
        }
        return false;
    }

    bool isUserInGroup(const MyString &domain, const MyString &user, const MyString &group) const
    {
        for (auto i : m_userGroups) {
            if (i.first.domain == domain && i.first.name == user) {
                for (auto j : i.second) {
                    if (j.domain == domain && j.name == group)
                        return true;
                }
            }
        }
        return false;
    }

    bool hasLocalUser(const MyString &name) const
    {
        return hasUser(m_computerName, name);
    }

    bool hasLocalGroup(const MyString &name) const
    {
        return hasGroup(m_computerName, name);
    }

    bool isLocalUserInGroup(const MyString &user, const MyString &group) const
    {
        return isUserInGroup(m_computerName, user, group);
    }

protected:
    IWbemServices *m_pWbemServices;
    bool m_userGroupInfoCached;
    MyString m_computerName;
    std::vector<struct Account> m_userAccounts;
    std::vector<struct Account> m_systemAccounts;
    std::vector<struct Account> m_groups;
    std::map<struct Account, std::vector<struct Account>> m_userGroups;

    IWbemServices *connectServer();
    HRESULT enumInstance(const _bstr_t &className,
                         bool (*processClassObject)(IWbemClassObject *, void *context),
                         void *context);

    HRESULT cacheAccount(const _bstr_t &cls, std::vector<struct Account> &var);

    HRESULT cacheComputerName();

    HRESULT cacheUserAccount()
    {
        return cacheAccount(USER_ACCOUNT_CLASS, m_userAccounts);
    }

    HRESULT cacheSystemAccount()
    {
        return cacheAccount(SYSTEM_ACCOUNT_CLASS, m_systemAccounts);
    }

    HRESULT cacheGroup()
    {
        return cacheAccount(GROUP_CLASS, m_groups);
    }

    HRESULT cacheUserGroup();
};

#endif
