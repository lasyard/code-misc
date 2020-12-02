class CmdCaller
{
public:
    CmdCaller();
    ~CmdCaller();

    HRESULT run(char *strCmd);
    const string &getStdout() const
    {
        return strStdout;
    }
    const string &getStderr() const
    {
        return strStderr;
    }
    DWORD getExitCode() const
    {
        return dwExitCode;
    }

protected:
    static const int bufLen;
    char *buf;
    string strStdout;
    string strStderr;
    DWORD dwExitCode;
};
