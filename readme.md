# x64dbg

因为 od 没有 64位的版本，所以便有个 x64dbg。x64dbg 也是支持 32位的。所以会看到一个叫 x96dbg 的程序。

## [sandboxie](https://sandboxie-plus.com/)

- [Sandboxie GitHub](https://github.com/sandboxie-plus/Sandboxie)

### NTFS 8.3 命名没打开

1. 打开注册表( regedit )
2. 找到 HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem
3. 修改 NtfsDisable8dot3NameCreation 的值为 0

## [Process Explorer](https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer)

有些程序反调试，调试器启动就会关闭，可以先用 Process Explorer 查看。

## [Ghidra](https://github.com/NationalSecurityAgency/ghidra)

IDA 是商业软件，Ghidra 是 NASA 开源的静态分析工具。
