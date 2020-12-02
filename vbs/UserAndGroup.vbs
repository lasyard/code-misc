strComputer = "localhost"

Set wbemServices = Getobject("winmgmts:\\" & strComputer & "\root\cimv2")

Set wbemObjectSet = wbemServices.InstancesOf("Win32_ComputerSystem")
Dim computerName
For Each wbemObject In wbemObjectSet
    computerName = wbemObject.Name
    Exit For
Next

WScript.Echo "Computer Name: " & computerName

Sub ShowAccount(className)
    Set wbemObjectSet = wbemServices.InstancesOf(className)
    For Each wbemObject In wbemObjectSet
        WScript.Echo wbemObject.Domain & "\" & wbemObject.Name
    Next
End Sub

WScript.Echo vbCrLf & "System Accounts:"
Call ShowAccount("Win32_SystemAccount")

WScript.Echo vbCrLf & "User Accounts:"
Call ShowAccount("Win32_UserAccount")

WScript.Echo vbCrLf & "Groups:"
Call ShowAccount("Win32_Group")

WScript.Echo vbCrLf & "Group User Relationship: "

Set wbemObjectSet = wbemServices.InstancesOf("Win32_GroupUser")
For Each wbemObject In wbemObjectSet
    WScript.Echo wbemObject.GroupComponent
    WScript.Echo vbTab & wbemObject.PartComponent
Next
