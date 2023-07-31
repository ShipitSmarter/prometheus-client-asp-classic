<%
    Response.CodePage = 65001
    Response.Charset = "utf-8"
    Response.ContentType = "text/plain; version=0.0.4"
    Response.Write Metrics.Registry.CollectAndExportAsText()
%>