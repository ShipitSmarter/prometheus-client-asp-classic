<% Option Explicit %>

<!-- #include virtual = "/prometheus-client/collector-registry.inc" -->
<!-- #include virtual = "/prometheus-client/counter.inc" -->
<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

Dim registry
Set registry = New CollectorRegistry

Function newCounter(name, help)
    Dim builder
    Set builder = New CounterBuilder
    builder().withName(name).withHelp(help)
    Set newCounter = builder.register(registry)
End Function

Function newLabeledCounter(name, help, labels)
    Dim builder
    Set builder = New CounterBuilder
    builder().withName(name).withHelp(help).withLabelNames(labels)
    Set newLabeledCounter = builder.register(registry)
End Function

Dim someLabeledCounter
Set someLabeledCounter = newLabeledCounter("some_name", "Description of some_name", Array("method", "post"))

Dim anotherLabeledCounter
Set anotherLabeledCounter = newLabeledCounter("another_name", "Description of another_name", Array("customer", "user", "location"))

Dim testLabeledCounterSample
Set testLabeledCounterSample = someLabeledCounter.getForLabels(Array("post", "200"))
testLabeledCounterSample.inc
testLabeledCounterSample.incByValue 3.254

' Create some extra samples for testing purposes

someLabeledCounter.getForLabels(Array("get", "200"))
someLabeledCounter.getForLabels(Array("post", "500"))
anotherLabeledCounter.getForLabels(Array("20", "267", "2367"))

Dim metric, metrics
metrics = registry.gather()
For Each metric In metrics
    Response.Write  "Family name: " & metric.Name & "<br>" & _
                    "Type: " & metric.MetricType & "<br>" & _
                    "Samples:<br>"
    Dim iterSample
    For Each iterSample in metric.Samples
        Response.Write  "&nbsp;&nbsp;Name: " & iterSample.Name & "<br>" & _
                        "&nbsp;&nbsp;Value: " & iterSample.Value & "<br>" & _
                        "&nbsp;&nbsp;Created: " & iterSample.Created & "<br>"
        Dim i, names, values
        names = iterSample.LabelNames
        values = iterSample.LabelValues
        For i = 0 To UBound(iterSample.LabelNames)
            Response.Write "&nbsp;&nbsp;" & names(i) & "=" & values(i) & "<br>"
        Next
        Response.Write "<br>"
    Next
Next

%>