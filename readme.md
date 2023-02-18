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

## [cutter](https://cutter.re/)

它汇总了很多逆向分析的工具，应该是打算把工具做成工具集。写了很多胶水程序。

静态分析工具，动态分析目前是测试阶段。

静态分析反编译器可以设配：

- Rizin 魔改 Ghidra 的 (RzGhidra)[https://github.com/rizinorg/rz-ghidra] 。


## [radare2](https://github.com/radareorg/radare2)

和 cutter 很像，也是汇总了很多逆向工具。比 cutter 做得早。

## [Rizin](https://github.com/rizinorg/rizin)

rizin 派生自 radare2 ，又有部分工具被 cutter 采用了。

开源的逆向工具一直都没有商用的 IDA 功能强。很多时候互相重用，整合上也不是很好，大概是投入没有商用的多。
