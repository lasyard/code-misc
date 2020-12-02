Attribute VB_Name = "code"

Option Explicit

Private sc As Object

Private Function GetWebData( _
    ByVal url As String, _
    Optional ByVal method As String = "GET" _
    ) As String
    On Error Resume Next
    Dim http As Object
    Set http = CreateObject("Microsoft.XMLHTTP")
    http.Open method, url, False
    http.Send
    Select Case http.Status
        Case 0
            GetWebData = http.responseText
        Case 200
            GetWebData = http.responseText
        Case Else
            GetWebData = ""
    End Select
End Function

Private Function RawGetStockDataFromHexun( _
    ByVal iType As Integer, _
    ByVal market As Integer, _
    Optional ByVal page As Integer = 1, _
    Optional ByVal count As Integer = 100 _
    ) As String
    Dim url As String
    url = "http://quote.tool.hexun.com/hqzx/quote.aspx"
    url = url & "?type=" & CStr(iType)
    url = url & "&market=" & CStr(market)
    url = url & "&page=" & CStr(page)
    url = url & "&count=" & CStr(count)
    RawGetStockDataFromHexun = GetWebData(url)
End Function

Private Function RawGetBondDataFromHexun( _
    ByVal iType As Integer _
    ) As String
    Dim url As String
    url = "http://quote.tool.hexun.com/hqzx/zq_quote.aspx"
    url = url & "?type=" & CStr(iType)
    RawGetBondDataFromHexun = GetWebData(url)
End Function

Private Function InitScriptIfNot()
    If sc Is Nothing Then
        Set sc = CreateObject("ScriptControl")
        sc.Language = "JScript"
        ' Add stock related functions
        sc.AddCode "var stocks = [ ]"
        sc.AddCode "var stock_pages = 0"
        sc.AddCode "var StockListPage = { GetData: null }"
        sc.AddCode "function setStockFun(mk) {" & _
        "if (!stocks[mk]) stocks[mk] = { _c: 0 };" & _
        "StockListPage.GetData = function(a, b, c) {" & _
        "stock_pages = b;" & _
        "for (var i in a) {" & _
        "if (stocks[mk][a[i][0]]) continue;" & _
        "stocks[mk][a[i][0]] = a[i];" & _
        "stocks[mk]._c++;" & _
        "}" & _
        "}" & _
        "}"
        sc.AddCode "function getStockInfo(mk, code, i) {" & _
        "var o;" & _
        "if (o = stocks[mk][code]) return o[i];" & _
        "return """";" & _
        "}"
        sc.AddCode "function getStockPages() { return stock_pages; }"
        sc.AddCode "function numStocks(mk) { return stocks[mk]._c; }"
        ' Add bond related functions
        sc.AddCode "var bonds = [ ]"
        sc.AddCode "var BondListPage = { GetData: null }"
        sc.AddCode "function setBondFun(t) {" & _
        "if (!bonds[t]) bonds[t] = { _c: 0 };" & _
        "BondListPage.GetData = function(a, b) {" & _
        "for (var i in a) {" & _
        "if (bonds[t][a[i][0]]) continue;" & _
        "bonds[t][a[i][0]] = a[i];" & _
        "bonds[t]._c++;" & _
        "}" & _
        "}" & _
        "}"
        sc.AddCode "function getBondInfo(t, code, i) {" & _
        "var o;" & _
        "if (o = bonds[t][code]) return o[i];" & _
        "return """";" & _
        "}"
        sc.AddCode "function numBonds(t) { return bonds[t]._c; }"
    End If
End Function

Private Function GetStockDataFromHexun( _
    ByVal market As Integer, _
    Optional ByVal count As Integer = 1000 _
    )
    InitScriptIfNot
    sc.Run "setStockFun", market
    Dim js As String
    Dim page As Integer
    If sc.Run("numStocks", market) = 0 Then
        page = 1
        Do
            js = RawGetStockDataFromHexun(2, market, page, count)
            sc.Eval js
            page = page + 1
        Loop While page <= sc.Run("getStockPages")
    End If
End Function

Private Function GetBondDataFromHexun( _
    ByVal iType As Integer _
    )
    InitScriptIfNot
    Dim js As String
    sc.Run "setBondFun", iType
    If sc.Run("numBonds", iType) = 0 Then
        js = RawGetBondDataFromHexun(iType)
        sc.Eval js
    End If
End Function

Public Function GetStockName(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockName = CStr(sc.Run("getStockInfo", market, code, 1))
End Function

Public Function GetStockNews(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockNews = CStr(sc.Run("getStockInfo", market, code, 2))
End Function

Public Function GetStockChange(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockChange = CStr(sc.Run("getStockInfo", market, code, 3))
End Function

Public Function GetStockClose(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockClose = CStr(sc.Run("getStockInfo", market, code, 4))
End Function

Public Function GetStockOpen(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockOpen = CStr(sc.Run("getStockInfo", market, code, 5))
End Function

Public Function GetStockHigh(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockHigh = CStr(sc.Run("getStockInfo", market, code, 6))
End Function

Public Function GetStockLow(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockLow = CStr(sc.Run("getStockInfo", market, code, 7))
End Function

Public Function GetStockVolume(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockVolume = CStr(sc.Run("getStockInfo", market, code, 8))
End Function

Public Function GetStockTurnover(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockTurnover = CStr(sc.Run("getStockInfo", market, code, 9))
End Function

Public Function GetStockHandover(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockHandover = CStr(sc.Run("getStockInfo", market, code, 10))
End Function

Public Function GetStockAmplitude(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockAmplitude = CStr(sc.Run("getStockInfo", market, code, 11))
End Function

Public Function GetStockRatio(ByVal market As Integer, ByVal code As String) As String
    GetStockDataFromHexun market
    GetStockRatio = CStr(sc.Run("getStockInfo", market, code, 12))
End Function

Public Function GetBondName(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondName = CStr(sc.Run("getBondInfo", iType, code, 1))
End Function

Public Function GetBondNews(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondNews = CStr(sc.Run("getBondInfo", iType, code, 2))
End Function

Public Function GetBondChange(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondChange = CStr(sc.Run("getBondInfo", iType, code, 3))
End Function

Public Function GetBondAmplitude(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondAmplitude = CStr(sc.Run("getBondInfo", iType, code, 4))
End Function

Public Function GetBondVolume(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondVolume = CStr(sc.Run("getBondInfo", iType, code, 5))
End Function

Public Function GetBondTurnover(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondTurnover = CStr(sc.Run("getBondInfo", iType, code, 6))
End Function

Public Function GetBondOpen(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondOpen = CStr(sc.Run("getBondInfo", iType, code, 7))
End Function

Public Function GetBondHigh(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondHigh = CStr(sc.Run("getBondInfo", iType, code, 8))
End Function

Public Function GetBondLow(ByVal iType As Integer, ByVal code As String) As String
    GetBondDataFromHexun iType
    GetBondLow = CStr(sc.Run("getBondInfo", iType, code, 9))
End Function

Sub Test()
    MsgBox GetStockName(1, "600519")
    MsgBox GetStockNews(1, "600519")
    MsgBox GetBondName(2, "120203")
End Sub
