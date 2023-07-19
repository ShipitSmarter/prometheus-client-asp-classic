<%
    Set Application("com_test") = Server.CreateObject("Example.Server")
    Response.Write "PI: " & Application("com_test").ComputePi & "<br>"
    Dim test: Set test = Server.CreateObject("Example.Test")
    test.SomeProperty = 15
    Response.Write "TestObjParam: " & Application("com_test").TestObjectParam(test) & "<br>"
    Set Application("com_test") = Nothing
%>