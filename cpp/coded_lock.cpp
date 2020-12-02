#include <stdlib.h>

#include <iomanip>
#include <iostream>

using namespace std;

class CodedLock
{
public:
    CodedLock(int m, int n, int codeBase);
    virtual ~CodedLock();

private:
    int m_codeBase;
    int m_codeNum;
    int m_keyNum;
    int m_codesPerKey;
    int **m_key;

    friend ostream &operator<<(ostream &os, const CodedLock &obj);
};

int main(int argc, char *argv[])
{
    int m = 0, n = 0;
    if (argc == 3) {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
    }
    if (m <= 0 || n <= 0 || m < n) {
        cerr << "The argument must be two integers and "
                "the first one is not less than the second one."
             << endl;
        return -1;
    }
    cout << CodedLock(m, n, 0);
    return 0;
}

CodedLock::CodedLock(int m, int n, int codeBase)
{
    m_keyNum = m;
    m_codeBase = codeBase;
    m_key = new int *[m_keyNum];
    if (n == 1) {
        m_codeNum = 1;
        m_codesPerKey = 1;
        for (int i = 0; i < m_keyNum; i++) {
            m_key[i] = new int[m_codesPerKey];
            m_key[i][0] = m_codeBase;
        }
    } else if (n == m) {
        m_codeNum = m;
        m_codesPerKey = 1;
        for (int i = 0; i < m_keyNum; i++) {
            m_key[i] = new int[m_codesPerKey];
            m_key[i][0] = m_codeBase + i;
        }
    } else {
        CodedLock code1(m - 1, n - 1, m_codeBase);
        CodedLock code2(m - 1, n, m_codeBase + code1.m_codeNum);
        m_codeNum = code1.m_codeNum + code2.m_codeNum;
        // code1.m_codesPerKey+code2.m_codesPerKey == code2.m_codeNum
        m_codesPerKey = code2.m_codeNum;
        int i, j;
        for (i = 0; i < m_keyNum - 1; i++) {
            m_key[i] = new int[m_codesPerKey];
            for (j = 0; j < code1.m_codesPerKey; j++) {
                m_key[i][j] = code1.m_key[i][j];
            }
            for (; j < m_codesPerKey; j++) {
                m_key[i][j] = code2.m_key[i][j - code1.m_codesPerKey];
            }
        }
        m_key[i] = new int[m_codesPerKey];
        for (j = 0; j < m_codesPerKey; j++) {
            m_key[i][j] = code2.m_codeBase + j;
        }
    }
}

CodedLock::~CodedLock()
{
    for (int i = 0; i < m_keyNum; i++)
        delete[] m_key[i];
    delete[] m_key;
}

ostream &operator<<(ostream &os, const CodedLock &obj)
{
    int i, j;
    os << "Codes: ";
    for (i = obj.m_codeBase; i < obj.m_codeBase + obj.m_codeNum; i++) {
        os << setw(5) << i;
    }
    os << endl;
    os << "Keys: " << endl;
    for (i = 0; i < obj.m_keyNum; i++) {
        for (j = 0; j < obj.m_codesPerKey; j++) {
            os << setw(5) << obj.m_key[i][j];
        }
        os << endl;
    }
    return os;
}
