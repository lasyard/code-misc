# Windows CMD

## `ape2flac.cmd`

用 Monkey's Audio 和 FLAC 进行音频转换的命令行脚本。

## `iso_run.cmd`

用 WinCDEmu 挂载 ISO 映像然后执行程序的命令行脚本。

## `vc_clear.cmd`

删除 VC 工程中的无用文件。

## `xp_clear.cmd`

删除 WinXP 中的无用文件。

## `zip_them.cmd`

用 7zip 压缩指定文件的 Windows 命令行脚本。

在需要进行压缩的目录下建立一个名为 FileList.txt 的文件，内容类似：

```
7Z<abc>
file1
file2
ZIP<def>
file3
file4
```

然后运行此脚本，将把 file1 和 file2 压缩到 abc.7z 中，file3 和 file4 压缩到 def.zip 中。

注意 7zip 必须安装在默认位置。
