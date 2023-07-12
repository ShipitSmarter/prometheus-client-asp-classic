<!-- #include virtual = "/prometheus-client/counter.inc" -->
<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

Response.Write "Hello World<br><br>"

Dim sample
Set sample = New CounterSample

sample.inc()
sample.incByValue(5.75)

Response.Write "Value: " & sample.Value & " Created: " & sample.Created

%>