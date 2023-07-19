<%
    Set Application("com_test") = Server.CreateObject("Example.Server")
    Response.Write "PI: " & Application("com_test").ComputePi
    Set Application("com_test") = Nothing
%>