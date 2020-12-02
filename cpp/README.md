# C++ Programming

## `txt2html.cpp`

**TXT 转 HTML**, 将 TXT 文件转换为 HTML 的 CLI 程序。

用来将 txt 文件转换为 html 文件，转换的方式由配置文件的内容决定。配置文件默认为 `txt2html.txt`.

一般情况下，配置文件中的行被直接写到目标文件中，除非该行以 @ 符号开头。这时又分两种情况：

1. 形如 `@ddd:s1...s2`
    ddd 为一个数字，它的含义是从源文件中读取 ddd 行，每行前面加上字符串 s1, 后面加上字符串 s2, 然后写入目标文件。如果 ddd = 0, 则不从源文件读取新内容，继续使用最后读入的一行。
2. 形如 `@$:s1...s2`
    含义基本同上，只是一直读到源文件结束为止。

配置文件内容举例：

```
<!DOCTYPE html>
<html>

<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
@1:<title>...</title>
</head>

<body>
@0:<h1>...</h1>
@$:<p>...</p>
</body>

</html>
```

## `coded_lock.cpp`

**密码锁问题**，递归方式实现求解密码锁问题的 CLI 程序。

> 一把密码锁需要若干个密码同时输入才能打开。现有 m 个人，每个人只知道其中部分密码。要求当且仅当其中 n 个人同时在场才能打开锁。求密码的设计方案。
