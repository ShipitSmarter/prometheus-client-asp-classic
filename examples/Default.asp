<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

Response.Write "Hello World<br><br>"

Dim currentDateTimeUtc
currentDateTimeUtc = getCurrentDateTimeUtc()
Response.Write "Current Time UTC: " & currentDateTimeUtc & "<br>"
Response.Write "Current Time Epoch: " & convertUtcDateTimeToEpoch(currentDateTimeUtc) & "<br>"

%>